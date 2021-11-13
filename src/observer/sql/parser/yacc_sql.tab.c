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
  YYSYMBOL_NUMBER = 56,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 57,                     /* FLOAT  */
  YYSYMBOL_ID = 58,                        /* ID  */
  YYSYMBOL_PATH = 59,                      /* PATH  */
  YYSYMBOL_SSS = 60,                       /* SSS  */
  YYSYMBOL_STAR = 61,                      /* STAR  */
  YYSYMBOL_STRING_V = 62,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 63,                  /* $accept  */
  YYSYMBOL_commands = 64,                  /* commands  */
  YYSYMBOL_command = 65,                   /* command  */
  YYSYMBOL_exit = 66,                      /* exit  */
  YYSYMBOL_help = 67,                      /* help  */
  YYSYMBOL_sync = 68,                      /* sync  */
  YYSYMBOL_begin = 69,                     /* begin  */
  YYSYMBOL_commit = 70,                    /* commit  */
  YYSYMBOL_rollback = 71,                  /* rollback  */
  YYSYMBOL_drop_table = 72,                /* drop_table  */
  YYSYMBOL_show_tables = 73,               /* show_tables  */
  YYSYMBOL_desc_table = 74,                /* desc_table  */
  YYSYMBOL_create_index = 75,              /* create_index  */
  YYSYMBOL_drop_index = 76,                /* drop_index  */
  YYSYMBOL_create_table = 77,              /* create_table  */
  YYSYMBOL_attr_def_list = 78,             /* attr_def_list  */
  YYSYMBOL_attr_def = 79,                  /* attr_def  */
  YYSYMBOL_number = 80,                    /* number  */
  YYSYMBOL_type = 81,                      /* type  */
  YYSYMBOL_ID_get = 82,                    /* ID_get  */
  YYSYMBOL_insert = 83,                    /* insert  */
  YYSYMBOL_record_list = 84,               /* record_list  */
  YYSYMBOL_record = 85,                    /* record  */
  YYSYMBOL_value_list = 86,                /* value_list  */
  YYSYMBOL_value = 87,                     /* value  */
  YYSYMBOL_delete = 88,                    /* delete  */
  YYSYMBOL_update = 89,                    /* update  */
  YYSYMBOL_select = 90,                    /* select  */
  YYSYMBOL_select_attr = 91,               /* select_attr  */
  YYSYMBOL_attr_list = 92,                 /* attr_list  */
  YYSYMBOL_inner_join_list = 93,           /* inner_join_list  */
  YYSYMBOL_inner_on = 94,                  /* inner_on  */
  YYSYMBOL_rel_list = 95,                  /* rel_list  */
  YYSYMBOL_where = 96,                     /* where  */
  YYSYMBOL_condition_list = 97,            /* condition_list  */
  YYSYMBOL_condition = 98,                 /* condition  */
  YYSYMBOL_comOp = 99,                     /* comOp  */
  YYSYMBOL_group_by = 100,                 /* group_by  */
  YYSYMBOL_group_by_attr = 101,            /* group_by_attr  */
  YYSYMBOL_order_by = 102,                 /* order_by  */
  YYSYMBOL_order_list = 103,               /* order_list  */
  YYSYMBOL_load_data = 104                 /* load_data  */
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
#define YYLAST   334

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  333

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   317


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
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   148,   148,   150,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   174,   179,   184,   190,   196,   202,   208,   214,   220,
     227,   232,   239,   246,   255,   257,   261,   272,   285,   288,
     289,   290,   291,   294,   303,   320,   322,   327,   332,   334,
     339,   342,   345,   352,   362,   374,   391,   411,   417,   423,
     429,   435,   442,   449,   456,   463,   470,   477,   483,   489,
     495,   501,   508,   510,   518,   526,   532,   539,   546,   553,
     560,   567,   574,   580,   586,   592,   598,   605,   607,   612,
     616,   618,   622,   624,   628,   630,   635,   656,   676,   696,
     718,   739,   760,   782,   783,   784,   785,   786,   787,   789,
     791,   796,   802,   804,   809,   815,   817,   824,   829,   834,
     839,   844,   850,   852,   857,   862,   867,   872,   877,   884
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
  "GROUP", "UNIQUE", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR",
  "STRING_V", "$accept", "commands", "command", "exit", "help", "sync",
  "begin", "commit", "rollback", "drop_table", "show_tables", "desc_table",
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
     315,   316,   317
};
#endif

