%%
([0-9]+) {
          integer_value = atoi(yytext);
          process_token();
          return(DIGIT);
}
(S|s)(T|t)(O|o)(R|r)(A|a)(G|g)(E|e)([ ]+)(S|s)($) {   
          process_token();
          return(STORAGE);
}
(T|t)(R|r)(A|a)(N|n)(S|s)(F|f)(E|e)(R|r) {   
          process_token();
          return(TRANSFER);
}
(A|a)(L|l)(L|l) {   
          process_token();
          return(ALL);
}
(B|b)(O|o)(T|t)(H|h) {   
          process_token();
          return(BOTH);
}
(R|r)(V|v)(E|e)(X|x)(P|p)(O|o) {   
          process_token();
          return(RVEXPO);
}
(R|r)(V|v)(N|n)(O|o)(R|r)(M|m) {   
          process_token();
          return(RVNORM);
}

(R|r)(V|v)(E|e)(R|r)(L|l) {   
          process_token();
          return(RVERL);
}
(R|r)(V|v)(U|u)(N|n)(I|i) {   
          process_token();
          return(RVUNI);
}


(E|e)(N|n)(T|t)(E|e)(R|r) {   
          process_token();
          return(ENTER);
}
(L|l)(E|e)(A|a)(V|v)(E|e) {   
          process_token();
          return(LEAVE);
}
(G|g)(E|e)(N|n)(E|e)(R|r)(A|a)(T|t)(E|e) {   
          process_token();
          return(GENERATE);
}
(S|s)(I|i)(M|m)(U|u)(L|l)(A|a)(T|t)(E|e) {   
          process_token();
          return(SIMULATE);
}
(R|r)(E|e)(L|l)(E|e)(A|a)(S|s)(E|e) {   
          process_token();
          return(RELEASE);
}
(S|s)(T|t)(A|a)(R|r)(T|t) {   
          process_token();
          return(START);
}
(E|e)(N|n)(D|d) {   
          process_token();
          return(END);
}
(Q|q)(U|u)(E|e)(U|u)(E|e) {   
          process_token();
          return(QUEUE);
}

(S|s)(E|e)(I|i)(Z|z)(E|e) {   
          process_token();
          return(SEIZE);
}
(D|d)(E|e)(P|p)(A|a)(R|r)(T|t) {   
          process_token();
          return(DEPART);
}
(A|a)(D|d)(V|v)(A|a)(N|n)(C|c)(E|e) {   
          process_token();
          return(ADVANCE);
}
(T|t)(E|e)(R|r)(M|m)(I|i)(N|n)(A|a)(T|t)(E|e) {
          process_token();
          return(TERMINATE);
}

(P|p)(R|r)(I|i)(O|o)(R|r)(I|i)(T|t)(Y|y)    {   
          process_token();
          return(PRIORITY);
}


[A-Za-z][A-Za-z0-9]* {
          process_token();
          return(IDENTIFIER);
}
"," {
          process_token();
          return(COMMA);
}


")" {
          process_token();
          return(RPAREN);
}


"(" {
          process_token();
          return(LPAREN);
}

"." {
          process_token();
          return(DOT);
}
"*" {
          process_token();
          return(COMMENT);
}
[\n\r] {
          Old_Char_Count = Char_Count;
          Char_Count = 0;
          Old_Line_Count = Line_Count;
          Line_Count++;
          return(NEWLINE);
}
[ ] {     
          process_token();
          return(BLANK);
}
. { 
          process_token();
          return (FILLER);
}
%%
 process_token()
{
          Old_Char_Count = Char_Count; 
          Char_Count += yyleng;
}

