extern char *malloc(), *realloc();

# line 2 "parse.y"
#define MAXINT "2147483647"
#define MAXUNITS 100
#define PU_END    -1
#define MAXFAC   100
#define MAXTABLE 100
#define NIL      '\0'
int Char_Count = 0;
int Old_Char_Count = 0;
int Line_Count = 1;
int Old_Line_Count = 1;
int integer_value; 
float real_value;
int   traverse;

struct prog_block {
   int id;
   int serve_time ;
   int serve_range ;
   int inter_time  ;
   int inter_range ; 
   int tran_mode;
   int transfer;
   int dist1;
   int dist;
   int mypri;
   char queue_text[80]   ;
   char serve_text[80]  ;
   char rel_text[80]  ;
   char dep_text[80]  ;
   int quit_factor;
   int percent;
   int br_case1;
   int br_case2;
   int br_end;
   int pu_code;
   int parent;
}prog[MAXUNITS]; 
char label[80];
struct server_rec {
   int   unit;
   int   id;
   int   num_servers;
   char  name[80]; 
}fac[MAXFAC];
int buffer[4] = {0,0,0,0}; 
char char_buffer[80];
int prog_unit = 0;
int br_unit   = 0;
int completion_total[20];
struct storage_tbl {
  int value;
  char name[80];
}tbl[MAXTABLE];
int table_cnt = 0;
  
no_runs =0;
no_fac  =0;
init_prog_blk ()
{
  prog_unit++;
  prog[prog_unit].serve_text[0] = NIL;
  prog[prog_unit].queue_text[0] = NIL;
  prog[prog_unit].rel_text[0] = NIL;
  prog[prog_unit].dep_text[0] = NIL;
  prog[prog_unit].pu_code = PU_END;
}              
int strequal(st1,st2)
   char st1[],st2[];                 
{ 
   char str1[80],str2[80];
   int i;
   strcpy(str1,st1);
   strcpy(str2,st2);
   if (strlen(str1) != strlen(str2))
      return 0;
   else
      for(i=0;i<strlen(str1);i++){
         if ((str1[i] <= 'z' ) && (str1[i] >= 'a'))
               str1[i] = str1[i] -32;
         if ((str2[i] <= 'z' ) && (str2[i] >= 'a'))
               str2[i] = str2[i] -32;
      }
      return ! (strcmp(str1,str2)); 
}
# define ADVANCE 257
# define BLANK 258
# define COMMA 259
# define COMMENT 260
# define DEPART 261
# define DIGIT 262
# define DOT 263
# define ENTER 264
# define END 265
# define FILLER 266
# define GENERATE 267
# define IDENTIFIER 268
# define LEAVE 269
# define NEWLINE 270
# define QUEUE 271
# define RELEASE 272
# define SEIZE 273
# define SIMULATE 274
# define START 275
# define STORAGE 276
# define TERMINATE 277
# define TRANSFER 278
# define BOTH 279
# define ALL 280
# define RVNORM 281
# define RVEXPO 282
# define RVERL 283
# define RVUNI 284
# define LPAREN 285
# define RPAREN 286
# define PRIORITY 287
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
#ifndef YYSTYPE
#define YYSTYPE int
#endif
YYSTYPE yylval, yyval;
# define YYERRCODE 256

# line 624 "parse.y"

#include "lex.yy.c"
int yyexca[] ={
-1, 0,
	274, 139,
	-2, 143,
-1, 1,
	0, -1,
	-2, 0,
-1, 4,
	270, 143,
	-2, 139,
-1, 7,
	270, 143,
	-2, 139,
-1, 9,
	270, 143,
	-2, 139,
-1, 43,
	270, 143,
	-2, 139,
-1, 56,
	270, 130,
	-2, 144,
-1, 62,
	270, 130,
	-2, 144,
-1, 70,
	270, 143,
	-2, 139,
-1, 81,
	270, 143,
	-2, 139,
-1, 94,
	267, 4,
	-2, 7,
-1, 108,
	270, 143,
	-2, 139,
-1, 129,
	270, 143,
	-2, 139,
-1, 136,
	270, 143,
	-2, 139,
-1, 140,
	270, 130,
	-2, 144,
-1, 159,
	270, 143,
	-2, 139,
-1, 160,
	270, 143,
	-2, 139,
-1, 178,
	270, 143,
	-2, 139,
-1, 199,
	267, 4,
	-2, 7,
-1, 238,
	270, 143,
	-2, 139,
-1, 239,
	270, 143,
	-2, 139,
-1, 248,
	270, 143,
	-2, 139,
-1, 249,
	270, 143,
	-2, 139,
-1, 250,
	270, 143,
	-2, 139,
-1, 259,
	270, 143,
	-2, 139,
-1, 260,
	270, 143,
	-2, 139,
-1, 265,
	270, 143,
	-2, 139,
-1, 304,
	270, 143,
	-2, 139,
-1, 308,
	270, 143,
	-2, 139,
-1, 325,
	270, 143,
	-2, 139,
-1, 326,
	270, 143,
	-2, 139,
-1, 365,
	270, 143,
	-2, 139,
-1, 373,
	270, 143,
	-2, 139,
-1, 374,
	270, 143,
	-2, 139,
-1, 381,
	270, 143,
	-2, 139,
-1, 384,
	270, 143,
	-2, 139,
	};
