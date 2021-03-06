
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  size_t record_num;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
  CompOp sub_comp;
	char id[MAX_NUM];

  Selects simple_sub_query;		
  Condition sub_query_conditions[MAX_NUM];
  size_t sub_query_condition_length;
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->record_num = 0;
  context->sub_query_condition_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  context->ssql->sstr.insertion.record_num = 0;
  context->ssql->sstr.selection.order_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
		DATE_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EQ
        LT
        GT
        LE
        GE
        NE
		MAX
		MIN
		COUNT
		AVG
		INNER
		JOIN
		ORDER
		BY
		ASC
		GROUP
		UNIQUE
		NOT
		NULL_T
		NULLABLE
		IS
		TEXT_T
		IN

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V
//非终结符

%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <number> number;

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index	
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5, $7, 0);
			RelAttr attr;
			relation_attr_init(&attr, NULL, $7);
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, &attr);
		}
	| CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
		CONTEXT->ssql->sstr.create_index.attr_num = 1;
		create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6, $8, 1);
	}
    ;

index_attr_list:
	/*empty*/
	| COMMA ID index_attr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $2);
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, &attr);
	}
	;

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE 
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
    |ID_get type
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
	|ID_get type NOT NULL_T
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
	|ID_get type NULLABLE
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
    ;
number:
		NUMBER {$$ = $1;}
		;
type:
	INT_T { $$=INTS; }
       | STRING_T { $$=CHARS; }
       | FLOAT_T { $$=FLOATS; }
	   | DATE_T { $$=DATES; }
	   | TEXT_T { $$=TEXTS; }
       ;
ID_get:
	ID 
	{
		char *temp=$1; 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;

	
insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES record record_list SEMICOLON 
		{
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->values, CONTEXT->value_length);

      //临时变量清零
      CONTEXT->value_length=0;
	  CONTEXT->record_num = 0;
    }	
	;
record_list:
	/* empty */
	| COMMA record record_list {

	}
	;
record:
	LBRACE value value_list RBRACE{
		inserts_record_length(&CONTEXT->ssql->sstr.insertion, CONTEXT->record_num, CONTEXT->value_length);
		CONTEXT->record_num++;
	}
	;
value_list:
    /* empty */
    | COMMA value value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
    ;
