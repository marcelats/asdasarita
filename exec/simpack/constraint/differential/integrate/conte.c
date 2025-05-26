/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/


float time,delta_time,in[4],out[4];

main()
{
  init_conditions();
  while (time < 5.0) {
   state();
   integrate(); 
   /* output time,x */ 
   printf("%f %f\n",time,out[1]); 
  } /* end while */
} /* end main */

init_conditions()
{
  out[1] = 1.0;
  out[2] = 1.0;
  out[3] = 1.0;
  time = 0.0;
  delta_time = 0.01;
}

state()
{ 
/* Calculate state: x''' + x' = 2 */
 in[1] = out[2];
 in[2] = out[3];
 in[3] = 2 - out[2];
}
 
integrate()
{
 int i;
 for(i=1;i<=3;i++)
   out[i] += in[i]*delta_time;
 time += delta_time;
}
 

