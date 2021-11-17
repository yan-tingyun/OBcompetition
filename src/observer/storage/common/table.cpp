/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/13.
//

#include <limits.h>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <unistd.h>
#include <fstream>

#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/default/disk_buffer_pool.h"
#include "storage/common/record_manager.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/common/index.h"
#include "storage/common/bplus_tree_index.h"
#include "storage/trx/trx.h"

#define is_leap_year(y) (((y) % 4  == 0 && (y) % 100 != 0) || (y) % 400 == 0)
using namespace std;

Table::Table() : 
    data_buffer_pool_(nullptr),
    file_id_(-1),
    record_handler_(nullptr) {
}

Table::~Table() {
  delete record_handler_;
  record_handler_ = nullptr;

  if (data_buffer_pool_ != nullptr && file_id_ >= 0) {
    data_buffer_pool_->close_file(file_id_);
    data_buffer_pool_ = nullptr;
  }

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(const char *path, const char *name, const char *base_dir, int attribute_count, const AttrInfo attributes[]) {

  if (nullptr == name || common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p",
        name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在

  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (-1 == fd) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s",
                path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", 
       path, errno, strerror(errno));
    return RC::IOERR;
  }

  close(fd);

  // 创建文件
  if ((rc = table_meta_.init(name, attribute_count, attributes)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc; // delete table file
  }

  std::fstream fs;
  fs.open(path, std::ios_base::out | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();


  // 创建数据文件
  std::string data_file = std::string(base_dir) + "/" + name + TABLE_DATA_SUFFIX;
  data_buffer_pool_ = theGlobalDiskBufferPool();
  rc = data_buffer_pool_->create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }



  // 如果field中有text字段，则创建存储text数据的外部文件,使用bp管理文件略麻烦，为解题起见，单独维护此外部文件
  bool flag = false;
  const int normal_field_start_index = table_meta_.sys_field_num();
  for (int i = normal_field_start_index; i < table_meta_.field_num(); i++) {
    const FieldMeta *field = table_meta_.field(i);
    if(field->type() == TEXTS){
      flag = true;
      break;
    }
  }

  if(flag){
    std::string text_data_file = std::string(base_dir) + "/" + name + TABLE_TEXT_SUFFIX;
    ofstream text_file(text_data_file,ios::binary);
    int cnt = 0;
    text_file.write((const char*)&cnt,4);
    text_file.close();
  }

  rc = init_record_handler(base_dir);

  base_dir_ = base_dir;

  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}



// Author yty 21/10/26
// implement drop table, close file and drop index first, then close data file and drop record file
RC Table::drop(const char *path, const char *name, const char *base_dir){
  LOG_INFO("Begin to drop table : %s", name);
  RC rc = RC::SUCCESS;
  
  // 删除索引文件及索引记录
  LOG_INFO("Begin to delete index");
  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    string index_file = index_data_file(base_dir, name, index_meta->name());
    if(remove(index_file.c_str()) != 0){
      LOG_ERROR("delete index file failed");
      return RC::IOERR_DELETE;
    }
  }
  indexes_.erase(indexes_.begin(), indexes_.end());

  // 删除数据文件
  string data_file = string(base_dir) + "/" + table_meta_.name() + TABLE_DATA_SUFFIX;
  if(remove(data_file.c_str()) != 0){
    LOG_ERROR("delete data file failed");
    return RC::IOERR_DELETE;
  }

  // 删除text数据文件
  std::string text_data_file = std::string(base_dir) + "/" + name + TABLE_TEXT_SUFFIX;
  remove(text_data_file.c_str());

  // 删除元数据文件 table_name.table
  if(remove(path) != 0){
    LOG_ERROR("delete metadata file failed");
    return RC::IOERR_DELETE;
  }
  return RC::SUCCESS;
}


RC Table::open(const char *meta_file, const char *base_dir) {
  // 加载元数据文件
  std::fstream fs;
  std::string meta_file_path = std::string(base_dir) + "/" + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file, strerror(errno));
    return RC::IOERR;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file);
    return RC::GENERIC_ERROR;
  }
  fs.close();

  // 加载数据文件
  RC rc = init_record_handler(base_dir);

  base_dir_ = base_dir;

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    const FieldMeta *field_meta = table_meta_.field(index_meta->field());
    if (field_meta == nullptr) {
      LOG_PANIC("Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
                name(), index_meta->name(), index_meta->field());
      return RC::GENERIC_ERROR;
    }

    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file = index_data_file(base_dir, name(), index_meta->name());
    rc = index->open(index_file.c_str(), *index_meta, *field_meta);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%d:%s",
                name(), index_meta->name(), index_file.c_str(), rc, strrc(rc));
      return rc;
    }
    indexes_.push_back(index);
  }
  return rc;
}

