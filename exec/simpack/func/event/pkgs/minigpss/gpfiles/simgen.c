#include "../../queuing/queuing.h" 
#include "y.tab.c" 
#include "error.c" 
#include "codgen.c" 
#define  Pri  1 
#define  ARRIVE_  1 
#define  REQUEST_ 2 
#define  SERVICE_ 3 
#define  DEPART_  4  
#define  BR_ARR_  5  
#define  BR_DEP_  6  
struct f_l{ 
   char fname[80]; 
   int  fid; 
}fac_list[MAXFAC]; 
int fac_list_cnt; 
main() 
{ 
int rn; 
int my_priority; 
float rnf, xx, yy; 
int OldId; 
int test; 
int rcount =0;    
int sim_error; 
int event; 
int loop; 
int num_sims; 
TOKEN token,a_token,token_loop; 
int num_to_serve; 
float curr_time = 0.0; 
float sample ; 
int   lower, upper,range; 
int print_flag; 
 
  printf("Reading Source mini-GPSS File\n");   
   sim_error = yyparse(); 
  if (sim_error == 0){ 
     puts("no syntax errors detected");  
     for(test=1;test<=prog_unit;test++){ 
/* 
      printf("==> prog_unit = %d \n",test); 
     printf("... activity time = %d \n",prog[test].serve_time); 
     printf("... activity range = %d \n",prog[test].serve_range); 
     printf("... inter-arrival time = %d \n",prog[test].inter_time); 
     printf("... inter-arrival range = %d \n",prog[test].inter_range); 
     printf("... transfer flag = %d \n",prog[test].transfer); 
     printf("... transfer percent = %d \n",prog[test].percent); 
     printf("... queue flag = %d \n",prog[test].queue_text != NIL); 
     printf("... serve flag = %d \n",prog[test].serve_text[0] != NIL); 
     printf("... release flag = %d \n",prog[test].rel_text != NIL); 
     printf("... number to serve = %d \n",completion_total[no_runs]); 
     printf("... decrement after completion by %d \n",prog[test].quit_factor); 
     printf("... code is %d \n",prog[test].pu_code); 
     printf("... parent = %d \n",prog[test].parent); 
     printf("... br_end = %d \n",prog[test].br_end); 
     printf("... br_case1 = %d \n",prog[test].br_case1); 
     printf("... br_case2 = %d \n",prog[test].br_case2);   
  */   
 
     } 
     init_simpack(LINKED); 
     for (loop=1;loop<=no_fac;loop++){ 
        if((OldId= InList(fac[loop].name)) == PU_END){ 
          fac[loop].id = create_facility(fac[loop].name,fac[loop].num_servers); 
          fac_list[fac_list_cnt].fid = fac[loop].id; 
          strcpy(fac_list[fac_list_cnt].fname,fac[loop].name); 
          prog[fac[loop].unit].id = fac[loop].id; 
        } 
        else{ 
          prog[fac[loop].unit].id = fac[loop].id = OldId; 
        } 
           
          
/*           printf("fac name = %s   id = %d  \n",fac[loop].name,fac[loop].id);  */ 
          
     } 
         
     for(num_sims=1;num_sims<=no_runs;num_sims++){ 
        num_to_serve = completion_total[num_sims]; 
        for(loop=1;loop<= prog_unit;loop++){ 
           if (prog[loop].parent == 1) { 
             if(prog[loop].transfer == 1){ 
             } 
             token_loop.attr[0] = (float) loop; 
	   /*  printf("scheduling arrival --\n"); */ 
             schedule(ARRIVE_,curr_time,token_loop);  
     /*         printf("schedule prog_unit # %d \n",token_loop);  */ 
           } 
        } 
        while(num_to_serve){ 
           next_event(&event,&token);  
           switch(event){ 
              case BR_ARR_: 
/*                           printf("...in BR_ARR\n");   */ 
                            rn = random(1,100) ; 
 
                            update_arrivals(); 
                            schedule(ARRIVE_,0.0,token); 
         
/*           trace_eventlist();            */ 
 
 
                            if( prog[tnum(token)].percent <= rn){ 
			       a_token.attr[0] = 
                                 (float) prog[tnum(token)].br_case1; 
                               schedule(REQUEST_,0.0,a_token); 
                                
                            } 
                            else{ 
                               prog[prog[tnum(token)].br_case2].transfer = 1; 
			       a_token.attr[0] =  
                                 (float) prog[tnum(token)].br_case2; 
                               schedule(REQUEST_,0.0,a_token); 
                                
                            }  
                            
                         break; 
              case ARRIVE_:    
/*                            printf("...Arrive\n");  
           trace_eventlist();   */ 
 
                         range = prog[tnum(token)].inter_range; 
                         lower = prog[tnum(token)].inter_time - range; 
                         upper = prog[tnum(token)].inter_time + range; 
                          
                        xx = prog[tnum(token)].inter_time; 
                         my_priority = prog[tnum(token)].mypri; 
  
                  
                       if (prog[tnum(token)].dist1 == 0) 
                                  sample = random(lower,upper); 
                       else  if (prog[tnum(token)].dist1 == 1) 
                                 sample = normal(xx,yy); 
                        else  if (prog[tnum(token)].dist1 == 2) 
                                 sample = expntl(xx); 
                         else  if (prog[tnum(token)].dist1 == 3) 
                                 sample = uniform(xx,yy); 
                        else  if (prog[tnum(token)].dist1 == 4) 
                                 sample =  erlang(xx,yy); 
                        else 
                         sample = random(lower,upper); 
                         if (prog[tnum(token)].transfer == 1){ 
                           schedule(BR_ARR_,sample,token);  
                         } 
                         else{ 
                            if (prog[tnum(token)].serve_text[0] == NIL){ 
                               schedule(SERVICE_,sample,token); 
                               if (prog[tnum(token)].parent == 1) 
                                  schedule(ARRIVE_,sample,token); 
                            } 
                            else {  
                               if (prog[tnum(token)].parent == 1){ 
                                  update_arrivals(); 
                                  schedule(ARRIVE_,sample,token); 
                               } 
                               schedule(REQUEST_,0.0,token); 
                           } 
                         } 
                        break; 
              case REQUEST_: 
  rcount++; 
/*                           printf("...in REQUEST==>%d \n",rcount); */ 
                             
/*           trace_eventlist();                             */ 
 
 
 
                         if (request(prog[tnum(token)].id,token,my_priority) != BUSY){ 
                            schedule(SERVICE_,0.0,token); 
                         } 
                      else if (prog[tnum(token)].tran_mode == 1) 
                             { /* let this token die   */ }                
                         else { 
                               /* schedule(REQUEST_,0.1,a_token); */ 
			    }; 
                         break;  
              case SERVICE_: 
/*                            printf("...in SERVICE\n");  
           trace_eventlist();   */ 
 
                         range = prog[tnum(token)].serve_range; 
                         lower = prog[tnum(token)].serve_time - range; 
                         upper = prog[tnum(token)].serve_time + range; 
                       /* printf(" l u r t= %d %d %d %d\n",lower,upper,range,token); */ 
 
 
 
 
                          
                        
                        xx = prog[tnum(token)].serve_time; 
                         yy = prog[tnum(token)].serve_range ; 
           
                        if (prog[tnum(token)].dist == 0) 
                                  sample = random(lower,upper); 
                       else  if (prog[tnum(token)].dist == 1) 
                                 sample = normal(xx,yy); 
                        else  if (prog[tnum(token)].dist == 2) 
                                 sample =  expntl(xx); 
                         else  if (prog[tnum(token)].dist == 3) 
                                 sample =  uniform(xx/100,yy/100); 
                          else  if (prog[tnum(token)].dist == 4) 
                           sample =  erlang(xx,yy); 
                         else 
                            sample = random(lower,upper);  
 
 
 
                         /* sample = random(lower,upper) ; */ 
                         schedule(DEPART_,sample,token); 
                         break; 
              case BR_DEP_: 
  /*                            printf("...in BR_DEP\n");   
           trace_eventlist();                             */ 
                         release(prog[tnum(token)].id,token); 
                         num_to_serve -= prog[tnum(token)].quit_factor; 
                         curr_time = sim_time(); 
                if ((prog[tnum(token)].br_end == 0)&&(prog[tnum(token)].pu_code != PU_END)){ 
                            prog[prog[tnum(token)].pu_code].transfer = 1; 
			    a_token.attr[0] = (float) prog[tnum(token)].pu_code; 
                            schedule(REQUEST_,0.0,a_token); 
                      } 
                         else  
                            update_completions();  
                         break; 
              case DEPART_: 
 
/*                            printf("...in DEPART\n");     
           trace_eventlist();   */ 
                         if (prog[tnum(token)].transfer == 1){ 
                           schedule(BR_DEP_,0.0,token);  
                         } 
                         else{ 
                            release(prog[tnum(token)].id,token); 
                            num_to_serve -= prog[tnum(token)].quit_factor; 
                            curr_time = sim_time(); 
                            if (prog[tnum(token)].pu_code != PU_END) { 
			       a_token.attr[0] = (float) prog[tnum(token)].pu_code; 
                               schedule(ARRIVE_,0.0,a_token); 
			     } 
                            else if (prog[tnum(token)].serve_text[0] != NIL) 
                              update_completions(); 
                         } 
              } 
        } 
     print_flag = 0; 
     for(loop=1;loop<=prog_unit;loop++) 
        if (prog[loop].serve_text[0] != NIL) { 
           print_flag = 1; 
       } 
     if (print_flag) { 
       /* printf("\nThe C generated code for this simulation is in the file: simgen.c\n"); */ 
       report_stats(); 
      /*  codgen(); */ 
     } 
     }    
  } 
} 
     
int InList(String) 
   char *String; 
{ 
   int loop; 
 
   if (fac_list_cnt == 0){ 
     fac_list_cnt++; 
     return -1; 
   } 
   else { 
      for (loop=1;loop<=fac_list_cnt;loop++){ 
          if (strequal(String,fac_list[loop].fname)) { 
            return fac_list[loop].fid;    
          } 
      } 
      fac_list_cnt++; 
      return -1; 
   } 
} 
 
 
int tnum(token) 
TOKEN token; 
{  
  return((int) token.attr[0]); 
}  
 
 
 
 
