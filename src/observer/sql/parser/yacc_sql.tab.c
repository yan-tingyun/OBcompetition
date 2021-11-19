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
  YYSYMBOL_UNIQUE = 55,                    /* UNIQUE  */
  YYSYMBOL_NOT = 56,                       /* NOT  */
  YYSYMBOL_NULL_T = 57,                    /* NULL_T  */
  YYSYMBOL_NULLABLE = 58,                  /* NULLABLE  */
  YYSYMBOL_IS = 59,                        /* IS  */
  YYSYMBOL_TEXT_T = 60,                    /* TEXT_T  */
  YYSYMBOL_NUMBER = 61,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 62,                     /* FLOAT  */
  YYSYMBOL_ID = 63,                        /* ID  */
  YYSYMBOL_PATH = 64,                      /* PATH  */
  YYSYMBOL_SSS = 65,                       /* SSS  */
  YYSYMBOL_STAR = 66,                      /* STAR  */
  YYSYMBOL_STRING_V = 67,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 68,                  /* $accept  */
  YYSYMBOL_commands = 69,                  /* commands  */
  YYSYMBOL_command = 70,                   /* command  */
  YYSYMBOL_exit = 71,                      /* exit  */
  YYSYMBOL_help = 72,                      /* help  */
  YYSYMBOL_sync = 73,                      /* sync  */
  YYSYMBOL_begin = 74,                     /* begin  */
  YYSYMBOL_commit = 75,                    /* commit  */
  YYSYMBOL_rollback = 76,                  /* rollback  */
  YYSYMBOL_drop_table = 77,                /* drop_table  */
  YYSYMBOL_show_tables = 78,               /* show_tables  */
  YYSYMBOL_desc_table = 79,                /* desc_table  */
  YYSYMBOL_create_index = 80,              /* create_index  */
  YYSYMBOL_index_attr_list = 81,           /* index_attr_list  */
  YYSYMBOL_drop_index = 82,                /* drop_index  */
  YYSYMBOL_create_table = 83,              /* create_table  */
  YYSYMBOL_attr_def_list = 84,             /* attr_def_list  */
  YYSYMBOL_attr_def = 85,                  /* attr_def  */
  YYSYMBOL_number = 86,                    /* number  */
  YYSYMBOL_type = 87,                      /* type  */
  YYSYMBOL_ID_get = 88,                    /* ID_get  */
  YYSYMBOL_insert = 89,                    /* insert  */
  YYSYMBOL_record_list = 90,               /* record_list  */
  YYSYMBOL_record = 91,                    /* record  */
  YYSYMBOL_value_list = 92,                /* value_list  */
  YYSYMBOL_value = 93,                     /* value  */
  YYSYMBOL_delete = 94,                    /* delete  */
  YYSYMBOL_update = 95,                    /* update  */
  YYSYMBOL_select = 96,                    /* select  */
  YYSYMBOL_select_attr = 97,               /* select_attr  */
  YYSYMBOL_attr_list = 98,                 /* attr_list  */
  YYSYMBOL_inner_join_list = 99,           /* inner_join_list  */
  YYSYMBOL_inner_on = 100,                 /* inner_on  */
  YYSYMBOL_rel_list = 101,                 /* rel_list  */
  YYSYMBOL_where = 102,                    /* where  */
  YYSYMBOL_condition_list = 103,           /* condition_list  */
  YYSYMBOL_condition = 104,                /* condition  */
  YYSYMBOL_comOp = 105,                    /* comOp  */
  YYSYMBOL_group_by = 106,                 /* group_by  */
  YYSYMBOL_group_by_attr = 107,            /* group_by_attr  */
  YYSYMBOL_order_by = 108,                 /* order_by  */
  YYSYMBOL_order_list = 109,               /* order_list  */
  YYSYMBOL_load_data = 110                 /* load_data  */
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
#define YYLAST   342

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  137
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  344

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   322


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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   153,   153,   155,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   179,   184,   189,   195,   201,   207,   213,   219,   225,
     232,   240,   247,   249,   257,   264,   273,   275,   279,   290,
     301,   312,   325,   328,   329,   330,   331,   332,   335,   344,
     361,   363,   368,   373,   375,   380,   383,   386,   390,   396,
     406,   418,   435,   455,   461,   467,   473,   479,   486,   493,
     500,   507,   514,   521,   527,   533,   539,   545,   552,   554,
     562,   570,   576,   583,   590,   597,   604,   611,   618,   624,
     630,   636,   642,   649,   651,   656,   660,   662,   666,   668,
     672,   674,   679,   700,   720,   740,   762,   783,   804,   826,
     827,   828,   829,   830,   831,   832,   833,   835,   837,   842,
     848,   850,   855,   861,   863,   870,   875,   880,   885,   890,
     896,   898,   903,   908,   913,   918,   923,   930
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
  "GROUP", "UNIQUE", "NOT", "NULL_T", "NULLABLE", "IS", "TEXT_T", "NUMBER",
  "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index",
  "index_attr_list", "drop_index", "create_table", "attr_def_list",
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
     315,   316,   317,   318,   319,   320,   321,   322
};
#endif

