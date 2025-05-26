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
#define MAXEQNS 9
#define MAXLEN 80
#define MAXINIT 9

int j,i,num_eqns,eqn_num,num_init;

char x[MAXEQNS][MAXLEN],dummy[MAXLEN],xaxis[5],yaxis[5],dumchar;
float xi[MAXEQNS][MAXINIT],bt,et,dt;

convert()
{
  printf("#include <math.h>\n\n");
  printf("float in[%d],out[%d],f[%d],savevar[%d],time,delta_time;\n",
          num_eqns+1,num_eqns+1,num_eqns+1,num_eqns+1);
  printf("int num_equations;\n\n");
  printf("main()\n{\nint i;\n");
  printf("for (i=1;i<=%d;i++) {\n",num_init);
  printf("init_conditions(i);\n");
  printf("while (time < %f) {\nstate();\nintegrate();\n",et);
  if (yaxis[0] != 'a') { 
    printf("printf(\"%%f %%f\\n\",");
  }else{
    printf("printf(\"%%f ");
    for (i=1;i<=num_eqns;i++) {
      printf("%%f ");
    }
    printf("\\n\",");
  }
  if (xaxis[0] == 't') {
    printf("time,");
  }else{
    printf("out[%s],",xaxis+1);
  }
  if (yaxis[0] == 't') {
    printf("time);\n");
  }else{
    if (yaxis[0] == 'x') {
      printf("out[%s]);\n",yaxis+1);
    }else{
      for (i=1;i<num_eqns;i++) {
        printf("out[%d],",i);
      }
      printf("out[%d]);\n",num_eqns);
    }
  }
  printf("}\nprintf(\"\\n\");\n");
  printf("}\n}\n\ninit_conditions(k)\nint k;\n{\nnum_equations=%d;\n",num_eqns);
  for (j=1;j<=num_init;j++) {
    printf("if (k == %d) {\n",j);
    for (i=1;i<=num_eqns;i++) {
      printf("out[%d] = %f;\n",i,xi[j][i]);
    }
    printf("}\n");
  }
  printf("time = %f;\n",bt);
  printf("delta_time = %f;\n}\n\nstate()\n{\n",dt);
  for (i=1;i<=num_eqns;i++) {
    printf("in[%d] = ",i);
    j = 0;
    while (x[i][j] != '\0') {
      if (x[i][j] != 'x') {
	printf("%c",x[i][j]);
      }else{
	printf("out[%c]",x[i][++j]);
      }
      ++j;
    }
    printf(";\n");
  }
  printf("}\n\nintegrate()\n{\nint i;\n");
  printf("for (i=1;i<=num_equations;i++) {\n");
  printf("f[i]=delta_time*in[i];\n");
  printf("savevar[i] = out[i];\n");
  printf("out[i]+=f[i]/2;\n");
  printf("}\ntime+=delta_time/2;\n");
  printf("state();\n\n");
  printf("for(i=1;i<=num_equations;i++) {\n");
  printf("f[i] +=2*delta_time*in[i];\n");
  printf("out[i]=savevar[i]+delta_time*in[i]/2;\n");
  printf("}\nstate();\n\n");
  printf("for(i=1;i<=num_equations;i++) {\n");
  printf("f[i] +=2*delta_time*in[i];\n");
  printf("out[i]=savevar[i]+delta_time*in[i];\n");
  printf("}\ntime+=delta_time/2;\nstate();\n\n");
  printf("for(i=1;i<=num_equations;i++) {\n");
  printf("out[i]=savevar[i]+(f[i]+delta_time*in[i])/6;\n");
  printf("}\n}\n");
}

main()
{

  scanf("%d",&num_eqns);

  for (i=1;i<=num_eqns;i++) {
    scanf("%*[^x]%*c");
    scanf("%d%*[^=]%*c",&eqn_num);
    scanf("%[^;]%*c",x[eqn_num]);
  }

  scanf("%*[^xb]%c",&dumchar);
  if (dumchar != 'x') {
    for (i=1;i<=num_eqns;i++) {
      xi[1][i]=0.0;
    }
    num_init = 1;
  }else{
    num_init = 0;
    while (dumchar == 'x') {
      num_init++;
      for (i=1;i<=num_eqns;i++) {
        scanf("%d%*[^0-9]",&eqn_num);
        scanf("%f",&(xi[num_init][i]));
	scanf("%*[^xb]%c",&dumchar);
      }
    }
  }
  scanf("%*[^=]%*c%f",&bt);
  scanf("%*[^e]%*[^=]%*c%f",&et);
  scanf("%*[^d]%*[^=]%*c%f",&dt);

  scanf("%*[^xt]%c",&dumchar);
  xaxis[0] = dumchar;
  if (dumchar == 'x') {
    scanf("%[0-9]",xaxis+1);
  }else{
    xaxis[1] = '\0';
  }

  scanf("%*[^xta]%c",&dumchar);
  yaxis[0] = dumchar;
  if (dumchar == 'x') {
    scanf("%[0-9]",yaxis+1);
  }else{
    yaxis[1] = '\0';
  }

  convert();
}