# define YYNPROD 172
# define YYLAST 908
int yyact[]={

    58,     4,   181,   105,   340,     4,   109,   283,     4,    39,
     4,    71,   399,   335,   104,   398,   103,    98,   224,   103,
   213,   214,   216,   215,   397,   304,   281,   107,   396,   270,
   208,   113,   269,   268,   113,   267,   114,   106,   293,   114,
   292,   291,   166,   290,     4,   119,    71,   417,   118,    71,
   117,   116,   223,    56,   315,   223,    45,    62,    73,    74,
    76,    75,   222,    62,    39,   328,   219,   223,    67,    67,
     8,     4,    84,   132,    70,   318,   103,   424,    81,   103,
    90,   212,     4,   131,   184,   329,   220,   369,   368,   103,
   208,    90,   222,   114,   113,   192,   114,   223,   221,   114,
   162,   244,   344,   161,   140,   243,     6,   143,   144,     4,
   242,   343,   186,   162,   148,   149,   161,     6,   167,     6,
    72,    47,    39,     9,    39,   420,     6,   173,   416,   264,
     4,   150,   164,    39,   168,   168,   168,     4,   141,    77,
     6,    62,     5,   410,   306,   408,   407,    39,   391,    52,
   189,   307,   182,   194,   194,   194,   194,   382,   351,   345,
     4,     4,   201,   342,   330,   278,   228,   205,   210,    50,
   206,   207,    52,    67,   188,   383,   375,   169,   170,     4,
     6,     6,     5,   319,   289,   227,   211,    68,   127,   239,
   189,    39,    39,   238,    44,   194,    60,    82,    42,    39,
   225,   226,   124,   246,    37,    16,    63,   160,    89,   251,
   282,    12,    13,    11,     3,    66,   198,   121,    79,    13,
    64,   280,   261,   262,   263,   112,    41,   147,   111,   146,
   110,   337,   305,   386,   367,   274,   241,   273,   240,     4,
     4,   409,   202,   275,   276,   277,    13,   314,    53,     4,
     4,     4,   376,    48,    39,   139,   102,    51,   253,   138,
     4,     4,   101,   419,   189,   252,     4,   137,   168,   168,
   168,   168,   100,   123,    39,    39,   284,   285,    54,   265,
   176,    39,   183,   365,   108,    91,    69,   364,   384,   125,
   381,   136,   193,   195,   196,   197,    91,    99,   308,   120,
   130,   129,   373,   135,    97,     4,   134,   338,   339,     4,
   300,   301,   302,   303,    38,    39,   347,   226,   331,   349,
   325,   326,   194,   194,   194,   194,     4,     4,   158,   159,
    96,   357,   348,   133,   171,    95,    65,   165,    39,   356,
   359,    57,    59,    61,   370,   371,   128,   126,   366,    55,
   178,   185,   203,    46,   358,    80,   190,    43,     7,   363,
    85,    86,    87,    88,   229,     1,     4,     0,     0,   387,
   388,   115,     0,     0,     4,     4,     0,    39,    78,   122,
     0,   392,     4,     0,   401,     4,     0,    39,   403,   402,
     0,   142,   182,     0,   125,   400,   190,   168,   168,   168,
   168,   393,   237,   152,   153,   154,   155,   260,     0,     0,
    39,   259,     0,     0,     0,     0,     0,    93,   421,     0,
    39,     0,     0,     0,     0,   174,   175,   177,     0,     0,
   179,   180,     0,     0,     0,   187,   156,     0,   298,   411,
   412,   413,   414,     0,     0,     0,     0,     0,     0,     0,
     0,   204,   151,     0,     0,     0,     0,     0,   288,   157,
     0,   352,   353,   354,   355,     0,     0,     0,     0,     0,
   190,     0,     0,     0,     0,     0,     0,     0,   309,   310,
   232,     0,   233,   234,   235,   316,   191,     0,   245,     0,
     0,     0,   248,   249,   250,     0,     0,     0,   254,     0,
   255,   256,   257,   258,     0,   230,   231,     0,     0,     0,
   209,     0,     0,   236,   266,     0,   218,     0,     0,   346,
     0,     0,    83,     2,     0,     0,   191,    10,     0,     0,
    36,     0,    40,   279,     0,     0,     0,     0,   286,   287,
     0,   247,   360,     0,     0,     0,     0,     0,   296,   297,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   311,   312,   313,     0,    49,     0,     0,   317,
     0,     0,     0,     0,     0,     0,   320,   321,   322,   323,
   324,   395,     0,     0,     0,     0,     0,     0,   332,   333,
   334,   404,     0,     0,     0,     0,     0,     0,     0,     0,
   191,     0,     0,     0,    94,     0,   350,     0,     0,     0,
     0,     0,     0,     0,   418,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   422,   361,   362,     0,     0,     0,
     0,   145,     0,   327,   372,     0,   374,     0,     0,   377,
   378,   379,   380,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   163,     0,     0,     0,     0,   389,   390,   172,
     0,     0,   394,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   405,   406,     0,     0,     0,     0,
     0,     0,   199,   200,     0,     0,     0,     0,   415,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   217,     0,     0,     0,     0,     0,     0,   423,    18,
     6,    17,    19,    20,    67,    21,    23,    22,    24,    26,
    27,    25,     0,    28,    29,    30,    31,    32,    33,    34,
    35,    18,    14,    17,    19,    20,    15,    21,    23,    22,
    24,    26,    27,    25,     0,    28,    29,    30,    31,    32,
    33,    34,    35,     0,     0,     0,     0,     0,     0,     0,
     0,   271,   272,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   294,   295,     0,     0,     0,     0,   299,    18,
     6,    92,    19,    20,     0,    21,    23,    22,    24,    26,
    27,    25,     0,    28,    29,    30,    31,    32,    33,    34,
    35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   336,     0,     0,
     0,   341,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   336,   341,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   385,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   336,     0,     0,   341 };
