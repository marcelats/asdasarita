/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/


/* Homoclinic Orbits (Silnikov) */

float in[4],out[4],f[4],savevar[4],time,delta_time;
int count,num_equations=3;

main()
{
  init_conditions();
  while (time < 250.0) {
   state();
   integrate(); 
   /* output time,x */
   printf("%f %f\n",out[1],out[2]);
  } /* end while */
  printf("\n");
} /* end main */

init_conditions()
{
  out[1] = 0.1234;
  out[2] = 0.2;
  out[3] = 0.1;
  time = 0.0;
  delta_time = 0.05;
}

state()
{ 
 float a=0.4,b=0.65,c=0.0,d=1.0;
 /* Calculate state:
    x1' = x2
    x2' = x3
    x3' = -ax3 - x2 +bx1(1 - cx1 - dx1(2))
 */
 in[1] = out[2];
 in[2] = out[3];
 in[3] = -a*out[3] - out[2] + b*out[1]*(1.0 - c*out[1] - d*out[1]*out[1]);
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




