/*---------------------------------------------
                   S I M P A C K
               Simulation Tool Package
           Copyright 1990, Paul A. Fishwick

This routine was written by a senior as part of
his senior thesis (James Bowman) in COP 4300 -
Systems Simulation at the University of Florida,
Dept. of Computer and Inf. Sciences.
---------------------------------------------*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct node {
    int marks,prior,max_kids;
    char text[10];
    struct node *parent,*lchild,*rchild;
  };
typedef struct node *nodeptr;
nodeptr *rootptr,*lastptr,last,root,token;
char dim,adim,ch,s[80];
int lefts,time_present=0,minus=0,uni=1, high_order;
FILE *fp;
float number;
typedef char phrase[80];
phrase msg[9] = {
  "",
  "Variable not in correct form. Should be like 'x[3]'.\n",
  "Order of variable >= specified high-order variable.\n",
  "Unexpected character of ",
  "Expecting a scale after e.\n",
  "Not expecting two decimal points in a number.\n",
  "Unmatched right parenthesis.\n",
  "Too many arguments in function.\n",
  "Expecting a function id.\n"
  };

int parse(void);
int lower(int c);
int lookup(char *s,int *time_present,char *dim);
nodeptr package_token(int m,int p,int k,char *t);
int decrement_mark(nodeptr *l,int *lefts);
void place_token(nodeptr *rootptr,nodeptr *lastptr,nodeptr token);
void attempt_lift(nodeptr *rootptr,nodeptr *lastptr,nodeptr token);
int number_of_kids(nodeptr token);
int dump_tree(FILE *fp,nodeptr root);
void print_error(int ec,char *ch);


/* gets necessary information and controls output */

main()
{
    char i,d;
    float bt,et,dt;

      root=last=NULL;
      rootptr=&root;
      lastptr=&last;
    fp = fopen("dump.in","w");
    printf("Welcome to Diffy Plotter.\n\n");
    printf("Which do you want to enter, a (S)ystem of 1st-order equations");
    printf("\n                         or a (H)igher-order equation?\n");
    printf("Enter 's' or 'h': ");
    scanf(" %c",&i);
    if (lower(i)=='s') {
       high_order = 0;
       printf("\n\nEnter dimension of system: ");
       scanf(" %c",&dim);
       fprintf(fp," %c\n",dim);
       d=dim--;
       for (i='1';i<=d;i++) {
	 printf("\nx[%c]' = ",i);
	 scanf(" ");
	 while (parse() > 0) {
	   printf("\nPress 'c' to reenter an equation. ");
	   scanf("%*[^cC]");
	   printf("\nx[%c]' = ",i);
	 } 
	 fprintf(fp,"x%c'=",i);
	 dump_tree(fp,root);
	 fprintf(fp,";\n");
       }
       
       /* get initial conditions */

       i = 'y';
       while (i == 'y') {
	 printf("\n\nEnter set of initial conditions.");
	 for (i='1';i<=d;i++) {
	   printf("\nx[%c] = ",i);
	   scanf(" %f",&number);
	   fprintf(fp,"\nx%c = %f",i,number);
	 }
	 
      	 printf("\n\nEnter another set of initial conditions? (y/n) ");
	 scanf("%*[^yYnN]");
	 i=lower(getchar());
       }
      
       /* get time constraints */ 

       printf("\nstart time = ");
       scanf(" %f",&bt);
       printf("\nend time = ");
       scanf(" %f",&et);
       printf("\ntime step size = ");
       scanf(" %f",&dt);
       fprintf(fp,"\nbt = %f",bt);
       fprintf(fp,"\net = %f",et);
       fprintf(fp,"\ndt = %f",dt);

       /* get plot info */

       printf("\n\nPlot what vs. what?");
       printf("\nx-axis (t or x[i]): ");
       scanf(" ");
       if (lower(getchar()) == 'x') {
	 scanf(" [ %c ]",&dim);
	 fprintf(fp,"\nx%c vs. ",dim);
       }
       else
	 fprintf(fp,"\nt vs. ");
       printf("\ny-axis (t, x[i], or a): ");
       scanf(" ");
       switch (lower(getchar())) {
       case 'x':
	 scanf(" [ %c ]",&dim);
	 fprintf(fp,"x%c\n",dim);
       break;
       case 't':
	 fprintf(fp,"t\n");
       break;
       default:
	 fprintf(fp,"a\n");
       }; /* switch */
    }


    else { /* higher-order equation */

       high_order = 1;
       printf("\n\nEnter an equation: ");
       scanf("%*[^xX]%*c");
       if (getchar() == '[') {
	 scanf("%*[^1234567890] ");
	 dim = getchar();
	 scanf("%*[^=]%*c");
	 while (parse() > 0) {
	   printf("\nPress 'c' to reenter the expression. ");
	   scanf("%*[^cC]%*c]");
	   printf("\nx[%c] = ",dim);
	 }
	 fprintf(fp,"%c\n",dim);
         printf("\nYour differential equation has an order of %c.",dim);
         if (time_present) {
           fprintf(fp,"x%c'=1.0;\n",dim--);
	   fprintf(fp,"x%c'=",dim);
	 }
         else
	   fprintf(fp,"x%c'=",dim);
         dump_tree(fp,*rootptr);
         fprintf(fp,";\n");
         for (i='1';i<dim;i++)
           fprintf(fp,"x%c'=x%c;\n",i,i+1);

	 /* get initial conditions */

         i = 'y';
         while (i == 'y') {
	   printf("\nEnter initial conditions.");
           for (i='0';i<=dim-1;i++) {
             printf("\nx[%c] = ",i);
             scanf("%f",&number);
	     fprintf(fp,"x%c = %f\n",i+1,number);
           }
      	 printf("\n\nEnter another set of initial conditions? (y/n) ");
	 scanf("%*[^yYnN]");
	 i=lower(getchar());
	 }

	 /* get time constraints */

         printf("\nstart time = ");
         scanf("%f",&number);
         if (time_present)
           fprintf(fp,"x%c = %f\n",dim+1,number);
         fprintf(fp,"bt = %f\n",number);
         printf("\nend time = ");
         scanf("%f",&number);
         fprintf(fp,"et = %f\n",number);
         printf("\ntime step size = ");
         scanf("%f",&number);
         fprintf(fp,"dt = %f\n",number);
     
         /* get plot info */

       printf("\n\nPlot what vs. what?");
       printf("\nx-axis (t or x[i]): ");
       scanf(" ");
       if (lower(getchar()) == 'x') {
	 scanf(" [ %c ]",&dim);
	 fprintf(fp,"x%c vs. ",dim+1);
       }
       else
	 fprintf(fp,"t vs. ");
       printf("\ny-axis (t, x[i], or a): ");
       scanf(" ");
       switch (lower(getchar())) {
       case 'x':
	 scanf(" [ %c ]",&dim);
	 fprintf(fp,"x%c\n",dim+1);
       break;
       case 't':
	 fprintf(fp,"t\n");
       break;
       default:
	 fprintf(fp,"a\n");
       }; /* switch */
       }
    } /* else higher-order */
    fclose(fp);
  } /* main */



