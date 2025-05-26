/*---------------------------------------------
                 S I M P A C K
            Simulation Tool Package
        Copyright 1990, Paul A. Fishwick
---------------------------------------------*/

#include "queuing.h"
#include <stdio.h>

#define NODES 20
#define MESSAGES 50
#define TRANSCEIVERS 200
#define MAX_MSG_LENGTH 20
#define LINK 0
#define REQUEST 1
#define RELEASE 2

int num_nodes,message_length[MESSAGES],event,message_id;
int length,message[MESSAGES][MAX_MSG_LENGTH],transceiver[TRANSCEIVERS][3];
int trans_count,facility_id,messages_routed,message_ptr[MESSAGES];
int token,num_transceivers,num_messages,message_tr[MESSAGES];
float graph[NODES][NODES],node_time;
TOKEN a_token;

// fn prototype declarations:
void proc_event (int event, int message_id);
void report_nodes (void);

main()
{
  int i,j;

  init_simpack(LINKED);
  /* read in the network topology and messages
     to be routed */
  scanf("%d",&num_nodes);
  scanf("%f",&node_time);
  for (i=0;i<num_nodes;i++)
    for (j=0;j<num_nodes;j++)
     scanf("%f",&graph[i][j]);

  scanf("%d",&num_messages);
  for (i=0;i<num_messages;i++) {
    scanf("%d",&length);
    message_length[i] = length;
    for (j=0;j<message_length[i];j++)
      scanf("%d",&message[i][j]);
  } /* end for */

  /* specify all transceivers as facilities */
  trans_count=0;
  for(i=0;i<num_nodes;i++)
    for (j=0;j<num_nodes;j++)
      if (graph[i][j] != 0.0) {
        transceiver[trans_count][0] = i;
        transceiver[trans_count][1] = j;
        facility_id = create_facility("tr",1);
        transceiver[trans_count][2] = facility_id;
        trans_count++;
      } /* end if */
  num_transceivers = trans_count;

  /* Each message is represented by a token.
     For each message, reset the pointer inside message path */
  for (i=0;i<num_messages;i++) {
    message_ptr[i] = 0;
    a_token.attr[0] = (float) i;
    schedule(LINK,0.0,a_token);
  }
  messages_routed = 0;
  while (messages_routed < num_messages) {
    next_event(&event,&a_token);
    message_id = (int) a_token.attr[0];
    proc_event(event,message_id);
  } /* end while */
  report_stats();
  report_nodes();
return 0;
} /* end main() */

void proc_event (int event, int message_id)
  {
    int i,j,trans_num,row,col;
    float link_time;

    i = message_id;
    switch (event) {

    case LINK: /* message traveling along a link */
     /* determine which transceiver is being requested */
     for (j=0;j<num_transceivers;j++)
      if ((message_ptr[i] < (message_length[i]-1)) &&
         (message[i][message_ptr[i]] == transceiver[j][0]) &&
         (message[i][message_ptr[i]+1] == transceiver[j][1]))
       trans_num = j;
     row = transceiver[trans_num][0];
     col = transceiver[trans_num][1];
     link_time = graph[row][col];
     a_token.attr[0] = (float) i;
     schedule(REQUEST,link_time,a_token);
     break;

    case REQUEST: /* message requesting a facility */
     /* determine which transceiver is being requested -
        then obtain facility or queue for it */
     for (j=0;j<num_transceivers;j++)
      if ((message_ptr[i] < (message_length[i]-1)) &&
         (message[i][message_ptr[i]] == transceiver[j][0]) &&
         (message[i][message_ptr[i]+1] == transceiver[j][1]))
       trans_num = j;
     if(message_ptr[i] < (message_length[i]-1)) {
       a_token.attr[0] = (float) i;
       if (request(transceiver[trans_num][2],a_token,0) == FREE) {
          /* total_time = graph[transceiver[trans_num][0],
                                transceiver[trans_num][1]] + 1.0; */
           message_tr[i] = trans_num;
           a_token.attr[0] = (float) i;
           schedule(RELEASE,node_time,a_token);
       } /* end if */
     } /* end if */
     break;

    case RELEASE:  /* message releasing a facility */
     /* release a facility. first find out which transceiver
        has this message token  */
       j = message_tr[i];
       a_token.attr[0] = (float) i;
       release(transceiver[j][2],a_token);
       /* update the message pointer */
       if(message_ptr[i] < (message_length[i]-2)) {
          message_ptr[i] += 1;
          a_token.attr[0] = (float) i;
          schedule(LINK,0.0,a_token);
       }
       else
          messages_routed++;
       break;
    } /* end switch */
} /* end check_transition() */

void report_nodes()
{
  int trans_count,i,j,transceivers_in_node;
  float node_busy_time[NODES],utilization,avg_busy_time;

  printf("\n");
  printf("----------------\n");
  printf("NODE Utilization\n");
  printf("----------------\n\n");
  /* loop through all transceivers to obtain node statistics */
  trans_count=0;
  for(i=0;i<num_nodes;i++)
    node_busy_time[i] = 0.0;
  for(i=0;i<num_nodes;i++) {
    transceivers_in_node = 0;
    for (j=0;j<num_nodes;j++)
      if (graph[i][j] != 0.0) {
        node_busy_time[i] += busy_time(transceiver[trans_count][2]);
        trans_count++;
        transceivers_in_node++;
      } /* end if */
  } /* end for */
  for(i=0;i<num_nodes;i++) {
    avg_busy_time = node_busy_time[i]/(float) transceivers_in_node;
    utilization = 100.0 * avg_busy_time/sim_time();
    printf("Node %d Utilization is %.1f%%\n",i,utilization);
  } /* end for */
} /* end report_nodes() */


