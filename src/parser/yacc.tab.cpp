/* A Bison parser, made by GNU Bison 3.5.1.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "yacc.y"

#include "ast.h"
#include "yacc.tab.h"
#include <iostream>
#include <memory>

int yylex(YYSTYPE *yylval, YYLTYPE *yylloc);

void yyerror(YYLTYPE *locp, const char* s) {
    std::cerr << "Parser Error at line " << locp->first_line << " column " << locp->first_column << ": " << s << std::endl;
}

using namespace ast;

#line 85 "yacc.tab.cpp"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_TAB_HPP_INCLUDED
# define YY_YY_YACC_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SHOW = 258,
    TABLES = 259,
    CREATE = 260,
    TABLE = 261,
    DROP = 262,
    DESC = 263,
    INSERT = 264,
    INTO = 265,
    VALUES = 266,
    DELETE = 267,
    FROM = 268,
    ASC = 269,
    ORDER = 270,
    BY = 271,
    WHERE = 272,
    UPDATE = 273,
    SET = 274,
    SELECT = 275,
    INT = 276,
    CHAR = 277,
    FLOAT = 278,
    BIGINT = 279,
    DATETIME = 280,
    INDEX = 281,
    AND = 282,
    JOIN = 283,
    EXIT = 284,
    HELP = 285,
    TXN_BEGIN = 286,
    TXN_COMMIT = 287,
    TXN_ABORT = 288,
    TXN_ROLLBACK = 289,
    ORDER_BY = 290,
    LIMIT = 291,
    AS = 292,
    SUM = 293,
    COUNT = 294,
    MAX = 295,
    MIN = 296,
    LEQ = 297,
    NEQ = 298,
    GEQ = 299,
    T_EOF = 300,
    IDENTIFIER = 301,
    VALUE_STRING = 302,
    VALUE_INT = 303,
    VALUE_FLOAT = 304,
    VALUE_BIGINT = 305,
    VALUE_DATETIME = 306
  };
#endif

/* Value type.  */

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (void);

#endif /* !YY_YY_YACC_TAB_HPP_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  49
/* YYLAST -- Last index in YYTABLE.  */
<<<<<<< HEAD
<<<<<<< HEAD
#define YYLAST   161
=======
#define YYLAST   150
=======
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   120
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
#define YYLAST   154
>>>>>>> feat: 拉取聚合函数部分内容

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
<<<<<<< HEAD
<<<<<<< HEAD
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  172
=======
<<<<<<< HEAD
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  167
=======
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  170
>>>>>>> feat: 拉取聚合函数部分内容

#define YYUNDEFTOK  2
#define YYMAXUTOK   306


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      53,    54,    60,     2,    55,     2,    56,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    52,
      58,    57,    59,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
       0,    63,    63,    68,    73,    78,    86,    87,    88,    89,
      93,    97,   101,   105,   112,   119,   123,   127,   131,   135,
     142,   146,   150,   154,   158,   165,   169,   176,   180,   187,
     194,   198,   202,   207,   212,   219,   223,   230,   234,   238,
     242,   246,   253,   260,   261,   268,   272,   279,   283,   290,
     294,   301,   305,   309,   313,   317,   321,   328,   332,   339,
     343,   350,   357,   361,   365,   370,   375,   379,   383,   390,
     397,   404,   411,   418,   422,   426,   434,   439,   443,   447,
     452,   459,   466,   467,   468,   471,   473
=======
<<<<<<< HEAD
       0,    61,    61,    66,    71,    76,    84,    85,    86,    87,
      91,    95,    99,   103,   110,   117,   121,   125,   129,   133,
     140,   144,   148,   152,   156,   163,   167,   174,   178,   185,
     192,   196,   200,   205,   210,   217,   221,   228,   232,   236,
     240,   244,   251,   258,   259,   266,   270,   277,   281,   288,
     292,   299,   303,   307,   311,   315,   319,   326,   330,   337,
     341,   348,   355,   359,   363,   368,   373,   377,   381,   388,
     395,   402,   409,   416,   420,   424,   431,   435,   439,   446,
     447,   448,   451,   453
=======
       0,    58,    58,    63,    68,    73,    81,    82,    83,    84,
      88,    92,    96,   100,   107,   111,   118,   122,   126,   130,
     134,   141,   145,   149,   153,   160,   164,   171,   175,   182,
     189,   193,   197,   202,   207,   214,   218,   225,   229,   233,
     237,   241,   248,   255,   256,   263,   267,   274,   278,   285,
     289,   296,   300,   304,   308,   312,   316,   323,   327,   334,
     338,   345,   352,   356,   360,   364,   368,   375,   379,   383,
     390,   391,   392,   395,   397
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
       0,    61,    61,    66,    71,    76,    84,    85,    86,    87,
      91,    95,    99,   103,   110,   114,   121,   125,   129,   133,
     137,   144,   148,   152,   156,   160,   167,   171,   178,   182,
     189,   196,   200,   204,   209,   214,   221,   225,   232,   236,
     240,   244,   248,   255,   262,   263,   270,   274,   281,   285,
     292,   296,   303,   307,   311,   315,   319,   323,   330,   334,
     341,   345,   352,   359,   363,   367,   372,   377,   381,   385,
     392,   399,   406,   413,   420,   424,   428,   435,   439,   443,
     450,   451,   452,   455,   457
>>>>>>> feat: 拉取聚合函数部分内容
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SHOW", "TABLES", "CREATE", "TABLE",
  "DROP", "DESC", "INSERT", "INTO", "VALUES", "DELETE", "FROM", "ASC",
  "ORDER", "BY", "WHERE", "UPDATE", "SET", "SELECT", "INT", "CHAR",
  "FLOAT", "BIGINT", "DATETIME", "INDEX", "AND", "JOIN", "EXIT", "HELP",
  "TXN_BEGIN", "TXN_COMMIT", "TXN_ABORT", "TXN_ROLLBACK", "ORDER_BY",
  "LIMIT", "AS", "SUM", "COUNT", "MAX", "MIN", "LEQ", "NEQ", "GEQ",
  "T_EOF", "IDENTIFIER", "VALUE_STRING", "VALUE_INT", "VALUE_FLOAT",
  "VALUE_BIGINT", "VALUE_DATETIME", "';'", "'('", "')'", "','", "'.'",
  "'='", "'<'", "'>'", "'*'", "$accept", "start", "stmt", "txnStmt",
  "dbStmt", "ddl", "dml", "fieldList", "colNameList", "field", "type",
  "valueList", "value", "condition", "optWhereClause", "whereClause",
  "col", "colList", "op", "expr", "setClauses", "setClause", "selector",
  "aggregator", "AGGRE_SUM", "AGGRE_COUNT", "AGGRE_MAX", "AGGRE_MIN",
  "tableList", "opt_order_clauses", "order_clauses", "order_clause",
  "opt_asc_desc", "tbName", "colName", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,    59,    40,    41,    44,    46,    61,    60,    62,
      42
};
# endif

#define YYPACT_NINF (-98)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

<<<<<<< HEAD
<<<<<<< HEAD
#define YYTABLE_NINF (-86)
=======
<<<<<<< HEAD
#define YYTABLE_NINF (-83)
=======
#define YYTABLE_NINF (-74)
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
#define YYTABLE_NINF (-84)
>>>>>>> feat: 拉取聚合函数部分内容

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
      39,    -1,    11,    12,   -27,    19,    27,   -27,    -7,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,    52,     6,   -83,   -83,
     -83,   -83,   -83,   -27,   -27,   -27,   -27,   -83,   -83,   -27,
     -27,    41,   -83,   -83,   -83,   -83,    18,   -83,   -83,    38,
      81,    96,    61,    62,    63,    64,    65,   -83,   -83,   -83,
      66,    67,   -83,    69,   107,   106,    79,    80,   -27,   -27,
      79,   -32,    79,    79,    79,    79,    79,    79,    74,    80,
     -83,   -83,     8,   -83,    71,   -83,   -12,   -83,   106,    75,
      77,    78,    82,    83,   -83,   -19,   -83,    76,    53,   -83,
      56,    55,   -83,   103,    33,    79,   -83,    55,   -27,   -27,
     118,   -83,    97,    98,   101,   102,   104,   -83,    79,   -83,
      87,   -83,   -83,   -83,   -83,   -83,    79,   -83,   -83,   -83,
     -83,   -83,   -83,    58,   -83,    80,   -83,   -83,   -83,   -83,
     -83,   -83,    32,   -83,   -83,   -83,   -83,   126,   -83,    79,
      79,    79,    79,    79,   -83,    95,   -83,   -83,    55,   -83,
     -83,   -83,   -83,    80,   -83,   -83,   -83,   -83,   -83,    90,
     -83,    16,     9,   -83,   -83,   -83,   -83,   -83,    99,    80,
     -83,   -83
