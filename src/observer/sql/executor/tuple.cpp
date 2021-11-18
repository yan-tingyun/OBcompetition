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

#include <fstream>

#define is_leap_year(y) (((y) % 4  == 0 && (y) % 100 != 0) || (y) % 400 == 0)
using namespace std;

Tuple::Tuple(const Tuple &other) {
  // LOG_PANIC("Copy constructor of tuple is not supported");
  // exit(1);
  values_.assign(other.values().begin(),other.values().end());
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
  values_.clear();
}

// add (Value && value)
void Tuple::add(TupleValue *value) {
  values_.emplace_back(value);
}
void Tuple::add(const std::shared_ptr<TupleValue> &other) {
  values_.emplace_back(other);
}
void Tuple::add(int value, int is_null) {
  add(new IntValue(value,is_null));
}

void Tuple::add(float value, int is_null) {
  add(new FloatValue(value,is_null));
}

void Tuple::add(const char *s, int len, int is_null) {
  add(new StringValue(s, len,is_null));
}

void Tuple::join_tuples(const Tuple &tuple_oth){
  values_.insert(values_.end(),tuple_oth.values().begin(), tuple_oth.values().end());
}

void Tuple::set_tupleVal(float val, int index){
  values_[index] = shared_ptr<TupleValue>(new FloatValue(val,0));
}

void Tuple::set_tupleVal(int val, int index){
  values_[index] = shared_ptr<TupleValue>(new IntValue(val,0));
}

void Tuple::set_tupleVal(const shared_ptr<TupleValue> &val, int index){
  values_[index] = val;
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
      schema.add(field_meta->type(), table_name, field_meta->name(), field_meta->nullable());
    }
  }
}

void TupleSchema::add(AttrType type, const char *table_name, const char *field_name, int is_null) {
  fields_.emplace_back(type, table_name, field_name, is_null);
}

void TupleSchema::add_if_not_exists(AttrType type, const char *table_name, const char *field_name, int is_null) {
  for (const auto &field: fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return;
    }
  }

  add(type, table_name, field_name, is_null);
}

void TupleSchema::append(const TupleSchema &other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto &field: other.fields_) {
    fields_.emplace_back(field);
  }
}