value:
    NUMBER{	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |FLOAT{
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |SSS {
			$1 = substr($1,1,strlen($1)-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    | NULL_T {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
	;
    
delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
    ;
update:			/*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
    ;


select:				/*  select 语句的语法解析树*/
    SELECT select_attr FROM ID rel_list where group_by order_by SEMICOLON
		{
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, $4);

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
/* author yty 21-11-9 implement of inner join function */
	| SELECT select_attr FROM ID INNER JOIN ID ON inner_on inner_join_list where group_by order_by SEMICOLON {
		// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
		selects_append_relation(&CONTEXT->ssql->sstr.selection, $7);
		selects_append_relation(&CONTEXT->ssql->sstr.selection, $4);

		selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

		CONTEXT->ssql->flag=SCF_SELECT;//"select";
		// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

		//临时变量清零
		CONTEXT->condition_length=0;
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		CONTEXT->value_length = 0;
	}
	;

/* author yty 21/11/1 implement of aggregate function */
select_attr:
    STAR {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
    | ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
  	| ID DOT ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
	| ID DOT STAR attr_list{
			RelAttr attr;
			relation_attr_init(&attr, $1, "*");
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| AVG LBRACE ID RBRACE attr_list {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| AVG LBRACE ID DOT ID RBRACE attr_list {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| MAX LBRACE ID RBRACE attr_list {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| MAX LBRACE ID DOT ID RBRACE attr_list {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| MIN LBRACE ID RBRACE attr_list {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| MIN LBRACE ID DOT ID RBRACE attr_list {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COUNT LBRACE STAR RBRACE attr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COUNT LBRACE ID DOT STAR RBRACE attr_list {
		RelAttr attr;
		relation_attr_init(&attr, $3, "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COUNT LBRACE ID RBRACE attr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COUNT LBRACE ID DOT ID RBRACE attr_list {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COUNT LBRACE NUMBER RBRACE attr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, NULL);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_NUM_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
    ;
attr_list:
    /* empty */
    | COMMA ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $2);
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
    | COMMA ID DOT ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, $4);
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
	| COMMA ID DOT STAR attr_list{
			RelAttr attr;
			relation_attr_init(&attr, $2, "*");
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
  	| COMMA AVG LBRACE ID RBRACE attr_list {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, NULL, $4);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA AVG LBRACE ID DOT ID RBRACE attr_list {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, $4, $6);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA MAX LBRACE ID RBRACE attr_list {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, $4);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA MAX LBRACE ID DOT ID RBRACE attr_list {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, $4, $6);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA MIN LBRACE ID RBRACE attr_list {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, $4);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA MIN LBRACE ID DOT ID RBRACE attr_list {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, $4, $6);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA COUNT LBRACE STAR RBRACE attr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA COUNT LBRACE ID DOT STAR RBRACE attr_list {
		RelAttr attr;
		relation_attr_init(&attr, $4, "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA COUNT LBRACE ID RBRACE attr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $4);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA COUNT LBRACE ID DOT ID RBRACE attr_list {
		RelAttr attr;
		relation_attr_init(&attr, $4, $6);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA COUNT LBRACE NUMBER RBRACE attr_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, NULL);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_NUM_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
    ;
inner_join_list:
	/* empty */
	| INNER JOIN ID ON inner_on inner_join_list {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, $3);
	}
	;
inner_on:
	condition condition_list {
	
	}
	;
rel_list:
    /* empty */
    | COMMA ID rel_list {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, $2);
		  }
    ;
where:
    /* empty */ 
    | WHERE condition condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
condition_list:
    /* empty */
    | AND condition condition_list {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
condition:
    ID comOp value 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
		|value comOp value 
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
		|ID comOp ID 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
    |value comOp ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
    |ID DOT ID comOp value
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
    |value comOp ID DOT ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, $3, $5);

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
    |ID DOT ID comOp ID DOT ID
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			RelAttr right_attr;
			relation_attr_init(&right_attr, $5, $7);

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }


	/* sub query part*/
	| ID comOp sub_query {
		// where id in (sub query) / not in
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);
		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, NULL);
		condition_append_subquery(&condition,&CONTEXT->simple_sub_query,1);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| ID DOT ID comOp sub_query {
		// where table.id > < = (sub query)
		// 这种subquery只能有一行返回值
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);
		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, NULL);
		condition_append_subquery(&condition,&CONTEXT->simple_sub_query,1);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| sub_query comOp ID DOT ID {
		// where table.id > < = (sub query)
		// 这种subquery只能有一行返回值
		RelAttr right_attr;
		relation_attr_init(&right_attr, $3, $5);
		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, NULL, 1, &right_attr, NULL);
		condition_append_subquery(&condition,&CONTEXT->simple_sub_query,0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| sub_query comOp ID {
		// where table.id > < = (sub query)
		// 这种subquery只能有一行返回值
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, $3);
		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, NULL, 1, &right_attr, NULL);
		condition_append_subquery(&condition,&CONTEXT->simple_sub_query,0);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
    ;
sub_query:
	LBRACE SELECT sub_query_attr FROM ID sub_query_cond RBRACE{
		selects_append_relation(&CONTEXT->simple_sub_query, $5);
		selects_append_relation(&CONTEXT->ssql->sstr.selection, $5);
		selects_append_conditions(&CONTEXT->simple_sub_query, CONTEXT->sub_query_conditions, CONTEXT->sub_query_condition_length);
		CONTEXT->sub_query_condition_length=0;
		CONTEXT->value_length = 0;
	}
	;
sub_query_attr:
	ID {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		selects_append_aggretype(&CONTEXT->simple_sub_query, NOTAGG);
		selects_append_attribute(&CONTEXT->simple_sub_query, &attr);
	}
	| ID DOT ID {
		RelAttr attr;
		relation_attr_init(&attr, $1, $3);
		selects_append_aggretype(&CONTEXT->simple_sub_query, NOTAGG);
		selects_append_attribute(&CONTEXT->simple_sub_query, &attr);
	}
	| COUNT LBRACE STAR RBRACE {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_aggretype(&CONTEXT->simple_sub_query, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->simple_sub_query, &attr);
	} 
	| COUNT LBRACE ID RBRACE {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		selects_append_aggretype(&CONTEXT->simple_sub_query, COUNT_F);
		selects_append_attribute(&CONTEXT->simple_sub_query, &attr);
	}
	| COUNT LBRACE ID DOT ID RBRACE {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		selects_append_aggretype(&CONTEXT->simple_sub_query, COUNT_F);
		selects_append_attribute(&CONTEXT->simple_sub_query, &attr);
	} 
	| MIN LBRACE ID RBRACE {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		selects_append_aggretype(&CONTEXT->simple_sub_query, MIN_F);
		selects_append_attribute(&CONTEXT->simple_sub_query, &attr);
	}
	| MIN LBRACE ID DOT ID RBRACE {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		selects_append_aggretype(&CONTEXT->simple_sub_query, MIN_F);
		selects_append_attribute(&CONTEXT->simple_sub_query, &attr);		
	}
	| MAX LBRACE ID RBRACE {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		selects_append_aggretype(&CONTEXT->simple_sub_query, MAX_F);
		selects_append_attribute(&CONTEXT->simple_sub_query, &attr);
	}
	| MAX LBRACE ID DOT ID RBRACE {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		selects_append_aggretype(&CONTEXT->simple_sub_query, MAX_F);
		selects_append_attribute(&CONTEXT->simple_sub_query, &attr);		
	}
	| AVG LBRACE ID RBRACE {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		selects_append_aggretype(&CONTEXT->simple_sub_query, AVG_F);
		selects_append_attribute(&CONTEXT->simple_sub_query, &attr);		
	}
	| AVG LBRACE ID DOT ID RBRACE {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		selects_append_aggretype(&CONTEXT->simple_sub_query, AVG_F);
		selects_append_attribute(&CONTEXT->simple_sub_query, &attr);			
	}
	;
sub_query_cond:
	/* empty */
	| WHERE sq_cond sq_cond_list {
	}
	;
sq_cond_list:
	/* empty */
	| AND sq_cond sq_cond_list {
	}
	;
sq_cond:
	ID sub_comOp value 
	{
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);

		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->sub_comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->sub_query_conditions[CONTEXT->sub_query_condition_length++] = condition;

	}
	|value sub_comOp value 
	{
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->sub_comp, 0, NULL, left_value, 0, NULL, right_value);
		CONTEXT->sub_query_conditions[CONTEXT->sub_query_condition_length++] = condition;

	}
	|ID sub_comOp ID 
	{
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, $3);

		Condition condition;
		condition_init(&condition, CONTEXT->sub_comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->sub_query_conditions[CONTEXT->sub_query_condition_length++] = condition;

	}
    |value sub_comOp ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

			Condition condition;
			condition_init(&condition, CONTEXT->sub_comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->sub_query_conditions[CONTEXT->sub_query_condition_length++] = condition;
		
		}
    |ID DOT ID sub_comOp value
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->sub_comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->sub_query_conditions[CONTEXT->sub_query_condition_length++] = condition;		
							
    }
    |value sub_comOp ID DOT ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, $3, $5);

			Condition condition;
			condition_init(&condition, CONTEXT->sub_comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->sub_query_conditions[CONTEXT->sub_query_condition_length++] = condition;
									
    }
	;
comOp:
  	  EQ { CONTEXT->comp = EQUAL_TO; }
    | LT { CONTEXT->comp = LESS_THAN; }
    | GT { CONTEXT->comp = GREAT_THAN; }
    | LE { CONTEXT->comp = LESS_EQUAL; }
    | GE { CONTEXT->comp = GREAT_EQUAL; }
    | NE { CONTEXT->comp = NOT_EQUAL; }
	| IS { CONTEXT->comp = IS_NULL; }
	| IS NOT { CONTEXT->comp = IS_NOT_NULL; }
	| IN { CONTEXT->comp = IN_SUB_QUERY; }
	| NOT IN { CONTEXT->comp = NOT_IN_SUB_QUERY; }
    ;
sub_comOp:
  	  EQ { CONTEXT->sub_comp = EQUAL_TO; }
    | LT { CONTEXT->sub_comp = LESS_THAN; }
    | GT { CONTEXT->sub_comp = GREAT_THAN; }
    | LE { CONTEXT->sub_comp = LESS_EQUAL; }
    | GE { CONTEXT->sub_comp = GREAT_EQUAL; }
    | NE { CONTEXT->sub_comp = NOT_EQUAL; }
	| IS { CONTEXT->sub_comp = IS_NULL; }
	| IS NOT { CONTEXT->sub_comp = IS_NOT_NULL; }
	| IN { CONTEXT->sub_comp = IN_SUB_QUERY; }
	| NOT IN { CONTEXT->sub_comp = NOT_IN_SUB_QUERY; }
    ;
group_by:
	/* empty */
	| GROUP BY ID group_by_attr {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| GROUP BY ID DOT ID group_by_attr {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	;
group_by_attr:
	/* empty */
	| COMMA ID group_by_attr {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $2);
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	| COMMA ID DOT ID group_by_attr {
		RelAttr attr;
		relation_attr_init(&attr, $2, $4);
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
	;
order_by:
	/* empty */
	| ORDER BY ID order_list {
		// default asc
		// 需要校验是否为单标查询情况
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
	| ORDER BY ID DOT ID order_list {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
	| ORDER BY ID ASC order_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
	| ORDER BY ID DESC order_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $3);
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
	| ORDER BY ID DOT ID ASC order_list {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
	| ORDER BY ID DOT ID DESC order_list {
		RelAttr attr;
		relation_attr_init(&attr, $3, $5);
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
	;
order_list:
	/*empty*/
	| COMMA ID order_list{
		RelAttr attr;
		relation_attr_init(&attr, NULL, $2);
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
	| COMMA ID DOT ID order_list {
		RelAttr attr;
		relation_attr_init(&attr, $2, $4);
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
	| COMMA ID ASC order_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $2);
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
	| COMMA ID DESC order_list {
		RelAttr attr;
		relation_attr_init(&attr, NULL, $2);
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
	| COMMA ID DOT ID ASC order_list {
		RelAttr attr;
		relation_attr_init(&attr, $2, $4);
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
	| COMMA ID DOT ID DESC order_list {
		RelAttr attr;
		relation_attr_init(&attr, $2, $4);
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
	;
load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}