RC Table::commit_insert(Trx *trx, const RID &rid) {
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->commit_insert(this, record);
}

RC Table::rollback_insert(Trx *trx, const RID &rid) {

  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // remove all indexes
  rc = delete_entry_of_indexes(record.data, rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d) while rollback insert, rc=%d:%s",
              rid.page_num, rid.slot_num, rc, strrc(rc));
  } else {
    rc = record_handler_->delete_record(&rid);
  }
  return rc;
}

RC Table::insert_record(Trx *trx, Record *record) {
  RC rc = RC::SUCCESS;

  if (trx != nullptr) {
    trx->init_trx_info(this, *record);
  }
  rc = record_handler_->insert_record(record->data, table_meta_.record_size(), &record->rid);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  if (trx != nullptr) {
    rc = trx->insert_record(this, record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to log operation(insertion) to trx");

      RC rc2 = record_handler_->delete_record(&record->rid);
      if (rc2 != RC::SUCCESS) {
        LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                  name(), rc2, strrc(rc2));
      }
      return rc;
    }
  }

  rc = insert_entry_of_indexes(record->data, record->rid);
  if (rc != RC::SUCCESS) {
    RC rc2 = delete_entry_of_indexes(record->data, record->rid, true);
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record->rid);
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    return rc;
  }
  return rc;
}

// Author yty 21/10/31 
// update function insert record to support insert multiple value into table
RC Table::insert_record(Trx *trx, int value_num, const Value *values, int record_num, const int record_pos[]) {
  if (record_num <= 0 || nullptr == values ) {
    LOG_ERROR("Invalid argument. record num=%d, values=%p", record_num, values);
    return RC::INVALID_ARGUMENT;
  }
  RC rc = RC::SUCCESS;

  // 判断是否有text字段，如果有则使用make record 4 text函数
  // 在record的text字段记录页面号
  bool flag = false;
  const int normal_field_start_index = table_meta_.sys_field_num();
  for (int i = normal_field_start_index; i < table_meta_.field_num(); i++) {
    const FieldMeta *field = table_meta_.field(i);
    if(field->type() == TEXTS){
      flag = true;
      break;
    }
  }

  if(!flag){
  // 思路：插入多条记录、需要对每条记录是否合法做判断，只要有一条记录不合法则rollback commit， 并且需要一并删除索引
  
    int start_pos = 0;

    for(int i = 0; i < record_num; ++i){
      // 对于每条记录来讲，value长度为 [start_pos - record_pos[i]) ,然后更新start_pos为record_pos[i]
      int single_record_len = record_pos[i] - start_pos;

      if (single_record_len <= 0 || nullptr == values ) {
        LOG_ERROR("Invalid argument. value num=%d, values=%p", single_record_len, values);
        return RC::INVALID_ARGUMENT;
      }

      Value record_val[single_record_len];
      for(int pos = 0; pos < single_record_len; ++pos)
        record_val[pos] = values[start_pos+pos];
      

      char *record_data;
      rc = make_record(single_record_len, record_val, record_data);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
        return rc;
      }

      Record record;
      record.data = record_data;
      // record.valid = true;
      rc = insert_record(trx, &record);
      delete[] record_data;

      if(rc != RC::SUCCESS)
        return rc;

      start_pos = record_pos[i];
    }

  }else{


    int start_pos = 0;

    for(int i = 0; i < record_num; ++i){
      // 对于每条记录来讲，value长度为 [start_pos - record_pos[i]) ,然后更新start_pos为record_pos[i]
      int single_record_len = record_pos[i] - start_pos;

      if (single_record_len <= 0 || nullptr == values ) {
        LOG_ERROR("Invalid argument. value num=%d, values=%p", single_record_len, values);
        return RC::INVALID_ARGUMENT;
      }

      Value record_val[single_record_len];
      for(int pos = 0; pos < single_record_len; ++pos)
        record_val[pos] = values[start_pos+pos];
      

      char *record_data;
      rc = make_record_for_text(single_record_len, record_val, record_data);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
        return rc;
      }

      Record record;
      record.data = record_data;
      // record.valid = true;
      rc = insert_record(trx, &record);
      delete[] record_data;

      if(rc != RC::SUCCESS)
        return rc;

      start_pos = record_pos[i];
    }

  }

  return rc;
}

