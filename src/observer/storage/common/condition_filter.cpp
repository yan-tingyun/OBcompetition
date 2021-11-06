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
// Created by Wangyunlai on 2021/5/7.
//

#include <stddef.h>
#include "condition_filter.h"
#include "record_manager.h"
#include "common/log/log.h"
#include "storage/common/table.h"
#include "sql/executor/tuple.h"

#define is_leap_year(y) (((y) % 4  == 0 && (y) % 100 != 0) || (y) % 400 == 0)
using namespace std;
using namespace common;

ConditionFilter::~ConditionFilter()
{}

DefaultConditionFilter::DefaultConditionFilter()
{
  left_.is_attr = false;
  left_.attr_length = 0;
  left_.attr_offset = 0;
  left_.value = nullptr;

  right_.is_attr = false;
  right_.attr_length = 0;
  right_.attr_offset = 0;
  right_.value = nullptr;
}
DefaultConditionFilter::~DefaultConditionFilter()
{}

RC DefaultConditionFilter::init(const ConDesc &left, const ConDesc &right, AttrType attr_type, CompOp comp_op)
{
  if (attr_type < CHARS || attr_type > DATES) {
    LOG_ERROR("Invalid condition with unsupported attribute type: %d", attr_type);
    return RC::INVALID_ARGUMENT;
  }

  if (comp_op < EQUAL_TO || comp_op >= NO_OP) {
    LOG_ERROR("Invalid condition with unsupported compare operation: %d", comp_op);
    return RC::INVALID_ARGUMENT;
  }

  left_ = left;
  right_ = right;

  attr_type_ = attr_type;
  comp_op_ = comp_op;
  return RC::SUCCESS;
}