#define YYPACT_NINF (-261)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -261,   114,  -261,     1,    89,    24,   -50,    10,    42,    44,
      22,    39,   129,   141,   142,   148,   150,   118,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,  -261,  -261,  -261,    54,    97,   149,   112,
     120,   168,   169,   175,   176,   102,  -261,   167,   196,   202,
    -261,   151,   152,   178,  -261,  -261,  -261,  -261,  -261,   179,
     200,   183,   156,   217,   218,   159,   160,   100,   161,    38,
     -17,  -261,   162,  -261,  -261,   197,   194,   165,   164,   170,
     171,   195,  -261,  -261,    23,    30,   214,    31,   215,    65,
     219,   220,   221,   222,   103,   223,   223,    -7,   224,   111,
     236,   203,   216,  -261,   225,     4,   228,   184,   223,   185,
     223,   186,   223,   223,    80,   223,   223,   187,   188,   189,
     101,   190,   143,  -261,  -261,  -261,   191,   205,   194,   146,
     238,  -261,  -261,  -261,    37,  -261,    -5,   213,  -261,   146,
     251,   170,   241,  -261,  -261,  -261,  -261,  -261,    -6,   198,
     243,  -261,   245,  -261,   246,  -261,  -261,   247,   248,  -261,
    -261,   249,    71,    72,   250,    81,   252,    94,   223,   223,
     242,   207,   226,   253,   224,   265,   209,  -261,  -261,  -261,
    -261,  -261,  -261,   227,   125,   132,   111,  -261,   194,   210,
     225,   271,   229,   230,  -261,   257,   231,   223,   223,   223,
     223,   223,   223,   232,   223,   233,   223,   223,   147,   223,
     223,   234,  -261,  -261,  -261,   244,   237,   235,   146,   259,
     238,  -261,    -5,  -261,  -261,  -261,   254,  -261,   213,   274,
     275,  -261,  -261,  -261,   264,  -261,   239,   267,   268,  -261,
    -261,  -261,  -261,  -261,  -261,   276,  -261,   281,  -261,  -261,
     282,   283,  -261,  -261,   284,   111,   240,   255,   285,   253,
    -261,  -261,   139,   256,  -261,  -261,  -261,  -261,   257,   288,
     289,   223,   223,   223,   223,   223,   260,   213,   119,   258,
    -261,  -261,   277,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,   261,   194,  -261,   262,   263,  -261,     2,
     266,   269,   226,   124,   286,   290,   270,   272,   290,  -261,
    -261,   278,   235,   273,  -261,  -261,  -261,    13,    14,  -261,
     111,   303,   286,   290,   279,   290,  -261,   290,   290,  -261,
     260,  -261,  -261,  -261,    15,  -261,  -261,  -261,  -261,   290,
     290,  -261,  -261,  -261
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
       0,     0,     0,     0,     0,    78,    63,     0,     0,     0,
      23,     0,     0,     0,    24,    25,    26,    22,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,    29,    28,     0,    98,     0,     0,     0,
       0,     0,    27,    34,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    78,    78,    78,    96,     0,     0,
       0,     0,     0,    48,    36,     0,     0,     0,    78,     0,
      78,     0,    78,    78,     0,    78,    78,     0,     0,     0,
       0,     0,     0,    79,    65,    66,     0,     0,    98,     0,
      50,    58,    55,    56,     0,    57,     0,   100,    59,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    39,     0,
       0,    69,     0,    71,     0,    77,    75,     0,     0,    73,
      67,     0,     0,     0,     0,     0,     0,     0,    78,    78,
      96,     0,   117,    53,     0,     0,     0,   109,   110,   111,
     112,   113,   114,   115,     0,     0,     0,    99,    98,     0,
      36,     0,     0,     0,    41,    32,     0,    78,    78,    78,
      78,    78,    78,     0,    78,     0,    78,    78,     0,    78,
      78,     0,    80,    81,    97,     0,     0,   123,     0,     0,
      50,    49,     0,   116,   104,   102,   105,   103,   100,     0,
       0,    37,    35,    42,     0,    40,     0,     0,     0,    70,
      72,    76,    74,    68,    84,     0,    86,     0,    92,    90,
       0,     0,    88,    82,     0,     0,     0,     0,     0,    53,
      52,    51,     0,     0,   101,    60,   137,    38,    32,     0,
       0,    78,    78,    78,    78,    78,    93,   100,   120,     0,
      61,    54,     0,   106,   107,    33,    30,    31,    85,    87,
      91,    89,    83,     0,    98,    95,     0,     0,   118,   130,
       0,     0,   117,   120,   120,   130,     0,     0,   130,   124,
     108,     0,   123,     0,   121,   119,   127,   130,   130,   126,
       0,     0,   120,   130,     0,   130,   131,   130,   130,   125,
      93,    62,   122,   134,   130,   133,   129,   128,    94,   130,
     130,   132,   136,   135
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,  -261,
    -261,  -261,  -261,    46,  -261,  -261,   122,   174,  -261,  -261,
    -261,  -261,    90,   144,    57,  -124,  -261,  -261,  -261,  -261,
     -94,   -13,     0,   153,  -125,  -220,   -95,  -130,    20,  -260,
      12,  -169,  -261
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   237,    29,    30,   142,   104,   234,   148,
     105,    31,   175,   130,   219,   136,    32,    33,    34,    47,
      71,   294,   276,   128,   100,   187,   277,   184,   217,   298,
     258,   309,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     123,   124,   125,   172,   137,   173,   185,    36,   264,    37,
     192,   126,   305,    48,   151,   188,   153,    49,   155,   156,
     306,   159,   160,   323,   327,   339,   143,   144,   145,   146,
     307,   306,   306,   306,   177,   178,   179,   180,   181,   182,
     108,   324,   127,   314,   315,    50,    95,   110,   113,    96,
     193,   109,   194,    52,   183,   308,    38,   295,   111,   114,
     225,   227,   332,   229,   147,   176,   325,   328,   340,    41,
      42,    43,    44,    51,   212,   213,   177,   178,   179,   180,
     181,   182,   116,    90,    91,    92,    93,    45,   202,   204,
      46,   228,   262,   117,   259,    39,   183,    40,   207,   203,
     205,    94,    53,   239,   240,   241,   242,   243,   244,   208,
     246,   210,   248,   249,     2,   252,   253,    60,     3,     4,
      69,    69,   211,     5,     6,     7,     8,     9,    10,    11,
      70,   122,    54,    12,    13,    14,   316,   296,   283,   319,
      15,    16,   296,   157,    55,    56,   158,   297,   326,   329,
      17,    57,   313,    58,   333,    59,   335,    62,   336,   337,
      61,    86,   164,    87,   165,   341,    88,   166,   131,   302,
     342,   343,   132,   133,   134,    63,   135,   288,   289,   290,
     291,   292,   131,    64,    65,    66,   132,   133,   224,   131,
     135,    67,    68,   132,   133,   226,   131,   135,    72,    73,
     132,   133,   282,   131,   135,    74,   168,   132,   133,   169,
     250,   135,    77,   251,    75,    76,    79,    78,    80,    81,
      82,    83,    84,    85,    89,    97,    99,    98,   101,   102,
     107,   112,   115,   103,   106,   118,   119,   120,   121,   138,
     129,    69,   139,   141,   149,   140,   186,   150,   152,   154,
     161,   162,   163,   167,   170,   171,   174,   189,   191,   196,
     126,   195,   197,   198,   199,   200,   201,   206,   221,   209,
     215,   218,   222,   230,   232,   236,   260,   265,   266,   255,
     216,   267,   263,   223,   269,   270,   257,   235,   280,   256,
     233,   286,   287,   271,   238,   245,   247,   254,   272,   273,
     274,   275,   268,   278,   296,   300,   331,   279,   306,   293,
     261,   301,   231,   320,   285,   190,   281,   338,   220,   284,
     330,   299,   312,   214,   321,   303,   304,     0,     0,   310,
       0,     0,   311,   317,     0,   318,   322,     0,     0,     0,
       0,     0,   334
};