int yypact[]={

   -78, -1000,  -204,  -147,   -78,   474, -1000,   -78,   -77,   -78,
 -1000, -1000,   474, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000,  -220, -1000,  -149,   474,
 -1000, -1000, -1000,   -78, -1000,   -99,   -95, -1000, -1000,  -220,
 -1000, -1000,   -77, -1000,   -77,   -77,   452,   -72,   -77,  -276,
  -150,  -223,   452,   -77, -1000, -1000, -1000, -1000,   -77, -1000,
   -78,   -77, -1000,   -77,   -77,   -77,   -77, -1000, -1000,   532,
   -89,   -78, -1000,  -241,   -77,  -234,  -235,  -237,  -240, -1000,
   532, -1000,   -77, -1000,  -192, -1000, -1000, -1000, -1000, -1000,
 -1000, -1000, -1000,  -132,   -77, -1000,   -77,   -77,   -78, -1000,
 -1000, -1000, -1000,   -77,  -139,   -89,   -77,   -77,   -77,   -77,
 -1000,   -77,   -89,   -77, -1000, -1000, -1000, -1000,  -155,   -78,
 -1000,   -77,   -77,  -152,  -152,  -152,   -78,  -136,   -77,   -77,
   452, -1000,  -155,   -77,   -77,  -184,   -77,  -158,   -77,   452,
 -1000,  -175,   452,   452,   452,   452, -1000, -1000, -1000,   -78,
   -78,   -77, -1000,  -192,   -77, -1000,   -77, -1000, -1000,   -77,
   -77, -1000,  -238,   -89,  -100,   -73,  -189,  -261,   -78,  -193,
  -180, -1000, -1000,  -168,   -77, -1000, -1000,  -102, -1000,   452,
   -77,   -77, -1000,   -77,   452,   -77,   -77,   -77,   -77,  -192,
  -163,   -77,   -77, -1000,   -89,   -77,   -77,   -77,   -77, -1000,
 -1000,   -77, -1000,   -77,   -77,   -77,   -77,  -163, -1000, -1000,
 -1000,   -77,   -77,  -141, -1000, -1000, -1000,   -77, -1000, -1000,
 -1000, -1000,  -251,  -253,  -254,  -257, -1000, -1000,   -78,   -78,
 -1000, -1000,   -77,   -77,   -77,  -103,   -77, -1000,  -118,  -118,
  -118,   -77,   -77,   -77,   -75,  -242,  -244,  -245,  -247,   -78,
   -78,   -77,   -77,   452, -1000,   -78,  -225,  -152,  -152,  -152,
  -152,  -117,  -117,   -77,   -77,   -77,   -77,   -77, -1000,  -217,
   -77, -1000,   -77, -1000,  -195, -1000,  -210,   -76, -1000,   -77,
   -77,   -77,   -77,   -77,  -117,  -117,  -194,  -104, -1000,  -168,
 -1000,   -77,   -77,   -77,   -78, -1000,   -77,   -77,   -78, -1000,
 -1000,  -105,  -162,  -109,   -77,   -77, -1000,  -276,   -77,   -77,
  -110,   452,   452,   452,   452,   -78,   -78, -1000, -1000, -1000,
 -1000, -1000, -1000, -1000, -1000, -1000,  -178,   -77,   -77,   -77,
 -1000,  -181, -1000,   -77,   -77, -1000, -1000,   -77, -1000,   -77,
   -83, -1000,   -77,   -77,   -77,   -77, -1000, -1000, -1000, -1000,
 -1000,  -111,   -86, -1000, -1000,   -78, -1000, -1000,   -77,   -77,
   -77,   -77,  -120,   -78,  -118,   -77,   -77,  -258,  -262,  -271,
  -274,   -78, -1000,   -77,   -78,  -184,   -77,   -77,   -77,  -122,
  -123, -1000, -1000, -1000,  -125, -1000,  -152,  -152,  -152,  -152,
 -1000,   -77, -1000, -1000, -1000,  -140,  -222, -1000, -1000,   -77,
 -1000, -1000, -1000, -1000, -1000,  -143, -1000,   -77, -1000,   -77,
 -1000,   -77, -1000,  -191, -1000 };
int yypgo[]={

     0,   365,   522,   358,   198,   357,   194,   353,   210,   349,
   286,    14,     7,   202,   347,   346,   200,   197,   335,   333,
    42,     0,    26,   330,   306,   304,   303,   302,   188,   301,
   300,   297,   207,   193,    25,    13,   189,     4,     3,    17,
   291,   290,   288,   287,   284,     2,     6,   283,   282,    18,
   279,   204,   278,   336,   273,   139,   272,   267,   265,   263,
   262,   259,   258,   256,   255,   252,   247,   242,   241,   238,
   237,   236,   235,   234,   233,   232,   231,   230,   229,   228,
   227,   225,   174,   221,   314,   220,   218,   208,   205,   217,
   216,   206,   215,   213,   214,   211 };
int yyr1[]={

     0,     1,     4,     4,     7,     9,     6,    15,    14,    12,
    19,    12,    24,    12,    26,    12,    27,    22,    22,    20,
    20,    13,    13,    13,    28,    28,    31,    31,    31,    40,
    17,    17,    41,    35,    35,    42,    37,    37,    38,    38,
    43,    43,    45,    48,    45,    16,    16,    49,    50,    49,
     3,    52,    54,     5,     8,     8,     8,     8,     8,    57,
    58,    59,    18,    56,    56,    61,    62,    23,    60,    60,
    64,    65,    25,    63,    63,    66,    32,    67,    68,    32,
    70,    33,    69,    69,    72,    36,    71,    71,    74,    47,
    73,    73,    76,    34,    75,    75,    39,    39,    39,    39,
    39,    39,    78,    44,    77,    77,    80,    46,    46,    79,
    79,    81,    81,    83,    29,    11,    11,    30,    51,    86,
    85,    87,    89,    87,    90,    87,    87,    55,    55,    55,
    55,    82,    82,    82,    82,    53,    92,    84,    84,     2,
     2,     2,    94,    94,    10,    10,    21,    93,    93,    95,
    95,    95,    91,    91,    88,    88,    88,    88,    88,    88,
    88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
    88,    88 };
int yyr2[]={

     0,     9,     6,     2,     1,     1,    16,     1,     8,     2,
     1,    14,     1,    22,     1,    14,     1,    10,     2,     2,
     2,     2,     2,     2,     6,     2,    16,    16,     2,     1,
     8,     4,     1,     8,     4,     1,     8,     4,     6,     2,
     6,     2,     2,     1,     4,    12,    12,     2,     1,     8,
     4,     1,     1,    18,     9,    23,    25,    25,    25,     1,
     1,     1,    26,     8,    14,     1,     1,    12,     8,    14,
     1,     1,    20,     8,    14,     1,    12,     1,     1,    20,
     1,     6,     8,    14,     1,     6,     8,    14,     1,     6,
     8,    14,     1,     6,     8,    14,     9,     5,    23,    23,
    23,    23,     1,     6,     8,    14,     1,     6,     3,     6,
    12,     4,    10,     1,    12,    11,     0,     4,     4,     1,
     6,     4,     1,     6,     1,    10,     1,     4,     5,     2,
     1,     4,     5,     4,     1,     2,     3,     4,     0,     0,
     6,     4,     4,     0,     0,     4,     2,     0,     4,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2 };