#define YYPACT_NINF (-267)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -267,   109,  -267,     1,   126,    31,   -21,    50,    40,     9,
      38,    28,   114,   124,   130,   145,   146,    75,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,  -267,    99,   104,   168,   123,
     128,   174,   179,   181,   182,    16,  -267,   169,   196,   198,
    -267,   144,   147,   170,  -267,  -267,  -267,  -267,  -267,   165,
     190,   172,   150,   206,   207,   153,   154,    85,   155,    92,
     -48,  -267,   156,  -267,  -267,   185,   184,   159,   158,   161,
     162,   186,  -267,  -267,     0,    12,   205,    35,   208,    36,
     210,   211,   212,   213,    43,   214,   214,    -7,   215,   103,
     220,   191,   195,  -267,   216,   142,   217,   177,   214,   178,
     214,   180,   214,   214,   -22,   214,   214,   183,   187,   188,
      86,   189,   133,  -267,  -267,  -267,   192,   193,   184,   132,
     219,  -267,  -267,     7,  -267,   112,   209,  -267,   132,   233,
     161,   223,  -267,  -267,  -267,  -267,   228,   194,   232,  -267,
     234,  -267,   236,  -267,  -267,   237,   238,  -267,  -267,   239,
      53,    66,   240,    76,   241,    78,   214,   214,   231,   201,
     218,   242,   215,   258,   204,  -267,  -267,  -267,  -267,  -267,
    -267,   117,   122,   103,  -267,   184,   221,   216,   260,   222,
     247,   224,   214,   214,   214,   214,   214,   214,   225,   214,
     226,   214,   214,   135,   214,   214,   227,  -267,  -267,  -267,
     230,   229,   235,   132,   249,   219,  -267,   112,  -267,  -267,
     243,  -267,   209,   264,   265,  -267,  -267,  -267,   252,   267,
     256,  -267,  -267,  -267,  -267,  -267,  -267,   257,  -267,   259,
    -267,  -267,   263,   270,  -267,  -267,   271,   103,   244,   245,
     272,   242,  -267,  -267,   127,   246,  -267,  -267,  -267,  -267,
    -267,   274,   214,   214,   214,   214,   214,   250,   209,    97,
     248,  -267,  -267,   261,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,   251,   184,  -267,   253,   254,  -267,     2,   255,
     262,   218,    98,   273,   275,   266,   268,   275,  -267,  -267,
     279,   235,   269,  -267,  -267,  -267,    13,    14,  -267,   103,
     287,   273,   275,   276,   275,  -267,   275,   275,  -267,   250,
    -267,  -267,  -267,    15,  -267,  -267,  -267,  -267,   275,   275,
    -267,  -267,  -267
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
       0,     0,     0,     0,     0,    72,    57,     0,     0,     0,
      23,     0,     0,     0,    24,    25,    26,    22,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    58,     0,    29,    28,     0,    92,     0,     0,     0,
       0,     0,    27,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    72,    72,    72,    90,     0,     0,
       0,     0,     0,    43,    34,     0,     0,     0,    72,     0,
      72,     0,    72,    72,     0,    72,    72,     0,     0,     0,
       0,     0,     0,    73,    59,    60,     0,     0,    92,     0,
      45,    50,    51,     0,    52,     0,    94,    53,     0,     0,
       0,     0,    39,    40,    41,    42,    37,     0,     0,    63,
       0,    65,     0,    71,    69,     0,     0,    67,    61,     0,
       0,     0,     0,     0,     0,     0,    72,    72,    90,     0,
     109,    48,     0,     0,     0,   103,   104,   105,   106,   107,
     108,     0,     0,     0,    93,    92,     0,    34,     0,     0,
       0,     0,    72,    72,    72,    72,    72,    72,     0,    72,
       0,    72,    72,     0,    72,    72,     0,    74,    75,    91,
       0,     0,   115,     0,     0,    45,    44,     0,    98,    96,
      99,    97,    94,     0,     0,    35,    33,    38,     0,     0,
       0,    64,    66,    70,    68,    62,    78,     0,    80,     0,
      86,    84,     0,     0,    82,    76,     0,     0,     0,     0,
       0,    48,    47,    46,     0,     0,    95,    54,   129,    36,
      30,     0,    72,    72,    72,    72,    72,    87,    94,   112,
       0,    55,    49,     0,   100,   101,    31,    79,    81,    85,
      83,    77,     0,    92,    89,     0,     0,   110,   122,     0,
       0,   109,   112,   112,   122,     0,     0,   122,   116,   102,
       0,   115,     0,   113,   111,   119,   122,   122,   118,     0,
       0,   112,   122,     0,   122,   123,   122,   122,   117,    87,
      56,   114,   126,   122,   125,   121,   120,    88,   122,   122,
     124,   128,   127
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,  -267,
    -267,  -267,  -267,  -267,  -267,   105,   160,  -267,  -267,  -267,
    -267,    79,   131,    44,  -123,  -267,  -267,  -267,  -267,   -94,
     -23,   -11,   137,  -125,  -214,   -95,  -130,    17,  -266,     6,
    -232,  -267
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,   141,   104,   228,   146,   105,
      31,   173,   130,   214,   135,    32,    33,    34,    47,    71,
     283,   267,   128,   100,   184,   268,   181,   212,   287,   250,
     298,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     123,   124,   125,   170,   136,   182,   171,    36,   256,    37,
      95,   126,   294,    96,   149,   185,   151,   108,   153,   154,
     295,   157,   158,   312,   316,   328,   303,   304,   109,   110,
     296,   295,   295,   295,    69,   174,   155,    48,    51,   156,
     111,   313,   127,    50,    70,   321,   175,   176,   177,   178,
     179,   180,   113,   116,   284,   297,    38,    49,   219,   221,
     223,    69,   305,   114,   117,   308,   314,   317,   329,    52,
     197,   122,   207,   208,   315,   318,    41,    42,    43,    44,
     322,   198,   324,   199,   325,   326,    53,   254,   222,    45,
     251,   330,    46,   202,   200,   205,   331,   332,   231,   232,
     233,   234,   235,   236,   203,   238,   206,   240,   241,     2,
     244,   245,    59,     3,     4,   285,   285,    54,     5,     6,
       7,     8,     9,    10,    11,   286,   302,    55,    12,    13,
      14,   274,    39,    56,    40,    15,    16,    90,    91,    92,
      93,    86,   162,    87,   163,    17,    88,   164,    57,    58,
      94,   175,   176,   177,   178,   179,   180,    60,   291,   131,
     132,   133,    61,   134,   142,   143,   144,   145,   277,   278,
     279,   280,   281,   131,   132,   218,    62,   134,   131,   132,
     220,    63,   134,   131,   132,   273,    64,   134,   131,   132,
      65,   166,   134,   242,   167,    66,   243,    67,    68,    73,
      72,    74,    75,    78,    77,    76,    79,    80,    81,    82,
      83,    84,    85,    89,    97,    98,    99,   101,   102,   103,
     106,   107,   112,   137,   139,   115,   118,   119,   120,   121,
     138,   129,    69,   147,   140,   148,   150,   172,   152,   186,
     188,   159,   183,   169,   189,   160,   161,   165,   191,   126,
     168,   192,   190,   193,   194,   195,   196,   201,   204,   210,
     213,   216,   217,   226,   229,   247,   252,   257,   258,   259,
     260,   255,   211,   261,   262,   271,   263,   276,   227,   224,
     264,   248,   230,   237,   239,   246,   249,   265,   266,   289,
     320,   285,   225,   295,   253,   272,   327,   270,   319,   282,
     187,   290,   269,   215,   275,   209,   288,   310,   301,     0,
       0,   292,   293,   299,   309,     0,     0,     0,     0,     0,
     300,     0,     0,     0,   306,     0,   307,   311,     0,     0,
       0,     0,     0,     0,   323
};