/* parses an expression and indicates success or error */

int parse(void)
{
      int i, ec=0;

      uni = 1;
      minus = 0;
      lefts = 0;
      root=last=NULL;
      scanf(" \r ");
      ch = lower(getchar());
      while (ch!='\n') {
        i=-1;

	switch (ch) { 	
        case '0': case '1': case '2': case '3': case '4':
 	case '5': case '6': case '7': case '8': case '9':
	  uni = 0;
	  i = -1;
          if (minus) {
              minus=0;
              s[++i]='-';
	    }
          s[++i]=ch;
	  while (isdigit(s[++i]=lower(getchar())));
	  if (s[i]=='.') {
	      while (isdigit(s[++i]=lower(getchar())));
	      if (s[i]=='e') {
		if ((isdigit(s[++i]=lower(getchar())))||(s[i]=='-')||(s[i]=='+')) {
		  while (isdigit(s[++i]=lower(getchar())));
		  ch=s[i];
		  s[i]='\0';
		  if (s[i-1]=='e')
		    print_error(ec=1,&ch);
		  else {
		    token = package_token(0,4,0,s);
		    place_token(rootptr,lastptr,token);
		  }
		}
		else
		  print_error(4,&ch);
	      }
	      else {
		ch=s[i];
		s[i]='\0';
		token=package_token(0,4,0,s);
		place_token(rootptr,lastptr,token);
	      } /* while */
	    }
	  else {
	    ch = s[i];
	    s[i] = '\0';
	    token=package_token(0,4,0,s);
	    place_token(rootptr,lastptr,token);
	  }
	break;


	case 'x':
	  uni = 0;
	  i = -1;
          if(minus) {
            minus=0;
            s[++i]='-';
          }
	  s[++i]=ch;
	  scanf(" ");
	  if ((getchar() == '[')&&(isdigit(s[++i]=getchar()))) {
	    if (high_order)
	      s[i]++;
	    s[++i]='\0';
	    ch=lower(getchar());
	    ch=lower(getchar());
	    token=package_token(0,4,0,s);
	    place_token(rootptr,lastptr,token);
	  }
	  else
	    print_error(ec=1,&ch);
	  break;


	case '.':
	  uni = 0;
	  i = -1;
          if(minus) {
            minus=0;
            s[++i]='-';
          }
	  s[++i]='.';
	  while (isdigit(s[++i]=lower(getchar())));
	  if (s[i]=='e')
	  {
	    if ((isdigit(s[++i]=lower(getchar())))||(s[i]=='-')||(s[i]=='+')) {
	      while (isdigit(s[++i]=lower(getchar())));
	      ch=s[i];
	      s[i]='\0';
	      if (s[i-1]=='e')
		print_error(4,&ch);
	      else {
		token=package_token(0,4,0,s);
		place_token(rootptr,lastptr,token);
	      }

	    }
	    else 
	      print_error(ec=4,&ch);
	  }
	  else {
	    ch=s[i];
	    s[i]='\0';
	    token=package_token(0,4,0,s);
	    place_token(rootptr,lastptr,token);
	  }
	  break;


	case 'a': case 'c': case 'e': case 'f': case 'l':
	case 'p': case 's': case 't':
	  uni = 0;
	  i = -1;
          if(minus) {
            minus=0;
            s[++i]='-';
          }
	  s[++i]=ch;
	  while isalnum(s[++i]=lower(getchar()));
	  ch=s[i];
	  s[i]='\0';
	  switch (lookup(s,&time_present,&dim)) {
	  case -1:
	      token=package_token(0,4,0,s);
	      place_token(rootptr,lastptr,token);
	  break;
	  case 0:
	      print_error(ec=8,&ch);
	  break;
	  case 1:
	      token=package_token(0,5,1,s);
	      place_token(rootptr,lastptr,token);
	  break;
	  case 2:
	      token=package_token(0,5,2,s);
	      place_token(rootptr,lastptr,token);
	  }
	break;


	case '+': case '-':
	  if (uni && (ch=='-')) {
	      minus = 1;
	      uni = 0;
	    }
	  else {
	  s[0]=ch;
	  s[1]='\0';
	  token=package_token(lefts,1,2,s);
	  place_token(rootptr,lastptr,token);
	  lefts=0;
	}
	  ch=lower(getchar());
	  break;


	case '*': case '/':
	  uni = 1;
	  s[0]=ch;
	  s[1]='\0';
	  token=package_token(lefts,2,2,s);
	  place_token(rootptr,lastptr,token);
	  lefts=0;
	  ch=lower(getchar());
	  break;


	case '^':
	  uni = 1;
	  s[0]=ch;
	  s[1]='\0';
	  token=package_token(lefts,3,2,s);
	  place_token(rootptr,lastptr,token);
	  lefts=0;
	  ch=lower(getchar());
	break;


	case '(':
          uni = 1;
          lefts++;
          scanf(" ");
	  if ((ch=lower(getchar()))=='-') {
              minus=1;
              ch=lower(getchar());
	    }
	break;


	case ')':
	  uni = 0;
	  if (decrement_mark(lastptr,&lefts))
	      ch=lower(getchar());
	  else
	      print_error(ec=6,&ch);
	break;


	case ',':
	  uni = 1;
	  last=*lastptr;
	  while ((last!=NULL)&&(last->prior!=5)) {
	    lefts+=last->marks;
	    last->marks=0;
	    last=last->parent;
	  }
	  if (last==NULL)
	    print_error(3,&ch);
	  else {
	    last->marks+=lefts;
	    lefts=0;
	  }
	  ch=lower(getchar());
	break;


	case ' ': case '\t':
	  ch=lower(getchar());
        break;
	case '\n': 
	break;
	default: print_error(ec=3,&ch);
	};
      }
      return ec;
} /* parse */