int yychk[]={

 -1000,    -1,    -2,   -94,   -21,   260,   258,    -3,   274,   270,
    -2,   -93,   -95,   -91,   258,   262,   -88,   259,   257,   260,
   261,   263,   265,   264,   266,   269,   267,   268,   271,   272,
   273,   274,   275,   276,   277,   278,    -2,   -51,   -84,   -21,
    -2,   -93,    -4,    -5,    -6,   276,    -7,   270,   -93,    -2,
   268,    -8,   267,    -4,   -52,    -9,   -21,   -10,   -21,   -10,
   -55,   -10,   -21,   -91,   -85,   -53,   -92,   262,   259,   -10,
   -11,   287,   270,   281,   282,   284,   283,   -55,   -84,   -86,
   -10,   -12,   -17,    -2,   -21,   -10,   -10,   -10,   -10,   -87,
   -21,   -88,   259,   -53,    -2,   -18,   -23,   -25,   -39,   -31,
   -56,   -60,   -63,   257,   -11,   -38,   278,   268,   -44,   -46,
   -77,   -79,   -81,   272,   277,   -10,   285,   285,   285,   285,
   -87,   -89,   -10,   -54,   -13,    -6,   -14,   -28,   -15,   -29,
   -30,   275,   265,   -19,   -24,   -26,   -40,   -57,   -61,   -64,
   -21,   270,   -10,   -21,   -21,    -2,   -78,   -80,   -21,   -21,
   270,   -53,   -10,   -10,   -10,   -10,   -84,   -53,   -51,   -16,
   -32,   271,   268,    -2,   -21,   -51,   -20,   270,   -21,   -20,
   -20,   -17,    -2,   263,   -10,   -10,   -55,   -10,   -32,   -10,
   -10,   -45,   -46,   -48,   268,   -51,   270,   -10,   -82,   -21,
   -91,   -53,   270,   -55,   -21,   -55,   -55,   -55,   -90,    -2,
    -2,   -21,   -67,   -28,   -10,   -21,   -21,   -21,   268,   -53,
   268,   259,   270,   281,   282,   284,   283,    -2,   -53,   259,
   279,   278,   272,   277,   -49,   -16,   -39,   -21,   268,   -82,
   -84,   -84,   -10,   -10,   -10,   -10,   -84,   -13,   -33,   -36,
   -69,   -71,   273,   268,   264,   -10,   -21,   -53,   -10,   -10,
   -10,   -21,   -58,   -62,   -10,   -10,   -10,   -10,   -10,   -33,
   -36,   -21,   -21,   -21,   270,   -50,   -10,   286,   286,   286,
   286,    -2,    -2,   -70,   -72,   -21,   -21,   -21,   268,   -10,
   -83,   -22,    -8,   -12,   -22,   -22,   -10,   -10,   -51,   259,
   285,   285,   285,   285,    -2,    -2,   -10,   -10,   -82,    -2,
   -20,   -20,   -20,   -20,   -34,   -75,   261,   268,   -34,   -51,
   -51,   -10,   -10,   -10,   -66,   271,   -51,   -10,   270,   259,
   -10,   -10,   -10,   -10,   -10,   -34,   -34,   -53,   259,   279,
   268,   -49,   -10,   -10,   -10,   -35,    -2,   -76,   -21,   -21,
   -37,    -2,   268,   273,   264,   268,   -51,   -21,   -11,   -21,
   -10,   268,   -55,   -55,   -55,   -55,   -35,   -37,   -39,   -38,
   -51,   -10,   -10,   -39,   -43,   -47,   -46,   -73,   269,   268,
   -21,   -21,   -10,   -27,   -10,   259,   -65,   -10,   -10,   -10,
   -10,   -41,   268,   261,   -42,    -2,   -74,   -21,   -21,   -10,
   -10,   268,   -12,   -22,   -10,   -51,   286,   286,   286,   286,
   -35,   -21,   -37,   -45,   -51,   -10,   -10,   268,   268,   -68,
   268,   -20,   -20,   -20,   -20,   -10,   268,   269,   -51,   -59,
   268,   -21,   -51,   -10,   268 };
int yydef[]={

    -2,    -2,     0,     0,    -2,   147,   146,    -2,   138,    -2,
   141,   142,   147,   149,   150,   151,   152,   153,   154,   155,
   156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
   166,   167,   168,   169,   170,   171,     4,    50,     0,   147,
   140,   148,     1,    -2,     3,     0,     0,   118,   137,     4,
    51,     5,     0,     2,   144,   144,    -2,     0,   144,   116,
     0,     0,    -2,   138,   129,   119,   135,   136,   144,   145,
    -2,     0,    54,   144,   144,   144,   144,   127,   128,   126,
     0,    -2,     9,   116,   144,     0,     0,     0,     0,   120,
   126,   122,   144,    52,    -2,    10,    12,    14,    29,    31,
    59,    65,    70,     0,   144,    28,     0,     0,    -2,    39,
   102,   106,   108,     0,     0,     0,   144,   144,   144,   144,
   121,   138,     0,   138,     6,    21,    22,    23,     0,    -2,
    25,     0,   138,     0,     0,     0,    -2,     0,   144,   144,
    -2,    97,     0,   144,   144,    43,   138,     0,   144,   134,
   111,     0,   130,   130,   130,   130,   123,   124,    53,    -2,
    -2,     0,    77,     0,   144,   117,     0,    19,    20,     0,
     0,    30,   116,     0,     0,     0,     0,     0,    -2,     0,
     0,    38,    42,     0,     0,   103,   107,     0,   109,   134,
   138,   138,   115,   144,   130,   144,   144,   144,   138,    -2,
     0,   144,     0,    24,     0,   144,   144,   144,     0,    60,
    66,   144,    96,   144,   144,   144,   144,     0,    63,    68,
    73,     0,     0,     0,    44,    47,    48,   144,   104,   131,
   132,   133,     0,     0,     0,     0,   125,     8,    -2,    -2,
    80,    84,     0,     0,     0,     0,   144,   113,    -2,    -2,
    -2,   144,   144,   138,     0,     0,     0,     0,     0,    -2,
    -2,   144,   144,   134,   112,    -2,     0,     0,     0,     0,
     0,     0,     0,   138,   138,   144,   144,   144,    75,     0,
   138,    11,   144,    18,     0,    15,     0,     0,    67,   144,
   144,   144,   144,   144,     0,     0,     0,     0,   110,     0,
    55,   144,   144,   144,    -2,    92,     0,     0,    -2,    81,
    85,     0,     0,     0,   138,     0,   114,   116,     0,   144,
     0,   130,   130,   130,   130,    -2,    -2,    64,    69,    74,
   105,    49,    56,    57,    58,    45,     0,   138,   144,   144,
    46,     0,    82,     0,     0,    86,    76,   144,    16,   144,
     0,    71,   144,   144,   144,   144,    26,    27,    32,    34,
    93,     0,     0,    35,    37,    -2,    41,    88,     0,     0,
   144,   144,     0,    -2,    -2,   144,   138,     0,     0,     0,
     0,    -2,    94,     0,    -2,    43,   138,   144,   144,     0,
     0,    78,    17,    13,     0,    72,     0,     0,     0,     0,
    33,   144,    36,    40,    89,     0,     0,    83,    87,   138,
    61,    98,    99,   100,   101,     0,    90,     0,    79,   138,
    95,   144,    62,     0,    91 };