RC DefaultConditionFilter::init(Table &table, const Condition &condition)
{
  const TableMeta &table_meta = table.table_meta();
  ConDesc left;
  ConDesc right;

  AttrType type_left = UNDEFINED;
  AttrType type_right = UNDEFINED;

  if (1 == condition.left_is_attr) {
    left.is_attr = true;
    const FieldMeta *field_left = table_meta.field(condition.left_attr.attribute_name);
    if (nullptr == field_left) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.left_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    left.attr_length = field_left->len();
    left.attr_offset = field_left->offset();

    left.value = nullptr;

    type_left = field_left->type();
  } else {
    left.is_attr = false;
    left.value = condition.left_value.data;  // 校验type 或者转换类型
    type_left = condition.left_value.type;

    left.attr_length = 0;
    left.attr_offset = 0;
  }

  if (1 == condition.right_is_attr) {
    right.is_attr = true;
    const FieldMeta *field_right = table_meta.field(condition.right_attr.attribute_name);
    if (nullptr == field_right) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.right_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    right.attr_length = field_right->len();
    right.attr_offset = field_right->offset();
    type_right = field_right->type();

    right.value = nullptr;
  } else {
    right.is_attr = false;
    right.value = condition.right_value.data;
    type_right = condition.right_value.type;

    right.attr_length = 0;
    right.attr_offset = 0;
  }

  // 校验和转换
  //  if (!field_type_compare_compatible_table[type_left][type_right]) {
  //    // 不能比较的两个字段， 要把信息传给客户端
  //    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  //  }
  // NOTE：这里没有实现不同类型的数据比较，比如整数跟浮点数之间的对比
  // 但是选手们还是要实现。这个功能在预选赛中会出现


  // 校验是否为日期属性，若为日期属性则将value值转为int
  if((type_left == DATES && type_right == CHARS)|| (type_right == DATES && type_left == CHARS)){
    if(type_left == DATES){
      RC rc = is_date(right.value);
      if(rc != RC::SUCCESS)
        return rc;

      char *p = new char[16];
      memcpy(p, right.value, 16);
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
      this->time_sec = calc_sec1970(time_int[0], time_int[1], time_int[2]);
      delete p;
      right.value = &this->time_sec;
      type_right = DATES;

      return init(left, right, type_left, condition.comp);
    }else{

      RC rc = is_date(left.value);
      if(rc != RC::SUCCESS)
        return rc;

      char *p = new char[16];
      memcpy(p, left.value, 16);
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
      this->time_sec = calc_sec1970(time_int[0], time_int[1], time_int[2]);
      delete p;
      left.value = &this->time_sec;
      type_left = DATES;

      return init(left, right, type_left, condition.comp);
    }
  }



  if (type_left != type_right) {
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  return init(left, right, type_left, condition.comp);
}

bool match_table(const char *table_name_in_condition, const char *table_name_to_match) {
  return 0 == strcmp(table_name_in_condition, table_name_to_match);
}

// 笛卡尔积连接 filter函数处理思路：
// 先分别将左属性 右属性与tuple field对应，然后生成临时供scan和笛卡尔积的两个tuple，最后合并成完整的所有元组记录
// 对同一对tuple set元组可能有多个约束条件，需要对临时的两个tuple依次遍历完所有的约束条件后再进行笛卡尔积连接
RC DefaultConditionFilter::init(const Condition &condition,const TupleSet &tuple_set_a,const TupleSet &tuple_set_b)
{
  ConDesc left;
  ConDesc right;
  left.is_attr = true;
  right.is_attr = true;

  AttrType type_left = UNDEFINED;
  AttrType type_right = UNDEFINED;

  if(match_table(condition.left_attr.relation_name, tuple_set_b.get_schema().field(0).table_name())){
    // 是tuple set b中的属性
    const TupleSchema &schema_b = tuple_set_b.get_schema();
    int i = 0;
    for(; i < schema_b.field_size(); ++i){
      if(strcmp(condition.left_attr.attribute_name, schema_b.field(i).field_name()) == 0){
        left_table = condition.left_attr.relation_name;
        // 存储在连接后的记录中的偏移量下标，这里也可以传入连接后的field数组，可以比这个简洁很多，优化考虑
        // field数组和tuple的记录是对应关系
        left.attr_offset = i + tuple_set_a.get_schema().field_size();
        left.value = nullptr;
        type_left = schema_b.field(i).type();
        break;
      }
    }
    if(i == schema_b.field_size()){
      LOG_WARN("No such field in condition. %s.%s", condition.left_attr.relation_name, condition.left_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
  }else{
    // 是连接表中的属性
    const TupleSchema &schema_a = tuple_set_a.get_schema();
    int i = 0;
    for(; i < schema_a.field_size(); ++i){
      if(strcmp(condition.left_attr.attribute_name, schema_a.field(i).field_name()) == 0 && strcmp(condition.left_attr.relation_name, schema_a.field(i).table_name()) == 0){
        left_table = condition.left_attr.relation_name;
        left.attr_offset = i;
        left.value = nullptr;
        type_left = schema_a.field(i).type();
        break;
      }
    }
    if(i == schema_a.field_size()){
      LOG_WARN("No such field in condition. %s.%s", condition.left_attr.relation_name, condition.left_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
  }


  if(match_table(condition.right_attr.relation_name, tuple_set_b.get_schema().field(0).table_name())){
    // 是tuple set b中的属性
    const TupleSchema &schema_b = tuple_set_b.get_schema();
    int i = 0;
    for(; i < schema_b.field_size(); ++i){
      if(strcmp(condition.right_attr.attribute_name, schema_b.field(i).field_name()) == 0){
        right_table = condition.right_attr.relation_name;
        right.attr_offset = i + tuple_set_a.get_schema().field_size();
        right.value = nullptr;
        type_right = schema_b.field(i).type();
        break;
      }
    }
    if(i == schema_b.field_size()){
      LOG_WARN("No such field in condition. %s.%s", condition.right_attr.relation_name, condition.right_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
  }else{
    // 是连接表中的属性
    const TupleSchema &schema_a = tuple_set_a.get_schema();
    int i = 0;
    for(; i < schema_a.field_size(); ++i){
      if(strcmp(condition.right_attr.attribute_name, schema_a.field(i).field_name()) == 0 && strcmp(condition.right_attr.relation_name, schema_a.field(i).table_name()) == 0){
        right_table = condition.right_attr.relation_name;
        right.attr_offset = i;
        right.value = nullptr;
        type_right = schema_a.field(i).type();
        break;
      }
    }
    if(i == schema_a.field_size()){
      LOG_WARN("No such field in condition. %s.%s", condition.right_attr.relation_name, condition.right_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
  }
  
  if (type_left != type_right) {
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  return init(left, right, type_left, condition.comp);
}




RC DefaultConditionFilter::is_date(void *v){
  char *p = new char[16];
  memcpy(p, v, 16);
  string str = p;
  vector<string> time;
  int len = str.size();
  for(int i = 0; i < len; ++i){
    int start = i;
    while(i<len && str[i] != '-')
      ++i;
    time.emplace_back(str.substr(start,i-start));  
  }
  delete p;
  len = time.size();
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
  if(!is_leap_year(time_int[0]) && time_int[1] == 2 && time_int[2] > 28)
    return RC::SCHEMA_FIELD_VALUE_ILLEGAL;

  return RC::SUCCESS;
}

int DefaultConditionFilter::calc_sec1970(int year, int month, int day){
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

bool DefaultConditionFilter::filter(const Record &rec) const
{
  char *left_value = nullptr;
  char *right_value = nullptr;

  if (left_.is_attr) {  // value
    left_value = (char *)(rec.data + left_.attr_offset);
  } else {
    left_value = (char *)left_.value;
  }

  if (right_.is_attr) {
    right_value = (char *)(rec.data + right_.attr_offset);
  } else {
    right_value = (char *)right_.value;
  }


  int cmp_result = 0;
  switch (attr_type_) {
    case CHARS: {  // 字符串都是定长的，直接比较
      // 按照C字符串风格来定
      cmp_result = strcmp(left_value, right_value);
    } break;
    case INTS: {
      // 没有考虑大小端问题
      // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
      int left = *(int *)left_value;
      int right = *(int *)right_value;
      cmp_result = left - right;
    } break;
    case FLOATS: {
      float left = *(float *)left_value;
      float right = *(float *)right_value;
      cmp_result = (int)(left - right);
    } break;
    case DATES: {
      // 没有考虑大小端问题
      // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
      int left = *(int *)left_value;
      int right = *(int *)right_value;
      cmp_result = left - right;
    } break;
    default: {
    }
  }

  switch (comp_op_) {
    case EQUAL_TO:
      return 0 == cmp_result;
    case LESS_EQUAL:
      return cmp_result <= 0;
    case NOT_EQUAL:
      return cmp_result != 0;
    case LESS_THAN:
      return cmp_result < 0;
    case GREAT_EQUAL:
      return cmp_result >= 0;
    case GREAT_THAN:
      return cmp_result > 0;

    default:
      break;
  }

  LOG_PANIC("Never should print this.");
  return cmp_result;  // should not go here
}


bool DefaultConditionFilter::filter_for_join(const Tuple &tuple){
  const char *left_value = nullptr;
  const char *right_value = nullptr;


  left_value = tuple.get_pointer(left_.attr_offset)->return_char_val();
  right_value = tuple.get_pointer(right_.attr_offset)->return_char_val();

  int cmp_result = 0;
  switch (attr_type_) {
    case CHARS: {  // 字符串都是定长的，直接比较
      // 按照C字符串风格来定
      cmp_result = strcmp(left_value, right_value);
    } break;
    case INTS: {
      // 没有考虑大小端问题
      // 对int和float，要考虑字节对齐问题,有些平台下直接转换可能会跪
      int left = *(int *)left_value;
      int right = *(int *)right_value;
      cmp_result = left - right;
    } break;
    case FLOATS: {
      float left = *(float *)left_value;
      float right = *(float *)right_value;
      cmp_result = (int)(left - right);
    } break;
    case DATES: {
      // 这里要按照char的方式判断，因为tuple里的数据已经是int转为标准日期格式的数据了
      cmp_result = strcmp(left_value, right_value);
    } break;
    default: {
    }
  }

  switch (comp_op_) {
    case EQUAL_TO:
      return 0 == cmp_result;
    case LESS_EQUAL:
      return cmp_result <= 0;
    case NOT_EQUAL:
      return cmp_result != 0;
    case LESS_THAN:
      return cmp_result < 0;
    case GREAT_EQUAL:
      return cmp_result >= 0;
    case GREAT_THAN:
      return cmp_result > 0;

    default:
      break;
  }

  LOG_PANIC("Never should print this.");
  return cmp_result;  // should not go here
}

CompositeConditionFilter::~CompositeConditionFilter()
{
  if (memory_owner_) {
    delete[] filters_;
    filters_ = nullptr;
  }
}

RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num, bool own_memory)
{
  filters_ = filters;
  filter_num_ = filter_num;
  memory_owner_ = own_memory;
  return RC::SUCCESS;
}
RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num)
{
  return init(filters, filter_num, false);
}

RC CompositeConditionFilter::init(Table &table, const Condition *conditions, int condition_num)
{
  if (condition_num == 0) {
    return RC::SUCCESS;
  }
  if (conditions == nullptr) {
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;
  ConditionFilter **condition_filters = new ConditionFilter *[condition_num];
  for (int i = 0; i < condition_num; i++) {
    DefaultConditionFilter *default_condition_filter = new DefaultConditionFilter();
    rc = default_condition_filter->init(table, conditions[i]);
    if (rc != RC::SUCCESS) {
      delete default_condition_filter;
      for (int j = i - 1; j >= 0; j--) {
        delete condition_filters[j];
        condition_filters[j] = nullptr;
      }
      delete[] condition_filters;
      condition_filters = nullptr;
      return rc;
    }
    condition_filters[i] = default_condition_filter;
  }
  return init((const ConditionFilter **)condition_filters, condition_num, true);
}

bool CompositeConditionFilter::filter(const Record &rec) const
{
  for (int i = 0; i < filter_num_; i++) {
    if (!filters_[i]->filter(rec)) {
      return false;
    }
  }
  return true;
}
