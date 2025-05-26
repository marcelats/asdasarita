
yyerror(s)
  char *s;
{
  printf("%s: ",s);

  print_error(yychar); 
  printf(" not expected",yychar);
  printf(" on line %d column %d. \n",Old_Line_Count+1, Old_Char_Count + 1  ); 
}
    
print_error(number)
   int number;
{
   switch(number){
   case DOT : 
                      printf("decimal point");
                      break; 
   case BLANK : 
                      printf("\' \'");
                      break; 
   case TRANSFER : 
                      printf("transfer statement");
                      break; 
   case ENTER : 
                      printf("enter statement");
                      break; 
   case LEAVE : 
                      printf("leave statement");
                      break; 
   case DIGIT : 
                      printf("literal");
                      break; 
   case GENERATE : 
                      printf("generate statement");
                      break; 
   case SIMULATE : 
                      printf("simulate statement");
                      break; 
   case STORAGE : 
                      printf("storage statement");
                      break; 
   case RELEASE : 
                      printf("release statement");
                      break; 
   case START : 
                      printf("start statement");
                      break; 
   case END : 
                      printf("end statement");
                      break; 
   case QUEUE : 
                      printf("queue statement");
                      break; 
   case SEIZE : 
                      printf("seize statement");
                      break; 
   case DEPART : 
                      printf("depart statement");
                      break; 
   case ADVANCE : 
                      printf("advance statement");
                      break; 
   case TERMINATE : 
                      printf("terminate statement");
                      break; 
   case IDENTIFIER : 
                      printf("identifier");
                      break; 
   case COMMA : 
                      printf("\',\'");
                      break; 
   case COMMENT : 
                      printf("\'*\'");
                      break; 
   case NEWLINE : 
                      printf("end of line");
                      break; 
   default:               
                      printf("invalid token");
                      break; 
                      
   }
}
