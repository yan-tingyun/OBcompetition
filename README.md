# OBcompetition
OceanBase数据库大赛参赛代码

赛事介绍：https://open.oceanbase.com/competition/index

赛题介绍：https://oceanbase-partner.github.io/lectures-on-dbms-implementation/miniob-topics

miniob基础数据库：https://github.com/oceanbase/miniob

最低环境配置：

项目为linux下的c++项目，cmake 3.14, c++14, flex 2.5.35（其他版本会报错）, bison 3.7

How to build:https://github.com/oceanbase/miniob/blob/main/docs/how_to_build.md


## 已完成
项目实现基本的数据库功能模块及部分查询操作，基础事务操作，支持五种数据类型（整数、浮点数、字符串、日期类型及超长文本(4096B)),支持字段为空


## 待实现
增加查询重写功能，优化重写sql

增加查询缓存功能，将频繁查询的表或sql语句及查询结果缓存至内存中，提高查询速度

实现复杂子查询，多层select from where嵌套的查询

查询优化，优化调整连接顺序
