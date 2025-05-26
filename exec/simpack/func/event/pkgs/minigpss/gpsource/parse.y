%{
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
%}
 
%token ADVANCE
%token BLANK
%token COMMA
%token COMMENT
%token DEPART
%token DIGIT
%token DOT
%token ENTER
%token END
%token FILLER
%token GENERATE
%token IDENTIFIER
%token LEAVE
%token NEWLINE
%token QUEUE 
%token RELEASE
%token SEIZE
%token SIMULATE
%token START
%token STORAGE
%token TERMINATE 
%token TRANSFER
%token BOTH
%token ALL
%token RVNORM
%token RVEXPO
%token RVERL
%token RVUNI
%token LPAREN
%token RPAREN
%token PRIORITY


%%
program   :  
            remarks sim_st remarks sto_blk  
            {
              YYACCEPT;
            }
          ;
sto_blk  :
            sto_st remarks sto_blk |
            prog_blk
          ;
prog_blk  :  
            { init_prog_blk() ;
              prog[prog_unit].parent = 1; 

            } gen_st 
            {
               prog[prog_unit].inter_time = buffer[0];
               prog[prog_unit].inter_range = buffer[1];
            }  spaces pri_st
              tra_blk 
            remarks opt_prog
          ; 
prog_blk2 :
           { prog[prog_unit].pu_code = prog_unit + 1; 
             init_prog_blk();
           } 
           serv_blk remarks opt_prog
     ;
tra_blk  :
            fac_blk| 
            remarks tra_st {prog[prog_unit].transfer = 1;
                            br_unit = prog_unit;
                           }
            opt_nwl space spaces opt_gbw1  |
            remarks tra_st2 {prog[prog_unit].transfer = 1;
                            br_unit = prog_unit;
                            }    
            opt_nwl space spaces opt_gbw1            
NEWLINE space spaces opt_gbw1  |
            remarks tra_st3 {prog[prog_unit].transfer = 1;
                            br_unit = prog_unit;
                            }    
            opt_nwl space spaces opt_gbw1            

     ;




opt_gbw1  :  gen_st spaces pri_st 
     {
               prog[prog_unit].inter_time = buffer[0];
               prog[prog_unit].inter_range = buffer[1];
            }

     tra_blk | tra_blk;  

opt_nwl : NEWLINE | space;

          
opt_prog :
           prog_blk | 
           prog_blk2|
           opt_sta 
         ;
opt_sta  :
           sta_st remarks opt_sta |
           end_st
          ;
fac_pt     :   pri_st spaces que_st remarks sei_st remarks dep_st adv_serv1|
               pri_st spaces que_st remarks ent_st remarks dep_st adv_serv2 |
               rel_blk 
           ;
fac_blk  :
             remarks adv_st  
            {
               prog[prog_unit].inter_time += buffer[0];
               prog[prog_unit].inter_range += buffer[1];
            } fac_blk |
             remarks fac_pt
            ;
adv_serv1 :
             remarks adv_st  
            {
               prog[prog_unit].serve_time += buffer[0];
               prog[prog_unit].serve_range += buffer[1];
            } adv_serv1|
             remarks rel_blk 
            ;
adv_serv2 :
             remarks adv_st  
            {
               prog[prog_unit].serve_time += buffer[0];
               prog[prog_unit].serve_range += buffer[1];
            } adv_serv2|
             remarks lev_blk 
            ;
rel_blk     : 
            rel_st remarks new_f |
            ter_st 
          ;
lev_blk     : 
            lev_st 
            remarks
            new_f|
            ter_st
          ;
new_f:
           ter_st |
           { prog[prog_unit].pu_code = prog_unit + 1; 
             init_prog_blk();
           } 
            new_f_bk
           ;
serv_blk  :que_st remarks sei_st remarks dep_st adv_serv1|
           que_st remarks ent_st remarks dep_st adv_serv2 
          ;

      
new_f_bk : serv_blk | 
           
           adv_st 
            {
               prog[prog_unit].serve_time += buffer[0];
               prog[prog_unit].serve_range += buffer[1];
            }
           remarks new_f_bk 
         ;
sim_st   :   SIMULATE
             end_rmks 
          ;
sto_st   :
              STORAGE IDENTIFIER 
              { table_cnt++;
               strcpy(tbl[table_cnt].name,yytext);}
              spaces COMMA spaces number
              { tbl[table_cnt].value = integer_value; }
              end_rmks
          ;
gen_st   :   GENERATE space opt_pms NEWLINE 
       { prog[prog_unit].dist1 = 0; prog[prog_unit].mypri = 1;}   |