static const yytype_int16 yycheck[] =
{
      94,    95,    96,   128,    99,   129,   136,     6,   228,     8,
      16,    18,    10,    63,   108,   139,   110,     7,   112,   113,
      18,   115,   116,    10,    10,    10,    22,    23,    24,    25,
      28,    18,    18,    18,    39,    40,    41,    42,    43,    44,
      17,    28,    49,   303,   304,     3,    63,    17,    17,    66,
      56,    28,    58,    31,    59,    53,    55,   277,    28,    28,
     184,   185,   322,   188,    60,    28,    53,    53,    53,    45,
      46,    47,    48,    29,   168,   169,    39,    40,    41,    42,
      43,    44,    17,    45,    46,    47,    48,    63,    17,    17,
      66,   186,   222,    28,   218,     6,    59,     8,    17,    28,
      28,    63,    63,   197,   198,   199,   200,   201,   202,    28,
     204,    17,   206,   207,     0,   209,   210,    63,     4,     5,
      18,    18,    28,     9,    10,    11,    12,    13,    14,    15,
      28,    28,     3,    19,    20,    21,   305,    18,   262,   308,
      26,    27,    18,    63,     3,     3,    66,    28,   317,   318,
      36,     3,    28,     3,   323,    37,   325,     8,   327,   328,
      63,    61,    61,    63,    63,   334,    66,    66,    57,   294,
     339,   340,    61,    62,    63,    63,    65,   271,   272,   273,
     274,   275,    57,    63,    16,    16,    61,    62,    63,    57,
      65,    16,    16,    61,    62,    63,    57,    65,    31,     3,
      61,    62,    63,    57,    65,     3,    63,    61,    62,    66,
      63,    65,    34,    66,    63,    63,    16,    38,    35,    63,
       3,     3,    63,    63,    63,    63,    32,    30,    63,    65,
      35,    17,    17,    63,    63,    16,    16,    16,    16,     3,
      16,    18,    39,    18,    16,    29,    33,    63,    63,    63,
      63,    63,    63,    63,    63,    50,    18,     6,    17,    16,
      18,    63,    17,    17,    17,    17,    17,    17,     3,    17,
      63,    18,    63,    63,     3,    18,    17,     3,     3,    35,
      54,    17,    28,    56,    17,    17,    51,    57,     3,    52,
      61,     3,     3,    17,    63,    63,    63,    63,    17,    17,
      17,    17,    63,    63,    18,    28,     3,    52,    18,    49,
     220,    50,   190,    35,   268,   141,   259,   330,   174,    63,
     320,    63,   302,   170,   312,    63,    63,    -1,    -1,    63,
      -1,    -1,    63,    63,    -1,    63,    63,    -1,    -1,    -1,
      -1,    -1,    63
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    69,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    36,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    82,
      83,    89,    94,    95,    96,   110,     6,     8,    55,     6,
       8,    45,    46,    47,    48,    63,    66,    97,    63,     7,
       3,    29,    31,    63,     3,     3,     3,     3,     3,    37,
      63,    63,     8,    63,    63,    16,    16,    16,    16,    18,
      28,    98,    31,     3,     3,    63,    63,    34,    38,    16,
      35,    63,     3,     3,    63,    63,    61,    63,    66,    63,
      45,    46,    47,    48,    63,    63,    66,    63,    30,    32,
     102,    63,    65,    63,    85,    88,    63,    35,    17,    28,
      17,    28,    17,    17,    28,    17,    17,    28,    16,    16,
      16,    16,    28,    98,    98,    98,    18,    49,   101,    16,
      91,    57,    61,    62,    63,    65,    93,   104,     3,    39,
      29,    18,    84,    22,    23,    24,    25,    60,    87,    16,
      63,    98,    63,    98,    63,    98,    98,    63,    66,    98,
      98,    63,    63,    63,    61,    63,    66,    63,    63,    66,
      63,    50,   102,    93,    18,    90,    28,    39,    40,    41,
      42,    43,    44,    59,   105,   105,    33,   103,    93,     6,
      85,    17,    16,    56,    58,    63,    16,    17,    17,    17,
      17,    17,    17,    28,    17,    28,    17,    17,    28,    17,
      17,    28,    98,    98,   101,    63,    54,   106,    18,    92,
      91,     3,    63,    56,    63,    93,    63,    93,   104,   102,
      63,    84,     3,    61,    86,    57,    18,    81,    63,    98,
      98,    98,    98,    98,    98,    63,    98,    63,    98,    98,
      63,    66,    98,    98,    63,    35,    52,    51,   108,    93,
      17,    90,   105,    28,   103,     3,     3,    17,    63,    17,
      17,    17,    17,    17,    17,    17,   100,   104,    63,    52,
       3,    92,    63,    93,    63,    81,     3,     3,    98,    98,
      98,    98,    98,    49,    99,   103,    18,    28,   107,    63,
      28,    50,   102,    63,    63,    10,    18,    28,    53,   109,
      63,    63,   106,    28,   107,   107,   109,    63,    63,   109,
      35,   108,    63,    10,    28,    53,   109,    10,    53,   109,
     100,     3,   107,   109,    63,   109,   109,   109,    99,    10,
      53,   109,   109,   109
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    68,    69,    69,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    80,    81,    81,    82,    83,    84,    84,    85,    85,
      85,    85,    86,    87,    87,    87,    87,    87,    88,    89,
      90,    90,    91,    92,    92,    93,    93,    93,    93,    94,
      95,    96,    96,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    99,    99,   100,   101,   101,   102,   102,
     103,   103,   104,   104,   104,   104,   104,   104,   104,   105,
     105,   105,   105,   105,   105,   105,   105,   106,   106,   106,
     107,   107,   107,   108,   108,   108,   108,   108,   108,   108,
     109,   109,   109,   109,   109,   109,   109,   110
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    10,     0,     3,     4,     8,     0,     3,     5,     2,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     7,
       0,     3,     4,     0,     3,     1,     1,     1,     1,     5,
       8,     9,    14,     1,     2,     4,     4,     5,     7,     5,
       7,     5,     7,     5,     7,     5,     7,     5,     0,     3,
       5,     5,     6,     8,     6,     8,     6,     8,     6,     8,
       6,     8,     6,     0,     6,     2,     0,     3,     0,     3,
       0,     3,     3,     3,     3,     3,     5,     5,     7,     1,
       1,     1,     1,     1,     1,     1,     2,     0,     4,     6,
       0,     3,     5,     0,     4,     6,     5,     5,     7,     7,
       0,     3,     5,     4,     4,     6,     6,     8
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
#line 179 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1465 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 184 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1473 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 189 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1481 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 195 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1489 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 201 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1497 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 207 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1505 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 213 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1514 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 219 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1522 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 225 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1531 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID index_attr_list RBRACE SEMICOLON  */
#line 233 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string), 0);
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-3].string));
			create_index_append_attr(&CONTEXT->ssql->sstr.create_index, &attr);
		}