=======
<<<<<<< HEAD
      39,     1,    11,    13,   -20,    18,    32,   -20,    -7,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,    36,    16,   -83,   -83,
     -83,   -83,   -83,   -20,   -20,   -20,   -20,   -83,   -83,   -20,
     -20,    56,   -83,   -83,   -83,   -83,     3,   -83,   -83,    20,
      71,    77,    40,    42,    46,    64,    62,   -83,   -83,   -83,
      66,    67,   -83,    68,    80,   104,    78,    81,   -20,   -20,
      78,   -16,    78,    78,    78,    78,    78,    78,    70,    81,
     -83,   -83,    -1,   -83,    69,   -83,   -14,   -83,   104,    74,
      75,    76,    79,    82,   -83,   -19,   -83,    85,     7,   -83,
      23,    65,   -83,   103,    22,    78,   -83,    65,   -20,   -20,
     116,   -83,    97,    98,   100,   101,   102,   -83,    78,   -83,
      87,   -83,   -83,   -83,   -83,   -83,    78,   -83,   -83,   -83,
     -83,   -83,   -83,    28,   -83,    81,   -83,   -83,   -83,   -83,
     -83,   -83,    55,   -83,   -83,   -83,   -83,   124,   -83,    78,
      78,    78,    78,    78,   -83,    94,   -83,   -83,    65,   -83,
     -83,   -83,   -83,    81,   -83,   -83,   -83,   -83,   -83,    89,
     -83,    10,   -83,   -83,   -83,   -83,   -83
=======
      42,     7,     0,     4,   -26,    27,    28,   -26,   -25,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,    40,     6,   -78,   -78,
     -78,   -78,   -78,    43,   -26,   -26,   -26,   -26,   -78,   -78,
     -26,   -26,    34,    11,   -78,   -78,    16,    53,    20,   -78,
     -78,   -78,   -26,    30,    33,   -78,    56,    44,    85,    64,
      65,   -26,    64,   -78,    64,    64,    64,    59,    65,   -78,
     -78,    -5,   -78,    57,   -78,     8,   -78,   -78,   -31,   -78,
      70,   -14,   -78,    10,    55,   -78,    80,    31,    64,   -78,
      55,   -26,   -26,    94,   -78,    64,   -78,    63,   -78,   -78,
     -78,   -78,   -78,    64,   -78,   -78,   -78,   -78,   -78,   -78,
      15,   -78,    65,   -78,   -78,   -78,   -78,   -78,   -78,    45,
     -78,   -78,   -78,   -78,    95,   -78,   -78,    71,   -78,   -78,
      55,   -78,   -78,   -78,   -78,    65,    66,   -78,     5,   -78,
     -78,   -78,   -78,   -78
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
      62,     7,    23,    24,   -40,    22,    28,   -40,   -20,   -98,
     -98,   -98,   -98,   -98,   -98,   -98,    36,    -4,   -98,   -98,
     -98,   -98,   -98,    43,   -40,   -40,   -40,   -40,   -98,   -98,
     -40,   -40,    45,   -98,   -98,   -98,   -98,   -12,   -98,   -98,
      12,    68,    72,    16,    67,    69,    70,    20,   -98,   -98,
     -98,   -40,    71,    73,   -98,    74,   109,    60,    52,    79,
     -40,   -40,    52,    17,    52,    52,    52,   -98,    52,    52,
      52,    76,    79,   -98,   -98,    -1,   -98,    75,   -98,    -2,
     -98,    60,    77,    80,    81,    82,    83,   -98,    19,   -98,
      86,    25,   -98,    30,    66,   -98,   102,     3,    52,   -98,
      66,   -40,   -40,   117,   -98,   101,   103,   104,   105,   106,
     -98,    52,   -98,    91,   -98,   -98,   -98,   -98,   -98,    52,
     -98,   -98,   -98,   -98,   -98,   -98,    64,   -98,    79,   -98,
     -98,   -98,   -98,   -98,   -98,    55,   -98,   -98,   -98,   -98,
     122,   -98,    52,    52,    52,    52,    52,   -98,    97,   -98,
     -98,    66,   -98,   -98,   -98,   -98,    79,   -98,   -98,   -98,
     -98,   -98,    92,   -98,    26,   -98,   -98,   -98,   -98,   -98
>>>>>>> feat: 拉取聚合函数部分内容
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     4,
       3,    10,    11,    12,    13,     5,     0,     0,     9,     6,
<<<<<<< HEAD
<<<<<<< HEAD
       7,     8,    14,     0,     0,     0,     0,    85,    17,     0,
       0,     0,    69,    70,    71,    72,    86,    62,    49,    63,
=======
<<<<<<< HEAD
       7,     8,    14,     0,     0,     0,     0,    82,    17,     0,
       0,     0,    69,    70,    71,    72,    83,    62,    49,    63,
>>>>>>> feat: 更改parser的部分以支持index相关操作
       0,     0,     0,     0,     0,     0,     0,    48,     1,     2,
       0,     0,    16,     0,     0,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      21,    86,    43,    59,     0,    50,    43,    73,    43,     0,
       0,     0,     0,     0,    47,     0,    25,     0,     0,    27,
       0,     0,    45,    44,     0,     0,    22,     0,     0,     0,
      78,    24,     0,     0,     0,     0,     0,    15,     0,    30,
       0,    32,    33,    34,    29,    18,     0,    19,    39,    37,
      38,    40,    41,     0,    35,     0,    55,    54,    56,    51,
      52,    53,     0,    60,    61,    75,    74,     0,    23,     0,
       0,     0,     0,     0,    26,     0,    28,    20,     0,    46,
      57,    58,    42,     0,    64,    68,    67,    66,    65,     0,
<<<<<<< HEAD
      36,    84,    76,    79,    31,    83,    82,    81,     0,     0,
      77,    80
=======
      36,    81,    76,    31,    80,    79,    78
=======
       7,     8,    14,     0,     0,     0,     0,     0,    73,    18,
       0,     0,     0,    74,    62,    49,    63,     0,     0,    48,
       1,     2,     0,     0,     0,    17,     0,     0,    43,     0,
       0,     0,     0,    15,     0,     0,     0,     0,     0,    22,
      74,    43,    59,     0,    50,    43,    64,    47,     0,    25,
       0,     0,    27,     0,     0,    45,    44,     0,     0,    23,
       0,     0,     0,    68,    16,     0,    30,     0,    32,    33,
      34,    29,    19,     0,    20,    39,    37,    38,    40,    41,
       0,    35,     0,    55,    54,    56,    51,    52,    53,     0,
      60,    61,    66,    65,     0,    24,    26,     0,    28,    21,
       0,    46,    57,    58,    42,     0,     0,    36,    72,    67,
      31,    71,    70,    69
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
       7,     8,    14,     0,     0,     0,     0,     0,    83,    18,
       0,     0,     0,    70,    71,    72,    73,    84,    63,    50,
      64,     0,     0,     0,     0,     0,     0,     0,    49,     1,
       2,     0,     0,     0,    17,     0,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    15,     0,     0,
       0,     0,     0,    22,    84,    44,    60,     0,    51,    44,
      74,    44,     0,     0,     0,     0,     0,    48,     0,    26,
       0,     0,    28,     0,     0,    46,    45,     0,     0,    23,
       0,     0,     0,    78,    25,     0,     0,     0,     0,     0,
      16,     0,    31,     0,    33,    34,    35,    30,    19,     0,
      20,    40,    38,    39,    41,    42,     0,    36,     0,    56,
      55,    57,    52,    53,    54,     0,    61,    62,    76,    75,
       0,    24,     0,     0,     0,     0,     0,    27,     0,    29,
      21,     0,    47,    58,    59,    43,     0,    65,    69,    68,
      67,    66,     0,    37,    82,    77,    32,    81,    80,    79