GENERATE space spaces  RVNORM spaces LPAREN  spaces opt_pms  
             spaces RPAREN  opt_nwl  {prog[prog_unit].dist1 = 1;
                        prog[prog_unit].mypri = 1;} |
GENERATE space spaces RVEXPO  spaces LPAREN spaces opt_pms
             spaces RPAREN opt_nwl spaces {prog[prog_unit].dist1 = 2;
                prog[prog_unit].mypri = 1;} |
GENERATE space spaces RVUNI spaces LPAREN spaces opt_pms
             spaces RPAREN opt_nwl spaces {prog[prog_unit].dist1 = 3;
                     prog[prog_unit].mypri = 1;} |
GENERATE space spaces RVERL spaces LPAREN spaces opt_pms
              spaces  RPAREN opt_nwl spaces  {prog[prog_unit].dist1 = 4;
                         prog[prog_unit].mypri = 1;} 

          ;



tra_st   :   tra_st_lab  
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
             }
             DOT number 
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
             }
             spaces COMMA spaces COMMA spaces IDENTIFIER
             { strcpy(label,yytext);
              
             }
             end_rmks     
             
          ;

tra_st_lab   :   TRANSFER space spaces number |
                 IDENTIFIER space spaces TRANSFER space spaces number;  


tra_st2   :     tra_st2_lab
{
                      prog[prog_unit].percent =  100;
                  prog[prog_unit].tran_mode = 0;
             }
             spaces IDENTIFIER
             { strcpy(label,yytext);
              
             }
             end_rmks     
             
          ;


tra_st2_lab   :   TRANSFER space spaces COMMA |
                  IDENTIFIER space spaces TRANSFER space spaces COMMA;  


tra_st3   :  tra_st3_lab
{
                      prog[prog_unit].percent =  50;
                     prog[prog_unit].tran_mode =  1;

             }
             spaces COMMA spaces COMMA 
          spaces IDENTIFIER
             { strcpy(label,yytext);
  
             }
             end_rmks     
             
          ;



tra_st3_lab   :   TRANSFER space spaces  BOTH 
                    |IDENTIFIER space spaces TRANSFER space spaces  BOTH
            ;

que_st   :   QUEUE space spaces IDENTIFIER 
             { 
               strcpy(prog[prog_unit].queue_text,yytext) ; }
             end_rmks |
             IDENTIFIER
             {     if (prog_unit > 1){ 
                      prog[br_unit].br_case1 = br_unit;
                      prog[br_unit].br_case2 = prog_unit;
                      prog[prog_unit-1].br_end = prog_unit-1;
                      if (strequal(yytext,label) == 0){ 
                        yyerror("syntax error");
                        YYERROR;
                      }
                   }
                
             }
             space spaces QUEUE space spaces IDENTIFIER
             { strcpy(prog[prog_unit].queue_text,yytext) ; }
             end_rmks 
          ;
sei_st   :   sei_st_lab
             {  
               strcpy(prog[prog_unit].serve_text,yytext);
      if (strequal(prog[prog_unit].serve_text,prog[prog_unit].queue_text) == 0){
                 /* yyerror("syntax error");
                  YYERROR ; */ ; 
               }
               strcpy(fac[++no_fac].name,yytext);
               fac[no_fac].num_servers = 1;
               fac[no_fac].unit = prog_unit;
              }
             end_rmks 
          ;


sei_st_lab   :   SEIZE space spaces IDENTIFIER |
                 IDENTIFIER space spaces SEIZE space spaces IDENTIFIER;

ent_st   :   ent_st_lab
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
            }
             end_rmks 
          ;

ent_st_lab   :   ENTER space spaces IDENTIFIER |
                 IDENTIFIER space spaces ENTER space spaces IDENTIFIER;

lev_st   :   lev_st_lab
               {
              strcpy(prog[prog_unit].rel_text,yytext) ; 
          if (strequal(prog[prog_unit].rel_text,prog[prog_unit].serve_text) == 0)
                  {yyerror("syntax error");
                  YYERROR ; 
               } 
              } 
             end_rmks 
          ;


lev_st_lab   :   LEAVE space spaces IDENTIFIER |
                 IDENTIFIER  space spaces LEAVE space spaces IDENTIFIER;

dep_st   :   dep_st_lab
               {
             strcpy(prog[prog_unit].dep_text,yytext);
        if (strequal(prog[prog_unit].dep_text,prog[prog_unit].queue_text) == 0){
                  yyerror("syntax error");
                  YYERROR ; 
               }
              } 
             end_rmks 
          ;

dep_st_lab   :   DEPART space spaces IDENTIFIER |
                   IDENTIFIER  space spaces DEPART space spaces IDENTIFIER;


