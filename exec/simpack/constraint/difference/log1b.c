#define X_BUFFER 2
int pointer;

main()
{ float x[X_BUFFER],a;
  int time,t();

  pointer = X_BUFFER - 1; 
  x[t(-1)] = 0.8; a = 1.2;  /* set initial conditions and parameters */
  time = 0;
  while (time < 100) {
    x[t(0)] = a*x[t(-1)]*(1.0 - x[t(-1)]); /* difference equation */
    printf("%d %f\n",time,x[t(0)]);
    pointer = (pointer+1) % X_BUFFER;
    time++;
  } /* end while */
} /* end main */

int t(index)
int index;
{int new_pointer;
 new_pointer = pointer + index;
 if (new_pointer < 0)
   return(X_BUFFER + new_pointer);
 else
   return(new_pointer % X_BUFFER);
}