const char *Table::name() const {
  return table_meta_.name();
}

const TableMeta &Table::table_meta() const {
  return table_meta_;
}

string Table::base_dir(){
  return base_dir_;
}

RC Table::make_record_for_text(int value_num, const Value *values, char * &record_out){
  // 检查字段类型是否一致
  if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
    return RC::SCHEMA_FIELD_MISSING;
  }

  std::string text_data_file = std::string(base_dir_) + "/" + table_meta_.name() + TABLE_TEXT_SUFFIX;
  ifstream fin(text_data_file,ios::binary);
  int cnt;
  fin.read((char*)&cnt, 4);
  fin.close();

  const int normal_field_start_index = table_meta_.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value &value = values[i];

    // 增加日期字段的校验，若field type为日期字段但数据为char类型，则判断一下是否是日期格式
    if(field->type() == 4 && value.type == 1 && is_date(value) == RC::SUCCESS)
      continue;

    // 增加空字段校验，如果插入字段为空则校验字段能否为空
    if(value.type == 6){
      if(field->nullable()){
        // is_null == 1, nullable
        continue;
      }else{
        LOG_ERROR("field can not be null, plz insert a not null value");
        return RC::SCHEMA_FIELD_VALUE_ILLEGAL;
      }
    }

    // text 字段校验
    if(field->type() == TEXTS && value.type == CHARS)
      continue;

    if (field->type() != value.type) {
      LOG_ERROR("Invalid value type. field name=%s, type=%d, but given=%d",
        field->name(), field->type(), value.type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }
  // 复制所有字段的值
  int record_size = table_meta_.record_size();
  char *record = new char [record_size];

  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value &value = values[i];

    // 如果是日期类型，能运行到这里说明通过了合法性校验，则将字符串的值转为整数保存
    if(field->type() == 4 && *(int*)value.data != 16777215){
      char *p = new char[16];
      memcpy(p, value.data, 16);
      string str = p;
      int len = str.size();
      int time_int[3];
      for(int i = 0, j = 0; i < len; ++i){
        int start = i;
        while(i<len && str[i] != '-')
          ++i;
        time_int[j] = atoi((str.substr(start,i-start)).c_str()); 
        ++j; 
      }
      int time_sec = calc_sec1970(time_int[0], time_int[1], time_int[2]);
      delete p;
      memcpy(record + field->offset(), &time_sec, field->len());
      continue;
    }

    // 如果是text类型则在text.data文件中插入text数据，在text中的偏移量记录在数据位置
    if(field->type() == TEXTS){
      char text_data[4097];
      memcpy(text_data, value.data, 4096);
      int text_offset = 4 + cnt*4096;
      ofstream fout(text_data_file, ios::binary | ios::in);
      fout.seekp(text_offset, ios::beg);
      fout.write(text_data, 4096);
      fout.close();
      cnt++;
      memcpy(record + field->offset(), &text_offset, field->len());
      continue;
    }

    memcpy(record + field->offset(), value.data, field->len());
  }

  ofstream fout(text_data_file, ios::binary | ios::in);
  fout.seekp(0,ios::beg);
  fout.write((const char*)&cnt,4);
  fout.close();

  record_out = record;
  return RC::SUCCESS;
}