>>>>>>> feat: 拉取聚合函数部分内容
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,    84,    40,
     -83,   -83,   -82,    21,   -11,   -83,    -8,   -83,   -83,   -83,
     -83,    54,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -17,   -83,    -3,   -54
=======
<<<<<<< HEAD
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,    83,    35,
     -83,   -83,   -82,    19,    21,   -83,    -8,   -83,   -83,   -83,
     -83,    51,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,    -3,   -54
=======
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,    60,    35,
     -78,   -78,   -77,    13,   -45,   -78,    -8,   -78,   -78,   -78,
     -78,    41,   -78,   -78,   -78,   -78,   -78,    -3,   -47
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
     -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,    84,    35,
     -98,   -98,   -97,    21,   -44,   -98,    -8,   -98,   -98,   -98,
     -98,    49,   -98,   -98,   -98,   -98,   -98,   -98,   -98,   -98,
     -98,   -98,    -3,   -56
>>>>>>> feat: 拉取聚合函数部分内容
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
      -1,    16,    17,    18,    19,    20,    21,    85,    88,    86,
     114,   123,   124,    92,    70,    93,    94,    39,   132,   152,
      72,    73,    40,    41,    42,    43,    44,    45,    76,   138,
<<<<<<< HEAD
     162,   163,   167,    46,    47
=======
     162,   166,    46,    47
=======
      -1,    16,    17,    18,    19,    20,    21,    68,    71,    69,
      91,   100,   101,    75,    59,    76,    77,    36,   109,   124,
      61,    62,    37,    65,   115,   129,   133,    38,    39
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
      -1,    16,    17,    18,    19,    20,    21,    88,    91,    89,
     117,   126,   127,    95,    73,    96,    97,    40,   135,   155,
      75,    76,    41,    42,    43,    44,    45,    46,    79,   141,
     165,   169,    47,    48
>>>>>>> feat: 拉取聚合函数部分内容
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
      38,    28,    74,    22,    31,    69,    79,    81,    82,    83,
      84,    87,    89,    89,    71,   134,    98,    23,    25,    27,
      50,    51,    52,    53,   165,    69,    54,    55,    80,    29,
     166,    32,    33,    34,    35,   107,   108,    24,    26,    36,
      30,    74,     1,    99,     2,   168,     3,     4,     5,    75,
     150,     6,    48,    37,    87,    77,    78,     7,    49,     8,
      56,    96,   146,    95,   169,   100,   160,   101,     9,    10,
      11,    12,    13,    14,   -85,   126,   127,   128,    36,   118,
     119,   120,   121,   122,    15,   154,   155,   156,   157,   158,
     129,   130,   131,    57,    58,   135,   136,   109,   110,   111,
     112,   113,   118,   119,   120,   121,   122,   115,   116,    59,
     117,   116,   147,   148,    60,    61,    62,    63,    68,    65,
      66,    64,    67,    69,   151,    71,    36,    91,    97,   102,
     125,   103,   104,   137,   139,   140,   105,   106,   141,   142,
     145,   143,   153,   159,   164,   161,   149,   170,   144,   133,
       0,    90,   171,     0,     0,     0,     0,     0,     0,     0,
       0,   161
=======
<<<<<<< HEAD
      38,    28,    74,    69,    31,    22,    79,    81,    82,    83,
      84,    87,    89,    89,    98,   134,    69,    23,   164,    25,
      50,    51,    52,    53,   165,    27,    54,    55,    29,    71,
      32,    33,    34,    35,   107,   108,    48,    24,    36,    26,
      99,    74,     1,    80,     2,    30,     3,     4,     5,    75,
     150,     6,    37,    95,    87,    77,    78,     7,   -82,     8,
     115,   116,   146,   126,   127,   128,   160,    49,     9,    10,
      11,    12,    13,    14,    57,    56,   117,   116,   129,   130,
     131,   147,   148,    15,    58,   154,   155,   156,   157,   158,
      59,    68,    60,    96,    61,   135,   136,   100,    62,   101,
      36,   118,   119,   120,   121,   122,   109,   110,   111,   112,
     113,   118,   119,   120,   121,   122,    63,    64,    65,    66,
      67,    69,    91,    71,   151,    97,    36,   102,   103,   104,
     125,   137,   105,   139,   140,   106,   141,   142,   143,   145,
     153,   159,   163,   144,   149,   161,   133,     0,     0,     0,
      90
=======
      35,    29,    63,   111,    32,    67,    24,    70,    72,    72,
      26,    22,    58,   131,    28,    33,    79,    84,    85,   132,
      83,    43,    44,    45,    46,    58,    25,    47,    48,    34,
      27,    63,   122,    23,    92,    93,    81,    30,    70,    53,
      40,    31,    64,   127,    78,     1,   118,     2,    66,     3,
       4,     5,    41,    49,     6,    57,    42,    82,    94,    93,
       7,   -73,     8,   119,   120,    50,    51,   103,   104,   105,
      52,     9,    10,    11,    12,    13,    14,    54,   112,   113,
      55,    15,   106,   107,   108,    33,    95,    96,    97,    98,
      99,    86,    87,    88,    89,    90,    95,    96,    97,    98,
      99,   123,    58,    56,    60,    33,    74,   102,    80,   114,
     117,   125,     0,   126,   130,   121,    73,   128,     0,   110,
     116
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
      39,    29,    77,   137,    32,    28,    82,    84,    85,    86,
      87,    22,    90,    92,    92,    72,    72,    33,    34,    35,
      36,    52,    53,    54,    55,    37,   101,    56,    57,    24,
      26,    99,    30,    23,   167,   103,    49,   104,   153,    38,
     168,    31,    77,   -83,   129,   130,   131,    50,    67,    25,
      27,    78,   102,    98,   163,    90,    51,    80,    81,   132,
     133,   134,    74,   149,    58,     1,    59,     2,    62,     3,
       4,     5,   110,   111,     6,    66,    83,    72,   118,   119,
       7,    60,     8,   120,   119,    61,   157,   158,   159,   160,
     161,     9,    10,    11,    12,    13,    14,    74,   138,   139,
      37,   121,   122,   123,   124,   125,    15,   112,   113,   114,
     115,   116,   121,   122,   123,   124,   125,   150,   151,    63,
      71,    64,    65,    68,    37,    69,    70,   154,    94,   128,
     105,   100,   140,   106,   107,   108,   109,   142,   156,   143,
     144,   145,   146,   148,   162,   166,   147,   136,   164,   152,
       0,     0,     0,     0,    93
>>>>>>> feat: 拉取聚合函数部分内容
};

