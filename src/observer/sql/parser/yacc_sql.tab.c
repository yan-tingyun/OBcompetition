/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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
	char id[MAX_NUM];
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


#line 132 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_DESC = 10,                      /* DESC  */
  YYSYMBOL_SHOW = 11,                      /* SHOW  */
  YYSYMBOL_SYNC = 12,                      /* SYNC  */
  YYSYMBOL_INSERT = 13,                    /* INSERT  */
  YYSYMBOL_DELETE = 14,                    /* DELETE  */
  YYSYMBOL_UPDATE = 15,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 16,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 17,                    /* RBRACE  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 19,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 20,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 21,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 22,                     /* INT_T  */
  YYSYMBOL_STRING_T = 23,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 24,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 25,                    /* DATE_T  */
  YYSYMBOL_HELP = 26,                      /* HELP  */
  YYSYMBOL_EXIT = 27,                      /* EXIT  */
  YYSYMBOL_DOT = 28,                       /* DOT  */
  YYSYMBOL_INTO = 29,                      /* INTO  */
  YYSYMBOL_VALUES = 30,                    /* VALUES  */
  YYSYMBOL_FROM = 31,                      /* FROM  */
  YYSYMBOL_WHERE = 32,                     /* WHERE  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_SET = 34,                       /* SET  */
  YYSYMBOL_ON = 35,                        /* ON  */
  YYSYMBOL_LOAD = 36,                      /* LOAD  */
  YYSYMBOL_DATA = 37,                      /* DATA  */
  YYSYMBOL_INFILE = 38,                    /* INFILE  */
  YYSYMBOL_EQ = 39,                        /* EQ  */
  YYSYMBOL_LT = 40,                        /* LT  */
  YYSYMBOL_GT = 41,                        /* GT  */
  YYSYMBOL_LE = 42,                        /* LE  */
  YYSYMBOL_GE = 43,                        /* GE  */
  YYSYMBOL_NE = 44,                        /* NE  */
  YYSYMBOL_MAX = 45,                       /* MAX  */
  YYSYMBOL_MIN = 46,                       /* MIN  */
  YYSYMBOL_COUNT = 47,                     /* COUNT  */
  YYSYMBOL_AVG = 48,                       /* AVG  */
  YYSYMBOL_INNER = 49,                     /* INNER  */
  YYSYMBOL_JOIN = 50,                      /* JOIN  */
  YYSYMBOL_ORDER = 51,                     /* ORDER  */
  YYSYMBOL_BY = 52,                        /* BY  */
  YYSYMBOL_ASC = 53,                       /* ASC  */
  YYSYMBOL_GROUP = 54,                     /* GROUP  */
  YYSYMBOL_NUMBER = 55,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 56,                     /* FLOAT  */
  YYSYMBOL_ID = 57,                        /* ID  */
  YYSYMBOL_PATH = 58,                      /* PATH  */
  YYSYMBOL_SSS = 59,                       /* SSS  */
  YYSYMBOL_STAR = 60,                      /* STAR  */
  YYSYMBOL_STRING_V = 61,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 62,                  /* $accept  */
  YYSYMBOL_commands = 63,                  /* commands  */
  YYSYMBOL_command = 64,                   /* command  */
  YYSYMBOL_exit = 65,                      /* exit  */
  YYSYMBOL_help = 66,                      /* help  */
  YYSYMBOL_sync = 67,                      /* sync  */
  YYSYMBOL_begin = 68,                     /* begin  */
  YYSYMBOL_commit = 69,                    /* commit  */
  YYSYMBOL_rollback = 70,                  /* rollback  */
  YYSYMBOL_drop_table = 71,                /* drop_table  */
  YYSYMBOL_show_tables = 72,               /* show_tables  */
  YYSYMBOL_desc_table = 73,                /* desc_table  */
  YYSYMBOL_create_index = 74,              /* create_index  */
  YYSYMBOL_drop_index = 75,                /* drop_index  */
  YYSYMBOL_create_table = 76,              /* create_table  */
  YYSYMBOL_attr_def_list = 77,             /* attr_def_list  */
  YYSYMBOL_attr_def = 78,                  /* attr_def  */
  YYSYMBOL_number = 79,                    /* number  */
  YYSYMBOL_type = 80,                      /* type  */
  YYSYMBOL_ID_get = 81,                    /* ID_get  */
  YYSYMBOL_insert = 82,                    /* insert  */
  YYSYMBOL_record_list = 83,               /* record_list  */
  YYSYMBOL_record = 84,                    /* record  */
  YYSYMBOL_value_list = 85,                /* value_list  */
  YYSYMBOL_value = 86,                     /* value  */
  YYSYMBOL_delete = 87,                    /* delete  */
  YYSYMBOL_update = 88,                    /* update  */
  YYSYMBOL_select = 89,                    /* select  */
  YYSYMBOL_select_attr = 90,               /* select_attr  */
  YYSYMBOL_attr_list = 91,                 /* attr_list  */
  YYSYMBOL_inner_join_list = 92,           /* inner_join_list  */
  YYSYMBOL_inner_on = 93,                  /* inner_on  */
  YYSYMBOL_rel_list = 94,                  /* rel_list  */
  YYSYMBOL_where = 95,                     /* where  */
  YYSYMBOL_condition_list = 96,            /* condition_list  */
  YYSYMBOL_condition = 97,                 /* condition  */
  YYSYMBOL_comOp = 98,                     /* comOp  */
  YYSYMBOL_group_by = 99,                  /* group_by  */
  YYSYMBOL_group_by_attr = 100,            /* group_by_attr  */
  YYSYMBOL_order_by = 101,                 /* order_by  */
  YYSYMBOL_order_list = 102,               /* order_list  */
  YYSYMBOL_load_data = 103                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   326

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  324

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   316


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   147,   147,   149,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   173,   178,   183,   189,   195,   201,   207,   213,   219,
     226,   234,   241,   250,   252,   256,   267,   280,   283,   284,
     285,   286,   289,   298,   315,   317,   322,   327,   329,   334,
     337,   340,   347,   357,   369,   386,   406,   412,   418,   424,
     430,   437,   444,   451,   458,   465,   472,   478,   484,   490,
     496,   503,   505,   513,   521,   527,   534,   541,   548,   555,
     562,   569,   575,   581,   587,   593,   600,   602,   607,   611,
     613,   617,   619,   623,   625,   630,   651,   671,   691,   713,
     734,   755,   777,   778,   779,   780,   781,   782,   784,   786,
     791,   797,   799,   804,   810,   812,   819,   824,   829,   834,
     839,   845,   847,   852,   857,   862,   867,   872,   879
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE",
  "MAX", "MIN", "COUNT", "AVG", "INNER", "JOIN", "ORDER", "BY", "ASC",
  "GROUP", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V",
  "$accept", "commands", "command", "exit", "help", "sync", "begin",
  "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "drop_index", "create_table", "attr_def_list",
  "attr_def", "number", "type", "ID_get", "insert", "record_list",
  "record", "value_list", "value", "delete", "update", "select",
  "select_attr", "attr_list", "inner_join_list", "inner_on", "rel_list",
  "where", "condition_list", "condition", "comOp", "group_by",
  "group_by_attr", "order_by", "order_list", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316
};
#endif