RC Table::make_record(int value_num, const Value *values, char * &record_out) {
  // 检查字段类型是否一致
  if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
    return RC::SCHEMA_FIELD_MISSING;
  }

  const int normal_field_start_index = table_meta_.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value &value = values[i];

    // 增加日期字段的校验，若field type为日期字段但数据为char类型，则判断一下是否是日期格式
    if(field->type() == 4 && value.type == 1 && is_date(value) == RC::SUCCESS)
      continue;

    // 增加空字段校验，如果插入字段为空则校验字段能否为空
    if(value.type == 6){
      if(field->nullable()){
        // is_null == 1, nullable
        continue;
      }else{
        LOG_ERROR("field can not be null, plz insert a not null value");
        return RC::SCHEMA_FIELD_VALUE_ILLEGAL;
      }
    }

    if (field->type() != value.type) {
      LOG_ERROR("Invalid value type. field name=%s, type=%d, but given=%d",
        field->name(), field->type(), value.type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }
  // 复制所有字段的值
  int record_size = table_meta_.record_size();
  char *record = new char [record_size];

  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value &value = values[i];

    // 如果是日期类型，能运行到这里说明通过了合法性校验，则将字符串的值转为整数保存
    if(field->type() == 4 && *(int*)value.data != 16777215){
      char *p = new char[16];
      memcpy(p, value.data, 16);
      string str = p;
      int len = str.size();
      int time_int[3];
      for(int i = 0, j = 0; i < len; ++i){
        int start = i;
        while(i<len && str[i] != '-')
          ++i;
        time_int[j] = atoi((str.substr(start,i-start)).c_str()); 
        ++j; 
      }
      int time_sec = calc_sec1970(time_int[0], time_int[1], time_int[2]);
      delete p;
      memcpy(record + field->offset(), &time_sec, field->len());
      continue;
    }

    memcpy(record + field->offset(), value.data, field->len());
  }

  record_out = record;
  return RC::SUCCESS;
}


// author yty 21/10/27
// check date type, if true than turn date time value to type of INT
// check date illegal
RC Table::is_date(const Value &value){
  char *p = new char[16];
  memcpy(p, value.data, 16);
  string str = p;
  vector<string> time;
  int len = str.size();
  for(int i = 0; i < len; ++i){
    int start = i;
    while(i<len && str[i] != '-')
      ++i;
    time.emplace_back(str.substr(start,i-start));  
  }
  len = time.size();
  delete p;
  if(len != 3)
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  int time_int[3];
  for(int i = 0; i < 3; ++i){
    for(auto &c : time[i]){
      if(c-'0'>9)
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
    time_int[i] = atoi(time[i].c_str());
  }

  // 合法性校验
  int day[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
  if((time_int[0] < 1970 || time_int[0] > 2038)
      || (time_int[1] < 1 || time_int[1] > 12)
      || (time_int[2] < 1 || time_int[2] > day[time_int[1]]))
    return RC::SCHEMA_FIELD_VALUE_ILLEGAL;
  if(!is_leap_year(time_int[0]) && time_int[1]==2 && time_int[2] > 28)
    return RC::SCHEMA_FIELD_VALUE_ILLEGAL;

  return RC::SUCCESS;
}

int Table::calc_sec1970(int year, int month, int day){
  int sec = 0;
  int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  for(int i = 1970; i < year; i++){
    if(is_leap_year(i))
        sec += 366 * 24 * 60 * 60;
    else
        sec += 365 * 24 * 60 * 60;
  }

  for(int i = 1; i < month; i++){
      sec += days[i] * 24 * 60 * 60;
      if(i == 2 && is_leap_year(year)){
          sec += 24 * 60 * 60;
      }
  }

  sec += (day - 1) * 24 * 60 * 60;
  return sec;
}

RC Table::init_record_handler(const char *base_dir) {
  std::string data_file = std::string(base_dir) + "/" + table_meta_.name() + TABLE_DATA_SUFFIX;
  if (nullptr == data_buffer_pool_) {
    data_buffer_pool_ = theGlobalDiskBufferPool();
  }

  int data_buffer_pool_file_id;
  RC rc = data_buffer_pool_->open_file(data_file.c_str(), &data_buffer_pool_file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s",
              data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler();
  rc = record_handler_->init(*data_buffer_pool_, data_buffer_pool_file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  file_id_ = data_buffer_pool_file_id;
  return rc;
}

/**
 * 为了不把Record暴露出去，封装一下
 */
class RecordReaderScanAdapter {
public:
  explicit RecordReaderScanAdapter(void (*record_reader)(const char *data, void *context), void *context)
      : record_reader_(record_reader), context_(context){
  }

  void consume(const Record *record) {
    record_reader_(record->data, context_);
  }
private:
  void (*record_reader_)(const char *, void *);
  void *context_;
};
static RC scan_record_reader_adapter(Record *record, void *context) {
  RecordReaderScanAdapter &adapter = *(RecordReaderScanAdapter *)context;
  adapter.consume(record);
  return RC::SUCCESS;
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context, void (*record_reader)(const char *data, void *context)) {
  RecordReaderScanAdapter adapter(record_reader, context);
  return scan_record(trx, filter, limit, (void *)&adapter, scan_record_reader_adapter);
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context, RC (*record_reader)(Record *record, void *context)) {
  if (nullptr == record_reader) {
    return RC::INVALID_ARGUMENT;
  }

  if (0 == limit) {
    return RC::SUCCESS;
  }

  if (limit < 0) {
    limit = INT_MAX;
  }

  IndexScanner *index_scanner = find_index_for_scan(filter);
  if (index_scanner != nullptr) {
    return scan_record_by_index(trx, index_scanner, filter, limit, context, record_reader);
  }

  RC rc = RC::SUCCESS;
  RecordFileScanner scanner;
  rc = scanner.open_scan(*data_buffer_pool_, file_id_, filter);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. file id=%d. rc=%d:%s", file_id_, rc, strrc(rc));
    return rc;
  }

  int record_count = 0;
  Record record;
  rc = scanner.get_first_record(&record);
  for ( ; RC::SUCCESS == rc && record_count < limit; rc = scanner.get_next_record(&record)) {
    if (trx == nullptr || trx->is_visible(this, &record)) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        break;
      }
      record_count++;
    }
  }

  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_ERROR("failed to scan record. file id=%d, rc=%d:%s", file_id_, rc, strrc(rc));
  }
  scanner.close_scan();
  return rc;
}

