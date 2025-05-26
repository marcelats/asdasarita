/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1993, Paul A. Fishwick
---------------------------------------------*/
/* Simulation of a six phase boiling water
   FSA controller */

/* phases */
#define COLD 1
#define HEATING 2
#define COOLING 3
#define BOILING 4
#define OVERFLOW 5
#define UNDERFLOW 6
#define NOT_COLD 2
#define EXCEPTION 5

/* internal event conditions */
#define T_IS_AMBIENT 1
#define T_IS_100 2
#define HW_IS_0 3
#define HF_IS_HT 4

#define UNDEFINED -99999.0
#define HT 50.0
#define FALSE 0
#define TRUE 1
#define MAX_STATES 6
#define MAX_EXT_EVENTS 2
#define MAX_INT_EVENTS 4

int transition_ext[MAX_STATES+1][MAX_EXT_EVENTS];
int transition_int[MAX_STATES+1][MAX_INT_EVENTS+1];
int internal_event(),external_event();
float in[4],out[4],f[4],savevar[4],time,delta_time;
float ambient;
float k1,k2,k3,k4,k5;
int num_equations,phase,map[4][MAX_STATES+1];
int output_type = 0, output_value = 0;

main()
{
  int i,potential_event;
  init_conditions();
  while (time < 25.0) {
   state(phase); /* update equations of state */
   integrate(phase);  /* integrate state variables */
   /* external events */
   phase = transition_ext[phase][external_event()]; 
   for (i=1;i<=4;i++) { /* internal events */
     potential_event = transition_int[phase][i];
     if (potential_event && internal_event(i))
        phase = potential_event;
   }
   /* output time,value */
   if (output_type == 1 && out[output_value] != UNDEFINED)
     printf("%f %f\n",time,out[output_value]);
   else if (output_type == 2)
      printf("%f %d\n",time,map[output_value][phase]);
   else if (output_type == 3)
      printf("%f %d\n",time,external_event());
   else if (output_type == 4)
      printf("%f %f %f\n",out[1],out[2],out[3]);
  } /* end while */
} /* end main */


init_conditions()
{
  int i,j,num_states,num_levels;
  /* preset key variables, parameters and states */
  num_equations = 3;
  ambient = 20.0; /* ambient temperature in Celsius */
  out[1] = ambient; /* Temperature (T) */
  out[2] = 5.0; /* Water Height (Hw) */
  out[3] = 5.0; /* Foam Height (Hf) */
  time = 0.0;
  delta_time = 0.01;
  phase = COLD;
  /* parameters for equations of state */
  k1 = 4.0; k2 = 2.0; k3 = 0.8; k4 = 0.8; k5 = 0.5;

  /* read in the information to output */
  scanf("%d %d",&output_type,&output_value);

  /* read in number of states */
  scanf("%d",&num_states);

  /* Read in transition table transition_ext */
  /* read in transition array */
  for (i=1;i<=num_states;i++) 
    for (j=0;j<MAX_EXT_EVENTS;j++)
      scanf("%d",&transition_ext[i][j]);

  /* Read in transition table transition_int */
  /* read in transition array */
  for (i=1;i<=num_states;i++) 
    for (j=1;j<=MAX_INT_EVENTS;j++)
      scanf("%d",&transition_int[i][j]);

  /* read in the number of FSA abstraction levels */
  scanf("%d",&num_levels);
  /* Read in abstraction level table */
  for (i=1;i<=num_levels;i++) 
    for (j=1;j<=MAX_STATES;j++)
      scanf("%d",&map[i][j]);
}

state(phase)
int phase;
{ 
/* update the system state for each phase 
   in[1] = T'   out[1] = T    Temperature
   in[2] = Hw'  out[1] = Hw   Water Height
   in[3] = Hf'  out[1] = Hf   Foam Height */

switch (phase) {

   case COLD:
              in[1] = 0.0;
              in[2] = 0.0;
              in[3] = 0.0;
              break;
   case HEATING:
              in[1] = k1*(100.0 - out[1]);
              in[2] = 0.0;
              in[3] = 0.0;
              break;
   case COOLING:
              in[1] = k2*(ambient - out[1]);
              in[2] = 0.0;
              in[3] = -k3;
              break;
   case BOILING:
              in[1] = 0.0;
              in[2] = -k4;
              in[3] = k5;
              break;
   case OVERFLOW:
              in[1] = -k4;
              in[2] = k5;
              in[3] = 0.0;
              break;
   case UNDERFLOW:
              out[1] = UNDEFINED;
              in[1] = 0.0;
              in[2] = 0.0;
              in[3] = 0.0;
              break;
  } /* end switch */
} /* end state () */

int internal_event(event)
int event;
{
  int value;
  switch (event) {

  case T_IS_AMBIENT:  
   if (out[1]<=(ambient+0.01)) {
     value=TRUE; 
     out[1] = ambient; }
   else value=FALSE;    
   return(value);
  case T_IS_100:  
   if (out[1]>=99.9) {
     value=TRUE; 
     out[1] = 100.0; }
   else value=FALSE;
   return(value);
  case HW_IS_0: 
   if (out[2]<=0.01) {
     value=TRUE; 
     out[2] = 0.0; }
   else value=FALSE;
   return(value);
  case HF_IS_HT: 
   if (out[3]>=HT) {
     value=TRUE; 
     out[3] = HT; }
   else value=FALSE;
   return (value);
  } /* end switch */
} /* end internal_event() */

int external_event()
{
  if (time < 3.0)
    return(0);
  else if (time < 5.0)
    return(1);
  else if (time < 5.5)
    return(0);
  else if (time < 10.0)
    return(1);
  else if (time < 14.0)
    return(0);
  else if (time < 20.0)
    return(1);
  else if (time < 40.0)
    return(0);
  else if (time < 42.0)
    return(1);
  else if (time < 45.0)
    return(0);
  else if (time < 90.0)
    return(1);
  else return(0);
} /*  end external_event() */

/* int external_event()
{
 if (time < 5.0)
   return(0);
 else if (time < 10.0)
   return(1);
 else if (time < 15.0)
   return(0);
 else if (time < 20.0)
   return(1);
 else if (time < 25.0)
   return(0);
 else if (time < 30.0)
   return(1);
 else if (time < 35.0)
   return(0);
 else if (time < 40.0)
   return(1);
 else return(0);
} */
 
integrate(phase)
int phase;
{
  int i;

  for (i=1;i<=num_equations;i++) {
    f[i] = delta_time*in[i];
    savevar[i] = out[i];
    out[i] += f[i]/2;
  }
  time += delta_time/2;
  state(phase);

  for (i=1;i<=num_equations;i++) {
    f[i] += 2*delta_time*in[i];
    out[i] = savevar[i] + delta_time*in[i]/2;
  }
  state(phase);

  for (i=1;i<=num_equations;i++) {
    f[i] += 2*delta_time*in[i];
    out[i] = savevar[i] + delta_time*in[i];
  }
  time += delta_time/2;
  state(phase);

  for (i=1;i<=num_equations;i++) 
    out[i] = savevar[i] + (f[i] + delta_time*in[i])/6;
} /* integrate */