static const yytype_int16 yycheck[] =
{
      94,    95,    96,   128,    99,   135,   129,     6,   222,     8,
      58,    18,    10,    61,   108,   138,   110,    17,   112,   113,
      18,   115,   116,    10,    10,    10,   292,   293,    28,    17,
      28,    18,    18,    18,    18,    28,    58,    58,    29,    61,
      28,    28,    49,     3,    28,   311,    39,    40,    41,    42,
      43,    44,    17,    17,   268,    53,    55,     7,   181,   182,
     185,    18,   294,    28,    28,   297,    53,    53,    53,    31,
      17,    28,   166,   167,   306,   307,    45,    46,    47,    48,
     312,    28,   314,    17,   316,   317,    58,   217,   183,    58,
     213,   323,    61,    17,    28,    17,   328,   329,   192,   193,
     194,   195,   196,   197,    28,   199,    28,   201,   202,     0,
     204,   205,    37,     4,     5,    18,    18,     3,     9,    10,
      11,    12,    13,    14,    15,    28,    28,     3,    19,    20,
      21,   254,     6,     3,     8,    26,    27,    45,    46,    47,
      48,    56,    56,    58,    58,    36,    61,    61,     3,     3,
      58,    39,    40,    41,    42,    43,    44,    58,   283,    56,
      57,    58,    58,    60,    22,    23,    24,    25,   262,   263,
     264,   265,   266,    56,    57,    58,     8,    60,    56,    57,
      58,    58,    60,    56,    57,    58,    58,    60,    56,    57,
      16,    58,    60,    58,    61,    16,    61,    16,    16,     3,
      31,     3,    58,    38,    34,    58,    16,    35,    58,     3,
       3,    58,    58,    58,    58,    30,    32,    58,    60,    58,
      58,    35,    17,     3,    29,    17,    16,    16,    16,    16,
      39,    16,    18,    16,    18,    58,    58,    18,    58,     6,
      17,    58,    33,    50,    16,    58,    58,    58,    16,    18,
      58,    17,    58,    17,    17,    17,    17,    17,    17,    58,
      18,     3,    58,     3,    17,    35,    17,     3,     3,    17,
       3,    28,    54,    17,    17,     3,    17,     3,    56,    58,
      17,    52,    58,    58,    58,    58,    51,    17,    17,    28,
       3,    18,   187,    18,   215,   251,   319,    52,   309,    49,
     140,    50,    58,   172,    58,   168,    58,   301,   291,    -1,
      -1,    58,    58,    58,    35,    -1,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    58,    -1,    58,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    58
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    64,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    36,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    83,    88,    89,    90,   104,     6,     8,    55,     6,
       8,    45,    46,    47,    48,    58,    61,    91,    58,     7,
       3,    29,    31,    58,     3,     3,     3,     3,     3,    37,
      58,    58,     8,    58,    58,    16,    16,    16,    16,    18,
      28,    92,    31,     3,     3,    58,    58,    34,    38,    16,
      35,    58,     3,     3,    58,    58,    56,    58,    61,    58,
      45,    46,    47,    48,    58,    58,    61,    58,    30,    32,
      96,    58,    60,    58,    79,    82,    58,    35,    17,    28,
      17,    28,    17,    17,    28,    17,    17,    28,    16,    16,
      16,    16,    28,    92,    92,    92,    18,    49,    95,    16,
      85,    56,    57,    58,    60,    87,    98,     3,    39,    29,
      18,    78,    22,    23,    24,    25,    81,    16,    58,    92,
      58,    92,    58,    92,    92,    58,    61,    92,    92,    58,
      58,    58,    56,    58,    61,    58,    58,    61,    58,    50,
      96,    87,    18,    84,    28,    39,    40,    41,    42,    43,
      44,    99,    99,    33,    97,    87,     6,    79,    17,    16,
      58,    16,    17,    17,    17,    17,    17,    17,    28,    17,
      28,    17,    17,    28,    17,    17,    28,    92,    92,    95,
      58,    54,   100,    18,    86,    85,     3,    58,    58,    87,
      58,    87,    98,    96,    58,    78,     3,    56,    80,    17,
      58,    92,    92,    92,    92,    92,    92,    58,    92,    58,
      92,    92,    58,    61,    92,    92,    58,    35,    52,    51,
     102,    87,    17,    84,    99,    28,    97,     3,     3,    17,
       3,    17,    17,    17,    17,    17,    17,    94,    98,    58,
      52,     3,    86,    58,    87,    58,     3,    92,    92,    92,
      92,    92,    49,    93,    97,    18,    28,   101,    58,    28,
      50,    96,    58,    58,    10,    18,    28,    53,   103,    58,
      58,   100,    28,   101,   101,   103,    58,    58,   103,    35,
     102,    58,    10,    28,    53,   103,    10,    53,   103,    94,
       3,   101,   103,    58,   103,   103,   103,    93,    10,    53,
     103,   103,   103
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    64,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    75,    76,    77,    78,    78,    79,    79,    80,    81,
      81,    81,    81,    82,    83,    84,    84,    85,    86,    86,
      87,    87,    87,    88,    89,    90,    90,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    93,    93,    94,
      95,    95,    96,    96,    97,    97,    98,    98,    98,    98,
      98,    98,    98,    99,    99,    99,    99,    99,    99,   100,
     100,   100,   101,   101,   101,   102,   102,   102,   102,   102,
     102,   102,   103,   103,   103,   103,   103,   103,   103,   104
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,    10,     4,     8,     0,     3,     5,     2,     1,     1,
       1,     1,     1,     1,     7,     0,     3,     4,     0,     3,
       1,     1,     1,     5,     8,     9,    14,     1,     2,     4,
       4,     5,     7,     5,     7,     5,     7,     5,     7,     5,
       7,     5,     0,     3,     5,     5,     6,     8,     6,     8,
       6,     8,     6,     8,     6,     8,     6,     0,     6,     2,
       0,     3,     0,     3,     0,     3,     3,     3,     3,     3,
       5,     5,     7,     1,     1,     1,     1,     1,     1,     0,
       4,     6,     0,     3,     5,     0,     4,     6,     5,     5,
       7,     7,     0,     3,     5,     4,     4,     6,     6,     8
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
#line 174 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1449 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 179 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1457 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 184 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1465 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 190 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1473 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 196 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1481 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 202 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1489 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 208 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1498 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 214 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1506 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 220 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1515 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 228 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string), 0);
		}
