/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

/* NOTE: This program is the SimPack equivalent
of an SMPL program by M. H. MacDougall, "Simulating
Computer Systems", MIT Press, 1987 */


#include "queuing.h"

#define ARRIVAL 1
#define REQUEST_SERVER 2
#define RELEASE_SERVER 3

int GetArgs (int argc, char * argv [] );

int main (int argc, char * argv [] )
  {
  int event,queue_id,i,iteration;
  TOKEN customer;
  double sample;
  int limit = GetArgs (argc, argv);
  int ii;

  for (ii = 0; ii < limit; ii++)
    {

    customer.attr[0] = 1;
    init_simpack(LINKED);
    queue_id = create_facility("queue",1);
    schedule(ARRIVAL,0.0,customer);
    iteration = 0;
    while (sim_time()< 1000.0)
      {
        next_event(&event,&customer);
        /* printf("%d %f\n",iteration,sim_time()); */
        iteration++;
        switch(event)
          {
          case ARRIVAL:
              update_arrivals();
              schedule(REQUEST_SERVER,0.0,customer);
              customer.attr[0] += 1;
              schedule(ARRIVAL,2.0,customer);
              break;
          case REQUEST_SERVER:
              if (request(queue_id,customer,0) == FREE) {
                sample = expntl(2.0);
                schedule(RELEASE_SERVER,sample,customer);
              }
              break;
          case RELEASE_SERVER:
              release(queue_id,customer);
              update_completions();
              break;
          }
      }
    end_simpack (); // also reports stats
    }
  return 0; // pacify compiler
  } /* end main() */



/*=============================================================================
Get loop limit from cmd line arg.  Use default if none specified.
-----------------------------------------------------------------------------*/

int GetArgs (int argc, char * argv [] )
  {
  if (argc < 2) return 1;
  if (strlen(argv [1]) < 1) return 1;
  istrstream stgstrm (argv[1]);
  int loop_limit;
  stgstrm >> loop_limit;
  return loop_limit;
  }