typedef struct { char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif

#if YYDEBUG

yytoktype yytoks[] =
{
	"ADVANCE",	257,
	"BLANK",	258,
	"COMMA",	259,
	"COMMENT",	260,
	"DEPART",	261,
	"DIGIT",	262,
	"DOT",	263,
	"ENTER",	264,
	"END",	265,
	"FILLER",	266,
	"GENERATE",	267,
	"IDENTIFIER",	268,
	"LEAVE",	269,
	"NEWLINE",	270,
	"QUEUE",	271,
	"RELEASE",	272,
	"SEIZE",	273,
	"SIMULATE",	274,
	"START",	275,
	"STORAGE",	276,
	"TERMINATE",	277,
	"TRANSFER",	278,
	"BOTH",	279,
	"ALL",	280,
	"RVNORM",	281,
	"RVEXPO",	282,
	"RVERL",	283,
	"RVUNI",	284,
	"LPAREN",	285,
	"RPAREN",	286,
	"PRIORITY",	287,
	"-unknown-",	-1	/* ends search */
};

char * yyreds[] =
{
	"-no such reduction-",
	"program : remarks sim_st remarks sto_blk",
	"sto_blk : sto_st remarks sto_blk",
	"sto_blk : prog_blk",
	"prog_blk : /* empty */",
	"prog_blk : gen_st",
	"prog_blk : gen_st spaces pri_st tra_blk remarks opt_prog",
	"prog_blk2 : /* empty */",
	"prog_blk2 : serv_blk remarks opt_prog",
	"tra_blk : fac_blk",
	"tra_blk : remarks tra_st",
	"tra_blk : remarks tra_st opt_nwl space spaces opt_gbw1",
	"tra_blk : remarks tra_st2",
	"tra_blk : remarks tra_st2 opt_nwl space spaces opt_gbw1 NEWLINE space spaces opt_gbw1",
	"tra_blk : remarks tra_st3",
	"tra_blk : remarks tra_st3 opt_nwl space spaces opt_gbw1",
	"opt_gbw1 : gen_st spaces pri_st",
	"opt_gbw1 : gen_st spaces pri_st tra_blk",
	"opt_gbw1 : tra_blk",
	"opt_nwl : NEWLINE",
	"opt_nwl : space",
	"opt_prog : prog_blk",
	"opt_prog : prog_blk2",
	"opt_prog : opt_sta",
	"opt_sta : sta_st remarks opt_sta",
	"opt_sta : end_st",
	"fac_pt : pri_st spaces que_st remarks sei_st remarks dep_st adv_serv1",
	"fac_pt : pri_st spaces que_st remarks ent_st remarks dep_st adv_serv2",
	"fac_pt : rel_blk",
	"fac_blk : remarks adv_st",
	"fac_blk : remarks adv_st fac_blk",
	"fac_blk : remarks fac_pt",
	"adv_serv1 : remarks adv_st",
	"adv_serv1 : remarks adv_st adv_serv1",
	"adv_serv1 : remarks rel_blk",
	"adv_serv2 : remarks adv_st",
	"adv_serv2 : remarks adv_st adv_serv2",
	"adv_serv2 : remarks lev_blk",
	"rel_blk : rel_st remarks new_f",
	"rel_blk : ter_st",
	"lev_blk : lev_st remarks new_f",
	"lev_blk : ter_st",
	"new_f : ter_st",
	"new_f : /* empty */",
	"new_f : new_f_bk",
	"serv_blk : que_st remarks sei_st remarks dep_st adv_serv1",
	"serv_blk : que_st remarks ent_st remarks dep_st adv_serv2",
	"new_f_bk : serv_blk",
	"new_f_bk : adv_st",
	"new_f_bk : adv_st remarks new_f_bk",
	"sim_st : SIMULATE end_rmks",
	"sto_st : STORAGE IDENTIFIER",
	"sto_st : STORAGE IDENTIFIER spaces COMMA spaces number",
	"sto_st : STORAGE IDENTIFIER spaces COMMA spaces number end_rmks",
	"gen_st : GENERATE space opt_pms NEWLINE",
	"gen_st : GENERATE space spaces RVNORM spaces LPAREN spaces opt_pms spaces RPAREN opt_nwl",
	"gen_st : GENERATE space spaces RVEXPO spaces LPAREN spaces opt_pms spaces RPAREN opt_nwl spaces",
	"gen_st : GENERATE space spaces RVUNI spaces LPAREN spaces opt_pms spaces RPAREN opt_nwl spaces",
	"gen_st : GENERATE space spaces RVERL spaces LPAREN spaces opt_pms spaces RPAREN opt_nwl spaces",
	"tra_st : tra_st_lab",
	"tra_st : tra_st_lab DOT number",
	"tra_st : tra_st_lab DOT number spaces COMMA spaces COMMA spaces IDENTIFIER",
	"tra_st : tra_st_lab DOT number spaces COMMA spaces COMMA spaces IDENTIFIER end_rmks",
	"tra_st_lab : TRANSFER space spaces number",
	"tra_st_lab : IDENTIFIER space spaces TRANSFER space spaces number",
	"tra_st2 : tra_st2_lab",
	"tra_st2 : tra_st2_lab spaces IDENTIFIER",
	"tra_st2 : tra_st2_lab spaces IDENTIFIER end_rmks",
	"tra_st2_lab : TRANSFER space spaces COMMA",
	"tra_st2_lab : IDENTIFIER space spaces TRANSFER space spaces COMMA",
	"tra_st3 : tra_st3_lab",
	"tra_st3 : tra_st3_lab spaces COMMA spaces COMMA spaces IDENTIFIER",
	"tra_st3 : tra_st3_lab spaces COMMA spaces COMMA spaces IDENTIFIER end_rmks",
	"tra_st3_lab : TRANSFER space spaces BOTH",
	"tra_st3_lab : IDENTIFIER space spaces TRANSFER space spaces BOTH",
	"que_st : QUEUE space spaces IDENTIFIER",
	"que_st : QUEUE space spaces IDENTIFIER end_rmks",
	"que_st : IDENTIFIER",
	"que_st : IDENTIFIER space spaces QUEUE space spaces IDENTIFIER",
	"que_st : IDENTIFIER space spaces QUEUE space spaces IDENTIFIER end_rmks",
	"sei_st : sei_st_lab",
	"sei_st : sei_st_lab end_rmks",
	"sei_st_lab : SEIZE space spaces IDENTIFIER",
	"sei_st_lab : IDENTIFIER space spaces SEIZE space spaces IDENTIFIER",
	"ent_st : ent_st_lab",
	"ent_st : ent_st_lab end_rmks",
	"ent_st_lab : ENTER space spaces IDENTIFIER",
	"ent_st_lab : IDENTIFIER space spaces ENTER space spaces IDENTIFIER",
	"lev_st : lev_st_lab",
	"lev_st : lev_st_lab end_rmks",
	"lev_st_lab : LEAVE space spaces IDENTIFIER",
	"lev_st_lab : IDENTIFIER space spaces LEAVE space spaces IDENTIFIER",
	"dep_st : dep_st_lab",
	"dep_st : dep_st_lab end_rmks",
	"dep_st_lab : DEPART space spaces IDENTIFIER",
	"dep_st_lab : IDENTIFIER space spaces DEPART space spaces IDENTIFIER",
	"adv_st : ADVANCE space opt_pms NEWLINE",
	"adv_st : ADVANCE NEWLINE",
	"adv_st : ADVANCE space spaces RVNORM spaces LPAREN spaces opt_pms spaces RPAREN opt_nwl",
	"adv_st : ADVANCE space spaces RVEXPO spaces LPAREN spaces opt_pms spaces RPAREN opt_nwl",
	"adv_st : ADVANCE space spaces RVUNI spaces LPAREN spaces opt_pms spaces RPAREN opt_nwl",
	"adv_st : ADVANCE space spaces RVERL spaces LPAREN spaces opt_pms spaces RPAREN opt_nwl",
	"rel_st : rel_st_lab",
	"rel_st : rel_st_lab end_rmks",
	"rel_st_lab : RELEASE space spaces IDENTIFIER",
	"rel_st_lab : IDENTIFIER space spaces RELEASE space spaces IDENTIFIER",
	"ter_st : ter_st_lab1",
	"ter_st : ter_st_lab1 NEWLINE",
	"ter_st : ter_st_lab2",
	"ter_st_lab1 : TERMINATE space opt_num",
	"ter_st_lab1 : IDENTIFIER space spaces TERMINATE space opt_num",
	"ter_st_lab2 : TERMINATE NEWLINE",
	"ter_st_lab2 : IDENTIFIER space spaces TERMINATE NEWLINE",
	"sta_st : START space spaces number",
	"sta_st : START space spaces number end_rmks",
	"pri_st : PRIORITY space spaces number NEWLINE",
	"pri_st : /* empty */",
	"end_st : END end_rmks",
	"end_rmks : note NEWLINE",
	"params : number",
	"params : number opt_pm2",
	"opt_pm2 : space opt_pm2",
	"opt_pm2 : anylet",
	"opt_pm2 : anylet note",
	"opt_pm2 : COMMA spaces number",
	"opt_pm2 : COMMA spaces number note",
	"opt_pm2 : /* empty */",
	"opt_pms : space opt_pms",
	"opt_pms : anyst note",
	"opt_pms : params",
	"opt_pms : /* empty */",
	"opt_num : space opt_num",
	"opt_num : anyst note",
	"opt_num : number note",
	"opt_num : /* empty */",
	"number : integer",
	"integer : DIGIT",
	"note : space anytext",
	"note : /* empty */",
	"remarks : /* empty */",
	"remarks : remark NEWLINE remarks",
	"remarks : space remarks",
	"remark : COMMENT anytext",
	"remark : /* empty */",
	"spaces : /* empty */",
	"spaces : space spaces",
	"space : BLANK",
	"anytext : /* empty */",
	"anytext : vistoken anytext",
	"vistoken : anyst",
	"vistoken : BLANK",
	"vistoken : DIGIT",
	"anyst : anylet",
	"anyst : COMMA",
	"anylet : ADVANCE",
	"anylet : COMMENT",
	"anylet : DEPART",
	"anylet : DOT",
	"anylet : END",
	"anylet : ENTER",
	"anylet : FILLER",
	"anylet : LEAVE",
	"anylet : GENERATE",
	"anylet : IDENTIFIER",
	"anylet : QUEUE",
	"anylet : RELEASE",
	"anylet : SEIZE",
	"anylet : SIMULATE",
	"anylet : START",
	"anylet : STORAGE",
	"anylet : TERMINATE",
	"anylet : TRANSFER",
};
#endif /* YYDEBUG */
#line 1 "/usr/lib/yaccpar"
/*	@(#)yaccpar 1.10 89/04/04 SMI; from S5R3 1.10	*/

/*
** Skeleton parser driver for yacc output
*/

/*
** yacc user known macros and defines
*/
#define YYERROR		goto yyerrlab
#define YYACCEPT	{ free(yys); free(yyv); return(0); }
#define YYABORT		{ free(yys); free(yyv); return(1); }
#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( "syntax error - cannot backup" );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#define YYRECOVERING()	(!!yyerrflag)
#ifndef YYDEBUG
#	define YYDEBUG	1	/* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;			/* set to 1 to get debugging */

/*
** driver internal defines
*/
#define YYFLAG		(-1000)

/*
** static variables used by the parser
*/
static YYSTYPE *yyv;			/* value stack */
static int *yys;			/* state stack */

static YYSTYPE *yypv;			/* top of value stack */
static int *yyps;			/* top of state stack */

static int yystate;			/* current state */
static int yytmp;			/* extra var (lasts between blocks) */

int yynerrs;			/* number of errors */

int yyerrflag;			/* error recovery flag */
int yychar;			/* current input token number */


/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
int
yyparse()
{
	register YYSTYPE *yypvt;	/* top of value stack for $vars */
	unsigned yymaxdepth = YYMAXDEPTH;

	/*
	** Initialize externals - yyparse may be called more than once
	*/
	yyv = (YYSTYPE*)malloc(yymaxdepth*sizeof(YYSTYPE));
	yys = (int*)malloc(yymaxdepth*sizeof(int));
	if (!yyv || !yys)
	{
		yyerror( "out of memory" );
		return(1);
	}
	yypv = &yyv[-1];
	yyps = &yys[-1];
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;

	goto yystack;
	{
		register YYSTYPE *yy_pv;	/* top of value stack */
		register int *yy_ps;		/* top of state stack */
		register int yy_state;		/* current state */
		register int  yy_n;		/* internal state number info */

		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;

		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;

		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;

			(void)printf( "State %d, token ", yy_state );
			if ( yychar == 0 )
				(void)printf( "end-of-file\n" );
			else if ( yychar < 0 )
				(void)printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				(void)printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ yymaxdepth ] )	/* room on stack? */
		{
			/*
			** reallocate and recover.  Note that pointers
			** have to be reset, or bad things will happen
			*/
			int yyps_index = (yy_ps - yys);
			int yypv_index = (yy_pv - yyv);
			int yypvt_index = (yypvt - yyv);
			yymaxdepth += YYMAXDEPTH;
			yyv = (YYSTYPE*)realloc((char*)yyv,
				yymaxdepth * sizeof(YYSTYPE));
			yys = (int*)realloc((char*)yys,
				yymaxdepth * sizeof(int));
			if (!yyv || !yys)
			{
				yyerror( "yacc stack overflow" );
				return(1);
			}
			yy_ps = yys + yyps_index;
			yy_pv = yyv + yypv_index;
			yypvt = yyv + yypvt_index;
		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;

		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;		/* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
			yychar = 0;		/* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;

			(void)printf( "Received token " );
			if ( yychar == 0 )
				(void)printf( "end-of-file\n" );
			else if ( yychar < 0 )
				(void)printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				(void)printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )	/*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}

	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
				yychar = 0;		/* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;

				(void)printf( "Received token " );
				if ( yychar == 0 )
					(void)printf( "end-of-file\n" );
				else if ( yychar < 0 )
					(void)printf( "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					(void)printf( "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register int *yyxi = yyexca;

				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}

		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )	/* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:		/* new error */
				yyerror( "syntax error" );
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
				yynerrs++;
			skip_init:
			case 1:
			case 2:		/* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)					{
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#	define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						(void)printf( _POP_, *yy_ps,
							yy_ps[-1] );
#	undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:		/* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;

					(void)printf( "Error recovery discards " );
					if ( yychar == 0 )
						(void)printf( "token end-of-file\n" );
					else if ( yychar < 0 )
						(void)printf( "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						(void)printf( "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )	/* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			(void)printf( "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;			/* value to switch over */
		yypvt = yy_pv;			/* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];

			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/
	switch( yytmp )
	{
		
case 1:
# line 124 "parse.y"
{
              YYACCEPT;
            } break;
case 4:
# line 133 "parse.y"
{ init_prog_blk() ;
              prog[prog_unit].parent = 1; 

            } break;
case 5:
# line 137 "parse.y"
{
               prog[prog_unit].inter_time = buffer[0];
               prog[prog_unit].inter_range = buffer[1];
            } break;
case 7:
# line 145 "parse.y"
{ prog[prog_unit].pu_code = prog_unit + 1; 
             init_prog_blk();
           } break;
case 10:
# line 152 "parse.y"
{prog[prog_unit].transfer = 1;
                            br_unit = prog_unit;
                           } break;
case 12:
# line 156 "parse.y"
{prog[prog_unit].transfer = 1;
                            br_unit = prog_unit;
                            } break;
case 14:
# line 161 "parse.y"
{prog[prog_unit].transfer = 1;
                            br_unit = prog_unit;
                            } break;
case 16:
# line 172 "parse.y"
{
               prog[prog_unit].inter_time = buffer[0];
               prog[prog_unit].inter_range = buffer[1];
            } break;
case 29:
# line 197 "parse.y"
{
               prog[prog_unit].inter_time += buffer[0];
               prog[prog_unit].inter_range += buffer[1];
            } break;
case 32:
# line 205 "parse.y"
{
               prog[prog_unit].serve_time += buffer[0];
               prog[prog_unit].serve_range += buffer[1];
            } break;
case 35:
# line 213 "parse.y"
{
               prog[prog_unit].serve_time += buffer[0];
               prog[prog_unit].serve_range += buffer[1];
            } break;
case 43:
# line 231 "parse.y"
{ prog[prog_unit].pu_code = prog_unit + 1; 
             init_prog_blk();
           } break;
case 48:
# line 244 "parse.y"
{
               prog[prog_unit].serve_time += buffer[0];
               prog[prog_unit].serve_range += buffer[1];
            } break;
case 51:
# line 255 "parse.y"
{ table_cnt++;
               strcpy(tbl[table_cnt].name,yytext);} break;
case 52:
# line 258 "parse.y"
{ tbl[table_cnt].value = integer_value; } break;
case 54:
# line 262 "parse.y"
{ prog[prog_unit].dist1 = 0; prog[prog_unit].mypri = 1;} break;
case 55:
# line 264 "parse.y"
{prog[prog_unit].dist1 = 1;
                        prog[prog_unit].mypri = 1;} break;
case 56:
# line 267 "parse.y"
{prog[prog_unit].dist1 = 2;
                prog[prog_unit].mypri = 1;} break;
case 57:
# line 270 "parse.y"
{prog[prog_unit].dist1 = 3;
                     prog[prog_unit].mypri = 1;} break;
case 58:
# line 273 "parse.y"
{prog[prog_unit].dist1 = 4;
                         prog[prog_unit].mypri = 1;} break;
case 59:
# line 281 "parse.y"
{  
                if (strlen(yytext) != 1){
                   yyerror("syntax error");
                   YYERROR;
                }
                if ((integer_value == 0) || (integer_value == 1)) {

                  prog[prog_unit].percent = integer_value;
                  prog[prog_unit].tran_mode = 0;

	       }
               else{
                  yyerror("syntax error");
                  YYERROR;
               }
             } break;
case 60:
# line 298 "parse.y"
{  
                if (strlen(yytext) != 2){
                   yyerror("syntax error");
                   YYERROR;
                }
                if (prog[prog_unit].percent ==1) {
                     if (integer_value != 0) {
                      yyerror("syntax error");
                      YYERROR;
                    }
                    else {
                      prog[prog_unit].percent =  100;
                      prog[prog_unit].tran_mode =  0; }

                 }
                 else{
                  if ((integer_value >= 0) || (integer_value <= 99)) {
                    prog[prog_unit].percent = (integer_value);
                    prog[prog_unit].tran_mode = 0;  }
                 else{
                    yyerror("syntax error");
                    YYERROR;
               }
             }
             } break;
case 61:
# line 324 "parse.y"
{ strcpy(label,yytext);
              
             } break;
case 65:
# line 336 "parse.y"
{
                      prog[prog_unit].percent =  100;
                  prog[prog_unit].tran_mode = 0;
             } break;
case 66:
# line 341 "parse.y"
{ strcpy(label,yytext);
              
             } break;
case 70:
# line 354 "parse.y"
{
                      prog[prog_unit].percent =  50;
                     prog[prog_unit].tran_mode =  1;

             } break;
case 71:
# line 361 "parse.y"
{ strcpy(label,yytext);
  
             } break;
case 75:
# line 375 "parse.y"
{ 
               strcpy(prog[prog_unit].queue_text,yytext) ; } break;
case 77:
# line 379 "parse.y"
{     if (prog_unit > 1){ 
                      prog[br_unit].br_case1 = br_unit;
                      prog[br_unit].br_case2 = prog_unit;
                      prog[prog_unit-1].br_end = prog_unit-1;
                      if (strequal(yytext,label) == 0){ 
                        yyerror("syntax error");
                        YYERROR;
                      }
                   }
                
             } break;
case 78:
# line 391 "parse.y"
{ strcpy(prog[prog_unit].queue_text,yytext) ; } break;
case 80:
# line 395 "parse.y"
{  
               strcpy(prog[prog_unit].serve_text,yytext);
      if (strequal(prog[prog_unit].serve_text,prog[prog_unit].queue_text) == 0){
                 /* yyerror("syntax error");
                  YYERROR ; */ ; 
               }
               strcpy(fac[++no_fac].name,yytext);
               fac[no_fac].num_servers = 1;
               fac[no_fac].unit = prog_unit;
              } break;