static const yytype_int16 yycheck[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
       8,     4,    56,     4,     7,    17,    60,    61,    62,    63,
      64,    65,    66,    67,    46,    97,    28,     6,     6,    46,
      23,    24,    25,    26,     8,    17,    29,    30,    60,    10,
      14,    38,    39,    40,    41,    54,    55,    26,    26,    46,
      13,    95,     3,    55,     5,    36,     7,     8,     9,    57,
     132,    12,     0,    60,   108,    58,    59,    18,    52,    20,
      19,    72,   116,    55,    55,    76,   148,    78,    29,    30,
      31,    32,    33,    34,    56,    42,    43,    44,    46,    47,
      48,    49,    50,    51,    45,   139,   140,   141,   142,   143,
      57,    58,    59,    55,    13,    98,    99,    21,    22,    23,
      24,    25,    47,    48,    49,    50,    51,    54,    55,    13,
      54,    55,    54,    55,    53,    53,    53,    53,    11,    53,
      53,    56,    53,    17,   132,    46,    46,    53,    57,    54,
      27,    54,    54,    15,    37,    37,    54,    54,    37,    37,
      53,    37,    16,    48,    54,   153,   125,    48,   108,    95,
      -1,    67,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   169
=======
<<<<<<< HEAD
       8,     4,    56,    17,     7,     4,    60,    61,    62,    63,
      64,    65,    66,    67,    28,    97,    17,     6,     8,     6,
      23,    24,    25,    26,    14,    45,    29,    30,    10,    45,
      37,    38,    39,    40,    53,    54,     0,    26,    45,    26,
      54,    95,     3,    59,     5,    13,     7,     8,     9,    57,
     132,    12,    59,    54,   108,    58,    59,    18,    55,    20,
      53,    54,   116,    41,    42,    43,   148,    51,    29,    30,
      31,    32,    33,    34,    54,    19,    53,    54,    56,    57,
      58,    53,    54,    44,    13,   139,   140,   141,   142,   143,
      13,    11,    52,    72,    52,    98,    99,    76,    52,    78,
      45,    46,    47,    48,    49,    50,    21,    22,    23,    24,
      25,    46,    47,    48,    49,    50,    52,    55,    52,    52,
      52,    17,    52,    45,   132,    56,    45,    53,    53,    53,
      27,    15,    53,    36,    36,    53,    36,    36,    36,    52,
      16,    47,    53,   108,   125,   153,    95,    -1,    -1,    -1,
      67
=======
       8,     4,    49,    80,     7,    52,     6,    54,    55,    56,
       6,     4,    17,     8,    40,    40,    61,    48,    49,    14,
      65,    24,    25,    26,    27,    17,    26,    30,    31,    54,
      26,    78,   109,    26,    48,    49,    28,    10,    85,    42,
       0,    13,    50,   120,    49,     3,    93,     5,    51,     7,
       8,     9,    46,    19,    12,    11,    13,    49,    48,    49,
      18,    50,    20,    48,    49,    49,    13,    36,    37,    38,
      50,    29,    30,    31,    32,    33,    34,    47,    81,    82,
      47,    39,    51,    52,    53,    40,    41,    42,    43,    44,
      45,    21,    22,    23,    24,    25,    41,    42,    43,    44,
      45,   109,    17,    47,    40,    40,    47,    27,    51,    15,
      47,    16,    -1,    42,    48,   102,    56,   125,    -1,    78,
      85
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
       8,     4,    58,   100,     7,    45,    62,    63,    64,    65,
      66,     4,    68,    69,    70,    17,    17,    37,    38,    39,
      40,    24,    25,    26,    27,    45,    28,    30,    31,     6,
       6,    75,    10,    26,     8,    79,     0,    81,   135,    59,
      14,    13,    98,    55,    41,    42,    43,    51,    51,    26,
      26,    59,    54,    54,   151,   111,    13,    60,    61,    56,
      57,    58,    45,   119,    19,     3,    54,     5,    52,     7,
       8,     9,    53,    54,    12,    55,    59,    17,    53,    54,
      18,    13,    20,    53,    54,    13,   142,   143,   144,   145,
     146,    29,    30,    31,    32,    33,    34,    45,   101,   102,
      45,    46,    47,    48,    49,    50,    44,    21,    22,    23,
      24,    25,    46,    47,    48,    49,    50,    53,    54,    52,
      11,    52,    52,    52,    45,    52,    52,   135,    52,    27,
      53,    56,    15,    53,    53,    53,    53,    36,    16,    36,
      36,    36,    36,    52,    47,    53,   111,    98,   156,   128,
      -1,    -1,    -1,    -1,    70
>>>>>>> feat: 拉取聚合函数部分内容
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     7,     8,     9,    12,    18,    20,    29,
<<<<<<< HEAD
<<<<<<< HEAD
      30,    31,    32,    33,    34,    45,    62,    63,    64,    65,
      66,    67,     4,     6,    26,     6,    26,    46,    94,    10,
      13,    94,    38,    39,    40,    41,    46,    60,    77,    78,
      83,    84,    85,    86,    87,    88,    94,    95,     0,    52,
      94,    94,    94,    94,    94,    94,    19,    55,    13,    13,
      53,    53,    53,    53,    56,    53,    53,    53,    11,    17,
      75,    46,    81,    82,    95,    77,    89,    94,    94,    95,
      60,    95,    95,    95,    95,    68,    70,    95,    69,    95,
      69,    53,    74,    76,    77,    55,    75,    57,    28,    55,
      75,    75,    54,    54,    54,    54,    54,    54,    55,    21,
      22,    23,    24,    25,    71,    54,    55,    54,    47,    48,
      49,    50,    51,    72,    73,    27,    42,    43,    44,    57,
      58,    59,    79,    82,    73,    94,    94,    15,    90,    37,
      37,    37,    37,    37,    70,    53,    95,    54,    55,    74,
      73,    77,    80,    16,    95,    95,    95,    95,    95,    48,
      73,    77,    91,    92,    54,     8,    14,    93,    36,    55,
      48,    92
=======
<<<<<<< HEAD
      30,    31,    32,    33,    34,    44,    61,    62,    63,    64,
      65,    66,     4,     6,    26,     6,    26,    45,    92,    10,
      13,    92,    37,    38,    39,    40,    45,    59,    76,    77,
      82,    83,    84,    85,    86,    87,    92,    93,     0,    51,
      92,    92,    92,    92,    92,    92,    19,    54,    13,    13,
      52,    52,    52,    52,    55,    52,    52,    52,    11,    17,
      74,    45,    80,    81,    93,    76,    88,    92,    92,    93,
      59,    93,    93,    93,    93,    67,    69,    93,    68,    93,
      68,    52,    73,    75,    76,    54,    74,    56,    28,    54,
      74,    74,    53,    53,    53,    53,    53,    53,    54,    21,
      22,    23,    24,    25,    70,    53,    54,    53,    46,    47,
      48,    49,    50,    71,    72,    27,    41,    42,    43,    56,
      57,    58,    78,    81,    72,    92,    92,    15,    89,    36,
      36,    36,    36,    36,    69,    52,    93,    53,    54,    73,
      72,    76,    79,    16,    93,    93,    93,    93,    93,    47,
      72,    76,    90,    53,     8,    14,    91
=======
      30,    31,    32,    33,    34,    39,    56,    57,    58,    59,
      60,    61,     4,    26,     6,    26,     6,    26,    40,    82,
      10,    13,    82,    40,    54,    71,    72,    77,    82,    83,
       0,    46,    13,    82,    82,    82,    82,    82,    82,    19,
      49,    13,    50,    82,    47,    47,    47,    11,    17,    69,
      40,    75,    76,    83,    71,    78,    82,    83,    62,    64,
      83,    63,    83,    63,    47,    68,    70,    71,    49,    69,
      51,    28,    49,    69,    48,    49,    21,    22,    23,    24,
      25,    65,    48,    49,    48,    41,    42,    43,    44,    45,
      66,    67,    27,    36,    37,    38,    51,    52,    53,    73,
      76,    67,    82,    82,    15,    79,    64,    47,    83,    48,
      49,    68,    67,    71,    74,    16,    42,    67,    71,    80,
      48,     8,    14,    81
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
      30,    31,    32,    33,    34,    44,    61,    62,    63,    64,
      65,    66,     4,    26,     6,    26,     6,    26,    45,    92,
      10,    13,    92,    37,    38,    39,    40,    45,    59,    76,
      77,    82,    83,    84,    85,    86,    87,    92,    93,     0,
      51,    13,    92,    92,    92,    92,    92,    92,    19,    54,
      13,    13,    52,    52,    52,    52,    55,    92,    52,    52,
      52,    11,    17,    74,    45,    80,    81,    93,    76,    88,
      92,    92,    93,    59,    93,    93,    93,    93,    67,    69,
      93,    68,    93,    68,    52,    73,    75,    76,    54,    74,
      56,    28,    54,    74,    74,    53,    53,    53,    53,    53,
      53,    54,    21,    22,    23,    24,    25,    70,    53,    54,
      53,    46,    47,    48,    49,    50,    71,    72,    27,    41,
      42,    43,    56,    57,    58,    78,    81,    72,    92,    92,
      15,    89,    36,    36,    36,    36,    36,    69,    52,    93,
      53,    54,    73,    72,    76,    79,    16,    93,    93,    93,
      93,    93,    47,    72,    76,    90,    53,     8,    14,    91
>>>>>>> feat: 拉取聚合函数部分内容
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
<<<<<<< HEAD
<<<<<<< HEAD
       0,    61,    62,    62,    62,    62,    63,    63,    63,    63,
      64,    64,    64,    64,    65,    66,    66,    66,    66,    66,
      67,    67,    67,    67,    67,    68,    68,    69,    69,    70,
      71,    71,    71,    71,    71,    72,    72,    73,    73,    73,
      73,    73,    74,    75,    75,    76,    76,    77,    77,    78,
      78,    79,    79,    79,    79,    79,    79,    80,    80,    81,
      81,    82,    83,    83,    84,    84,    84,    84,    84,    85,
      86,    87,    88,    89,    89,    89,    90,    90,    90,    91,
      91,    92,    93,    93,    93,    94,    95
=======
<<<<<<< HEAD
       0,    60,    61,    61,    61,    61,    62,    62,    62,    62,
      63,    63,    63,    63,    64,    65,    65,    65,    65,    65,
      66,    66,    66,    66,    66,    67,    67,    68,    68,    69,
      70,    70,    70,    70,    70,    71,    71,    72,    72,    72,
      72,    72,    73,    74,    74,    75,    75,    76,    76,    77,
      77,    78,    78,    78,    78,    78,    78,    79,    79,    80,
      80,    81,    82,    82,    83,    83,    83,    83,    83,    84,
      85,    86,    87,    88,    88,    88,    89,    89,    90,    91,
      91,    91,    92,    93
=======
       0,    55,    56,    56,    56,    56,    57,    57,    57,    57,
      58,    58,    58,    58,    59,    59,    60,    60,    60,    60,
      60,    61,    61,    61,    61,    62,    62,    63,    63,    64,
      65,    65,    65,    65,    65,    66,    66,    67,    67,    67,
      67,    67,    68,    69,    69,    70,    70,    71,    71,    72,
      72,    73,    73,    73,    73,    73,    73,    74,    74,    75,
      75,    76,    77,    77,    78,    78,    78,    79,    79,    80,
      81,    81,    81,    82,    83
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
       0,    60,    61,    61,    61,    61,    62,    62,    62,    62,
      63,    63,    63,    63,    64,    64,    65,    65,    65,    65,
      65,    66,    66,    66,    66,    66,    67,    67,    68,    68,
      69,    70,    70,    70,    70,    70,    71,    71,    72,    72,
      72,    72,    72,    73,    74,    74,    75,    75,    76,    76,
      77,    77,    78,    78,    78,    78,    78,    78,    79,    79,
      80,    80,    81,    82,    82,    83,    83,    83,    83,    83,
      84,    85,    86,    87,    88,    88,    88,    89,    89,    90,
      91,    91,    91,    92,    93
>>>>>>> feat: 拉取聚合函数部分内容
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
<<<<<<< HEAD
<<<<<<< HEAD
       1,     1,     1,     1,     2,     6,     3,     2,     6,     6,
       7,     4,     5,     6,     5,     1,     3,     1,     3,     2,
       1,     4,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     3,     0,     2,     1,     3,     3,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     1,     6,     6,     6,     6,     6,     1,
<<<<<<< HEAD
       1,     1,     1,     1,     3,     3,     3,     5,     0,     1,
       3,     2,     1,     1,     0,     1,     1
=======
       1,     1,     1,     1,     3,     3,     3,     0,     2,     1,
       1,     0,     1,     1
=======
=======
>>>>>>> feat: 拉取聚合函数部分内容
       1,     1,     1,     1,     2,     4,     6,     3,     2,     6,
       6,     7,     4,     5,     6,     5,     1,     3,     1,     3,
       2,     1,     4,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     3,     0,     2,     1,     3,     3,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     1,     6,     6,     6,     6,     6,
       1,     1,     1,     1,     1,     3,     3,     3,     0,     2,
       1,     1,     0,     1,     1
<<<<<<< HEAD
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
>>>>>>> feat: 拉取聚合函数部分内容
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

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
        yyerror (&yylloc, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
<<<<<<< HEAD
#line 64 "yacc.y"
=======
#line 62 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        parse_tree = (yyvsp[-1].sv_node);
        YYACCEPT;
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1598 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1590 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1564 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 3:
#line 69 "yacc.y"
=======
#line 1590 "yacc.tab.cpp"
    break;

  case 3:
#line 67 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        parse_tree = std::make_shared<Help>();
        YYACCEPT;
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1607 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1599 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1573 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 4:
#line 74 "yacc.y"
=======
#line 1599 "yacc.tab.cpp"
    break;

  case 4:
#line 72 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1616 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1608 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1582 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 5:
#line 79 "yacc.y"
=======
#line 1608 "yacc.tab.cpp"
    break;

  case 5:
#line 77 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        parse_tree = nullptr;
        YYACCEPT;
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1625 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1617 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1591 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 10:
#line 94 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
<<<<<<< HEAD
#line 1633 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1625 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1599 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 11:
#line 98 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
<<<<<<< HEAD
#line 1641 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1633 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1607 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 12:
#line 102 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
<<<<<<< HEAD
#line 1649 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1641 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1615 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 13:
#line 106 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
<<<<<<< HEAD
#line 1657 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1649 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1623 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 14:
#line 113 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
<<<<<<< HEAD
#line 1665 "yacc.tab.cpp"
    break;

  case 15:
#line 120 "yacc.y"
=======
<<<<<<< HEAD
#line 1657 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
    break;

  case 15:
#line 118 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.y"
=======
#line 1631 "yacc.tab.cpp"
    break;

  case 15:
#line 112 "yacc.y"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    {
        (yyval.sv_node) = std::make_shared<ShowIndex>((yyvsp[0].sv_str));
    }
<<<<<<< HEAD
#line 1673 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1665 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1639 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 16:
#line 124 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
<<<<<<< HEAD
#line 1681 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1673 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1647 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 17:
#line 128 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
<<<<<<< HEAD
#line 1689 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1681 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1655 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 18:
#line 132 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
<<<<<<< HEAD
#line 1697 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1689 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1663 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 19:
#line 136 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
<<<<<<< HEAD
#line 1705 "yacc.tab.cpp"
    break;

  case 20:
#line 143 "yacc.y"
=======
<<<<<<< HEAD
#line 1697 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
    break;

  case 20:
#line 141 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.y"
=======
#line 1671 "yacc.tab.cpp"
    break;

  case 20:
#line 135 "yacc.y"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
<<<<<<< HEAD
#line 1713 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1705 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1679 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 21:
#line 147 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<InsertStmt>((yyvsp[-4].sv_str), (yyvsp[-1].sv_vals));
    }