#define YYPACT_NINF (-275)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -275,   109,  -275,   125,   191,    15,   -45,    27,    36,     6,
      20,   -14,    52,    61,    73,    87,   113,    31,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,    37,    60,    68,    69,
     122,   127,   133,   144,    63,  -275,   153,   190,   193,  -275,
     143,   145,   167,  -275,  -275,  -275,  -275,  -275,   165,   188,
     170,   203,   204,   151,   152,    55,   154,    32,    46,  -275,
     155,  -275,  -275,   180,   181,   157,   156,   159,   160,  -275,
    -275,    -1,     8,   201,     9,   202,    24,   205,   206,   207,
     208,    64,   209,   209,   -11,   210,    91,   217,   186,   199,
    -275,   211,   147,   214,   209,   174,   209,   175,   209,   209,
     132,   209,   209,   176,   177,   178,    77,   179,   134,  -275,
    -275,  -275,   182,   187,   181,    85,   220,  -275,  -275,     5,
    -275,   136,   212,  -275,    85,   234,   159,   224,  -275,  -275,
    -275,  -275,   226,   189,  -275,   227,  -275,   230,  -275,  -275,
     231,   232,  -275,  -275,   233,    25,    41,   235,    56,   236,
      57,   209,   209,   225,   194,   200,   237,   210,   253,   213,
    -275,  -275,  -275,  -275,  -275,  -275,    99,   126,    91,  -275,
     181,   215,   211,   254,   216,   241,   209,   209,   209,   209,
     209,   209,   218,   209,   219,   209,   209,   138,   209,   209,
     221,  -275,  -275,  -275,   228,   222,   229,    85,   242,   220,
    -275,   136,  -275,  -275,   238,  -275,   212,   257,   258,  -275,
    -275,  -275,   245,   261,  -275,  -275,  -275,  -275,  -275,  -275,
     248,  -275,   250,  -275,  -275,   251,   252,  -275,  -275,   256,
      91,   239,   240,   274,   237,  -275,  -275,   131,   243,  -275,
    -275,  -275,  -275,  -275,   209,   209,   209,   209,   209,   244,
     212,    65,   246,  -275,  -275,   255,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,   247,   181,  -275,   249,   259,  -275,     1,
     260,   262,   200,    83,   263,   264,   265,   266,   264,  -275,
    -275,   267,   229,   268,  -275,  -275,  -275,    12,    13,  -275,
      91,   276,   263,   264,   269,   264,  -275,   264,   264,  -275,
     244,  -275,  -275,  -275,    14,  -275,  -275,  -275,  -275,   264,
     264,  -275,  -275,  -275
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,     0,     0,     0,    71,    56,     0,     0,     0,    23,
       0,     0,     0,    24,    25,    26,    22,    21,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    57,
       0,    29,    28,     0,    91,     0,     0,     0,     0,    27,
      31,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    71,    71,    71,    89,     0,     0,     0,     0,     0,
      42,    33,     0,     0,    71,     0,    71,     0,    71,    71,
       0,    71,    71,     0,     0,     0,     0,     0,     0,    72,
      58,    59,     0,     0,    91,     0,    44,    49,    50,     0,
      51,     0,    93,    52,     0,     0,     0,     0,    38,    39,
      40,    41,    36,     0,    62,     0,    64,     0,    70,    68,
       0,     0,    66,    60,     0,     0,     0,     0,     0,     0,
       0,    71,    71,    89,     0,   108,    47,     0,     0,     0,
     102,   103,   104,   105,   106,   107,     0,     0,     0,    92,
      91,     0,    33,     0,     0,     0,    71,    71,    71,    71,
      71,    71,     0,    71,     0,    71,    71,     0,    71,    71,
       0,    73,    74,    90,     0,     0,   114,     0,     0,    44,
      43,     0,    97,    95,    98,    96,    93,     0,     0,    34,
      32,    37,     0,     0,    63,    65,    69,    67,    61,    77,
       0,    79,     0,    85,    83,     0,     0,    81,    75,     0,
       0,     0,     0,     0,    47,    46,    45,     0,     0,    94,
      53,   128,    35,    30,    71,    71,    71,    71,    71,    86,
      93,   111,     0,    54,    48,     0,    99,   100,    78,    80,
      84,    82,    76,     0,    91,    88,     0,     0,   109,   121,
       0,     0,   108,   111,   111,   121,     0,     0,   121,   115,
     101,     0,   114,     0,   112,   110,   118,   121,   121,   117,
       0,     0,   111,   121,     0,   121,   122,   121,   121,   116,
      86,    55,   113,   125,   121,   124,   120,   119,    87,   121,
     121,   123,   127,   126
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,   102,   149,  -275,  -275,  -275,
    -275,    78,   119,    44,  -120,  -275,  -275,  -275,  -275,   -91,
     -21,   -10,   128,  -121,  -210,   -92,  -123,    16,  -274,     2,
    -146,  -275
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,   137,   101,   222,   142,   102,
      31,   168,   126,   208,   131,    32,    33,    34,    46,    69,
     274,   259,   124,    97,   179,   260,   176,   206,   278,   243,
     289,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     119,   120,   121,   165,   132,   166,   249,   122,   177,   294,
     295,   285,    47,   144,   180,   146,   104,   148,   149,   286,
     152,   153,   303,   307,   319,   106,   109,   105,   312,   287,
     286,   286,   286,   169,    48,    50,   107,   110,   123,    49,
     304,   112,   191,    52,   170,   171,   172,   173,   174,   175,
     275,    51,   113,   192,   288,    53,   213,   215,   193,   217,
      40,    41,    42,    43,    54,   305,   308,   320,    58,   194,
     201,   202,    44,   196,   199,    45,    55,    87,    88,    89,
      90,    67,    67,   276,   197,   200,   216,   244,   247,    91,
      56,    68,   118,   277,    59,   224,   225,   226,   227,   228,
     229,   276,   231,    92,   233,   234,    93,   237,   238,     2,
      83,   293,    84,     3,     4,    85,    57,    60,     5,     6,
       7,     8,     9,    10,    11,    61,    62,   266,    12,    13,
      14,    36,   157,    37,   158,    15,    16,   159,    63,   296,
     127,   128,   299,    64,   130,    17,   127,   128,   129,    65,
     130,   306,   309,   282,   127,   128,   212,   313,   130,   315,
      66,   316,   317,   268,   269,   270,   271,   272,   321,   138,
     139,   140,   141,   322,   323,   170,   171,   172,   173,   174,
     175,   127,   128,   214,    70,   130,   127,   128,   265,   150,
     130,   161,   151,    71,   162,   235,    72,    38,   236,    39,
      73,    75,    74,    76,    77,    78,    79,    80,    81,    82,
      95,    86,    94,    96,    98,    99,   100,   103,   108,   111,
     133,   114,   115,   116,   117,   134,   125,    67,   135,   136,
     143,   145,   147,   154,   155,   156,   160,   164,   167,   163,
     181,   183,   184,   122,   186,   178,   185,   187,   188,   189,
     190,   204,   195,   198,   205,   207,   210,   220,   223,   245,
     250,   251,   252,   240,   253,   254,   248,   255,   256,   257,
     211,   221,   218,   258,   241,   230,   232,   263,   239,   311,
     242,   276,   286,   280,   219,   182,   209,   246,   264,   318,
     310,   203,   262,   273,   301,     0,   261,   281,   292,     0,
     267,     0,   300,   279,     0,     0,   283,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   284,   290,     0,   291,
       0,     0,   297,   298,     0,   302,   314
};