/* returns lower case, leaving non-upper case characters alone. */
int lower(int c)
{
  if (c >= 'A' && c <= 'Z')
    return c + 'a' - 'A';
  else
    return c;
}



int lookup(char *s,int *time_present,char *dim)
{
  int i=-1;
  struct entry {
      char f_id[8];
      int max_kids;
  };
  struct entry table[] = {
    "sin",1,
    "cos",1,
    "tan",1,
    "asin",1,
    "acos",1,
    "atan",1,
    "atan2",2,
    "sinh",1,
    "cosh",1,
    "tanh",1,
    "exp",1,
    "log",1,
    "log10",1,
    "pow",2,
    "sqrt",1,
    "fabs",1,
    0,0
  };

  if (strcmp(s,"t")==0) {
    if (*time_present)
      ;
    else {
      *time_present+=1;
      *dim+=1;
    }
    s[0]='x';
    s[1]=*dim;
    s[2]='\0';
    return -1;
  }
  else {
    while ((strcmp(s,table[++i].f_id)!=0)&&(table[i].f_id))
      ;
    if (table[i].f_id)
      return table[i].max_kids;
    else
      return 0;
  }
}



nodeptr package_token(int m,int p,int k,char *t)
{
  struct node *token;
  char *dumby;

  token=(nodeptr)malloc(sizeof(struct node));
  if (token!=NULL) {
      token->marks=m;
      token->prior=p;
      token->max_kids=k;
      dumby=strcpy((token->text),t);
      token->parent=token->lchild=token->rchild=NULL;
  };
  return token;
}