#line 1543 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 240 "yacc_sql.y"
                                                                  {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
		CONTEXT->ssql->sstr.create_index.attr_num = 1;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string), 1);
	}
#line 1553 "yacc_sql.tab.c"
    break;

  case 33: /* index_attr_list: COMMA ID index_attr_list  */
#line 249 "yacc_sql.y"
                                   {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, &attr);
	}
#line 1563 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 258 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1572 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 265 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1584 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 275 "yacc_sql.y"
                                   {    }
#line 1590 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 280 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number), 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1605 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type  */
#line 291 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1620 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type NOT NULL_T  */
#line 302 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1635 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type NULLABLE  */
#line 313 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1650 "yacc_sql.tab.c"
    break;

  case 42: /* number: NUMBER  */
#line 325 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1656 "yacc_sql.tab.c"
    break;

  case 43: /* type: INT_T  */
#line 328 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1662 "yacc_sql.tab.c"
    break;

  case 44: /* type: STRING_T  */
#line 329 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1668 "yacc_sql.tab.c"
    break;

  case 45: /* type: FLOAT_T  */
#line 330 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1674 "yacc_sql.tab.c"
    break;

  case 46: /* type: DATE_T  */
#line 331 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1680 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 332 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1686 "yacc_sql.tab.c"
    break;

  case 48: /* ID_get: ID  */
