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
// Created by Wangyunlai on 2021/5/14.
//

#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "common/log/log.h"

#define is_leap_year(y) (((y) % 4  == 0 && (y) % 100 != 0) || (y) % 400 == 0)
using namespace std;

Tuple::Tuple(const Tuple &other) {
  LOG_PANIC("Copy constructor of tuple is not supported");
  exit(1);
}

Tuple::Tuple(Tuple &&other) noexcept : values_(std::move(other.values_)) {
}

Tuple & Tuple::operator=(Tuple &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  values_.swap(other.values_);
  return *this;
}

Tuple::~Tuple() {
}

// add (Value && value)
void Tuple::add(TupleValue *value) {
  values_.emplace_back(value);
}
void Tuple::add(const std::shared_ptr<TupleValue> &other) {
  values_.emplace_back(other);
}
void Tuple::add(int value) {
  add(new IntValue(value));
}

void Tuple::add(float value) {
  add(new FloatValue(value));
}

void Tuple::add(const char *s, int len) {
  add(new StringValue(s, len));
}

////////////////////////////////////////////////////////////////////////////////

std::string TupleField::to_string() const {
  return std::string(table_name_) + "." + field_name_ + std::to_string(type_);
}

////////////////////////////////////////////////////////////////////////////////
void TupleSchema::from_table(const Table *table, TupleSchema &schema) {
  const char *table_name = table->name();
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = 0; i < field_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      schema.add(field_meta->type(), table_name, field_meta->name());
    }
  }
}

void TupleSchema::add(AttrType type, const char *table_name, const char *field_name) {
  fields_.emplace_back(type, table_name, field_name);
}

void TupleSchema::add_if_not_exists(AttrType type, const char *table_name, const char *field_name) {
  for (const auto &field: fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return;
    }
  }

  add(type, table_name, field_name);
}

void TupleSchema::append(const TupleSchema &other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto &field: other.fields_) {
    fields_.emplace_back(field);
  }
}

int TupleSchema::index_of_field(const char *table_name, const char *field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = fields_[i];
    if (0 == strcmp(field.table_name(), table_name) && 0 == strcmp(field.field_name(), field_name)) {
      return i;
    }
  }
  return -1;
}

void TupleSchema::print(std::ostream &os) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  // 判断有多张表还是只有一张表
  std::set<std::string> table_names;
  for (const auto &field: fields_) {
    table_names.insert(field.table_name());
  }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    if (table_names.size() > 1) {
      os << iter->table_name() << ".";
    }
    os << iter->field_name() << " | ";
  }

  if (table_names.size() > 1) {
    os << fields_.back().table_name() << ".";
  }
  os << fields_.back().field_name() << std::endl;
}