case 84:
# line 413 "parse.y"
{  
              if (strequal(yytext,prog[prog_unit].queue_text) == 0){
                  yyerror("syntax error");
                  YYERROR ; 
               }
               buffer[3] = 0;           
               for(traverse = 1; traverse<=table_cnt;traverse++){
                    if (strequal(yytext,tbl[traverse].name )== 1){
                           buffer[3] = traverse;
                           break; 
                    }
               }

               
               if (buffer[3] == 0){
                  yyerror("syntax error");
                  YYERROR ; 
               }
               else{
                  strcpy(fac[++no_fac].name,yytext);
                  fac[no_fac].num_servers = tbl[buffer[3]].value;
                  fac[no_fac].unit = prog_unit;
                  strcpy(prog[prog_unit].serve_text,yytext);
              } 
            } break;
case 88:
# line 445 "parse.y"
{
              strcpy(prog[prog_unit].rel_text,yytext) ; 
          if (strequal(prog[prog_unit].rel_text,prog[prog_unit].serve_text) == 0)
                  {yyerror("syntax error");
                  YYERROR ; 
               } 
              } break;
case 92:
# line 460 "parse.y"
{
             strcpy(prog[prog_unit].dep_text,yytext);
        if (strequal(prog[prog_unit].dep_text,prog[prog_unit].queue_text) == 0){
                  yyerror("syntax error");
                  YYERROR ; 
               }
              } break;
