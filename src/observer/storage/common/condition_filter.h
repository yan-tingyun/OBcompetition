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

#ifndef __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_
#define __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_

#include "rc.h"
#include "sql/parser/parse.h"

struct Record;
class Table;
class Tuple;
class TupleSet;

struct ConDesc {
  bool   is_attr;     // 是否属性，false 表示是值
  int    attr_length; // 如果是属性，表示属性值长度
  int    attr_offset; // 如果是属性，表示在记录中的偏移量
  void * value;       // 如果是值类型，这里记录值的数据
  int    is_null;     // 如果是值类型，这里记录值是否为空
};

class ConditionFilter {
public:
  virtual ~ConditionFilter();

  /**
   * Filter one record
   * @param rec
   * @return true means match condition, false means failed to match.
   */
  virtual bool filter(const Record &rec) const = 0;
};

class DefaultConditionFilter : public ConditionFilter {
public:
  DefaultConditionFilter();
  virtual ~DefaultConditionFilter();

  RC init(const ConDesc &left, const ConDesc &right, AttrType attr_type, CompOp comp_op);
  RC init(Table &table, const Condition &condition);

  // filter for cartesian product
  RC init(const Condition &condition,const TupleSet &tuple_set_a,const TupleSet &tuple_set_b);

  virtual bool filter(const Record &rec) const;

  // 这里写法有问题，参考scan record filter过程
  bool filter_for_join(const Tuple &tuple);

private:
  // 日期校验
  RC is_date(void *v);
  int calc_sec1970(int year, int month, int day);

public:
  const ConDesc &left() const {
    return left_;
  }

  const ConDesc &right() const {
    return right_;
  }

  CompOp comp_op() const {
    return comp_op_;
  }
public:
  char *left_table;
  char *right_table;

private:
  ConDesc  left_;
  ConDesc  right_;
  AttrType attr_type_ = UNDEFINED;
  CompOp   comp_op_ = NO_OP;
  // 记录日期类型数据转换为int类型后的值，因为要将这个变量的值随着对象生存周期保存
  int time_sec; 
};

class CompositeConditionFilter : public ConditionFilter {
public:
  CompositeConditionFilter() = default;
  virtual ~CompositeConditionFilter();

  RC init(const ConditionFilter *filters[], int filter_num);
  RC init(Table &table, const Condition *conditions, int condition_num);
  virtual bool filter(const Record &rec) const;

public:
  int filter_num() const {
    return filter_num_;
  }
  const ConditionFilter &filter(int index) const {
    return *filters_[index];
  }

private:
  RC init(const ConditionFilter *filters[], int filter_num, bool own_memory);
private:
  const ConditionFilter **      filters_ = nullptr;
  int                           filter_num_ = 0;
  bool                          memory_owner_ = false; // filters_的内存是否由自己来控制
};

#endif // __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_