void TupleSchema::print_for_aggrefun(std::ostream &os) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  // 判断有多张表还是只有一张表
  std::set<std::string> table_names;
  for (const auto &field: fields_) {
    table_names.insert(field.table_name());
  }

  for(auto iter = aggtype_pos.begin(); iter != aggtype_pos.end()-1; ++iter){
    switch(iter->second){
      case COUNT_F:{
        os << "COUNT(";
        if (table_names.size() > 1) {
          os << fields_[iter->first].table_name() << ".";
        }
        os << fields_[iter->first].field_name() << ") | ";
      } 
      break;
      case COUNT_STAR_F:{
        os << "COUNT(*) | ";
      } 
      break;
      case COUNT_NUM_F:{
        os << "COUNT(1) | ";
      } 
      break;
      case MAX_F:{
        os << "MAX(";
        if (table_names.size() > 1) {
          os << fields_[iter->first].table_name() << ".";
        }
        os << fields_[iter->first].field_name() << ") | ";
      }
      break;
      case MIN_F:{
        os << "MIN(";
        if (table_names.size() > 1) {
          os << fields_[iter->first].table_name() << ".";
        }
        os << fields_[iter->first].field_name() << ") | ";
      }
      break;
      case AVG_F:{
        os << "AVG(";
        if (table_names.size() > 1) {
          os << fields_[iter->first].table_name() << ".";
        }
        os << fields_[iter->first].field_name() << ") | ";
      }
      break;
      default:{
        os << "ERROR : aggregate function can't be selected with common fields!" << endl;
        return;
      }
    }
  }

  switch(aggtype_pos.back().second){
    case COUNT_F:{
      os << "COUNT(";
      if (table_names.size() > 1) {
        os << fields_[aggtype_pos.back().first].table_name() << ".";
      }
      os << fields_[aggtype_pos.back().first].field_name() << ")" << std::endl;
    } 
    break;
    case COUNT_STAR_F:{
      os << "COUNT(*)" << endl;
    } 
    break;
    case COUNT_NUM_F:{
      os << "COUNT(1)" << endl;
    } 
    break;
    case MAX_F:{
      os << "MAX(";
      if (table_names.size() > 1) {
        os << fields_[aggtype_pos.back().first].table_name() << ".";
      }
      os << fields_[aggtype_pos.back().first].field_name() << ")" << std::endl;
    }
    break;
    case MIN_F:{
      os << "MIN(";
      if (table_names.size() > 1) {
        os << fields_[aggtype_pos.back().first].table_name() << ".";
      }
      os << fields_[aggtype_pos.back().first].field_name() << ")" << std::endl;
    }
    break;
    case AVG_F:{
      os << "AVG(";
      if (table_names.size() > 1) {
        os << fields_[aggtype_pos.back().first].table_name() << ".";
      }
      os << fields_[aggtype_pos.back().first].field_name() << ")" << std::endl;
    }
    break;
    default:{
      os << "ERROR : aggregate function can't be selected with common fields!" << endl;
      return;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet &&other) : tuples_(std::move(other.tuples_)), schema_(other.schema_){
  other.schema_.clear();
}

TupleSet &TupleSet::operator=(TupleSet &&other) {
  if (this == &other) {
    return *this;
  }

  schema_.clear();
  schema_.append(other.schema_);
  other.schema_.clear();

  tuples_.clear();
  tuples_.swap(other.tuples_);
  return *this;
}

void TupleSet::add(Tuple &&tuple) {
  tuples_.emplace_back(std::move(tuple));
}

void TupleSet::clear() {
  tuples_.clear();
  schema_.clear();
}

void TupleSet::print(std::ostream &os) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  if(schema_.aggtype_pos.front().second != NOTAGG){
    schema_.print_for_aggrefun(os);


    for(auto iter = schema_.aggtype_pos.begin(); iter != schema_.aggtype_pos.end()-1; ++iter){
      switch(iter->second){
        case COUNT_F:{
          if(tuples_.size() == 0){
            os << "NULL | ";
            continue;
          }
          int cnt = 0;
          for (const Tuple &item : tuples_) {
            // 需要增加对null字段的判断
            // count(column) 需要care null字段判断
            ++cnt;               
          }
          os << to_string(cnt);
          os << " | ";
        } 
        break;
        case COUNT_STAR_F:
        case COUNT_NUM_F:{
          if(tuples_.size() == 0){
            os << "NULL | ";
            continue;
          }
          int cnt = 0;
          for (const Tuple &item : tuples_) {
            ++cnt;               
          }
          os << to_string(cnt);
          os << " | ";
        } 
        break;
        case MAX_F:{
          if(tuples_.size() == 0){
            os << "NULL | ";
            continue;
          }
          shared_ptr<TupleValue> max_val = tuples_[0].values()[iter->first];
          for (const Tuple &item : tuples_) {
            if(item.values()[iter->first]->compare(*max_val) > 0)
              max_val = item.values()[iter->first];                   
          }
          (*max_val).to_string(os);
          os << " | ";
        }
        break;
        case MIN_F:{
          if(tuples_.size() == 0){
            os << "NULL | ";
            continue;
          }
          shared_ptr<TupleValue> min_val = tuples_[0].values()[iter->first];
          for (const Tuple &item : tuples_) {
            if(item.values()[iter->first]->compare(*min_val) < 0)
              min_val = item.values()[iter->first];                   
          }
          (*min_val).to_string(os);
          os << " | ";
        }
        break;
        case AVG_F:{
          if(tuples_.size() == 0){
            os << "NULL | ";
            continue;
          }
          float avg_val = 0;
          int cnt = 0;
          for (const Tuple &item : tuples_) {
            // 需要增加对null字段的判断
            ++cnt;
            avg_val += item.values()[iter->first]->return_val();                
          }
          avg_val /= cnt;
          int v_for_out = avg_val * 100;
          avg_val = v_for_out / 100.0;
          char *res;
          sprintf(res, "%g", avg_val);
          os << res;
          os << " | ";
        }
        break;
        default:{
          os << "ERROR : aggregate function can't be selected with common fields!" << endl;
          return;
        }
      }
    }

    switch(schema_.aggtype_pos.back().second){
      case COUNT_F:{
        if(tuples_.size() == 0){
          os << "NULL" << endl;
          return;
        }
        int cnt = 0;
        for (const Tuple &item : tuples_) {
          // 需要增加对null字段的判断
          // count(column) 需要care null字段判断
          ++cnt;               
        }
        os << to_string(cnt) << endl;
      } 
      break;
      case COUNT_STAR_F:
      case COUNT_NUM_F:{
        if(tuples_.size() == 0){
          os << "NULL" << endl;
          return;
        }
        int cnt = 0;
        for (const Tuple &item : tuples_) {
          ++cnt;               
        }
        os << to_string(cnt) << endl;
      } 
      break;
      case MAX_F:{
        if(tuples_.size() == 0){
          os << "NULL" << endl;
          return;
        }
        shared_ptr<TupleValue> max_val = tuples_[0].values()[schema_.aggtype_pos.back().first];
        for (const Tuple &item : tuples_) {
          if(item.values()[schema_.aggtype_pos.back().first]->compare(*max_val) > 0)
            max_val = item.values()[schema_.aggtype_pos.back().first];                   
        }
        (*max_val).to_string(os);
        os << endl;
      }
      break;
      case MIN_F:{
        if(tuples_.size() == 0){
          os << "NULL" << endl;
          return;
        }
        shared_ptr<TupleValue> min_val = tuples_[0].values()[schema_.aggtype_pos.back().first];
        for (const Tuple &item : tuples_) {
          if(item.values()[schema_.aggtype_pos.back().first]->compare(*min_val) < 0)
            min_val = item.values()[schema_.aggtype_pos.back().first];                   
        }
        (*min_val).to_string(os);
        os << endl;
      }
      break;
      case AVG_F:{
        if(tuples_.size() == 0){
          os << "NULL" << endl;
          return;
        }
        float avg_val = 0;
        int cnt = 0;
        for (const Tuple &item : tuples_) {
          // 需要增加对null字段的判断
          ++cnt;
          avg_val += item.values()[schema_.aggtype_pos.back().first]->return_val();                
        }
        avg_val /= cnt;
        int v_for_out = avg_val * 100;
        avg_val = v_for_out / 100.0;
        char res[64];
        sprintf(res, "%g", avg_val);
        os << res << endl;
      }
      break;
      default:{
        os << "ERROR : aggregate function can't be selected with common fields!" << endl;
        return;
      }
    }

  
  
  
  
  }else{
    schema_.print(os);

    for (const Tuple &item : tuples_) {
      const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
      for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
            iter != end; ++iter) {
        (*iter)->to_string(os);
        os << " | ";
      }
      values.back()->to_string(os);
      os << std::endl;
    }
  }
}