case 96:
# line 475 "parse.y"
{ prog[prog_unit].dist = 0;} break;
case 97:
# line 476 "parse.y"
{buffer[0] = buffer[1] = 0;
                    prog[prog_unit].dist = 0; } break;
case 98:
# line 480 "parse.y"
{prog[prog_unit].dist = 1;} break;
case 99:
# line 483 "parse.y"
{prog[prog_unit].dist = 2;} break;
case 100:
# line 486 "parse.y"
{prog[prog_unit].dist = 3;} break;
case 101:
# line 489 "parse.y"
{prog[prog_unit].dist = 4;} break;
case 102:
# line 505 "parse.y"
{
              strcpy(prog[prog_unit].rel_text,yytext) ; 
          if (strequal(prog[prog_unit].rel_text,prog[prog_unit].serve_text) == 0)
                  {yyerror("syntax error");
                  YYERROR ; 
               } 

              } break;
case 106:
# line 519 "parse.y"
{ prog[prog_unit].quit_factor = integer_value; } break;
case 108:
# line 522 "parse.y"
{ prog[prog_unit].quit_factor = 0 ; } break;
case 113:
# line 532 "parse.y"
{ completion_total[++no_runs] = integer_value; } break;
case 115:
# line 539 "parse.y"
{ prog[prog_unit].mypri = integer_value; } break;
case 119:
# line 547 "parse.y"
{ buffer[0] = integer_value;} break;
case 122:
# line 553 "parse.y"
{buffer[1] = 0;} break;
case 124:
# line 554 "parse.y"
{buffer[1] = integer_value;} break;
case 126:
# line 555 "parse.y"
{ buffer[1] = 0;} break;
case 128:
# line 558 "parse.y"
{ buffer[0] = buffer[1] = 0; } break;
case 130:
# line 560 "parse.y"
{buffer[0] = buffer[1] = 0;} break;
case 132:
# line 563 "parse.y"
{ integer_value = 0; } break;
case 134:
# line 565 "parse.y"
{ integer_value = 0; } break;
case 136:
# line 569 "parse.y"
{    
                           if ((yyleng >10) || ((yyleng == 10) &&    
                              (strcmp(yytext,MAXINT) > 0)))  {
                                 yyerror("syntax error"); 
                                 YYERROR;
                           }
                           else
                              integer_value = atoi(yytext); 
                       } break;
	}
	goto yystack;		/* reset registers in driver code */
}