<<<<<<< HEAD
#line 1721 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1713 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1687 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 22:
#line 151 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DeleteStmt>((yyvsp[-1].sv_str), (yyvsp[0].sv_conds));
    }
<<<<<<< HEAD
#line 1729 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1721 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1695 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 23:
#line 155 "yacc.y"
=======
#line 1617 "yacc.tab.cpp"
    break;

  case 10:
#line 92 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnBegin>();
    }
#line 1625 "yacc.tab.cpp"
    break;

  case 11:
#line 96 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnCommit>();
    }
#line 1633 "yacc.tab.cpp"
    break;

  case 12:
#line 100 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnAbort>();
    }
#line 1641 "yacc.tab.cpp"
    break;

  case 13:
#line 104 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<TxnRollback>();
    }
#line 1649 "yacc.tab.cpp"
    break;

  case 14:
#line 111 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowTables>();
    }
#line 1657 "yacc.tab.cpp"
    break;

  case 15:
#line 115 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<ShowIndex>((yyvsp[0].sv_str));
    }
#line 1665 "yacc.tab.cpp"
    break;

  case 16:
#line 122 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateTable>((yyvsp[-3].sv_str), (yyvsp[-1].sv_fields));
    }
#line 1673 "yacc.tab.cpp"
    break;

  case 17:
#line 126 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropTable>((yyvsp[0].sv_str));
    }
#line 1681 "yacc.tab.cpp"
    break;

  case 18:
#line 130 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DescTable>((yyvsp[0].sv_str));
    }
#line 1689 "yacc.tab.cpp"
    break;

  case 19:
#line 134 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<CreateIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1697 "yacc.tab.cpp"
    break;

  case 20:
#line 138 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DropIndex>((yyvsp[-3].sv_str), (yyvsp[-1].sv_strs));
    }
#line 1705 "yacc.tab.cpp"
    break;

  case 21:
#line 145 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<InsertStmt>((yyvsp[-4].sv_str), (yyvsp[-1].sv_vals));
    }
#line 1713 "yacc.tab.cpp"
    break;

  case 22:
#line 149 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<DeleteStmt>((yyvsp[-1].sv_str), (yyvsp[0].sv_conds));
    }
#line 1721 "yacc.tab.cpp"
    break;

  case 23:
#line 153 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
<<<<<<< HEAD
        (yyval.sv_node) = std::make_shared<SelectStmt>((yyvsp[-4].sv_cols), (yyvsp[-2].sv_strs), (yyvsp[-1].sv_conds), (yyvsp[0].op_sv_orderbys));
    }
#line 1737 "yacc.tab.cpp"
=======
        (yyval.sv_node) = std::make_shared<UpdateStmt>((yyvsp[-3].sv_str), (yyvsp[-1].sv_set_clauses), (yyvsp[0].sv_conds));
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1729 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 24:
#line 159 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<AggreStmt>((yyvsp[-3].sv_aggre_col), (yyvsp[-1].sv_str), (yyvsp[0].sv_conds));
    }
<<<<<<< HEAD
#line 1745 "yacc.tab.cpp"
=======
#line 1737 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1703 "yacc.tab.cpp"
=======
#line 1729 "yacc.tab.cpp"
>>>>>>> feat: 拉取聚合函数部分内容
    break;

  case 24:
#line 157 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<SelectStmt>((yyvsp[-4].sv_cols), (yyvsp[-2].sv_strs), (yyvsp[-1].sv_conds), (yyvsp[0].sv_orderby));
    }
<<<<<<< HEAD
#line 1711 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 25:
#line 166 "yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
<<<<<<< HEAD
#line 1753 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1745 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 26:
#line 170 "yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
<<<<<<< HEAD
#line 1761 "yacc.tab.cpp"
=======
#line 1753 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1719 "yacc.tab.cpp"
=======
#line 1737 "yacc.tab.cpp"
    break;

  case 25:
#line 161 "yacc.y"
    {
        (yyval.sv_node) = std::make_shared<AggreStmt>((yyvsp[-3].sv_aggre_col), (yyvsp[-1].sv_str), (yyvsp[0].sv_conds));
    }
#line 1745 "yacc.tab.cpp"
>>>>>>> feat: 拉取聚合函数部分内容
    break;

  case 26:
#line 168 "yacc.y"
    {
        (yyval.sv_fields) = std::vector<std::shared_ptr<Field>>{(yyvsp[0].sv_field)};
    }
<<<<<<< HEAD
#line 1727 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 27:
#line 177 "yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
<<<<<<< HEAD
#line 1769 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1761 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 28:
#line 181 "yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 1777 "yacc.tab.cpp"
    break;

  case 29:
#line 188 "yacc.y"
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len));
    }
<<<<<<< HEAD
#line 1785 "yacc.tab.cpp"
=======
#line 1777 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1735 "yacc.tab.cpp"
=======
#line 1753 "yacc.tab.cpp"
    break;

  case 27:
#line 172 "yacc.y"
    {
        (yyval.sv_fields).push_back((yyvsp[0].sv_field));
    }
#line 1761 "yacc.tab.cpp"
>>>>>>> feat: 拉取聚合函数部分内容
    break;

  case 28:
#line 179 "yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 1769 "yacc.tab.cpp"
    break;

  case 29:
#line 183 "yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
<<<<<<< HEAD
#line 1751 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 30:
#line 195 "yacc.y"
=======
#line 1777 "yacc.tab.cpp"
    break;

  case 30:
#line 190 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_field) = std::make_shared<ColDef>((yyvsp[-1].sv_str), (yyvsp[0].sv_type_len));
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1793 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1785 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1759 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 31:
#line 199 "yacc.y"
=======
#line 1785 "yacc.tab.cpp"
    break;

  case 31:
#line 197 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_INT, sizeof(int));
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1801 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1793 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 32:
#line 203 "yacc.y"
=======
#line 1793 "yacc.tab.cpp"
    break;

  case 32:
#line 201 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_STRING, (yyvsp[-1].sv_int));
    }
<<<<<<< HEAD
#line 1809 "yacc.tab.cpp"
    break;

  case 33:
#line 208 "yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_BIGINT, sizeof(int64_t));
    }
#line 1817 "yacc.tab.cpp"
    break;

  case 34:
#line 213 "yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_DATETIME, sizeof(uint64_t));
    }
<<<<<<< HEAD
#line 1825 "yacc.tab.cpp"
=======
#line 1817 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1767 "yacc.tab.cpp"
    break;

  case 32:
#line 198 "yacc.y"
=======
#line 1801 "yacc.tab.cpp"
    break;

  case 33:
#line 205 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_FLOAT, sizeof(float));
    }
#line 1809 "yacc.tab.cpp"
    break;

  case 34:
#line 210 "yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_BIGINT, sizeof(int64_t));
    }
<<<<<<< HEAD
#line 1791 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 35:
#line 220 "yacc.y"
    {
        (yyval.sv_vals) = std::vector<std::shared_ptr<Value>>{(yyvsp[0].sv_val)};
    }
<<<<<<< HEAD
#line 1833 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1825 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 36:
#line 224 "yacc.y"
    {
        (yyval.sv_vals).push_back((yyvsp[0].sv_val));
    }
<<<<<<< HEAD
#line 1841 "yacc.tab.cpp"
=======
#line 1833 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1799 "yacc.tab.cpp"
=======
#line 1817 "yacc.tab.cpp"
    break;

  case 35:
#line 215 "yacc.y"
    {
        (yyval.sv_type_len) = std::make_shared<TypeLen>(SV_TYPE_DATETIME, sizeof(uint64_t));
    }
#line 1825 "yacc.tab.cpp"
>>>>>>> feat: 拉取聚合函数部分内容
    break;

  case 36:
#line 222 "yacc.y"
    {
        (yyval.sv_vals) = std::vector<std::shared_ptr<Value>>{(yyvsp[0].sv_val)};
    }
<<<<<<< HEAD
#line 1807 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 37:
#line 231 "yacc.y"
=======
#line 1833 "yacc.tab.cpp"
    break;

  case 37:
#line 226 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_vals).push_back((yyvsp[0].sv_val));
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1849 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1841 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1815 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 38:
#line 235 "yacc.y"
=======
#line 1841 "yacc.tab.cpp"
    break;

  case 38:
#line 233 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_val) = std::make_shared<IntLit>((yyvsp[0].sv_int));
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1857 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1849 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1823 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 39:
#line 239 "yacc.y"
=======
#line 1849 "yacc.tab.cpp"
    break;

  case 39:
#line 237 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_val) = std::make_shared<FloatLit>((yyvsp[0].sv_float));
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1865 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1857 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1831 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 40:
#line 243 "yacc.y"
=======
#line 1857 "yacc.tab.cpp"
    break;

  case 40:
#line 241 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_val) = std::make_shared<StringLit>((yyvsp[0].sv_str));
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1873 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1865 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 41:
#line 247 "yacc.y"
=======
#line 1865 "yacc.tab.cpp"
    break;

  case 41:
#line 245 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_val) = std::make_shared<BigIntLit>((yyvsp[0].sv_str));
    }
<<<<<<< HEAD
#line 1881 "yacc.tab.cpp"
    break;

  case 42:
#line 254 "yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_col), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_expr));
    }
#line 1889 "yacc.tab.cpp"
    break;

  case 43:
#line 260 "yacc.y"
                      { /* ignore*/ }
#line 1895 "yacc.tab.cpp"
    break;

  case 44:
#line 262 "yacc.y"
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
#line 1903 "yacc.tab.cpp"
    break;

  case 45:
<<<<<<< HEAD
#line 269 "yacc.y"
=======
#line 267 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.y"
=======
#line 1839 "yacc.tab.cpp"
    break;

  case 41:
#line 242 "yacc.y"
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
#line 1873 "yacc.tab.cpp"
    break;

  case 42:
#line 249 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_val) = std::make_shared<DateTimeLit>((yyvsp[0].sv_str));
    }
#line 1881 "yacc.tab.cpp"
    break;

  case 43:
#line 256 "yacc.y"
    {
        (yyval.sv_cond) = std::make_shared<BinaryExpr>((yyvsp[-2].sv_col), (yyvsp[-1].sv_comp_op), (yyvsp[0].sv_expr));
    }