RC Table::scan_record_by_index(Trx *trx, IndexScanner *scanner, ConditionFilter *filter, int limit, void *context,
                               RC (*record_reader)(Record *, void *)) {
  RC rc = RC::SUCCESS;
  RID rid;
  Record record;
  int record_count = 0;
  while (record_count < limit) {
    rc = scanner->next_entry(&rid);
    if (rc != RC::SUCCESS) {
      if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
        break;
      }
      LOG_ERROR("Failed to scan table by index. rc=%d:%s", rc, strrc(rc));
      break;
    }

    rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to fetch record of rid=%d:%d, rc=%d:%s", rid.page_num, rid.slot_num, rc, strrc(rc));
      break;
    }

    if ((trx == nullptr || trx->is_visible(this, &record)) && (filter == nullptr || filter->filter(record))) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        LOG_TRACE("Record reader break the table scanning. rc=%d:%s", rc, strrc(rc));
        break;
      }
    }

    record_count++;
  }

  scanner->destroy();
  return rc;
}

class IndexInserter {
public:
  explicit IndexInserter(Index *index) : index_(index) {
  }

  RC insert_index(const Record *record) {
    return index_->insert_entry(record->data, &record->rid);
  }
private:
  Index * index_;
};

static RC insert_index_record_reader_adapter(Record *record, void *context) {
  IndexInserter &inserter = *(IndexInserter *)context;
  return inserter.insert_index(record);
}

RC Table::create_index(Trx *trx, const char *index_name, const char *attribute_name, const int is_unique) {
  if (index_name == nullptr || common::is_blank(index_name) ||
      attribute_name == nullptr || common::is_blank(attribute_name)) {
    return RC::INVALID_ARGUMENT;
  }
  if (table_meta_.index(index_name) != nullptr ||
      table_meta_.find_index_by_field((attribute_name))) {
    return RC::SCHEMA_INDEX_EXIST;
  }

  const FieldMeta *field_meta = table_meta_.field(attribute_name);
  if (!field_meta) {
    return RC::SCHEMA_FIELD_MISSING;
  }

  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, *field_meta, is_unique);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // 创建索引相关数据
  BplusTreeIndex *index = new BplusTreeIndex();
  std::string index_file = index_data_file(base_dir_.c_str(), name(), index_name);
  rc = index->create(index_file.c_str(), new_index_meta, *field_meta);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // 遍历当前的所有数据，插入这个索引
  IndexInserter index_inserter(index);
  rc = scan_record(trx, nullptr, -1, &index_inserter, insert_index_record_reader_adapter);
  if (rc != RC::SUCCESS) {
    // rollback
    delete index;

    // delete index file
    if(remove(index_file.c_str()) != 0){
      LOG_ERROR("delete index file failed");
      return RC::IOERR_DELETE;
    }
    LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }
  indexes_.push_back(index);

  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }
  // 创建元数据临时文件
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR; // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }
  fs.close();

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). " \
              "system error=%d:%s", tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("add a new index (%s) on the table (%s)", index_name, name());

  return rc;
}