#line 1524 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 232 "yacc_sql.y"
                                                                  {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string), 1);
	}
#line 1533 "yacc_sql.tab.c"
    break;

  case 32: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 240 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1542 "yacc_sql.tab.c"
    break;

  case 33: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 247 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1554 "yacc_sql.tab.c"
    break;

  case 35: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 257 "yacc_sql.y"
                                   {    }
#line 1560 "yacc_sql.tab.c"
    break;

  case 36: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 262 "yacc_sql.y"
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
#line 1575 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def: ID_get type  */
#line 273 "yacc_sql.y"
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
#line 1590 "yacc_sql.tab.c"
    break;

  case 38: /* number: NUMBER  */
#line 285 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1596 "yacc_sql.tab.c"
    break;

  case 39: /* type: INT_T  */
#line 288 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1602 "yacc_sql.tab.c"
    break;

  case 40: /* type: STRING_T  */
#line 289 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1608 "yacc_sql.tab.c"
    break;

  case 41: /* type: FLOAT_T  */
#line 290 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1614 "yacc_sql.tab.c"
    break;

  case 42: /* type: DATE_T  */
#line 291 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1620 "yacc_sql.tab.c"
    break;

  case 43: /* ID_get: ID  */
#line 295 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1629 "yacc_sql.tab.c"
    break;

  case 44: /* insert: INSERT INTO ID VALUES record record_list SEMICOLON  */