static const yytype_int16 yycheck[] =
{
      91,    92,    93,   124,    96,   125,   216,    18,   131,   283,
     284,    10,    57,   104,   134,   106,    17,   108,   109,    18,
     111,   112,    10,    10,    10,    17,    17,    28,   302,    28,
      18,    18,    18,    28,     7,    29,    28,    28,    49,     3,
      28,    17,    17,    57,    39,    40,    41,    42,    43,    44,
     260,    31,    28,    28,    53,     3,   176,   177,    17,   180,
      45,    46,    47,    48,     3,    53,    53,    53,    37,    28,
     161,   162,    57,    17,    17,    60,     3,    45,    46,    47,
      48,    18,    18,    18,    28,    28,   178,   207,   211,    57,
       3,    28,    28,    28,    57,   186,   187,   188,   189,   190,
     191,    18,   193,    57,   195,   196,    60,   198,   199,     0,
      55,    28,    57,     4,     5,    60,     3,    57,     9,    10,
      11,    12,    13,    14,    15,    57,    57,   247,    19,    20,
      21,     6,    55,     8,    57,    26,    27,    60,    16,   285,
      55,    56,   288,    16,    59,    36,    55,    56,    57,    16,
      59,   297,   298,   274,    55,    56,    57,   303,    59,   305,
      16,   307,   308,   254,   255,   256,   257,   258,   314,    22,
      23,    24,    25,   319,   320,    39,    40,    41,    42,    43,
      44,    55,    56,    57,    31,    59,    55,    56,    57,    57,
      59,    57,    60,     3,    60,    57,     3,     6,    60,     8,
      57,    34,    57,    38,    16,    35,     3,     3,    57,    57,
      30,    57,    57,    32,    57,    59,    57,    57,    17,    17,
       3,    16,    16,    16,    16,    39,    16,    18,    29,    18,
      16,    57,    57,    57,    57,    57,    57,    50,    18,    57,
       6,    17,    16,    18,    17,    33,    57,    17,    17,    17,
      17,    57,    17,    17,    54,    18,     3,     3,    17,    17,
       3,     3,    17,    35,     3,    17,    28,    17,    17,    17,
      57,    55,    57,    17,    52,    57,    57,     3,    57,     3,
      51,    18,    18,    28,   182,   136,   167,   209,   244,   310,
     300,   163,    52,    49,   292,    -1,    57,    50,   282,    -1,
      57,    -1,    35,    57,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    57,    57,    -1,    57,
      -1,    -1,    57,    57,    -1,    57,    57
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    63,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    36,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    82,    87,    88,    89,   103,     6,     8,     6,     8,
      45,    46,    47,    48,    57,    60,    90,    57,     7,     3,
      29,    31,    57,     3,     3,     3,     3,     3,    37,    57,
      57,    57,    57,    16,    16,    16,    16,    18,    28,    91,
      31,     3,     3,    57,    57,    34,    38,    16,    35,     3,
       3,    57,    57,    55,    57,    60,    57,    45,    46,    47,
      48,    57,    57,    60,    57,    30,    32,    95,    57,    59,
      57,    78,    81,    57,    17,    28,    17,    28,    17,    17,
      28,    17,    17,    28,    16,    16,    16,    16,    28,    91,
      91,    91,    18,    49,    94,    16,    84,    55,    56,    57,
      59,    86,    97,     3,    39,    29,    18,    77,    22,    23,
      24,    25,    80,    16,    91,    57,    91,    57,    91,    91,
      57,    60,    91,    91,    57,    57,    57,    55,    57,    60,
      57,    57,    60,    57,    50,    95,    86,    18,    83,    28,
      39,    40,    41,    42,    43,    44,    98,    98,    33,    96,
      86,     6,    78,    17,    16,    57,    17,    17,    17,    17,
      17,    17,    28,    17,    28,    17,    17,    28,    17,    17,
      28,    91,    91,    94,    57,    54,    99,    18,    85,    84,
       3,    57,    57,    86,    57,    86,    97,    95,    57,    77,
       3,    55,    79,    17,    91,    91,    91,    91,    91,    91,
      57,    91,    57,    91,    91,    57,    60,    91,    91,    57,
      35,    52,    51,   101,    86,    17,    83,    98,    28,    96,
       3,     3,    17,     3,    17,    17,    17,    17,    17,    93,
      97,    57,    52,     3,    85,    57,    86,    57,    91,    91,
      91,    91,    91,    49,    92,    96,    18,    28,   100,    57,
      28,    50,    95,    57,    57,    10,    18,    28,    53,   102,
      57,    57,    99,    28,   100,   100,   102,    57,    57,   102,
      35,   101,    57,    10,    28,    53,   102,    10,    53,   102,
      93,     3,   100,   102,    57,   102,   102,   102,    92,    10,
      53,   102,   102,   102
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    63,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    77,    78,    78,    79,    80,    80,
      80,    80,    81,    82,    83,    83,    84,    85,    85,    86,
      86,    86,    87,    88,    89,    89,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    92,    92,    93,    94,
      94,    95,    95,    96,    96,    97,    97,    97,    97,    97,
      97,    97,    98,    98,    98,    98,    98,    98,    99,    99,
      99,   100,   100,   100,   101,   101,   101,   101,   101,   101,
     101,   102,   102,   102,   102,   102,   102,   102,   103
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,     4,     8,     0,     3,     5,     2,     1,     1,     1,
       1,     1,     1,     7,     0,     3,     4,     0,     3,     1,
       1,     1,     5,     8,     9,    14,     1,     2,     4,     4,
       5,     7,     5,     7,     5,     7,     5,     7,     5,     7,
       5,     0,     3,     5,     5,     6,     8,     6,     8,     6,
       8,     6,     8,     6,     8,     6,     0,     6,     2,     0,
       3,     0,     3,     0,     3,     3,     3,     3,     3,     5,
       5,     7,     1,     1,     1,     1,     1,     1,     0,     4,
       6,     0,     3,     5,     0,     4,     6,     5,     5,     7,
       7,     0,     3,     5,     4,     4,     6,     6,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 21: /* exit: EXIT SEMICOLON  */
#line 173 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1443 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 178 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1451 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 183 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1459 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 189 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1467 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 195 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1475 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 201 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1483 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 207 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1492 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 213 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1500 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 219 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1509 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 227 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1518 "yacc_sql.tab.c"
    break;

  case 31: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 235 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1527 "yacc_sql.tab.c"
    break;

  case 32: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 242 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1539 "yacc_sql.tab.c"
    break;

  case 34: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 252 "yacc_sql.y"
                                   {    }
#line 1545 "yacc_sql.tab.c"
    break;

  case 35: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 257 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1560 "yacc_sql.tab.c"
    break;

  case 36: /* attr_def: ID_get type  */
#line 268 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1575 "yacc_sql.tab.c"
    break;

  case 37: /* number: NUMBER  */
#line 280 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1581 "yacc_sql.tab.c"
    break;

  case 38: /* type: INT_T  */
#line 283 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1587 "yacc_sql.tab.c"
    break;

  case 39: /* type: STRING_T  */
#line 284 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1593 "yacc_sql.tab.c"
    break;

  case 40: /* type: FLOAT_T  */
#line 285 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1599 "yacc_sql.tab.c"
    break;

  case 41: /* type: DATE_T  */
#line 286 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1605 "yacc_sql.tab.c"
    break;

  case 42: /* ID_get: ID  */
#line 290 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1614 "yacc_sql.tab.c"
    break;

  case 43: /* insert: INSERT INTO ID VALUES record record_list SEMICOLON  */
#line 299 "yacc_sql.y"
                {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string), CONTEXT->values, CONTEXT->value_length);

      //临时变量清零
      CONTEXT->value_length=0;
	  CONTEXT->record_num = 0;
    }
