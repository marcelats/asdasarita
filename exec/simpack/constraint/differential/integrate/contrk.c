/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

float in[4],out[4],f[4],savevar[4],time,delta_time;
int num_equations;

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
  num_equations = 3;
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

  for (i=1;i<=num_equations;i++) {
    f[i] = delta_time*in[i];
    savevar[i] = out[i];
    out[i] += f[i]/2;
  }
  time += delta_time/2;
  state();

  for (i=1;i<=num_equations;i++) {
    f[i] += 2*delta_time*in[i];
    out[i] = savevar[i] + delta_time*in[i]/2;
  }
  state();

  for (i=1;i<=num_equations;i++) {
    f[i] += 2*delta_time*in[i];
    out[i] = savevar[i] + delta_time*in[i];
  }
  time += delta_time/2;
  state();

  for (i=1;i<=num_equations;i++) 
    out[i] = savevar[i] + (f[i] + delta_time*in[i])/6;
}