#line 304 "yacc_sql.y"
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
#line 1649 "yacc_sql.tab.c"
    break;

  case 46: /* record_list: COMMA record record_list  */
#line 322 "yacc_sql.y"
                                   {

	}
#line 1657 "yacc_sql.tab.c"
    break;

  case 47: /* record: LBRACE value value_list RBRACE  */
#line 327 "yacc_sql.y"
                                      {
		inserts_record_length(&CONTEXT->ssql->sstr.insertion, CONTEXT->record_num, CONTEXT->value_length);
		CONTEXT->record_num++;
	}
#line 1666 "yacc_sql.tab.c"
    break;

  case 49: /* value_list: COMMA value value_list  */
#line 334 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1674 "yacc_sql.tab.c"
    break;

  case 50: /* value: NUMBER  */
#line 339 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1682 "yacc_sql.tab.c"
    break;

  case 51: /* value: FLOAT  */
#line 342 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1690 "yacc_sql.tab.c"
    break;

  case 52: /* value: SSS  */
#line 345 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1699 "yacc_sql.tab.c"
    break;

  case 53: /* delete: DELETE FROM ID where SEMICOLON  */
#line 353 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1711 "yacc_sql.tab.c"
    break;

  case 54: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 363 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1723 "yacc_sql.tab.c"
    break;

  case 55: /* select: SELECT select_attr FROM ID rel_list where group_by order_by SEMICOLON  */