#line 1889 "yacc.tab.cpp"
    break;

  case 44:
#line 262 "yacc.y"
                      { /* ignore*/ }
#line 1895 "yacc.tab.cpp"
    break;

  case 45:
#line 264 "yacc.y"
    {
        (yyval.sv_conds) = (yyvsp[0].sv_conds);
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 1911 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1903 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1869 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 46:
#line 273 "yacc.y"
    {
        (yyval.sv_conds) = std::vector<std::shared_ptr<BinaryExpr>>{(yyvsp[0].sv_cond)};
    }
<<<<<<< HEAD
#line 1919 "yacc.tab.cpp"
    break;

  case 47:
#line 280 "yacc.y"
=======
<<<<<<< HEAD
#line 1911 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
    break;

  case 47:
#line 278 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.y"
=======
#line 1877 "yacc.tab.cpp"
    break;

  case 46:
#line 268 "yacc.y"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    {
        (yyval.sv_conds).push_back((yyvsp[0].sv_cond));
    }
<<<<<<< HEAD
#line 1927 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1919 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1885 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 48:
#line 284 "yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
<<<<<<< HEAD
#line 1935 "yacc.tab.cpp"
    break;

  case 49:
#line 291 "yacc.y"
=======
<<<<<<< HEAD
#line 1927 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
    break;

  case 49:
#line 289 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.y"
=======
#line 1893 "yacc.tab.cpp"
    break;

  case 48:
#line 279 "yacc.y"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    {
        (yyval.sv_col) = std::make_shared<Col>("", (yyvsp[0].sv_str));
    }
<<<<<<< HEAD
#line 1943 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1935 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1901 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 50:
#line 295 "yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[0].sv_col)};
    }
<<<<<<< HEAD
#line 1951 "yacc.tab.cpp"
    break;

  case 51:
#line 302 "yacc.y"
=======
<<<<<<< HEAD
#line 1943 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
    break;

  case 51:
#line 300 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.y"
=======
#line 1909 "yacc.tab.cpp"
    break;

  case 50:
#line 290 "yacc.y"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    {
        (yyval.sv_cols).push_back((yyvsp[0].sv_col));
    }
<<<<<<< HEAD
#line 1959 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1951 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1917 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 52:
#line 306 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_EQ;
    }
<<<<<<< HEAD
#line 1967 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1959 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1925 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 53:
#line 310 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LT;
    }
<<<<<<< HEAD
#line 1975 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1967 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1933 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 54:
#line 314 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GT;
    }
<<<<<<< HEAD
#line 1983 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1975 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1941 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 55:
#line 318 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_NE;
    }
<<<<<<< HEAD
#line 1991 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1983 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1949 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 56:
#line 322 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LE;
    }
<<<<<<< HEAD
#line 1999 "yacc.tab.cpp"
    break;

  case 57:
#line 329 "yacc.y"
=======
<<<<<<< HEAD
#line 1991 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
    break;

  case 57:
#line 327 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.y"
=======
#line 1957 "yacc.tab.cpp"
    break;

  case 56:
#line 317 "yacc.y"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    {
        (yyval.sv_comp_op) = SV_OP_GE;
    }
<<<<<<< HEAD
#line 2007 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 1999 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1965 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 58:
#line 333 "yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_val));
    }
<<<<<<< HEAD
#line 2015 "yacc.tab.cpp"
    break;

  case 59:
#line 340 "yacc.y"
=======
<<<<<<< HEAD
#line 2007 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
    break;

  case 59:
#line 338 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.y"
=======
#line 1973 "yacc.tab.cpp"
    break;

  case 58:
#line 328 "yacc.y"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_col));
    }
<<<<<<< HEAD
#line 2023 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 2015 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 1981 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 60:
#line 344 "yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
<<<<<<< HEAD
#line 2031 "yacc.tab.cpp"
    break;

  case 61:
#line 351 "yacc.y"
=======
<<<<<<< HEAD
#line 2023 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
    break;

  case 61:
#line 349 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.y"
=======
#line 1989 "yacc.tab.cpp"
    break;

  case 60:
#line 339 "yacc.y"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));
    }
<<<<<<< HEAD
#line 2039 "yacc.tab.cpp"
    break;

  case 62:
#line 358 "yacc.y"
=======
<<<<<<< HEAD
#line 2031 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
    break;

  case 62:
#line 356 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.y"
=======
#line 1997 "yacc.tab.cpp"
    break;

  case 61:
#line 346 "yacc.y"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_val));
    }
<<<<<<< HEAD
#line 2047 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 2039 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 64:
#line 366 "yacc.y"
=======
#line 1903 "yacc.tab.cpp"
    break;

  case 46:
#line 271 "yacc.y"
    {
        (yyval.sv_conds) = std::vector<std::shared_ptr<BinaryExpr>>{(yyvsp[0].sv_cond)};
    }
#line 1911 "yacc.tab.cpp"
    break;

  case 47:
#line 275 "yacc.y"
    {
        (yyval.sv_conds).push_back((yyvsp[0].sv_cond));
    }
#line 1919 "yacc.tab.cpp"
    break;

  case 48:
#line 282 "yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>((yyvsp[-2].sv_str), (yyvsp[0].sv_str));
    }
#line 1927 "yacc.tab.cpp"
    break;

  case 49:
#line 286 "yacc.y"
    {
        (yyval.sv_col) = std::make_shared<Col>("", (yyvsp[0].sv_str));
    }
#line 1935 "yacc.tab.cpp"
    break;

  case 50:
#line 293 "yacc.y"
    {
        (yyval.sv_cols) = std::vector<std::shared_ptr<Col>>{(yyvsp[0].sv_col)};
    }
#line 1943 "yacc.tab.cpp"
    break;

  case 51:
#line 297 "yacc.y"
    {
        (yyval.sv_cols).push_back((yyvsp[0].sv_col));
    }
#line 1951 "yacc.tab.cpp"
    break;

  case 52:
#line 304 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_EQ;
    }
#line 1959 "yacc.tab.cpp"
    break;

  case 53:
#line 308 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LT;
    }
#line 1967 "yacc.tab.cpp"
    break;

  case 54:
#line 312 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GT;
    }
#line 1975 "yacc.tab.cpp"
    break;

  case 55:
#line 316 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_NE;
    }
#line 1983 "yacc.tab.cpp"
    break;

  case 56:
#line 320 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_LE;
    }
#line 1991 "yacc.tab.cpp"
    break;

  case 57:
#line 324 "yacc.y"
    {
        (yyval.sv_comp_op) = SV_OP_GE;
    }
#line 1999 "yacc.tab.cpp"
    break;

  case 58:
#line 331 "yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_val));
    }
#line 2007 "yacc.tab.cpp"
    break;

  case 59:
#line 335 "yacc.y"
    {
        (yyval.sv_expr) = std::static_pointer_cast<Expr>((yyvsp[0].sv_col));
    }
#line 2015 "yacc.tab.cpp"
    break;

  case 60:
#line 342 "yacc.y"
    {
        (yyval.sv_set_clauses) = std::vector<std::shared_ptr<SetClause>>{(yyvsp[0].sv_set_clause)};
    }
#line 2023 "yacc.tab.cpp"
    break;

  case 61:
#line 346 "yacc.y"
    {
        (yyval.sv_set_clauses).push_back((yyvsp[0].sv_set_clause));
    }
#line 2031 "yacc.tab.cpp"
    break;

  case 62:
#line 353 "yacc.y"
    {
        (yyval.sv_set_clause) = std::make_shared<SetClause>((yyvsp[-2].sv_str), (yyvsp[0].sv_val));
    }
#line 2039 "yacc.tab.cpp"
    break;

  case 63:
#line 360 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_cols) = {};
    }
<<<<<<< HEAD
#line 2055 "yacc.tab.cpp"
    break;

  case 65:
#line 371 "yacc.y"
    {
        (yyval.sv_aggre_col) = std::make_shared<AggreCol>((yyvsp[-5].sv_ag_type), (yyvsp[-3].sv_str), (yyvsp[0].sv_str));
    }
#line 2063 "yacc.tab.cpp"
    break;

  case 66:
#line 376 "yacc.y"
    {
        (yyval.sv_aggre_col) = std::make_shared<AggreCol>((yyvsp[-5].sv_ag_type), (yyvsp[-3].sv_str), (yyvsp[0].sv_str));
    }
