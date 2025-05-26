# include "stdio.h"
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX BUFSIZ
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin = {stdin}, *yyout = {stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;
# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
{
          integer_value = atoi(yytext);
          process_token();
          return(DIGIT);
}
break;
case 2:
{   
          process_token();
          return(STORAGE);
}
break;
case 3:
{   
          process_token();
          return(TRANSFER);
}
break;
case 4:
{   
          process_token();
          return(ALL);
}
break;
case 5:
{   
          process_token();
          return(BOTH);
}
break;
case 6:
{   
          process_token();
          return(RVEXPO);
}
break;
case 7:
{   
          process_token();
          return(RVNORM);
}
break;
case 8:
{   
          process_token();
          return(RVERL);
}
break;
case 9:
{   
          process_token();
          return(RVUNI);
}
break;
case 10:
{   
          process_token();
          return(ENTER);
}
break;
case 11:
{   
          process_token();
          return(LEAVE);
}
break;
case 12:
{   
          process_token();
          return(GENERATE);
}
break;
case 13:
{   
          process_token();
          return(SIMULATE);
}
break;
case 14:
{   
          process_token();
          return(RELEASE);
}
break;
case 15:
{   
          process_token();
          return(START);
}
break;
case 16:
{   
          process_token();
          return(END);
}
break;
case 17:
{   
          process_token();
          return(QUEUE);
}
break;
case 18:
{   
          process_token();
          return(SEIZE);
}
break;
case 19:
{   
          process_token();
          return(DEPART);
}
break;
case 20:
{   
          process_token();
          return(ADVANCE);
}
break;
case 21:
{
          process_token();
          return(TERMINATE);
}
break;
case 22:
   {   
          process_token();
          return(PRIORITY);
}
break;
case 23:
{
          process_token();
          return(IDENTIFIER);
}
break;
case 24:
{
          process_token();
          return(COMMA);
}
break;
case 25:
{
          process_token();
          return(RPAREN);
}
break;
case 26:
{
          process_token();
          return(LPAREN);
}
break;
case 27:
{
          process_token();
          return(DOT);
}
break;
case 28:
{
          process_token();
          return(COMMENT);
}
break;
case 29:
{
          Old_Char_Count = Char_Count;
          Char_Count = 0;
          Old_Line_Count = Line_Count;
          Line_Count++;
          return(NEWLINE);
}
break;
case 30:
{     
          process_token();
          return(BLANK);
}
break;
case 31:
{ 
          process_token();
          return (FILLER);
}
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */
 process_token()
{
          Old_Char_Count = Char_Count; 
          Char_Count += yyleng;
}

int yyvstop[] = {
0,

31,
0,

29,
0,

29,
31,
0,

30,
31,
0,

26,
31,
0,

25,
31,
0,

28,
31,
0,

24,
31,
0,

27,
31,
0,

1,
31,
0,

23,
31,
0,

23,
31,
0,

23,
31,
0,

23,
31,
0,

23,
31,
0,

23,
31,
0,

23,
31,
0,

23,
31,
0,

23,
31,
0,

23,
31,
0,

23,
31,
0,

23,
31,
0,

1,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

4,
23,
0,

23,
0,

23,
0,

16,
23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

5,
23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

10,
23,
0,

23,
0,

11,
23,
0,

23,
0,

17,
23,
0,

23,
0,

8,
23,
0,

23,
0,

23,
0,

9,
23,
0,

18,
23,
0,

23,
0,

15,
23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

19,
23,
0,

23,
0,

23,
0,

23,
0,

6,
23,
0,

7,
23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

20,
23,
0,

23,
0,

23,
0,

14,
23,
0,

23,
0,

23,
0,

23,
0,

23,
0,

12,
23,
0,

22,
23,
0,

13,
23,
0,

23,
0,

3,
23,
0,

21,
23,
0,

2,
0,
0};
# define YYTYPE char
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	1,3,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	1,4,	
0,0,	0,0,	1,5,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	1,6,	0,0,	0,0,	
0,0,	0,0,	125,127,	0,0,	
0,0,	1,7,	1,8,	1,9,	
122,122,	1,10,	0,0,	1,11,	
0,0,	1,12,	12,25,	12,25,	
12,25,	12,25,	12,25,	12,25,	
12,25,	12,25,	12,25,	12,25,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,13,	1,14,	
1,15,	1,16,	1,17,	1,15,	
1,18,	1,15,	1,15,	1,15,	
1,15,	1,19,	1,15,	1,15,	
1,15,	1,20,	1,21,	1,22,	
1,23,	1,24,	1,15,	1,15,	
1,15,	1,15,	1,15,	1,15,	
0,0,	0,0,	0,0,	122,125,	
0,0,	0,0,	0,0,	1,14,	
1,15,	1,16,	1,17,	1,15,	
1,18,	1,15,	1,15,	1,15,	
1,15,	1,19,	1,15,	1,15,	
1,15,	1,20,	1,21,	1,22,	
1,23,	1,24,	1,15,	1,15,	
1,15,	1,15,	1,15,	1,15,	
2,7,	2,8,	2,9,	122,125,	
2,10,	0,0,	2,11,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	2,14,	2,15,	
2,16,	2,17,	2,15,	2,18,	
2,15,	2,15,	2,15,	2,15,	
2,19,	2,15,	2,15,	2,15,	
2,20,	2,21,	2,22,	2,23,	
2,24,	2,15,	2,15,	2,15,	
2,15,	2,15,	2,15,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	2,14,	2,15,	
2,16,	2,17,	2,15,	2,18,	
2,15,	2,15,	2,15,	2,15,	
2,19,	2,15,	2,15,	2,15,	
2,20,	2,21,	2,22,	2,23,	
2,24,	2,15,	2,15,	2,15,	
2,15,	2,15,	2,15,	13,26,	
13,26,	13,26,	13,26,	13,26,	
13,26,	13,26,	13,26,	13,26,	
13,26,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
13,26,	13,26,	13,26,	13,27,	
13,26,	13,26,	13,26,	13,26,	
13,26,	13,26,	13,26,	13,28,	
13,26,	13,26,	13,26,	13,26,	
13,26,	13,26,	13,26,	13,26,	
13,26,	13,26,	13,26,	13,26,	
13,26,	13,26,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
13,26,	13,26,	13,26,	13,27,	
13,26,	13,26,	13,26,	13,26,	
13,26,	13,26,	13,26,	13,28,	
13,26,	13,26,	13,26,	13,26,	
13,26,	13,26,	13,26,	13,26,	
13,26,	13,26,	13,26,	13,26,	
13,26,	13,26,	14,26,	15,26,	
16,26,	16,30,	17,26,	18,26,	
18,32,	0,0,	14,26,	15,26,	
16,26,	14,29,	17,26,	18,26,	
17,31,	19,26,	19,33,	20,26,	
0,0,	0,0,	0,0,	26,26,	
21,26,	19,26,	0,0,	20,26,	
0,0,	0,0,	0,0,	26,26,	
21,26,	20,34,	14,26,	15,26,	
16,26,	16,30,	17,26,	18,26,	
18,32,	21,35,	14,26,	15,26,	
16,26,	14,29,	17,26,	18,26,	
17,31,	19,26,	19,33,	20,26,	
22,26,	22,36,	0,0,	26,26,	
21,26,	19,26,	0,0,	20,26,	
22,26,	23,26,	23,38,	26,26,	
21,26,	20,34,	23,39,	24,26,	
24,41,	23,26,	22,37,	27,26,	
28,26,	21,35,	29,26,	24,26,	
0,0,	23,40,	32,26,	27,26,	
28,44,	24,42,	29,26,	30,26,	
22,26,	22,36,	32,26,	0,0,	
32,49,	27,43,	29,45,	30,26,	
22,26,	23,26,	23,38,	30,46,	
0,0,	0,0,	23,39,	24,26,	
24,41,	23,26,	22,37,	27,26,	
28,26,	0,0,	29,26,	24,26,	
31,47,	23,40,	32,26,	27,26,	
28,44,	24,42,	29,26,	30,26,	
31,26,	0,0,	32,26,	0,0,	
32,49,	27,43,	29,45,	30,26,	
31,48,	33,50,	34,26,	30,46,	
33,26,	35,26,	35,52,	34,51,	
0,0,	36,26,	34,26,	40,59,	
33,26,	35,26,	40,26,	38,26,	
31,47,	36,53,	37,26,	37,54,	
38,57,	39,26,	40,26,	38,26,	
31,26,	40,60,	37,26,	0,0,	
37,55,	39,26,	39,58,	0,0,	
31,48,	33,50,	34,26,	37,56,	
33,26,	35,26,	35,52,	34,51,	
44,26,	36,26,	34,26,	40,59,	
33,26,	35,26,	40,26,	38,26,	
44,26,	36,53,	37,26,	37,54,	
38,57,	39,26,	40,26,	38,26,	
41,26,	40,60,	37,26,	0,0,	
37,55,	39,26,	39,58,	42,62,	
41,26,	43,63,	42,26,	37,56,	
43,26,	45,26,	41,61,	47,26,	
44,26,	45,64,	42,26,	46,65,	
43,26,	45,26,	46,26,	47,26,	
44,26,	48,26,	48,66,	49,26,	
49,67,	0,0,	46,26,	0,0,	
41,26,	48,26,	0,0,	49,26,	
0,0,	0,0,	0,0,	42,62,	
41,26,	43,63,	42,26,	0,0,	
43,26,	45,26,	41,61,	47,26,	
50,26,	45,64,	42,26,	46,65,	
43,26,	45,26,	46,26,	47,26,	
50,26,	48,26,	48,66,	49,26,	
49,67,	51,26,	46,26,	53,26,	
53,71,	48,26,	50,68,	49,26,	
52,26,	51,26,	54,26,	53,26,	
51,69,	0,0,	0,0,	55,26,	
52,26,	0,0,	54,26,	56,26,	
50,26,	0,0,	0,0,	55,26,	
54,72,	52,70,	55,74,	56,26,	
50,26,	56,75,	54,73,	57,26,	
0,0,	51,26,	0,0,	53,26,	
53,71,	58,26,	50,68,	57,26,	
52,26,	51,26,	54,26,	53,26,	
51,69,	58,26,	0,0,	55,26,	
52,26,	0,0,	54,26,	56,26,	
59,26,	57,76,	58,77,	55,26,	
54,72,	52,70,	55,74,	56,26,	
59,26,	56,75,	54,73,	57,26,	
60,26,	61,26,	59,78,	64,26,	
65,26,	58,26,	0,0,	57,26,	
60,26,	61,26,	61,80,	64,26,	
65,26,	58,26,	60,79,	62,26,	
63,26,	0,0,	65,83,	0,0,	
59,26,	57,76,	58,77,	62,26,	
63,26,	62,81,	63,82,	0,0,	
59,26,	68,26,	68,86,	66,26,	
60,26,	61,26,	59,78,	64,26,	
65,26,	68,26,	0,0,	66,26,	
60,26,	61,26,	61,80,	64,26,	
65,26,	66,84,	60,79,	62,26,	
63,26,	0,0,	65,83,	67,26,	
69,26,	0,0,	0,0,	62,26,	
63,26,	62,81,	63,82,	67,26,	
69,26,	68,26,	68,86,	66,26,	
72,26,	67,85,	69,87,	70,26,	
70,88,	68,26,	71,89,	66,26,	
72,90,	71,26,	73,26,	70,26,	
0,0,	66,84,	0,0,	74,26,	
75,26,	71,26,	73,26,	67,26,	
69,26,	75,93,	73,91,	74,26,	
75,26,	0,0,	0,0,	67,26,	
69,26,	74,92,	0,0,	77,26,	
72,26,	67,85,	69,87,	70,26,	
70,88,	0,0,	71,89,	77,95,	
72,90,	71,26,	73,26,	70,26,	
76,26,	76,94,	0,0,	74,26,	
75,26,	71,26,	73,26,	78,26,	
76,26,	75,93,	73,91,	74,26,	
75,26,	79,97,	81,26,	78,26,	
79,26,	74,92,	0,0,	77,26,	
80,26,	0,0,	81,26,	78,96,	
79,26,	80,98,	0,0,	77,95,	
80,26,	81,99,	84,26,	0,0,	
76,26,	76,94,	82,100,	82,26,	
0,0,	0,0,	84,26,	78,26,	
76,26,	86,26,	83,26,	82,26,	
0,0,	79,97,	81,26,	78,26,	
79,26,	86,26,	83,26,	88,26,	
80,26,	0,0,	81,26,	78,96,	
79,26,	80,98,	83,101,	88,26,	
80,26,	81,99,	84,26,	89,26,	
87,26,	85,102,	82,100,	82,26,	
85,26,	87,103,	84,26,	89,26,	
87,26,	86,26,	83,26,	82,26,	
85,26,	90,26,	89,104,	92,26,	
0,0,	86,26,	83,26,	88,26,	
93,26,	90,26,	0,0,	92,26,	
92,106,	0,0,	83,101,	88,26,	
93,26,	0,0,	91,26,	89,26,	
87,26,	85,102,	94,26,	96,26,	
85,26,	87,103,	91,26,	89,26,	
87,26,	91,105,	94,26,	96,26,	
85,26,	90,26,	89,104,	92,26,	
95,107,	100,26,	100,111,	95,26,	
93,26,	90,26,	0,0,	92,26,	
92,106,	100,26,	0,0,	95,26,	
93,26,	97,26,	91,26,	99,26,	
97,108,	99,110,	94,26,	96,26,	
98,26,	97,26,	91,26,	99,26,	
0,0,	91,105,	94,26,	96,26,	
98,26,	101,26,	98,109,	105,26,	
95,107,	100,26,	100,111,	95,26,	
106,26,	101,26,	102,26,	105,26,	
0,0,	100,26,	103,26,	95,26,	
106,26,	97,26,	102,26,	99,26,	
97,108,	99,110,	103,26,	107,26,	
98,26,	97,26,	102,112,	99,26,	
104,26,	104,114,	103,113,	107,26,	
98,26,	101,26,	98,109,	105,26,	
104,26,	108,26,	108,116,	107,115,	
106,26,	101,26,	102,26,	105,26,	
0,0,	108,26,	103,26,	0,0,	
106,26,	111,26,	102,26,	110,26,	
110,118,	109,117,	103,26,	107,26,	
109,26,	111,26,	102,112,	110,26,	
104,26,	104,114,	103,113,	107,26,	
109,26,	112,26,	112,119,	114,26,	
104,26,	108,26,	108,116,	107,115,	
113,26,	112,26,	117,26,	114,26,	
0,0,	108,26,	115,26,	115,121,	
113,26,	111,26,	117,26,	110,26,	
110,118,	109,117,	115,26,	116,122,	
109,26,	111,26,	117,123,	110,26,	
119,26,	113,120,	118,26,	120,26,	
109,26,	112,26,	112,119,	114,26,	
119,26,	121,26,	118,26,	120,26,	
113,26,	112,26,	117,26,	114,26,	
118,124,	121,26,	115,26,	115,121,	
113,26,	0,0,	117,26,	0,0,	
0,0,	0,0,	115,26,	0,0,	
123,26,	123,126,	117,123,	116,26,	
119,26,	113,120,	118,26,	120,26,	
123,26,	124,26,	126,26,	116,26,	
119,26,	121,26,	118,26,	120,26,	
0,0,	124,26,	126,26,	0,0,	
118,124,	121,26,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
123,26,	123,126,	0,0,	116,26,	
0,0,	0,0,	0,0,	0,0,	
123,26,	124,26,	126,26,	116,26,	
0,0,	0,0,	0,0,	0,0,	
0,0,	124,26,	126,26,	0,0,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		0,	
yycrank+-84,	yysvec+1,	0,	
yycrank+0,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+3,
yycrank+0,	0,		yyvstop+5,
yycrank+0,	0,		yyvstop+8,
yycrank+0,	0,		yyvstop+11,
yycrank+0,	0,		yyvstop+14,
yycrank+0,	0,		yyvstop+17,
yycrank+0,	0,		yyvstop+20,
yycrank+0,	0,		yyvstop+23,
yycrank+2,	0,		yyvstop+26,
yycrank+159,	0,		yyvstop+29,
yycrank+214,	yysvec+13,	yyvstop+32,
yycrank+215,	yysvec+13,	yyvstop+35,
yycrank+216,	yysvec+13,	yyvstop+38,
yycrank+218,	yysvec+13,	yyvstop+41,
yycrank+219,	yysvec+13,	yyvstop+44,
yycrank+229,	yysvec+13,	yyvstop+47,
yycrank+231,	yysvec+13,	yyvstop+50,
yycrank+236,	yysvec+13,	yyvstop+53,
yycrank+264,	yysvec+13,	yyvstop+56,
yycrank+273,	yysvec+13,	yyvstop+59,
yycrank+279,	yysvec+13,	yyvstop+62,
yycrank+0,	yysvec+12,	yyvstop+65,
yycrank+235,	yysvec+13,	yyvstop+67,
yycrank+283,	yysvec+13,	yyvstop+69,
yycrank+284,	yysvec+13,	yyvstop+71,
yycrank+286,	yysvec+13,	yyvstop+73,
yycrank+295,	yysvec+13,	yyvstop+75,
yycrank+320,	yysvec+13,	yyvstop+77,
yycrank+290,	yysvec+13,	yyvstop+79,
yycrank+340,	yysvec+13,	yyvstop+81,
yycrank+338,	yysvec+13,	yyvstop+83,
yycrank+341,	yysvec+13,	yyvstop+85,
yycrank+345,	yysvec+13,	yyvstop+87,
yycrank+354,	yysvec+13,	yyvstop+89,
yycrank+351,	yysvec+13,	yyvstop+91,
yycrank+357,	yysvec+13,	yyvstop+93,
yycrank+350,	yysvec+13,	yyvstop+95,
yycrank+392,	yysvec+13,	yyvstop+97,
yycrank+402,	yysvec+13,	yyvstop+99,
yycrank+404,	yysvec+13,	yyvstop+101,
yycrank+376,	yysvec+13,	yyvstop+103,
yycrank+405,	yysvec+13,	yyvstop+106,
yycrank+414,	yysvec+13,	yyvstop+108,
yycrank+407,	yysvec+13,	yyvstop+110,
yycrank+417,	yysvec+13,	yyvstop+113,
yycrank+419,	yysvec+13,	yyvstop+115,
yycrank+440,	yysvec+13,	yyvstop+117,
yycrank+453,	yysvec+13,	yyvstop+119,
yycrank+460,	yysvec+13,	yyvstop+121,
yycrank+455,	yysvec+13,	yyvstop+123,
yycrank+462,	yysvec+13,	yyvstop+125,
yycrank+467,	yysvec+13,	yyvstop+127,
yycrank+471,	yysvec+13,	yyvstop+129,
yycrank+483,	yysvec+13,	yyvstop+131,
yycrank+489,	yysvec+13,	yyvstop+133,
yycrank+504,	yysvec+13,	yyvstop+135,
yycrank+516,	yysvec+13,	yyvstop+137,
yycrank+517,	yysvec+13,	yyvstop+139,
yycrank+531,	yysvec+13,	yyvstop+141,
yycrank+532,	yysvec+13,	yyvstop+143,
yycrank+519,	yysvec+13,	yyvstop+145,
yycrank+520,	yysvec+13,	yyvstop+148,
yycrank+547,	yysvec+13,	yyvstop+150,
yycrank+567,	yysvec+13,	yyvstop+152,
yycrank+545,	yysvec+13,	yyvstop+154,
yycrank+568,	yysvec+13,	yyvstop+156,
yycrank+583,	yysvec+13,	yyvstop+158,
yycrank+589,	yysvec+13,	yyvstop+160,
yycrank+580,	yysvec+13,	yyvstop+162,
yycrank+590,	yysvec+13,	yyvstop+164,
yycrank+595,	yysvec+13,	yyvstop+166,
yycrank+596,	yysvec+13,	yyvstop+168,
yycrank+624,	yysvec+13,	yyvstop+170,
yycrank+611,	yysvec+13,	yyvstop+172,
yycrank+631,	yysvec+13,	yyvstop+174,
yycrank+640,	yysvec+13,	yyvstop+176,
yycrank+644,	yysvec+13,	yyvstop+178,
yycrank+638,	yysvec+13,	yyvstop+180,
yycrank+659,	yysvec+13,	yyvstop+182,
yycrank+666,	yysvec+13,	yyvstop+184,
yycrank+654,	yysvec+13,	yyvstop+186,
yycrank+692,	yysvec+13,	yyvstop+189,
yycrank+665,	yysvec+13,	yyvstop+191,
yycrank+688,	yysvec+13,	yyvstop+194,
yycrank+675,	yysvec+13,	yyvstop+196,
yycrank+687,	yysvec+13,	yyvstop+199,
yycrank+701,	yysvec+13,	yyvstop+201,
yycrank+718,	yysvec+13,	yyvstop+204,
yycrank+703,	yysvec+13,	yyvstop+206,
yycrank+708,	yysvec+13,	yyvstop+208,
yycrank+722,	yysvec+13,	yyvstop+211,
yycrank+739,	yysvec+13,	yyvstop+214,
yycrank+723,	yysvec+13,	yyvstop+216,
yycrank+749,	yysvec+13,	yyvstop+219,
yycrank+756,	yysvec+13,	yyvstop+221,
yycrank+751,	yysvec+13,	yyvstop+223,
yycrank+737,	yysvec+13,	yyvstop+225,
yycrank+765,	yysvec+13,	yyvstop+227,
yycrank+774,	yysvec+13,	yyvstop+230,
yycrank+778,	yysvec+13,	yyvstop+232,
yycrank+792,	yysvec+13,	yyvstop+234,
yycrank+767,	yysvec+13,	yyvstop+236,
yycrank+772,	yysvec+13,	yyvstop+239,
yycrank+787,	yysvec+13,	yyvstop+242,
yycrank+801,	yysvec+13,	yyvstop+244,
yycrank+820,	yysvec+13,	yyvstop+246,
yycrank+815,	yysvec+13,	yyvstop+248,
yycrank+813,	yysvec+13,	yyvstop+250,
yycrank+829,	yysvec+13,	yyvstop+253,
yycrank+836,	yysvec+13,	yyvstop+255,
yycrank+831,	yysvec+13,	yyvstop+257,
yycrank+842,	yysvec+13,	yyvstop+260,
yycrank+887,	yysvec+13,	yyvstop+262,
yycrank+838,	yysvec+13,	yyvstop+264,
yycrank+858,	yysvec+13,	yyvstop+266,
yycrank+856,	yysvec+13,	yyvstop+268,
yycrank+859,	yysvec+13,	yyvstop+271,
yycrank+865,	yysvec+13,	yyvstop+274,
yycrank+12,	0,		0,	
yycrank+884,	yysvec+13,	yyvstop+277,
yycrank+893,	yysvec+13,	yyvstop+279,
yycrank+2,	0,		0,	
yycrank+894,	yysvec+13,	yyvstop+282,
yycrank+0,	0,		yyvstop+285,
0,	0,	0};
struct yywork *yytop = yycrank+1002;
struct yysvf *yybgin = yysvec+1;
char yymatch[] = {
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,012 ,01  ,01  ,015 ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
040 ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,01  ,01  ,01  ,01  ,01  ,
0};
char yyextra[] = {
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
#ifndef lint
static	char ncform_sccsid[] = "@(#)ncform 1.6 88/02/08 SMI"; /* from S5R2 1.2 */
#endif

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych, yyfirst;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	yyfirst=1;
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank && !yyfirst){  /* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
			yyfirst=0;
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
yyback(p, m)
	int *p;
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	}
yyoutput(c)
  int c; {
	output(c);
	}
yyunput(c)
   int c; {
	unput(c);
	}