adv_st   :   ADVANCE space opt_pms NEWLINE
        { prog[prog_unit].dist = 0;}    |
             ADVANCE NEWLINE {buffer[0] = buffer[1] = 0;
                    prog[prog_unit].dist = 0; }    |

         ADVANCE  space spaces  RVNORM spaces LPAREN  spaces opt_pms  
             spaces RPAREN opt_nwl  {prog[prog_unit].dist = 1;} |

         ADVANCE  space spaces  RVEXPO spaces LPAREN  spaces opt_pms  
             spaces RPAREN opt_nwl  {prog[prog_unit].dist = 2;} |

         ADVANCE  space spaces  RVUNI spaces LPAREN  spaces opt_pms  
             spaces RPAREN opt_nwl  {prog[prog_unit].dist = 3;} |

         ADVANCE  space spaces  RVERL spaces LPAREN  spaces opt_pms  
             spaces RPAREN opt_nwl  {prog[prog_unit].dist = 4;} 



/*
            ADVANCE space spaces RVNORM space opt_pms NEWLINE
 { prog[prog_unit].dist = 1;}    |
            ADVANCE space spaces RVEXPO space opt_pms NEWLINE
           { prog[prog_unit].dist = 2;}    |
               ADVANCE space spaces RVERL  space opt_pms NEWLINE   
             {prog[prog_unit].dist = 3;}   |
              ADVANCE space spaces RVUNI space opt_pms NEWLINE
              {prog[prog_unit].dist = 4;}            
  */           
          ;
rel_st   :   rel_st_lab
               {
              strcpy(prog[prog_unit].rel_text,yytext) ; 
          if (strequal(prog[prog_unit].rel_text,prog[prog_unit].serve_text) == 0)
                  {yyerror("syntax error");
                  YYERROR ; 
               } 

              }
             end_rmks   
          ;
rel_st_lab   :   RELEASE space spaces IDENTIFIER |
                 IDENTIFIER space spaces RELEASE space spaces IDENTIFIER;

ter_st   :   ter_st_lab1
             { prog[prog_unit].quit_factor = integer_value; }  
             NEWLINE   |
             ter_st_lab2
             { prog[prog_unit].quit_factor = 0 ; }
          ;

ter_st_lab1 : TERMINATE space opt_num | IDENTIFIER space spaces
          TERMINATE space opt_num;

ter_st_lab2 : TERMINATE NEWLINE | IDENTIFIER space spaces 
              TERMINATE NEWLINE; 

sta_st  :   START space spaces number
             { completion_total[++no_runs] = integer_value; }
                 
            end_rmks 
          ;


pri_st : PRIORITY space spaces number NEWLINE
                  { prog[prog_unit].mypri = integer_value; } |
    ;
end_st   :   END 
             end_rmks 
          ;
end_rmks :   note NEWLINE
          ;
params   :    number
                { buffer[0] = integer_value;}
              opt_pm2


opt_pm2  :
               space opt_pm2|
               anylet   {buffer[1] = 0;} note|
               COMMA spaces number {buffer[1] = integer_value;} note|
                /* null */ { buffer[1] = 0;} 
          ; 
opt_pms   :    space opt_pms |
               anyst note { buffer[0] = buffer[1] = 0; } | 
               params  |
               /* null */ {buffer[0] = buffer[1] = 0;}
          ;
opt_num  :   space opt_num|
             anyst  note { integer_value = 0; } |           
             number note  |
             /* null */ { integer_value = 0; }
          ;
number   :   integer
           ;
integer  :   DIGIT    {    
                           if ((yyleng >10) || ((yyleng == 10) &&    
                              (strcmp(yytext,MAXINT) > 0)))  {
                                 yyerror("syntax error"); 
                                 YYERROR;
                           }
                           else
                              integer_value = atoi(yytext); 
                       }
           ;
note     :  space anytext |
            /* null */ 
          ;
remarks  : /* null */ |
           remark NEWLINE  remarks |
           space remarks 
           ;
remark   :  COMMENT anytext |
            /* null */  
          ;
spaces   :  /* null */ |
            space spaces 
          ;
space    :  BLANK
          ;
anytext  :  /* null */ |
            vistoken anytext
          ;
vistoken :  anyst |
            BLANK |
            DIGIT  
          ;  
anyst    :
            anylet|
            COMMA;

anylet    :  ADVANCE |
            COMMENT |
            DEPART | 
            DOT |
            END | 
            ENTER |
            FILLER | 
            LEAVE |
            GENERATE |
            IDENTIFIER | 
            QUEUE | 
            RELEASE | 
            SEIZE | 
            SIMULATE |
            START | 
            STORAGE |
            TERMINATE |
            TRANSFER     
           ;
%%
#include "lex.yy.c"