#line 1634 "yacc_sql.tab.c"
    break;

  case 45: /* record_list: COMMA record record_list  */
#line 317 "yacc_sql.y"
                                   {

	}
#line 1642 "yacc_sql.tab.c"
    break;

  case 46: /* record: LBRACE value value_list RBRACE  */
#line 322 "yacc_sql.y"
                                      {
		inserts_record_length(&CONTEXT->ssql->sstr.insertion, CONTEXT->record_num, CONTEXT->value_length);
		CONTEXT->record_num++;
	}
#line 1651 "yacc_sql.tab.c"
    break;

  case 48: /* value_list: COMMA value value_list  */
#line 329 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1659 "yacc_sql.tab.c"
    break;

  case 49: /* value: NUMBER  */
#line 334 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1667 "yacc_sql.tab.c"
    break;

  case 50: /* value: FLOAT  */
#line 337 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1675 "yacc_sql.tab.c"
    break;

  case 51: /* value: SSS  */
#line 340 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1684 "yacc_sql.tab.c"
    break;

  case 52: /* delete: DELETE FROM ID where SEMICOLON  */
#line 348 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1696 "yacc_sql.tab.c"
    break;

  case 53: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 358 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1708 "yacc_sql.tab.c"
    break;

  case 54: /* select: SELECT select_attr FROM ID rel_list where group_by order_by SEMICOLON  */
