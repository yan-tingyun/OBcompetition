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
// Created by Longda on 2021/4/13.
//

#include <string>
#include <sstream>

#include "execute_stage.h"
#include "algorithm"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "event/execution_plan_event.h"
#include "sql/executor/execution_node.h"
#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"

using namespace common;
using namespace std;

RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);
RC sort_tuple_sets(const Selects &selects, TupleSet &tuple_set, vector<int> &pos_to_sortfunc);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag) {
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties() {
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event) {
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SQLStageEvent *sql_event = exe_event->sql_event();
  sql_event->done_immediate();

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event) {
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SessionEvent *session_event = exe_event->sql_event()->session_event();
  Query *sql = exe_event->sqls();
  const char *current_db = session_event->get_client()->session->get_current_db().c_str();

  CompletionCallback *cb = new (std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr) {
    LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
    exe_event->done_immediate();
    return;
  }
  exe_event->push_callback(cb);

  switch (sql->flag) {
    case SCF_SELECT: { // select
      std::stringstream ss;
      do_select(current_db, sql, exe_event->sql_event()->session_event(), ss);
      if(ss.str().size() == 0)
        session_event->set_response("FAILURE\n");
      exe_event->done_immediate();
    }
    break;

    case SCF_INSERT:
    case SCF_UPDATE:
    case SCF_DELETE:
    case SCF_CREATE_TABLE:
    case SCF_SHOW_TABLES:
    case SCF_DESC_TABLE:
    case SCF_DROP_TABLE:
    case SCF_CREATE_INDEX:
    case SCF_DROP_INDEX: 
    case SCF_LOAD_DATA: {
      StorageEvent *storage_event = new (std::nothrow) StorageEvent(exe_event);
      if (storage_event == nullptr) {
        LOG_ERROR("Failed to new StorageEvent");
        event->done_immediate();
        return;
      }

      default_storage_stage_->handle_event(storage_event);
    }
    break;
    case SCF_SYNC: {
      RC rc = DefaultHandler::get_default().sync();
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_BEGIN: {
      session_event->get_client()->session->set_trx_multi_operation_mode(true);
      session_event->set_response(strrc(RC::SUCCESS));
      exe_event->done_immediate();
    }
    break;
    case SCF_COMMIT: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->commit();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_HELP: {
      const char *response = "show tables;\n"
          "desc `table name`;\n"
          "create table `table name` (`column name` `column type`, ...);\n"
          "drop table `table name`;\n"
          "create index `index name` on `table` (`column`);\n"
          "insert into `table` values(`value1`,`value2`),(`value3`,`value4`)...;\n"
          "update `table` set column=value [where `column`=`value`];\n"
          "delete from `table` [where `column`=`value`];\n"
          "select [ * | `columns` ] from `table`;\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    case SCF_EXIT: {
      // do nothing
      const char *response = "Unsupported\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    default: {
      exe_event->done_immediate();
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right) {
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

bool match_table(const Selects &selects, const char *table_name_in_condition, const char *table_name_to_match) {
  if (table_name_in_condition != nullptr) {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }

  return selects.relation_num == 1;
}


/* 计算笛卡尔积
* param : 所有元组集合 vector<TupleSet>
* param : 拼接后的元素集合
* param : 当前拼接的元组index 下标
* param : select查询对象
* param : unordered_set, 每个table与其投影出的属性的列的下标范围，在组合后的连接表中的pos
*/
RC cartesian(vector<TupleSet> &tuple_sets, TupleSet &tuple_set, int cur_index, const Selects &selects, unordered_map<string, pair<int,int>> &table_to_valuepos){
  // 先将 schema的field拼接再连接每条元组记录，满足条件的
  if(cur_index == -1)
    return RC::SUCCESS;

  TupleSet &tuple_set_oth = tuple_sets[cur_index];
  // 每两张连接表最后需要从新set field数组tuple_field_join
  vector<TupleField> tuple_field_join = tuple_set.get_schema().fields();

  table_to_valuepos.insert({tuple_set_oth.get_schema().field(0).table_name(), pair<int,int>{tuple_field_join.size(), tuple_field_join.size()+tuple_set_oth.get_schema().field_size()}});
  
  tuple_field_join.insert(tuple_field_join.end(),
                        tuple_set_oth.get_schema().fields().begin(),
                        tuple_set_oth.get_schema().fields().end());



  vector<DefaultConditionFilter *> condition_filters;
  // 记得在用完filter条件后将filter对象析构掉
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];

    // 仅需要考虑两边都是属性的时候
    // 因为连接表中有多张表，因此需要在unordered_map中搜索是否有这张表的数据
    if ((condition.left_is_attr == 1 && condition.right_is_attr == 1) && 
      ((table_to_valuepos.count(condition.left_attr.relation_name) && match_table(selects, condition.right_attr.relation_name, tuple_set_oth.get_schema().field(0).table_name()))  // 左边和组合tuple对应右边和tuple[cur_index]对应
      || (match_table(selects, condition.left_attr.relation_name, tuple_set_oth.get_schema().field(0).table_name()) && table_to_valuepos.count(condition.right_attr.relation_name)))) // 右边和组合tuple对应左边和tuple[cur_index]对应
      {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      RC rc = condition_filter->init(condition, tuple_set, tuple_set_oth);
      
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    }
  }

  // 开始filter，先连接 连接表 和 待连接表 然后判断filter条件数量，如果为0就直接继续不然就filter
  vector<Tuple> tuples_join;
  for(auto &t : tuple_set.tuples()){
    for(auto &t_oth : tuple_set_oth.tuples()){
      Tuple tuple_join = t;
      tuple_join.join_tuples(t_oth);
      tuples_join.emplace_back(tuple_join);
    }
  }

  for(DefaultConditionFilter * &filter : condition_filters){
    for(auto iter = tuples_join.begin(); iter != tuples_join.end();){
      // 如果是不满足条件的元组就erase，并且修改迭代器防止失效
      if(!filter->filter_for_join(*iter)){
        iter = tuples_join.erase(iter);
      }else
        ++iter;
    }
  }

  for (DefaultConditionFilter * &filter : condition_filters) {
    delete filter;
  }
  // 给连接表set field、tuple set 开启下一个递归 
  tuple_set.set_schema_tuplefields(tuple_field_join);
  tuple_set.set_vec_tuple(tuples_join);

  return cartesian(tuple_sets, tuple_set, cur_index-1, selects, table_to_valuepos);

}

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event, std::stringstream &ss) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;

  // order list合法性校验 (其实应该先对属性、判断条件的合法性初步校验，可以省去后面的步骤)
  // 多表查询时，对order by的属性初步校验，如果不带表名则直接结束返回failure
  if(selects.relation_num > 1){
    for(size_t i = 0; i < selects.order_num; ++i){
      if(selects.orders[i].order_attr.relation_name == nullptr){
        LOG_ERROR("attribute : %s does not have relation name with it!", selects.orders[i].order_attr.attribute_name);
        end_trx_if_need(session, trx, false);
        return RC::SCHEMA_TABLE_LOST;
      }
    }
  }

  // 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
  std::vector<SelectExeNode *> select_nodes;

  // 针对关系数组里的每张表，分别取出属性列表里要查询的属性
  // 对于每张表分别生成执行节点，判断
  for (size_t i = 0; i < selects.relation_num; i++) {
    const char *table_name = selects.relations[i];
    SelectExeNode *select_node = new SelectExeNode;

    rc = create_selection_executor(trx, selects, db, table_name, *select_node);

    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    }
    select_nodes.push_back(select_node);
  }

  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    end_trx_if_need(session, trx, false);
    return RC::SQL_SYNTAX;
  }

  std::vector<TupleSet> tuple_sets;
  for (SelectExeNode *&node: select_nodes) {
    TupleSet tuple_set;
    rc = node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }

  if (tuple_sets.size() > 1) {
    // 本次查询了多张表，需要做join操作

    // tuple set的顺序与select节点relations的表顺序对应，但要保证返回结果是与属性顺序相对应
    // 将tuple进行笛卡尔积连接
    TupleSet &tupleset_join = tuple_sets.back();

    unordered_map<string, pair<int,int>> table_to_valuepos;
    table_to_valuepos.insert({tupleset_join.get_schema().field(0).table_name(), pair<int,int>{0,tupleset_join.get_schema().field_size()}});
    rc = cartesian(tuple_sets, tupleset_join, tuple_sets.size()-2, selects, table_to_valuepos);

    if(rc != RC::SUCCESS){
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      session_event->set_response(ss.str());
      end_trx_if_need(session, trx, true);
      return rc;
    }
    
    // 对tuple set按照order list排序
    // 注意校验合法性
    // 仍需判断是否为聚合函数计算，是则不需要排序操作，即order by无效
    vector<int> pos_to_sortfunc(tupleset_join.size());
    for(int i = 0; i < tupleset_join.size(); ++i)
      pos_to_sortfunc[i] = i;

    if(selects.order_num > 0){
      rc = sort_tuple_sets(selects, tupleset_join, pos_to_sortfunc);
      if(rc != RC::SUCCESS){
        for (SelectExeNode *& tmp_node: select_nodes) {
          delete tmp_node;
        }
        session_event->set_response(ss.str());
        end_trx_if_need(session, trx, true);
        return rc;
      }
    }

    // 打印结果思路：
    // unordered_map中存储了表名与涉及到的字段在连接表中的下标对应关系，分别在select attr_list from中的attrlist在连接表中做投影，然后输出结果
    tupleset_join.print_for_join(selects, ss, table_to_valuepos,pos_to_sortfunc);

  } else {
    // 对tuple排序
    // 注意校验合法性
    vector<int> pos_to_sortfunc(tuple_sets.front().size());
    for(int i = 0; i < tuple_sets.front().size(); ++i)
      pos_to_sortfunc[i] = i;
    if(selects.order_num > 0){
      rc = sort_tuple_sets(selects, tuple_sets.front(), pos_to_sortfunc);
      if(rc != RC::SUCCESS){
        for (SelectExeNode *& tmp_node: select_nodes) {
          delete tmp_node;
        }
        session_event->set_response(ss.str());
        end_trx_if_need(session, trx, true);
        return rc;
      }
    }

    // 当前只查询一张表，直接返回结果即可
    tuple_sets.front().print(selects,ss,pos_to_sortfunc);
  }

  for (SelectExeNode *& tmp_node: select_nodes) {
    delete tmp_node;
  }
  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
  return rc;
}