// Author: yty 21/10/22
// implement of update record
class RecordUpdater{
private:
  Table & table_;
  Trx *trx_;
  int updated_count_ = 0;
  const char *attribute_name;
  const Value *value;
public:
  RecordUpdater(Table &table, Trx *trx, const char *attribute_name, const Value *value) : 
              table_(table), trx_(trx), attribute_name(attribute_name), value(value) {
  }

  RC update_record(Record *record) {
    RC rc = RC::SUCCESS;
    rc = table_.update_record(trx_, record, attribute_name, value);
    if (rc == RC::SUCCESS) {
      updated_count_++;
    }
    return rc;
  }

  int updated_count() const {
    return updated_count_;
  }
};

static RC record_reader_update_adapter(Record *record, void *context) {
  RecordUpdater &record_updater = *(RecordUpdater *)context;
  return record_updater.update_record(record);
}


RC Table::update_record(Trx *trx, const char *attribute_name, const Value *value, ConditionFilter *filter, int *updated_count) {
  RecordUpdater updater(*this, trx, attribute_name, value);
  RC rc = scan_record(trx, filter, -1, &updater, record_reader_update_adapter);
  if (updated_count != nullptr) {
    *updated_count = updater.updated_count();
  }
  return rc;
  
  // return RC::GENERIC_ERROR;
}

RC Table::update_record(Trx *trx, Record *record, const char *attribute_name, const Value *value) {
  RC rc = RC::SUCCESS;
  rc = delete_entry_of_indexes(record->data, record->rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
              record->rid.page_num, record->rid.slot_num, rc, strrc(rc));
  } else {

    const FieldMeta *field = table_meta_.field(attribute_name);
    // 检查是否存在这个字段
    if(field == nullptr){
      LOG_ERROR("failed to update, field=%s missing!", attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }

    bool flag_date_type = false;

    if(field->type() == 4 && value->type == 1){
      RC rc = is_date(*value);
      if(rc != RC::SUCCESS)
        return rc;
      
      flag_date_type = true;
      char *p = new char[16];
      memcpy(p, value->data, 16);
      string str = p;
      int len = str.size();
      int time_int[3];
      for(int i = 0, j = 0; i < len; ++i){
        int start = i;
        while(i<len && str[i] != '-')
          ++i;
        time_int[j] = atoi((str.substr(start,i-start)).c_str()); 
        ++j; 
      }
      int time_sec = calc_sec1970(time_int[0], time_int[1], time_int[2]);
      delete p;
      memcpy(record->data + field->offset(), &time_sec, field->len());
    }else if(value->type == 6){
      if(field->nullable()==0){
        LOG_ERROR("field can not be null, plz update a not null value");
        return RC::SCHEMA_FIELD_VALUE_ILLEGAL;
      }
    }else if (field->type() != value->type) {
      LOG_ERROR("Invalid value type. field name=%s, type=%d, but given=%d",
        field->name(), field->type(), value->type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }

    if(!flag_date_type)
      memcpy(record->data + field->offset(), value->data, field->len());
    

    rc = record_handler_->update_record(record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Update record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
      return rc;
    }


    // insert 新的索引条目
    rc = insert_entry_of_indexes(record->data, record->rid);

    if (rc != RC::SUCCESS) {
      RC rc2 = delete_entry_of_indexes(record->data, record->rid, true);
      if (rc2 != RC::SUCCESS) {
        LOG_PANIC("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                  name(), rc2, strrc(rc2));
      }
      rc2 = record_handler_->delete_record(&record->rid);
      if (rc2 != RC::SUCCESS) {
        LOG_PANIC("Failed to rollback record data when update index entries failed. table name=%s, rc=%d:%s",
                  name(), rc2, strrc(rc2));
      }
      return rc;
    }
  }
  return rc;
}




class RecordDeleter {
public:
  RecordDeleter(Table &table, Trx *trx) : table_(table), trx_(trx) {
  }

  RC delete_record(Record *record) {
    RC rc = RC::SUCCESS;
    rc = table_.delete_record(trx_, record);
    if (rc == RC::SUCCESS) {
      deleted_count_++;
    }
    return rc;
  }

  int deleted_count() const {
    return deleted_count_;
  }

private:
  Table & table_;
  Trx *trx_;
  int deleted_count_ = 0;
};

static RC record_reader_delete_adapter(Record *record, void *context) {
  RecordDeleter &record_deleter = *(RecordDeleter *)context;
  return record_deleter.delete_record(record);
}

RC Table::delete_record(Trx *trx, ConditionFilter *filter, int *deleted_count) {
  RecordDeleter deleter(*this, trx);
  RC rc = scan_record(trx, filter, -1, &deleter, record_reader_delete_adapter);
  if (deleted_count != nullptr) {
    *deleted_count = deleter.deleted_count();
  }
  return rc;
}

RC Table::delete_record(Trx *trx, Record *record) {
  RC rc = RC::SUCCESS;
  if (trx != nullptr) {
    rc = trx->delete_record(this, record);
  } else {
    rc = delete_entry_of_indexes(record->data, record->rid, false);// 重复代码 refer to commit_delete
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
                record->rid.page_num, record->rid.slot_num, rc, strrc(rc));
    } else {
      rc = record_handler_->delete_record(&record->rid);
    }
  }
  return rc;
}