int decrement_mark(nodeptr *l,int *lefts)
{
  nodeptr temp=*l;

  while ((temp!=NULL)&&(temp->marks==0))
      temp=temp->parent;
  if (temp!=NULL) {
      temp->marks-=1;
      *l=temp;
      return 1;
  }
  else
      if (*lefts > 0) {
	  *lefts-=1;
	  *l=*rootptr;
	  return 1;
      }
      else
	  return 0;
}



void place_token(nodeptr *rootptr,nodeptr *lastptr,nodeptr token)
{
  nodeptr last= *lastptr;

  switch (token->prior) {
  case 5: case 4:
      if (last==NULL)
	  *rootptr=*lastptr=token;
      else {
	  switch (number_of_kids(last)) {
	  case 0:
	      last->lchild=token;
	      token->parent=last;
	      *lastptr=token;
	  break;
	  case 1:
	      last->rchild=token;
	      token->parent=last;
	      *lastptr=token;
	  break;
	  case 2:
	      fprintf(fp,"Too many kids!\n");
	  }
      } /* else */
  break;
  case 3: case 2: case 1:
      attempt_lift(rootptr,lastptr,token);
  }
}



void attempt_lift(nodeptr *rootptr,nodeptr *lastptr,nodeptr token)
{
    nodeptr last= *lastptr;
    nodeptr root= *rootptr;

    if (last!=NULL)
       token->marks+=last->marks;
    while ((last!=NULL)&&
       ((last->parent==NULL)||(last->parent->prior>=token->prior))&&
			 (token->marks==0)) {
       last->marks=0;
       *lastptr=last=last->parent;
       if (last!=NULL)
           token->marks+=last->marks;
    }  
    if ((last==NULL)||(last->parent==NULL)) {
	if (last!=NULL) {
	    token->marks+=last->marks;
	    last->marks=0;
	}
	token->lchild=*rootptr;
	if (root!=NULL)
	    root->parent=token;
	*rootptr=root=*lastptr=last=token;
    }
    else {
	token->marks+=last->marks;
	last->marks=0;
	if (number_of_kids(last->parent)==2)
	    last->parent->rchild=token;
	else
	    last->parent->lchild=token;
	token->parent=last->parent;
	token->lchild=last;
	*lastptr=last->parent=token;

    }
}



int number_of_kids(nodeptr token)
{
    if (token->lchild==NULL)
	return 0;
    else
	if (token->rchild==NULL)
	    return 1;
	else
	    return 2;
}



int dump_tree (FILE *fp,nodeptr root)
{
    if (root!=NULL)
	switch (root->prior) {
	case 1: case 2:
	    fprintf(fp,"(");
	    dump_tree(fp,root->lchild);
	    fprintf(fp,"%s",root->text);
	    dump_tree(fp,root->rchild);
	    fprintf(fp,")");
	break;
	case 3:
	    fprintf(fp,"pow(");
	    dump_tree(fp,root->lchild);
	    fprintf(fp,",");
	    dump_tree(fp,root->rchild);
	    fprintf(fp,")");
	break;
	case 4:
	    fprintf(fp,"%s",root->text);
	break;
	case 5:
	    fprintf(fp,"%s",root->text);
	    fprintf(fp,"(");
	    dump_tree(fp,root->lchild);
	    if (number_of_kids(root)==2) {
		fprintf(fp,",");
		dump_tree(fp,root->rchild);
	    }
	    fprintf(fp,")");
	};  /* switch*/
}



void print_error(int ec,char *ch)
{
    printf("\nParser Error!!! %s",msg[ec]);
    if (ec==3)
	   printf(" %c.\n\n",*ch);
    else
           printf("\n\n");
    *ch = '\n';
}