#line 375 "yacc_sql.y"
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
#line 1743 "yacc_sql.tab.c"
    break;

  case 56: /* select: SELECT select_attr FROM ID INNER JOIN ID ON inner_on inner_join_list where group_by order_by SEMICOLON  */
#line 391 "yacc_sql.y"
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
#line 1764 "yacc_sql.tab.c"
    break;

  case 57: /* select_attr: STAR  */
#line 411 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1775 "yacc_sql.tab.c"
    break;

  case 58: /* select_attr: ID attr_list  */
#line 417 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1786 "yacc_sql.tab.c"
    break;

  case 59: /* select_attr: ID DOT ID attr_list  */
#line 423 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1797 "yacc_sql.tab.c"
    break;

  case 60: /* select_attr: ID DOT STAR attr_list  */
#line 429 "yacc_sql.y"
                               {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1808 "yacc_sql.tab.c"
    break;

  case 61: /* select_attr: AVG LBRACE ID RBRACE attr_list  */
#line 435 "yacc_sql.y"
                                         {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1820 "yacc_sql.tab.c"
    break;

  case 62: /* select_attr: AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 442 "yacc_sql.y"
                                                {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1832 "yacc_sql.tab.c"
    break;

  case 63: /* select_attr: MAX LBRACE ID RBRACE attr_list  */
#line 449 "yacc_sql.y"
                                         {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1844 "yacc_sql.tab.c"
    break;

  case 64: /* select_attr: MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 456 "yacc_sql.y"
                                                {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1856 "yacc_sql.tab.c"
    break;

  case 65: /* select_attr: MIN LBRACE ID RBRACE attr_list  */
#line 463 "yacc_sql.y"
                                         {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1868 "yacc_sql.tab.c"
    break;

  case 66: /* select_attr: MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 470 "yacc_sql.y"
                                                {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1880 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr: COUNT LBRACE STAR RBRACE attr_list  */
#line 477 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1891 "yacc_sql.tab.c"
    break;

  case 68: /* select_attr: COUNT LBRACE ID DOT STAR RBRACE attr_list  */
#line 483 "yacc_sql.y"
                                                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1902 "yacc_sql.tab.c"
    break;

  case 69: /* select_attr: COUNT LBRACE ID RBRACE attr_list  */
#line 489 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1913 "yacc_sql.tab.c"
    break;

  case 70: /* select_attr: COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 495 "yacc_sql.y"
                                                  {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1924 "yacc_sql.tab.c"
    break;

  case 71: /* select_attr: COUNT LBRACE NUMBER RBRACE attr_list  */
#line 501 "yacc_sql.y"
                                               {
		RelAttr attr;
		relation_attr_init(&attr, NULL, NULL);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_NUM_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1935 "yacc_sql.tab.c"
    break;

  case 73: /* attr_list: COMMA ID attr_list  */
#line 510 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1948 "yacc_sql.tab.c"
    break;

  case 74: /* attr_list: COMMA ID DOT ID attr_list  */
#line 518 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1961 "yacc_sql.tab.c"
    break;

  case 75: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 526 "yacc_sql.y"
                                     {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_aggretype(&CONTEXT->ssql->sstr.selection, NOTAGG);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1972 "yacc_sql.tab.c"
    break;

  case 76: /* attr_list: COMMA AVG LBRACE ID RBRACE attr_list  */
#line 532 "yacc_sql.y"
                                               {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1984 "yacc_sql.tab.c"
    break;

  case 77: /* attr_list: COMMA AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 539 "yacc_sql.y"
                                                      {
		/* avg function */
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, AVG_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1996 "yacc_sql.tab.c"
    break;

  case 78: /* attr_list: COMMA MAX LBRACE ID RBRACE attr_list  */
#line 546 "yacc_sql.y"
                                               {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2008 "yacc_sql.tab.c"
    break;

  case 79: /* attr_list: COMMA MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 553 "yacc_sql.y"
                                                      {
		/*max function*/
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MAX_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2020 "yacc_sql.tab.c"
    break;

  case 80: /* attr_list: COMMA MIN LBRACE ID RBRACE attr_list  */
#line 560 "yacc_sql.y"
                                               {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2032 "yacc_sql.tab.c"
    break;

  case 81: /* attr_list: COMMA MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 567 "yacc_sql.y"
                                                      {
		/*min function*/
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, MIN_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2044 "yacc_sql.tab.c"
    break;

  case 82: /* attr_list: COMMA COUNT LBRACE STAR RBRACE attr_list  */
#line 574 "yacc_sql.y"
                                                   {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2055 "yacc_sql.tab.c"
    break;

  case 83: /* attr_list: COMMA COUNT LBRACE ID DOT STAR RBRACE attr_list  */
#line 580 "yacc_sql.y"
                                                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), "*");
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_STAR_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2066 "yacc_sql.tab.c"
    break;

  case 84: /* attr_list: COMMA COUNT LBRACE ID RBRACE attr_list  */
#line 586 "yacc_sql.y"
                                                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2077 "yacc_sql.tab.c"
    break;

  case 85: /* attr_list: COMMA COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 592 "yacc_sql.y"
                                                        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2088 "yacc_sql.tab.c"
    break;

  case 86: /* attr_list: COMMA COUNT LBRACE NUMBER RBRACE attr_list  */
#line 598 "yacc_sql.y"
                                                     {
		RelAttr attr;
		relation_attr_init(&attr, NULL, NULL);
		selects_append_aggretype(&CONTEXT->ssql->sstr.selection, COUNT_NUM_F);
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2099 "yacc_sql.tab.c"
    break;

  case 88: /* inner_join_list: INNER JOIN ID ON inner_on inner_join_list  */
#line 607 "yacc_sql.y"
                                                    {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));
	}
#line 2107 "yacc_sql.tab.c"
    break;

  case 89: /* inner_on: condition condition_list  */
#line 612 "yacc_sql.y"
                                 {
	
	}
#line 2115 "yacc_sql.tab.c"
    break;

  case 91: /* rel_list: COMMA ID rel_list  */
#line 618 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2123 "yacc_sql.tab.c"
    break;

  case 93: /* where: WHERE condition condition_list  */
#line 624 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2131 "yacc_sql.tab.c"
    break;

  case 95: /* condition_list: AND condition condition_list  */
#line 630 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2139 "yacc_sql.tab.c"
    break;

  case 96: /* condition: ID comOp value  */
#line 636 "yacc_sql.y"
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
#line 2164 "yacc_sql.tab.c"
    break;

  case 97: /* condition: value comOp value  */
#line 657 "yacc_sql.y"
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
#line 2188 "yacc_sql.tab.c"
    break;

  case 98: /* condition: ID comOp ID  */
#line 677 "yacc_sql.y"
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
#line 2212 "yacc_sql.tab.c"
    break;

  case 99: /* condition: value comOp ID  */
#line 697 "yacc_sql.y"
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
#line 2238 "yacc_sql.tab.c"
    break;

  case 100: /* condition: ID DOT ID comOp value  */
#line 719 "yacc_sql.y"
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
#line 2263 "yacc_sql.tab.c"
    break;

  case 101: /* condition: value comOp ID DOT ID  */
#line 740 "yacc_sql.y"
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
#line 2288 "yacc_sql.tab.c"
    break;

  case 102: /* condition: ID DOT ID comOp ID DOT ID  */
#line 761 "yacc_sql.y"
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
#line 2311 "yacc_sql.tab.c"
    break;

  case 103: /* comOp: EQ  */
#line 782 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2317 "yacc_sql.tab.c"
    break;

  case 104: /* comOp: LT  */
#line 783 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2323 "yacc_sql.tab.c"
    break;

  case 105: /* comOp: GT  */
#line 784 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2329 "yacc_sql.tab.c"
    break;

  case 106: /* comOp: LE  */
#line 785 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2335 "yacc_sql.tab.c"
    break;

  case 107: /* comOp: GE  */
#line 786 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2341 "yacc_sql.tab.c"
    break;

  case 108: /* comOp: NE  */
#line 787 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2347 "yacc_sql.tab.c"
    break;

  case 110: /* group_by: GROUP BY ID group_by_attr  */
#line 791 "yacc_sql.y"
                                    {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2357 "yacc_sql.tab.c"
    break;

  case 111: /* group_by: GROUP BY ID DOT ID group_by_attr  */
#line 796 "yacc_sql.y"
                                           {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2367 "yacc_sql.tab.c"
    break;

  case 113: /* group_by_attr: COMMA ID group_by_attr  */
#line 804 "yacc_sql.y"
                                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2377 "yacc_sql.tab.c"
    break;

  case 114: /* group_by_attr: COMMA ID DOT ID group_by_attr  */
#line 809 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2387 "yacc_sql.tab.c"
    break;

  case 116: /* order_by: ORDER BY ID order_list  */
#line 817 "yacc_sql.y"
                                 {
		// default asc
		// 需要校验是否为单标查询情况
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2399 "yacc_sql.tab.c"
    break;

  case 117: /* order_by: ORDER BY ID DOT ID order_list  */
#line 824 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2409 "yacc_sql.tab.c"
    break;

  case 118: /* order_by: ORDER BY ID ASC order_list  */
#line 829 "yacc_sql.y"
                                     {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2419 "yacc_sql.tab.c"
    break;

  case 119: /* order_by: ORDER BY ID DESC order_list  */
#line 834 "yacc_sql.y"
                                      {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
#line 2429 "yacc_sql.tab.c"
    break;

  case 120: /* order_by: ORDER BY ID DOT ID ASC order_list  */
#line 839 "yacc_sql.y"
                                            {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2439 "yacc_sql.tab.c"
    break;

  case 121: /* order_by: ORDER BY ID DOT ID DESC order_list  */
#line 844 "yacc_sql.y"
                                             {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
#line 2449 "yacc_sql.tab.c"
    break;

  case 123: /* order_list: COMMA ID order_list  */
#line 852 "yacc_sql.y"
                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2459 "yacc_sql.tab.c"
    break;

  case 124: /* order_list: COMMA ID DOT ID order_list  */
#line 857 "yacc_sql.y"
                                     {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2469 "yacc_sql.tab.c"
    break;

  case 125: /* order_list: COMMA ID ASC order_list  */
#line 862 "yacc_sql.y"
                                  {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2479 "yacc_sql.tab.c"
    break;

  case 126: /* order_list: COMMA ID DESC order_list  */
#line 867 "yacc_sql.y"
                                   {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
#line 2489 "yacc_sql.tab.c"
    break;

  case 127: /* order_list: COMMA ID DOT ID ASC order_list  */
#line 872 "yacc_sql.y"
                                         {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 0);
	}
#line 2499 "yacc_sql.tab.c"
    break;

  case 128: /* order_list: COMMA ID DOT ID DESC order_list  */
#line 877 "yacc_sql.y"
                                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-4].string), (yyvsp[-2].string));
		selects_append_orders(&CONTEXT->ssql->sstr.selection, &attr, 1);
	}
#line 2509 "yacc_sql.tab.c"
    break;

  case 129: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 885 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2518 "yacc_sql.tab.c"
    break;


#line 2522 "yacc_sql.tab.c"

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

#line 890 "yacc_sql.y"

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