#line 2071 "yacc.tab.cpp"
    break;

  case 67:
#line 380 "yacc.y"
    {
        (yyval.sv_aggre_col) = std::make_shared<AggreCol>((yyvsp[-5].sv_ag_type), (yyvsp[-3].sv_str), (yyvsp[0].sv_str));
    }
#line 2079 "yacc.tab.cpp"
    break;

  case 68:
#line 384 "yacc.y"
=======
#line 2047 "yacc.tab.cpp"
    break;

  case 65:
#line 368 "yacc.y"
    {
        (yyval.sv_aggre_col) = std::make_shared<AggreCol>((yyvsp[-5].sv_ag_type), (yyvsp[-3].sv_str), (yyvsp[0].sv_str));
    }
#line 2055 "yacc.tab.cpp"
    break;

  case 66:
#line 373 "yacc.y"
    {
        (yyval.sv_aggre_col) = std::make_shared<AggreCol>((yyvsp[-5].sv_ag_type), (yyvsp[-3].sv_str), (yyvsp[0].sv_str));
    }
#line 2063 "yacc.tab.cpp"
    break;

  case 67:
#line 378 "yacc.y"
    {
        (yyval.sv_aggre_col) = std::make_shared<AggreCol>((yyvsp[-5].sv_ag_type), (yyvsp[-3].sv_str), (yyvsp[0].sv_str));
    }
#line 2071 "yacc.tab.cpp"
    break;

  case 68:
#line 382 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_aggre_col) = std::make_shared<AggreCol>((yyvsp[-5].sv_ag_type), (yyvsp[-3].sv_str), (yyvsp[0].sv_str));
    }
<<<<<<< HEAD
#line 2087 "yacc.tab.cpp"
    break;

  case 69:
#line 391 "yacc.y"
=======
#line 2079 "yacc.tab.cpp"
    break;

  case 69:
#line 386 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_aggre_col) = std::make_shared<AggreCol>((yyvsp[-5].sv_ag_type), "", (yyvsp[0].sv_str));
    }
<<<<<<< HEAD
#line 2095 "yacc.tab.cpp"
    break;

  case 70:
#line 398 "yacc.y"
=======
#line 2087 "yacc.tab.cpp"
    break;

  case 70:
#line 393 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_ag_type) = SV_AGGRE_SUM;
    }
<<<<<<< HEAD
#line 2103 "yacc.tab.cpp"
    break;

  case 71:
#line 405 "yacc.y"
=======
#line 2095 "yacc.tab.cpp"
    break;

  case 71:
#line 400 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_ag_type) = SV_AGGRE_COUNT;
    }
<<<<<<< HEAD
#line 2111 "yacc.tab.cpp"
    break;

  case 72:
#line 412 "yacc.y"
=======
#line 2103 "yacc.tab.cpp"
    break;

  case 72:
#line 407 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_ag_type) = SV_AGGRE_MAX;
    }
<<<<<<< HEAD
#line 2119 "yacc.tab.cpp"
    break;

  case 73:
<<<<<<< HEAD
#line 419 "yacc.y"
=======
#line 417 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.y"
=======
#line 2005 "yacc.tab.cpp"
    break;

  case 62:
#line 353 "yacc.y"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
#line 2111 "yacc.tab.cpp"
    break;

  case 73:
#line 414 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_ag_type) = SV_AGGRE_MIN;
    }
<<<<<<< HEAD
<<<<<<< HEAD
#line 2127 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 2119 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 2013 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 74:
#line 423 "yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
<<<<<<< HEAD
#line 2135 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 2127 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 2021 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 75:
#line 427 "yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
<<<<<<< HEAD
#line 2143 "yacc.tab.cpp"
=======
<<<<<<< HEAD
#line 2135 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
    break;

  case 76:
#line 435 "yacc.y"
    {
        (yyval.op_sv_orderbys) = std::pair<std::vector<std::shared_ptr<OrderBy>>, int>{(yyvsp[0].sv_orderbys), -1};
    }
#line 2151 "yacc.tab.cpp"
    break;

  case 77:
#line 440 "yacc.y"
    {
        (yyval.op_sv_orderbys) = std::pair<std::vector<std::shared_ptr<OrderBy>>, int>{(yyvsp[-2].sv_orderbys), (yyvsp[0].sv_int)};
    }
#line 2159 "yacc.tab.cpp"
    break;

  case 78:
#line 443 "yacc.y"
                    { /* ignore*/ }
#line 2165 "yacc.tab.cpp"
    break;

  case 79:
#line 448 "yacc.y"
    { 
        (yyval.sv_orderbys) = std::vector<std::shared_ptr<OrderBy>>{(yyvsp[0].sv_orderby)}; 
    }
#line 2173 "yacc.tab.cpp"
    break;

  case 80:
#line 453 "yacc.y"
    {
        (yyval.sv_orderbys).push_back((yyvsp[0].sv_orderby));
    }
#line 2181 "yacc.tab.cpp"
    break;

  case 81:
#line 460 "yacc.y"
    { 
        (yyval.sv_orderby) = std::make_shared<OrderBy>((yyvsp[-1].sv_col), (yyvsp[0].sv_orderby_dir));
    }
#line 2189 "yacc.tab.cpp"
    break;

  case 82:
#line 466 "yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_ASC;     }
#line 2195 "yacc.tab.cpp"
    break;

  case 83:
#line 467 "yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_DESC;    }
#line 2201 "yacc.tab.cpp"
    break;

  case 84:
#line 468 "yacc.y"
            { (yyval.sv_orderby_dir) = OrderBy_DEFAULT; }
#line 2207 "yacc.tab.cpp"
    break;


<<<<<<< HEAD
#line 2211 "yacc.tab.cpp"
=======
#line 2179 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.tab.cpp"
=======
#line 2029 "yacc.tab.cpp"
    break;

  case 66:
#line 369 "yacc.y"
=======
#line 2119 "yacc.tab.cpp"
    break;

  case 74:
#line 421 "yacc.y"
    {
        (yyval.sv_strs) = std::vector<std::string>{(yyvsp[0].sv_str)};
    }
#line 2127 "yacc.tab.cpp"
    break;

  case 75:
#line 425 "yacc.y"
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2135 "yacc.tab.cpp"
    break;

  case 76:
#line 429 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容
    {
        (yyval.sv_strs).push_back((yyvsp[0].sv_str));
    }
#line 2143 "yacc.tab.cpp"
    break;

  case 77:
#line 436 "yacc.y"
    { 
        (yyval.sv_orderby) = (yyvsp[0].sv_orderby); 
    }
#line 2151 "yacc.tab.cpp"
    break;

  case 78:
#line 439 "yacc.y"
                      { /* ignore*/ }
#line 2157 "yacc.tab.cpp"
    break;

  case 79:
#line 444 "yacc.y"
    { 
        (yyval.sv_orderby) = std::make_shared<OrderBy>((yyvsp[-1].sv_col), (yyvsp[0].sv_orderby_dir));
    }
#line 2165 "yacc.tab.cpp"
    break;

  case 80:
#line 450 "yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_ASC;     }
#line 2171 "yacc.tab.cpp"
    break;

  case 81:
#line 451 "yacc.y"
                 { (yyval.sv_orderby_dir) = OrderBy_DESC;    }
#line 2177 "yacc.tab.cpp"
    break;

  case 82:
#line 452 "yacc.y"
            { (yyval.sv_orderby_dir) = OrderBy_DEFAULT; }
#line 2183 "yacc.tab.cpp"
    break;


<<<<<<< HEAD
#line 2081 "yacc.tab.cpp"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
#line 2187 "yacc.tab.cpp"
>>>>>>> feat: 拉取聚合函数部分内容

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
<<<<<<< HEAD
<<<<<<< HEAD
#line 474 "yacc.y"
=======
<<<<<<< HEAD
#line 454 "/home/jhaoc/cpp/rmdb-tut/src/parser/yacc.y"
=======
#line 398 "yacc.y"
>>>>>>> feat: 更改parser的部分以支持index相关操作
>>>>>>> feat: 更改parser的部分以支持index相关操作
=======
#line 458 "yacc.y"
>>>>>>> feat: 拉取聚合函数部分内容