void TupleSet::set_schema(const TupleSchema &schema) {
  schema_ = schema;
}

const TupleSchema &TupleSet::get_schema() const {
  return schema_;
}

bool TupleSet::is_empty() const {
  return tuples_.empty();
}

int TupleSet::size() const {
  return tuples_.size();
}

const Tuple &TupleSet::get(int index) const {
  return tuples_[index];
}

const std::vector<Tuple> &TupleSet::tuples() const {
  return tuples_;
}

/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set) :
      table_(table), tuple_set_(tuple_set){
}

void TupleRecordConverter::add_record(const char *record) {
  const TupleSchema &schema = tuple_set_.schema();
  Tuple tuple;
  const TableMeta &table_meta = table_->table_meta();
  for (const TupleField &field : schema.fields()) {
    const FieldMeta *field_meta = table_meta.field(field.field_name());
    assert(field_meta != nullptr);
    switch (field_meta->type()) {
      case INTS: {
        int value = *(int*)(record + field_meta->offset());
        tuple.add(value);
      }
      break;
      case FLOATS: {
        float value = *(float *)(record + field_meta->offset());
        tuple.add(value);
      }
        break;
      case CHARS: {
        const char *s = record + field_meta->offset();  // 现在当做Cstring来处理
        tuple.add(s, strlen(s));
      }
      break;
      case DATES: {
        // value 为距离1970-01-01年的秒数
        // 需要转换为YYYY-mm-dd的格式，用0填充不足位
        int value = *(int*)(record + field_meta->offset());
        long long sec = 0;
        int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int year = 1970;
        while(sec<=value){
          if(is_leap_year(year))
            sec += 366 * 24 * 60 * 60;
          else
            sec += 365 * 24 * 60 * 60;
          ++year;
        }
        --year;
        if(is_leap_year(year))
          sec -= 366 * 24 * 60 * 60;
        else
          sec -= 365 * 24 * 60 * 60;
        int month = 1;
        while(sec <= value){
          sec += days[month] * 24 * 60 * 60;
          if(month == 2 && is_leap_year(year)){
              sec += 24 * 60 * 60;
          }
          ++month;
        }
        --month;
        sec -= days[month] * 24 * 60 * 60;
        if(month == 2 && is_leap_year(year)){
            sec -= 24 * 60 * 60;
        }
        int day = (value-sec) / 86400 + 1;
        string timestamp = to_string(year) + "-" + 
                          ((to_string(month)).size() > 1 ? to_string(month) : "0" + to_string(month))
                          + "-" + ((to_string(day)).size() > 1 ? to_string(day) : "0" + to_string(day));
        tuple.add(timestamp.c_str(), timestamp.size());
      }
      break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
    }
  }

  tuple_set_.add(std::move(tuple));
}