void TupleSchema::set_tuplefield(const vector<TupleField> &tuplefields){
  fields_.assign(tuplefields.begin(), tuplefields.end());
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

void TupleSchema::print(const Selects &select,std::ostream &os) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  // 判断有多张表还是只有一张表
  // std::set<std::string> table_names;
  // for (const auto &field: fields_) {
  //   table_names.insert(field.table_name());
  // }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    if (select.relation_num > 1) {
      os << iter->table_name() << ".";
    }
    os << iter->field_name() << " | ";
  }

  if (select.relation_num > 1) {
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


void TupleSchema::print_for_multitables(ostream &os, vector<pair<int,int>> &print_col,unordered_map<string, pair<int,int>> &table_to_valuepos, const Selects selects) const{

  for(int i = selects.attr_num - 1; i > -1; --i){
    const RelAttr &attr = selects.attributes[i];
    if(0 == strcmp("*", attr.attribute_name) && nullptr == attr.relation_name){
      // select * from table1, table2 ..
      print_col.push_back({0, field_size()});
    }else{
      // select t1.*,t2.*from t1, t2.. / select t1.col1,t2.col2 from t1, t2...
      if(0 == strcmp("*", attr.attribute_name)){
        print_col.emplace_back(table_to_valuepos[attr.relation_name]);
      }else{
        int col_pos = index_of_field(attr.relation_name,attr.attribute_name);
        if(col_pos != -1)
          print_col.push_back({col_pos, col_pos+1});
      }
    }
  }

  for(int i = 0; i < print_col.size() - 1; ++i){
    for(int j = print_col[i].first; j < print_col[i].second; ++j){
      os << field(j).table_name() << "." << field(j).field_name() << " | ";
    }
  }

  for(int j = print_col.back().first; j < print_col.back().second-1; ++j){
    os << field(j).table_name() << "." << field(j).field_name() << " | ";
  }

  os << field(print_col.back().second-1).table_name() << "." << field(print_col.back().second-1).field_name() << endl;

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

void TupleSet::print(const Selects &select,std::ostream &os, const vector<int> &pos_to_sortfunc) const {
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

          if(!schema_.field(iter->first).is_null()){

            int cnt = tuples_.size();
            os << to_string(cnt);
            os << " | ";
          }else{
            int cnt = 0;
            for (const Tuple &item : tuples_) {
              if(!item.values()[iter->first]->is_null())
                ++cnt;                  
            }
            os << to_string(cnt) << " | ";
          }
        } 
        break;
        case COUNT_STAR_F:
        case COUNT_NUM_F:{
          if(tuples_.size() == 0){
            os << "NULL | ";
            continue;
          }
          // int cnt = 0;
          // for (const Tuple &item : tuples_) {
          //   ++cnt;               
          // }
          int cnt = tuples_.size();
          os << to_string(cnt);
          os << " | ";
        } 
        break;
        case MAX_F:{
          if(tuples_.size() == 0){
            os << "NULL | ";
            continue;
          }
          int index = 0;
          while(index < tuples_.size() && tuples_[index].values()[iter->first]->is_null())
            ++index;
          
          if(index == tuples_.size()){
            os << "NULL | ";
            continue;
          }

          shared_ptr<TupleValue> max_val = tuples_[index].values()[iter->first];
          for (const Tuple &item : tuples_) {
            if(!item.values()[iter->first]->is_null()
                && item.values()[iter->first]->compare(*max_val) > 0)
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

          int index = 0;
          while(index < tuples_.size() && tuples_[index].values()[iter->first]->is_null())
            ++index;
          
          if(index == tuples_.size()){
            os << "NULL | ";
            continue;
          }

          shared_ptr<TupleValue> min_val = tuples_[index].values()[iter->first];
          for (const Tuple &item : tuples_) {
            if(!item.values()[iter->first]->is_null()
                && item.values()[iter->first]->compare(*min_val) < 0)
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
            if(!item.values()[iter->first]->is_null()){
              ++cnt;
              avg_val += item.values()[iter->first]->return_val(); 
            }               
          }
          if(cnt == 0){
            os << "NULL | ";
            continue;
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
        if(!schema_.field(schema_.aggtype_pos.back().first).is_null()){

          int cnt = tuples_.size();
          os << to_string(cnt);
          os << endl;
        }else{
          int cnt = 0;
          for (const Tuple &item : tuples_) {
            if(!item.values()[schema_.aggtype_pos.back().first]->is_null())
              ++cnt;                  
          }
          os << to_string(cnt) << endl;
        }
      } 
      break;
      case COUNT_STAR_F:
      case COUNT_NUM_F:{
        if(tuples_.size() == 0){
          os << "NULL" << endl;
          return;
        }
        // int cnt = 0;
        // for (const Tuple &item : tuples_) {
        //   ++cnt;               
        // }
        int cnt = tuples_.size();
        os << to_string(cnt) << endl;
      } 
      break;
      case MAX_F:{
        if(tuples_.size() == 0){
          os << "NULL" << endl;
          return;
        }

        int index = 0;
        while(index < tuples_.size() && tuples_[index].values()[schema_.aggtype_pos.back().first]->is_null())
          ++index;
        
        if(index == tuples_.size()){
          os << "NULL" << endl;
          return;
        }

        shared_ptr<TupleValue> max_val = tuples_[0].values()[schema_.aggtype_pos.back().first];
        for (const Tuple &item : tuples_) {
          if(!item.values()[schema_.aggtype_pos.back().first]->is_null()
              && item.values()[schema_.aggtype_pos.back().first]->compare(*max_val) > 0)
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

        int index = 0;
        while(index < tuples_.size() && tuples_[index].values()[schema_.aggtype_pos.back().first]->is_null())
          ++index;
        
        if(index == tuples_.size()){
          os << "NULL" << endl;
          return;
        }

        shared_ptr<TupleValue> min_val = tuples_[0].values()[schema_.aggtype_pos.back().first];
        for (const Tuple &item : tuples_) {
          if(!item.values()[schema_.aggtype_pos.back().first]->is_null()
            && item.values()[schema_.aggtype_pos.back().first]->compare(*min_val) < 0)
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
          if(!item.values()[schema_.aggtype_pos.back().first]->is_null()){
            ++cnt;
            avg_val += item.values()[schema_.aggtype_pos.back().first]->return_val();  
          }              
        }

        if(cnt == 0){
          os << "NULL" << endl;
          return;
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
    schema_.print(select,os);

    for(int i = 0; i < tuples_.size(); ++i){
      const std::vector<std::shared_ptr<TupleValue>> &values = tuples_[pos_to_sortfunc[i]].values();
      for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
            iter != end; ++iter) {
        if(!(*iter)->is_null()){
          (*iter)->to_string(os);
          os << " | ";
        }else{
          os << "NULL | ";
        }
      }
      if(!values.back()->is_null())
        values.back()->to_string(os);
      else
        os << "NULL";
      os << std::endl;
    }
  }
}


void TupleSet::print_for_join(const Selects &selects, ostream &os, unordered_map<string, pair<int,int>> &table_to_valuepos, const vector<int> &pos_to_sortfunc) const {
  // vector<pair<int,int>> 
  // 先遍历结果集的表头，然后将表头每列对应数据列存在pair数组里，
  vector<pair<int, int>> print_col;
  schema_.print_for_multitables(os, print_col,table_to_valuepos, selects);

  for(int i = 0; i < tuples_.size(); ++i){
    const std::vector<std::shared_ptr<TupleValue>> &values = tuples_[pos_to_sortfunc[i]].values();
    for(int i = 0; i < print_col.size() - 1; ++i){
      for(int j = print_col[i].first; j < print_col[i].second; ++j){
        if(!values[j]->is_null())
          values[j]->to_string(os);
        else
          os<<"NULL";
        os << " | ";
      }
    }
    for(int j = print_col.back().first; j < print_col.back().second-1; ++j){
      if(!values[j]->is_null())
        values[j]->to_string(os);
      else
        os<<"NULL";
      os << " | ";
    }
    if(!values[print_col.back().second-1]->is_null())
      values[print_col.back().second-1]->to_string(os);
    else
      os<<"NULL";
    os << endl;
  }
}

void TupleSet::print_for_group(const Selects &selects, std::ostream &os,const vector<int> &pos_to_sortfunc){
  // 打印表头
  if (schema_.field_size() == 0) {
    os << "No schema";
    return;
  }
  const vector<TupleField> fields = schema_.fields();

  for (std::vector<TupleField>::const_iterator iter = fields.begin(), end = --fields.end();
      iter != end; ++iter) {
    if (selects.relation_num > 1) {
      os << iter->table_name() << ".";
    }
    os << iter->field_name() << " | ";
  }

  if (selects.relation_num > 1) {
    os << fields.back().table_name() << ".";
  }
  os << fields.back().field_name() << std::endl;

  for(int i = 0; i < tuples_.size(); ++i){
    const std::vector<std::shared_ptr<TupleValue>> &values = tuples_[pos_to_sortfunc[i]].values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
          iter != end; ++iter) {
      if(!(*iter)->is_null())
        (*iter)->to_string(os);
      else
        os<<"NULL";
      os << " | ";
    }
    if(!values.back()->is_null())
      values.back()->to_string(os);
    else
      os<<"NULL";
    os << std::endl;
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

void TupleSet::set_schema_tuplefields(const vector<TupleField> &tuplefields){
  schema_.set_tuplefield(tuplefields);
}

 void TupleSet::set_vec_tuple(const vector<Tuple> &tuple_vec){
   tuples_.clear();
   tuples_.reserve(tuple_vec.size());
   for(size_t i = 0; i < tuple_vec.size(); ++i)
    tuples_.emplace_back(tuple_vec[i]);
 }

/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set) :
      table_(table), tuple_set_(tuple_set){
}

void TupleRecordConverter::add_record(const char *record) {
  const TupleSchema &schema = tuple_set_.get_schema();
  Tuple tuple;
  const TableMeta &table_meta = table_->table_meta();
  for (const TupleField &field : schema.fields()) {
    const FieldMeta *field_meta = table_meta.field(field.field_name());
    assert(field_meta != nullptr);
    switch (field_meta->type()) {
      case INTS: {
        int value = *(int*)(record + field_meta->offset());
        if(*(int*)(record + field_meta->offset()) == 16777215)
          tuple.add(value,1);
        else
          tuple.add(value,0);
      }
      break;
      case FLOATS: {
        float value = *(float *)(record + field_meta->offset());
        if(*(int*)(record + field_meta->offset()) == 16777215)
          tuple.add(value,1);
        else
          tuple.add(value,0);
      }
        break;
      case CHARS: {
        const char *s = record + field_meta->offset();  // 现在当做Cstring来处理
        if(*(int*)s == 16777215)
          tuple.add(s, strlen(s),1);
        else
          tuple.add(s, strlen(s),0);
      }
      break;
      case TEXTS: {
        int text_offset = *(int*)(record + field_meta->offset());
        string text_data_file = table_->base_dir() + "/" + table_meta.name() + ".text";
        char *data = new char[4097];
        ifstream fin(text_data_file, ios::binary);
        fin.seekg(text_offset,ios::beg);
        fin.read(data, 4096);
        fin.close();
        
        tuple.add(data, strlen(data),0);
      }
      break;
      case DATES: {
        // value 为距离1970-01-01年的秒数
        // 需要转换为YYYY-mm-dd的格式，用0填充不足位
        int value = *(int*)(record + field_meta->offset());
        if(*(int*)(record + field_meta->offset()) == 16777215){
          tuple.add(value,1);
          break;
        }

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
        tuple.add(timestamp.c_str(), timestamp.size(),0);
      }
      break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
    }
  }

  tuple_set_.add(std::move(tuple));
}