RC Table::commit_delete(Trx *trx, const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = delete_entry_of_indexes(record.data, record.rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d). rc=%d:%s",
              rid.page_num, rid.slot_num, rc, strrc(rc));// panic?
  }

  rc = record_handler_->delete_record(&rid);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return rc;
}

RC Table::rollback_delete(Trx *trx, const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->rollback_delete(this, record); // update record in place
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const {
  for (Index *index: indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}

IndexScanner *Table::find_index_for_scan(const DefaultConditionFilter &filter) {
  const ConDesc *field_cond_desc = nullptr;
  const ConDesc *value_cond_desc = nullptr;
  if (filter.left().is_attr && !filter.right().is_attr) {
    field_cond_desc = &filter.left();
    value_cond_desc = &filter.right();
  } else if (filter.right().is_attr && !filter.left().is_attr) {
    field_cond_desc = &filter.right();
    value_cond_desc = &filter.left();
  }
  if (field_cond_desc == nullptr || value_cond_desc == nullptr) {
    return nullptr;
  }

  const FieldMeta *field_meta = table_meta_.find_field_by_offset(field_cond_desc->attr_offset);
  if (nullptr == field_meta) {
    LOG_PANIC("Cannot find field by offset %d. table=%s",
              field_cond_desc->attr_offset, name());
    return nullptr;
  }

  // 存在null值不走index
  if(field_meta->nullable())
    return nullptr;

  const IndexMeta *index_meta = table_meta_.find_index_by_field(field_meta->name());
  if (nullptr == index_meta) {
    return nullptr;
  }

  Index *index = find_index(index_meta->name());
  if (nullptr == index) {
    return nullptr;
  }

  return index->create_scanner(filter.comp_op(), (const char *)value_cond_desc->value);
}

IndexScanner *Table::find_index_for_scan(const ConditionFilter *filter) {
  if (nullptr == filter) {
    return nullptr;
  }

  // remove dynamic_cast
  const DefaultConditionFilter *default_condition_filter = dynamic_cast<const DefaultConditionFilter *>(filter);
  if (default_condition_filter != nullptr) {
    return find_index_for_scan(*default_condition_filter);
  }

  const CompositeConditionFilter *composite_condition_filter = dynamic_cast<const CompositeConditionFilter *>(filter);
  if (composite_condition_filter != nullptr) {
    int filter_num = composite_condition_filter->filter_num();
    for (int i = 0; i < filter_num; i++) {
      IndexScanner *scanner= find_index_for_scan(&composite_condition_filter->filter(i));
      if (scanner != nullptr) {
        return scanner; // 可以找到一个最优的，比如比较符号是=
      }
    }
  }
  return nullptr;
}

RC Table::sync() {
  RC rc = data_buffer_pool_->flush_all_pages(file_id_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to flush table's data pages. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }

  for (Index *index: indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
                name(), index->index_meta().name(), rc, strrc(rc));
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}