#line 336 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1695 "yacc_sql.tab.c"
    break;

  case 49: /* insert: INSERT INTO ID VALUES record record_list SEMICOLON  */
#line 345 "yacc_sql.y"
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
#line 1715 "yacc_sql.tab.c"
    break;

  case 51: /* record_list: COMMA record record_list  */
#line 363 "yacc_sql.y"
                                   {

	}
#line 1723 "yacc_sql.tab.c"
    break;

  case 52: /* record: LBRACE value value_list RBRACE  */
#line 368 "yacc_sql.y"
                                      {
		inserts_record_length(&CONTEXT->ssql->sstr.insertion, CONTEXT->record_num, CONTEXT->value_length);
		CONTEXT->record_num++;
	}
#line 1732 "yacc_sql.tab.c"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 375 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1740 "yacc_sql.tab.c"
    break;

  case 55: /* value: NUMBER  */
#line 380 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1748 "yacc_sql.tab.c"
    break;

  case 56: /* value: FLOAT  */
#line 383 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1756 "yacc_sql.tab.c"
    break;

  case 57: /* value: SSS  */
#line 386 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1765 "yacc_sql.tab.c"
    break;

  case 58: /* value: NULL_T  */
#line 390 "yacc_sql.y"
             {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1773 "yacc_sql.tab.c"
    break;

  case 59: /* delete: DELETE FROM ID where SEMICOLON  */
#line 397 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1785 "yacc_sql.tab.c"
    break;

  case 60: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 407 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1797 "yacc_sql.tab.c"
    break;

  case 61: /* select: SELECT select_attr FROM ID rel_list where group_by order_by SEMICOLON  */
#line 419 "yacc_sql.y"
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
#line 1817 "yacc_sql.tab.c"
    break;

  case 62: /* select: SELECT select_attr FROM ID INNER JOIN ID ON inner_on inner_join_list where group_by order_by SEMICOLON  */
#line 435 "yacc_sql.y"
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
#line 1838 "yacc_sql.tab.c"
    break;

  case 63: /* select_attr: STAR  */
#line 455 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1849 "yacc_sql.tab.c"
    break;

  case 64: /* select_attr: ID attr_list  */
#line 461 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1860 "yacc_sql.tab.c"
    break;

  case 65: /* select_attr: ID DOT ID attr_list  */
#line 467 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1871 "yacc_sql.tab.c"
    break;

  case 66: /* select_attr: ID DOT STAR attr_list  */
#line 473 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1882 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr: AVG LBRACE ID RBRACE attr_list  */
#line 479 "yacc_sql.y"
                                         {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1894 "yacc_sql.tab.c"
    break;

  case 68: /* select_attr: AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 486 "yacc_sql.y"
                                                {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1906 "yacc_sql.tab.c"
    break;

  case 69: /* select_attr: MAX LBRACE ID RBRACE attr_list  */
#line 493 "yacc_sql.y"
                                         {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1918 "yacc_sql.tab.c"
    break;

  case 70: /* select_attr: MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 500 "yacc_sql.y"
                                                {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1930 "yacc_sql.tab.c"
    break;

  case 71: /* select_attr: MIN LBRACE ID RBRACE attr_list  */
#line 507 "yacc_sql.y"
                                         {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1942 "yacc_sql.tab.c"
    break;

  case 72: /* select_attr: MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 514 "yacc_sql.y"
                                                {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1954 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: COUNT LBRACE STAR RBRACE attr_list  */
#line 521 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1965 "yacc_sql.tab.c"
    break;

  case 74: /* select_attr: COUNT LBRACE ID DOT STAR RBRACE attr_list  */
#line 527 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1976 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr: COUNT LBRACE ID RBRACE attr_list  */
#line 533 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1987 "yacc_sql.tab.c"
    break;

  case 76: /* select_attr: COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 539 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1998 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr: COUNT LBRACE NUMBER RBRACE attr_list  */
#line 545 "yacc_sql.y"
                                               {
		RelAttr attr;
		relation_attr_init(&attr, NULL, NULL);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_NUM_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2009 "yacc_sql.tab.c"
    break;

  case 79: /* attr_list: COMMA ID attr_list  */
#line 554 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2022 "yacc_sql.tab.c"
    break;

  case 80: /* attr_list: COMMA ID DOT ID attr_list  */
#line 562 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2035 "yacc_sql.tab.c"
    break;

  case 81: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 570 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2046 "yacc_sql.tab.c"
    break;

  case 82: /* attr_list: COMMA AVG LBRACE ID RBRACE attr_list  */
#line 576 "yacc_sql.y"
                                               {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2058 "yacc_sql.tab.c"
    break;

  case 83: /* attr_list: COMMA AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 583 "yacc_sql.y"
                                                      {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2070 "yacc_sql.tab.c"
    break;

  case 84: /* attr_list: COMMA MAX LBRACE ID RBRACE attr_list  */
#line 590 "yacc_sql.y"
                                               {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2082 "yacc_sql.tab.c"
    break;

  case 85: /* attr_list: COMMA MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 597 "yacc_sql.y"
                                                      {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2094 "yacc_sql.tab.c"
    break;

  case 86: /* attr_list: COMMA MIN LBRACE ID RBRACE attr_list  */
#line 604 "yacc_sql.y"
                                               {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2106 "yacc_sql.tab.c"
    break;

  case 87: /* attr_list: COMMA MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 611 "yacc_sql.y"
                                                      {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2118 "yacc_sql.tab.c"
    break;

  case 88: /* attr_list: COMMA COUNT LBRACE STAR RBRACE attr_list  */
#line 618 "yacc_sql.y"
                                                   {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2129 "yacc_sql.tab.c"
    break;

  case 89: /* attr_list: COMMA COUNT LBRACE ID DOT STAR RBRACE attr_list  */
#line 624 "yacc_sql.y"
                                                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2140 "yacc_sql.tab.c"
    break;

  case 90: /* attr_list: COMMA COUNT LBRACE ID RBRACE attr_list  */
#line 630 "yacc_sql.y"
                                                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2151 "yacc_sql.tab.c"
    break;

  case 91: /* attr_list: COMMA COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 636 "yacc_sql.y"
                                                        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2162 "yacc_sql.tab.c"
    break;

  case 92: /* attr_list: COMMA COUNT LBRACE NUMBER RBRACE attr_list  */
#line 642 "yacc_sql.y"
                                                     {
		RelAttr attr;
		relation_attr_init(&attr, NULL, NULL);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_NUM_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2173 "yacc_sql.tab.c"
    break;

  case 94: /* inner_join_list: INNER JOIN ID ON inner_on inner_join_list  */
#line 651 "yacc_sql.y"
                                                    {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));
	}
#line 2181 "yacc_sql.tab.c"
    break;

  case 95: /* inner_on: condition condition_list  */
#line 656 "yacc_sql.y"
                                 {
	
	}
#line 2189 "yacc_sql.tab.c"
    break;

  case 97: /* rel_list: COMMA ID rel_list  */
#line 662 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2197 "yacc_sql.tab.c"
    break;

  case 99: /* where: WHERE condition condition_list  */
#line 668 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2205 "yacc_sql.tab.c"
    break;

  case 101: /* condition_list: AND condition condition_list  */
#line 674 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2213 "yacc_sql.tab.c"
    break;

  case 102: /* condition: ID comOp value  */
#line 680 "yacc_sql.y"
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
#line 2238 "yacc_sql.tab.c"
    break;

  case 103: /* condition: value comOp value  */
#line 701 "yacc_sql.y"
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
#line 2262 "yacc_sql.tab.c"
    break;

  case 104: /* condition: ID comOp ID  */
#line 721 "yacc_sql.y"
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
#line 2286 "yacc_sql.tab.c"
    break;

  case 105: /* condition: value comOp ID  */
#line 741 "yacc_sql.y"
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
#line 2312 "yacc_sql.tab.c"
    break;

  case 106: /* condition: ID DOT ID comOp value  */
#line 763 "yacc_sql.y"
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
#line 2337 "yacc_sql.tab.c"
    break;

  case 107: /* condition: value comOp ID DOT ID  */
#line 784 "yacc_sql.y"
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
#line 2362 "yacc_sql.tab.c"
    break;

  case 108: /* condition: ID DOT ID comOp ID DOT ID  */
#line 805 "yacc_sql.y"
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
#line 2385 "yacc_sql.tab.c"
    break;

  case 109: /* comOp: EQ  */
#line 826 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2391 "yacc_sql.tab.c"
    break;

  case 110: /* comOp: LT  */
#line 827 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2397 "yacc_sql.tab.c"
    break;

  case 111: /* comOp: GT  */
#line 828 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2403 "yacc_sql.tab.c"
    break;

  case 112: /* comOp: LE  */
#line 829 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2409 "yacc_sql.tab.c"
    break;

  case 113: /* comOp: GE  */
#line 830 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2415 "yacc_sql.tab.c"
    break;

  case 114: /* comOp: NE  */
#line 831 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2421 "yacc_sql.tab.c"
    break;

  case 115: /* comOp: IS  */
#line 832 "yacc_sql.y"
             { CONTEXT->comp = IS_NULL; }
#line 2427 "yacc_sql.tab.c"
    break;

  case 116: /* comOp: IS NOT  */
#line 833 "yacc_sql.y"
                 { CONTEXT->comp = IS_NOT_NULL; }
#line 2433 "yacc_sql.tab.c"
    break;

  case 118: /* group_by: GROUP BY ID group_by_attr  */
#line 837 "yacc_sql.y"
                                    {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2443 "yacc_sql.tab.c"
    break;

  case 119: /* group_by: GROUP BY ID DOT ID group_by_attr  */
#line 842 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2453 "yacc_sql.tab.c"
    break;

  case 121: /* group_by_attr: COMMA ID group_by_attr  */
#line 850 "yacc_sql.y"
                                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2463 "yacc_sql.tab.c"
    break;

  case 122: /* group_by_attr: COMMA ID DOT ID group_by_attr  */
#line 855 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2473 "yacc_sql.tab.c"
    break;

  case 124: /* order_by: ORDER BY ID order_list  */
#line 863 "yacc_sql.y"
                                 {
		// default asc
		// 需要校验是否为单标查询情况
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2485 "yacc_sql.tab.c"
    break;

  case 125: /* order_by: ORDER BY ID DOT ID order_list  */
#line 870 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2495 "yacc_sql.tab.c"
    break;

  case 126: /* order_by: ORDER BY ID ASC order_list  */
#line 875 "yacc_sql.y"
                                     {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2505 "yacc_sql.tab.c"
    break;

  case 127: /* order_by: ORDER BY ID DESC order_list  */
#line 880 "yacc_sql.y"
                                      {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
#line 2515 "yacc_sql.tab.c"
    break;

  case 128: /* order_by: ORDER BY ID DOT ID ASC order_list  */
#line 885 "yacc_sql.y"
                                            {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2525 "yacc_sql.tab.c"
    break;

  case 129: /* order_by: ORDER BY ID DOT ID DESC order_list  */
#line 890 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
#line 2535 "yacc_sql.tab.c"
    break;

  case 131: /* order_list: COMMA ID order_list  */
#line 898 "yacc_sql.y"
                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2545 "yacc_sql.tab.c"
    break;

  case 132: /* order_list: COMMA ID DOT ID order_list  */
#line 903 "yacc_sql.y"
                                     {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2555 "yacc_sql.tab.c"
    break;

  case 133: /* order_list: COMMA ID ASC order_list  */
#line 908 "yacc_sql.y"
                                  {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2565 "yacc_sql.tab.c"
    break;

  case 134: /* order_list: COMMA ID DESC order_list  */
#line 913 "yacc_sql.y"
                                   {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
#line 2575 "yacc_sql.tab.c"
    break;

  case 135: /* order_list: COMMA ID DOT ID ASC order_list  */
#line 918 "yacc_sql.y"
                                         {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2585 "yacc_sql.tab.c"
    break;

  case 136: /* order_list: COMMA ID DOT ID DESC order_list  */
#line 923 "yacc_sql.y"
                                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
#line 2595 "yacc_sql.tab.c"
    break;

  case 137: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 931 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2604 "yacc_sql.tab.c"
    break;


#line 2608 "yacc_sql.tab.c"

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

#line 936 "yacc_sql.y"

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