RC sort_tuple_sets(const Selects &selects, TupleSet &tuple_set, vector<int> &pos_to_sortfunc){
  int order_num = selects.order_num;
  int tuple_num = tuple_set.size();

  // 校验，1、单标查询、多表排序，2、多表查询，排序不带表名，3、多表查询，排序出现非这些表中的表名，
  // 排序优先按照排序列表中第一个规则排，然后依次遵循后续规则
  // 但order list的顺序是倒序的，所以仍然从头开始排序等于先按后续规则排完倒着排到第一条规则
  TupleSchema tup_schema = tuple_set.get_schema();
  for(int i = 0; i < order_num; ++i){
    int field_index = 0;
    for(; field_index < tup_schema.field_size(); ++field_index){
      if((selects.orders[i].order_attr.relation_name == nullptr && strcmp(selects.orders[i].order_attr.attribute_name,tup_schema.field(field_index).field_name()) == 0)
        || (strcmp(selects.orders[i].order_attr.relation_name,tup_schema.field(field_index).table_name()) == 0 && strcmp(selects.orders[i].order_attr.attribute_name,tup_schema.field(field_index).field_name()) == 0)){
          break;
        }
    }
    if(field_index == tup_schema.field_size()){
      LOG_ERROR("%s %s not exist in table you select", selects.orders[i].order_attr.relation_name,selects.orders[i].order_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }

    // 直接对整个tuple set进行排序的话如果tuple set有很多个元组，对二维vector排序会产生大量
    // 时间空间开销，因此选择对一个下标对应数组排序，需要相应修改tuple print函数的输出方式
    if(selects.orders[i].order_type == 0){
      // asc 递增打印
      sort(pos_to_sortfunc.begin(), pos_to_sortfunc.end(), [&](int a, int b){
        return tuple_set.get(a).get(field_index).compare(tuple_set.get(b).get(field_index)) < 0;
      });
    }else{
      // desc 递减打印
      sort(pos_to_sortfunc.begin(), pos_to_sortfunc.end(), [&](int a, int b){
        return tuple_set.get(a).get(field_index).compare(tuple_set.get(b).get(field_index)) > 0;
      });
    }
  }
  return RC::SUCCESS;
}

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema) {
  const FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }

  schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
  return RC::SUCCESS;
}

// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node) {
  // 列出跟这张表关联的Attr
  TupleSchema schema;

  // 校验表是否存在
  Table * table = DefaultHandler::get_default().find_table(db, table_name);
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", table_name, db);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // 标记位，标记是否存在这张表中待查询的属性，因为有这样的查询 select t1.* from t1, t2;
  bool flag_exist_attr = false;

  /*
  * !!! 注意这个循环是从后往前
  * 
  * 遍历select节点中的所有
  */
  for (int i = selects.attr_num - 1; i >= 0; i--) {

    // 校验属性列表中的每个
    const RelAttr &attr = selects.attributes[i];

    // 单表情况或者多表的select *-----------是当前表的属性情况
    if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
      flag_exist_attr = true;
      // 对于select * from table 、 select count(1) from table 、 select count(*) from table 、 select table.* from
      if (0 == strcmp("*", attr.attribute_name) || (attr.attribute_name == nullptr && (selects.aggre_type[i] >= COUNT_F && selects.aggre_type[i] <= COUNT_NUM_F))) {

        // 若是聚合函数运算将对应属性下标与聚类类型对应
        // 此处仍需要修改，多表聚合函数对应存在问题
        schema.aggtype_pos.push_back({schema.field_size() ,selects.aggre_type[i]});

        // 列出这张表所有字段
        TupleSchema::from_table(table, schema);

        if(selects.aggre_type[i] == NOTAGG)
          break; // 没有校验，给出* 之后，再写字段的错误

      } else {
        // select tabel.attr from, select table1.attr from t1,t2

        // 校验是否为多表查询，多表查询不能不带表名
        if(selects.relation_num > 1 && nullptr == attr.relation_name){
          LOG_ERROR("attribute : %s does not have relation name with it!", attr.attribute_name);
          return RC::SCHEMA_TABLE_LOST;
        }


        // 为了聚合函数的实现
        // 此实现存在小问题：检查当前属性是否存在过 检查了两次，一次在下方，第二次在schema_add_field函数中，但数组很小，check double的代价不大
        // 标记当前聚合字段查询的属性是否已经被scan过了，如果scan过则将其在tuplefield数组中的下标与聚合类型相对应
        bool if_exist = false;

        if(selects.aggre_type[0] != NOTAGG){
    
          for(int j = 0; j < schema.field_size(); ++j){
            const TupleField &f = schema.field(j);
            if (0 == strcmp(f.table_name(), table_name) &&
                0 == strcmp(f.field_name(), attr.attribute_name)) {
              schema.aggtype_pos.push_back({j,selects.aggre_type[i]});
              if_exist = true;
            }
          }
        }

        // 如果第一次出现则将此字段下标与聚合函数类型对应
        if(!if_exist)
          schema.aggtype_pos.push_back({schema.field_size(),selects.aggre_type[i]});

        // 列出这张表相关字段
        RC rc = schema_add_field(table, attr.attribute_name, schema);
        if (rc != RC::SUCCESS) {
          return rc;
        }
        
      }
    }
  }

  if(!flag_exist_attr){
    // 如果有在from后涉及到的表但在选择属性中并未出现这张表的字段，为了做笛卡尔积也需要列出这张表所有字段
    TupleSchema::from_table(table, schema);
  }

  // 排序列表中 出现的属性字段也需要选择出来
  for(size_t i = 0; i < selects.order_num; ++i){
    if(match_table(selects,selects.orders[i].order_attr.relation_name ,table_name)){
      RC rc = schema_add_field(table, selects.orders[i].order_attr.attribute_name, schema);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
  }

  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  // 对于多表查询来讲还需要判断涉及两个表的过滤条件，这个需要在生成tuple set做笛卡尔积运算的时候完成
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];

    // 校验多表查询condition不带表名
    if(selects.relation_num > 1){
      if((condition.left_is_attr == 1 && condition.left_attr.relation_name == nullptr)
        || (condition.right_is_attr == 1 && condition.right_attr.relation_name == nullptr)){
          // 如果左边是属性名或者右边是属性名但对应relattr对象中的表名为空（没带表名） ，返回sql错误
          for (DefaultConditionFilter * &filter : condition_filters) {
            delete filter;
          }
          return RC::SQL_SYNTAX;
        }
    }

    // 如果有多表两边都是属性的判断条件也需要将这张表内涉及到判断的字段取出
    if(condition.left_is_attr == 1 && condition.right_is_attr == 1){
      if(match_table(selects, condition.left_attr.relation_name, table_name) && !match_table(selects, condition.right_attr.relation_name, table_name)){
        RC rc = schema_add_field(table, condition.left_attr.attribute_name, schema);
        if (rc != RC::SUCCESS) {
          return rc;
        }

      }else if(match_table(selects, condition.right_attr.relation_name, table_name) && !match_table(selects, condition.left_attr.relation_name, table_name)){
        RC rc = schema_add_field(table, condition.right_attr.attribute_name, schema);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
    }

    if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // 两边都是值
        (condition.left_is_attr == 1 && condition.right_is_attr == 0 && match_table(selects, condition.left_attr.relation_name, table_name)) ||  // 左边是属性右边是值
        (condition.left_is_attr == 0 && condition.right_is_attr == 1 && match_table(selects, condition.right_attr.relation_name, table_name)) ||  // 左边是值，右边是属性名
        (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
            match_table(selects, condition.left_attr.relation_name, table_name) && match_table(selects, condition.right_attr.relation_name, table_name)) // 左右都是属性名，并且表名都符合
        ) {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      RC rc = condition_filter->init(*table, condition);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    }
  }

  return select_node.init(trx, table, std::move(schema), std::move(condition_filters));
}