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

#ifndef __OBSERVER_SQL_EXECUTOR_VALUE_H_
#define __OBSERVER_SQL_EXECUTOR_VALUE_H_

#include <string.h>

#include <string>
#include <ostream>
#include <iostream>

using namespace std;

class TupleValue {
public:
  TupleValue() = default;
  virtual ~TupleValue() = default;

  virtual void to_string(std::ostream &os) const = 0;
  virtual int compare(const TupleValue &other) const = 0;
  // 便于聚合函数计算
  virtual float return_val() const = 0;
  // 返回char*类型value
  virtual string return_char_val() const = 0;
  // 返回值是否为空
  virtual bool is_null() const = 0;
private:
};

class IntValue : public TupleValue {
public:
  explicit IntValue(int value, int is_null) : value_(value), is_null_(is_null) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const IntValue & int_other = (const IntValue &)other;
    return value_ - int_other.value_;
  }

  float return_val() const override {
    return value_;
  }

  string  return_char_val() const override{
    return std::to_string(value_);
  }

  bool is_null() const override{
    return is_null_;
  }

private:
  int value_;
  int is_null_;
};

class FloatValue : public TupleValue {
public:
  explicit FloatValue(float value, int is_null) : value_(value), is_null_(is_null) {
  }

  void to_string(std::ostream &os) const override {
    int v_for_out = value_ * 100;
    float v = v_for_out / 100.0;
    os << v;
  }

  int compare(const TupleValue &other) const override {
    const FloatValue & float_other = (const FloatValue &)other;
    float result = value_ - float_other.value_;
    if (result > 0) { // 浮点数没有考虑精度问题
      return 1;
    }
    if (result < 0) {
      return -1;
    }
    return 0;
  }

  float return_val() const override {
    return value_;
  }


  string return_char_val() const override{
    return std::to_string(value_);
  }

  bool is_null() const override{
    return is_null_;
  }
private:
  float value_;
  int is_null_;
};

class StringValue : public TupleValue {
public:
  StringValue(const char *value, int len, int is_null) : value_(value, len), is_null_(is_null){
    if(value_.size() > 4096)
      value_ = value_.substr(0,4096);
    // cout << value_.size() << endl;
    // cout << value_[value_.size()-1] - '\0' << endl;
  }
  explicit StringValue(const char *value, int is_null) : value_(value), is_null_(is_null) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const StringValue &string_other = (const StringValue &)other;
    return strcmp(value_.c_str(), string_other.value_.c_str());
  }

  float return_val() const override {
    return atof(value_.c_str());
  }

  string return_char_val() const override{
    return value_;
  }

  bool is_null() const override{
    return is_null_;
  }
private:
  std::string value_;
  int is_null_;
};


#endif //__OBSERVER_SQL_EXECUTOR_VALUE_H_