#line 370 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 1728 "yacc_sql.tab.c"
    break;

  case 55: /* select: SELECT select_attr FROM ID INNER JOIN ID ON inner_on inner_join_list where group_by order_by SEMICOLON  */
#line 386 "yacc_sql.y"
                                                                                                                 {
		// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-7].string));
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-10].string));

		selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

		CONTEXT->ssql->flag=SCF_SELECT;//"select";
		// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

		//临时变量清零
		CONTEXT->condition_length=0;
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		CONTEXT->value_length = 0;
	}
#line 1749 "yacc_sql.tab.c"
    break;

  case 56: /* select_attr: STAR  */
#line 406 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1760 "yacc_sql.tab.c"
    break;

  case 57: /* select_attr: ID attr_list  */
#line 412 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1771 "yacc_sql.tab.c"
    break;

  case 58: /* select_attr: ID DOT ID attr_list  */
#line 418 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1782 "yacc_sql.tab.c"
    break;

  case 59: /* select_attr: ID DOT STAR attr_list  */
#line 424 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1793 "yacc_sql.tab.c"
    break;

  case 60: /* select_attr: AVG LBRACE ID RBRACE attr_list  */
#line 430 "yacc_sql.y"
                                         {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1805 "yacc_sql.tab.c"
    break;

  case 61: /* select_attr: AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 437 "yacc_sql.y"
                                                {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1817 "yacc_sql.tab.c"
    break;

  case 62: /* select_attr: MAX LBRACE ID RBRACE attr_list  */
#line 444 "yacc_sql.y"
                                         {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1829 "yacc_sql.tab.c"
    break;

  case 63: /* select_attr: MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 451 "yacc_sql.y"
                                                {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1841 "yacc_sql.tab.c"
    break;

  case 64: /* select_attr: MIN LBRACE ID RBRACE attr_list  */
#line 458 "yacc_sql.y"
                                         {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1853 "yacc_sql.tab.c"
    break;

  case 65: /* select_attr: MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 465 "yacc_sql.y"
                                                {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1865 "yacc_sql.tab.c"
    break;

  case 66: /* select_attr: COUNT LBRACE STAR RBRACE attr_list  */
#line 472 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1876 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr: COUNT LBRACE ID DOT STAR RBRACE attr_list  */
#line 478 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1887 "yacc_sql.tab.c"
    break;

  case 68: /* select_attr: COUNT LBRACE ID RBRACE attr_list  */
#line 484 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1898 "yacc_sql.tab.c"
    break;

  case 69: /* select_attr: COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 490 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1909 "yacc_sql.tab.c"
    break;

  case 70: /* select_attr: COUNT LBRACE NUMBER RBRACE attr_list  */
#line 496 "yacc_sql.y"
                                               {
		RelAttr attr;
		relation_attr_init(&attr, NULL, NULL);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_NUM_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1920 "yacc_sql.tab.c"
    break;

  case 72: /* attr_list: COMMA ID attr_list  */
#line 505 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1933 "yacc_sql.tab.c"
    break;

  case 73: /* attr_list: COMMA ID DOT ID attr_list  */
#line 513 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1946 "yacc_sql.tab.c"
    break;

  case 74: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 521 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1957 "yacc_sql.tab.c"
    break;

  case 75: /* attr_list: COMMA AVG LBRACE ID RBRACE attr_list  */
#line 527 "yacc_sql.y"
                                               {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1969 "yacc_sql.tab.c"
    break;

  case 76: /* attr_list: COMMA AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 534 "yacc_sql.y"
                                                      {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1981 "yacc_sql.tab.c"
    break;

  case 77: /* attr_list: COMMA MAX LBRACE ID RBRACE attr_list  */
#line 541 "yacc_sql.y"
                                               {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1993 "yacc_sql.tab.c"
    break;

  case 78: /* attr_list: COMMA MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 548 "yacc_sql.y"
                                                      {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2005 "yacc_sql.tab.c"
    break;

  case 79: /* attr_list: COMMA MIN LBRACE ID RBRACE attr_list  */
#line 555 "yacc_sql.y"
                                               {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2017 "yacc_sql.tab.c"
    break;

  case 80: /* attr_list: COMMA MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 562 "yacc_sql.y"
                                                      {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2029 "yacc_sql.tab.c"
    break;

  case 81: /* attr_list: COMMA COUNT LBRACE STAR RBRACE attr_list  */
#line 569 "yacc_sql.y"
                                                   {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2040 "yacc_sql.tab.c"
    break;

  case 82: /* attr_list: COMMA COUNT LBRACE ID DOT STAR RBRACE attr_list  */
#line 575 "yacc_sql.y"
                                                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2051 "yacc_sql.tab.c"
    break;

  case 83: /* attr_list: COMMA COUNT LBRACE ID RBRACE attr_list  */
#line 581 "yacc_sql.y"
                                                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2062 "yacc_sql.tab.c"
    break;

  case 84: /* attr_list: COMMA COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 587 "yacc_sql.y"
                                                        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2073 "yacc_sql.tab.c"
    break;

  case 85: /* attr_list: COMMA COUNT LBRACE NUMBER RBRACE attr_list  */
#line 593 "yacc_sql.y"
                                                     {
		RelAttr attr;
		relation_attr_init(&attr, NULL, NULL);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_NUM_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2084 "yacc_sql.tab.c"
    break;

  case 87: /* inner_join_list: INNER JOIN ID ON inner_on inner_join_list  */
#line 602 "yacc_sql.y"
                                                    {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));
	}
#line 2092 "yacc_sql.tab.c"
    break;

  case 88: /* inner_on: condition condition_list  */
#line 607 "yacc_sql.y"
                                 {
	
	}
#line 2100 "yacc_sql.tab.c"
    break;

  case 90: /* rel_list: COMMA ID rel_list  */
#line 613 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2108 "yacc_sql.tab.c"
    break;

  case 92: /* where: WHERE condition condition_list  */
#line 619 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2116 "yacc_sql.tab.c"
    break;

  case 94: /* condition_list: AND condition condition_list  */
#line 625 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2124 "yacc_sql.tab.c"
    break;

  case 95: /* condition: ID comOp value  */
#line 631 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

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
#line 2149 "yacc_sql.tab.c"
    break;

  case 96: /* condition: value comOp value  */
#line 652 "yacc_sql.y"
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
#line 2173 "yacc_sql.tab.c"
    break;

  case 97: /* condition: ID comOp ID  */
#line 672 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

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
#line 2197 "yacc_sql.tab.c"
    break;

  case 98: /* condition: value comOp ID  */
#line 692 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

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
#line 2223 "yacc_sql.tab.c"
    break;

  case 99: /* condition: ID DOT ID comOp value  */
#line 714 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
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
#line 2248 "yacc_sql.tab.c"
    break;

  case 100: /* condition: value comOp ID DOT ID  */
#line 735 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

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
#line 2273 "yacc_sql.tab.c"
    break;

  case 101: /* condition: ID DOT ID comOp ID DOT ID  */
#line 756 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

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
#line 2296 "yacc_sql.tab.c"
    break;

  case 102: /* comOp: EQ  */
#line 777 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2302 "yacc_sql.tab.c"
    break;

  case 103: /* comOp: LT  */
#line 778 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2308 "yacc_sql.tab.c"
    break;

  case 104: /* comOp: GT  */
#line 779 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2314 "yacc_sql.tab.c"
    break;

  case 105: /* comOp: LE  */
#line 780 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2320 "yacc_sql.tab.c"
    break;

  case 106: /* comOp: GE  */
#line 781 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2326 "yacc_sql.tab.c"
    break;

  case 107: /* comOp: NE  */
#line 782 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2332 "yacc_sql.tab.c"
    break;

  case 109: /* group_by: GROUP BY ID group_by_attr  */
#line 786 "yacc_sql.y"
                                    {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2342 "yacc_sql.tab.c"
    break;

  case 110: /* group_by: GROUP BY ID DOT ID group_by_attr  */
#line 791 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2352 "yacc_sql.tab.c"
    break;

  case 112: /* group_by_attr: COMMA ID group_by_attr  */
#line 799 "yacc_sql.y"
                                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2362 "yacc_sql.tab.c"
    break;

  case 113: /* group_by_attr: COMMA ID DOT ID group_by_attr  */
#line 804 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2372 "yacc_sql.tab.c"
    break;

  case 115: /* order_by: ORDER BY ID order_list  */
#line 812 "yacc_sql.y"
                                 {
		// default asc
		// 需要校验是否为单标查询情况
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2384 "yacc_sql.tab.c"
    break;

  case 116: /* order_by: ORDER BY ID DOT ID order_list  */
#line 819 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2394 "yacc_sql.tab.c"
    break;

  case 117: /* order_by: ORDER BY ID ASC order_list  */
#line 824 "yacc_sql.y"
                                     {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2404 "yacc_sql.tab.c"
    break;

  case 118: /* order_by: ORDER BY ID DESC order_list  */
#line 829 "yacc_sql.y"
                                      {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
#line 2414 "yacc_sql.tab.c"
    break;

  case 119: /* order_by: ORDER BY ID DOT ID ASC order_list  */
#line 834 "yacc_sql.y"
                                            {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2424 "yacc_sql.tab.c"
    break;

  case 120: /* order_by: ORDER BY ID DOT ID DESC order_list  */
#line 839 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
#line 2434 "yacc_sql.tab.c"
    break;

  case 122: /* order_list: COMMA ID order_list  */
#line 847 "yacc_sql.y"
                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2444 "yacc_sql.tab.c"
    break;

  case 123: /* order_list: COMMA ID DOT ID order_list  */
#line 852 "yacc_sql.y"
                                     {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2454 "yacc_sql.tab.c"
    break;

  case 124: /* order_list: COMMA ID ASC order_list  */
#line 857 "yacc_sql.y"
                                  {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2464 "yacc_sql.tab.c"
    break;

  case 125: /* order_list: COMMA ID DESC order_list  */
#line 862 "yacc_sql.y"
                                   {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
#line 2474 "yacc_sql.tab.c"
    break;

  case 126: /* order_list: COMMA ID DOT ID ASC order_list  */
#line 867 "yacc_sql.y"
                                         {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2484 "yacc_sql.tab.c"
    break;

  case 127: /* order_list: COMMA ID DOT ID DESC order_list  */
#line 872 "yacc_sql.y"
                                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
#line 2494 "yacc_sql.tab.c"
    break;

  case 128: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 880 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2503 "yacc_sql.tab.c"
    break;


#line 2507 "yacc_sql.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 885 "yacc_sql.y"

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
