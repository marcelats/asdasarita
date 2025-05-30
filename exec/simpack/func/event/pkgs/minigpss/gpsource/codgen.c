
/* THIS IS THE codgen.c FILE */

codgen()
{
   FILE   *newfile;
   int    l;
   newfile = fopen("simgen.c", "w");


   fprintf(newfile, "#include \"../../queuing/queuing.h\" \n");
   fprintf(newfile, "#include \"y.tab.c\" \n");
   fprintf(newfile, "#include \"error.c\" \n");
   fprintf(newfile, "#include \"codgen.c\" \n");
   fprintf(newfile, "#define  Pri  1 \n");
   fprintf(newfile, "#define  ARRIVE_  1 \n");
   fprintf(newfile, "#define  REQUEST_ 2 \n");
   fprintf(newfile, "#define  SERVICE_ 3 \n");
   fprintf(newfile, "#define  DEPART_  4  \n");
   fprintf(newfile, "#define  BR_ARR_  5  \n");
   fprintf(newfile, "#define  BR_DEP_  6  \n");
   fprintf(newfile, "struct f_l{ \n");
   fprintf(newfile, "   char fname[80]; \n");
   fprintf(newfile, "   int  fid; \n");
   fprintf(newfile, "}fac_list[MAXFAC]; \n");
   fprintf(newfile, "int fac_list_cnt; \n");
   fprintf(newfile, "main() \n");
   fprintf(newfile, "{ \n");
   fprintf(newfile, "int rn; \n");
   fprintf(newfile, "int my_priority; \n");
   fprintf(newfile, "float rnf, xx, yy; \n");
   fprintf(newfile, "int OldId; \n");
   fprintf(newfile, "int test; \n");
   fprintf(newfile, "int rcount =0;    \n");
   fprintf(newfile, "int sim_error; \n");
   fprintf(newfile, "int event; \n");
   fprintf(newfile, "int loop; \n");
   fprintf(newfile, "int num_sims; \n");
   fprintf(newfile, "TOKEN token,a_token,token_loop; \n");
   fprintf(newfile, "int num_to_serve; \n");
   fprintf(newfile, "float curr_time = 0.0; \n");
   fprintf(newfile, "float sample ; \n");
   fprintf(newfile, "int   lower, upper,range; \n");
   fprintf(newfile, "int print_flag; \n");
   fprintf(newfile, " \n");
   fprintf(newfile, "  printf(\"Reading Source mini-GPSS File\\n\");   \n");
   fprintf(newfile, "   sim_error = yyparse(); \n");
   fprintf(newfile, "  if (sim_error == 0){ \n");
   fprintf(newfile, "     puts(\"no syntax errors detected\");  \n");
   fprintf(newfile, "     for(test=1;test<=prog_unit;test++){ \n");
   fprintf(newfile, "/* \n");
   fprintf(newfile, "      printf(\"==> prog_unit = %%d \\n\",test); \n");
   fprintf(newfile, "     printf(\"... activity time = %%d \\n\",prog[test].serve_time); \n");
   fprintf(newfile, "     printf(\"... activity range = %%d \\n\",prog[test].serve_range); \n");
   fprintf(newfile, "     printf(\"... inter-arrival time = %%d \\n\",prog[test].inter_time); \n");
   fprintf(newfile, "     printf(\"... inter-arrival range = %%d \\n\",prog[test].inter_range); \n");
   fprintf(newfile, "     printf(\"... transfer flag = %%d \\n\",prog[test].transfer); \n");
   fprintf(newfile, "     printf(\"... transfer percent = %%d \\n\",prog[test].percent); \n");
   fprintf(newfile, "     printf(\"... queue flag = %%d \\n\",prog[test].queue_text != NIL); \n");
   fprintf(newfile, "     printf(\"... serve flag = %%d \\n\",prog[test].serve_text[0] != NIL); \n");
   fprintf(newfile, "     printf(\"... release flag = %%d \\n\",prog[test].rel_text != NIL); \n");
   fprintf(newfile, "     printf(\"... number to serve = %%d \\n\",completion_total[no_runs]); \n");
   fprintf(newfile, "     printf(\"... decrement after completion by %%d \\n\",prog[test].quit_factor); \n");
   fprintf(newfile, "     printf(\"... code is %%d \\n\",prog[test].pu_code); \n");
   fprintf(newfile, "     printf(\"... parent = %%d \\n\",prog[test].parent); \n");
   fprintf(newfile, "     printf(\"... br_end = %%d \\n\",prog[test].br_end); \n");
   fprintf(newfile, "     printf(\"... br_case1 = %%d \\n\",prog[test].br_case1); \n");
   fprintf(newfile, "     printf(\"... br_case2 = %%d \\n\",prog[test].br_case2);   \n");
   fprintf(newfile, "  */   \n");
   fprintf(newfile, " \n");
   fprintf(newfile, "     } \n");
   fprintf(newfile, "     init_simpack(LINKED); \n");
   fprintf(newfile, "     for (loop=1;loop<=no_fac;loop++){ \n");
   fprintf(newfile, "        if((OldId= InList(fac[loop].name)) == PU_END){ \n");
   fprintf(newfile, "          fac[loop].id = create_facility(fac[loop].name,fac[loop].num_servers); \n");
   fprintf(newfile, "          fac_list[fac_list_cnt].fid = fac[loop].id; \n");
   fprintf(newfile, "          strcpy(fac_list[fac_list_cnt].fname,fac[loop].name); \n");
   fprintf(newfile, "          prog[fac[loop].unit].id = fac[loop].id; \n");
   fprintf(newfile, "        } \n");
   fprintf(newfile, "        else{ \n");
   fprintf(newfile, "          prog[fac[loop].unit].id = fac[loop].id = OldId; \n");
   fprintf(newfile, "        } \n");
   fprintf(newfile, "           \n");
   fprintf(newfile, "          \n");
   fprintf(newfile, "/*           printf(\"fac name = %%s   id = %%d  \\n\",fac[loop].name,fac[loop].id);  */ \n");
   fprintf(newfile, "          \n");
   fprintf(newfile, "     } \n");
   fprintf(newfile, "         \n");
   fprintf(newfile, "     for(num_sims=1;num_sims<=no_runs;num_sims++){ \n");
   fprintf(newfile, "        num_to_serve = completion_total[num_sims]; \n");
   fprintf(newfile, "        for(loop=1;loop<= prog_unit;loop++){ \n");
   fprintf(newfile, "           if (prog[loop].parent == 1) { \n");
   fprintf(newfile, "             if(prog[loop].transfer == 1){ \n");
   fprintf(newfile, "             } \n");
   fprintf(newfile, "             token_loop.attr[0] = (float) loop; \n");
   fprintf(newfile, "	   /*  printf(\"scheduling arrival --\\n\"); */ \n");
   fprintf(newfile, "             schedule(ARRIVE_,curr_time,token_loop);  \n");
   fprintf(newfile, "     /*         printf(\"schedule prog_unit # %%d \\n\",token_loop);  */ \n");
   fprintf(newfile, "           } \n");
   fprintf(newfile, "        } \n");
   fprintf(newfile, "        while(num_to_serve){ \n");
   fprintf(newfile, "           next_event(&event,&token);  \n");
   fprintf(newfile, "           switch(event){ \n");
   fprintf(newfile, "              case BR_ARR_: \n");
   fprintf(newfile, "/*                           printf(\"...in BR_ARR\\n\");   */ \n");
   fprintf(newfile, "                            rn = random(1,100) ; \n");
   fprintf(newfile, " \n");
   fprintf(newfile, "                            update_arrivals(); \n");
   fprintf(newfile, "                            schedule(ARRIVE_,0.0,token); \n");
   fprintf(newfile, "         \n");
   fprintf(newfile, "/*           trace_eventlist();            */ \n");
   fprintf(newfile, " \n");
   fprintf(newfile, " \n");
   fprintf(newfile, "                            if( prog[tnum(token)].percent <= rn){ \n");
   fprintf(newfile, "			       a_token.attr[0] = \n");
   fprintf(newfile, "                                 (float) prog[tnum(token)].br_case1; \n");
   fprintf(newfile, "                               schedule(REQUEST_,0.0,a_token); \n");
   fprintf(newfile, "                                \n");
   fprintf(newfile, "                            } \n");
   fprintf(newfile, "                            else{ \n");
   fprintf(newfile, "                               prog[prog[tnum(token)].br_case2].transfer = 1; \n");
   fprintf(newfile, "			       a_token.attr[0] =  \n");
   fprintf(newfile, "                                 (float) prog[tnum(token)].br_case2; \n");
   fprintf(newfile, "                               schedule(REQUEST_,0.0,a_token); \n");
   fprintf(newfile, "                                \n");
   fprintf(newfile, "                            }  \n");
   fprintf(newfile, "                            \n");
   fprintf(newfile, "                         break; \n");
   fprintf(newfile, "              case ARRIVE_:    \n");
   fprintf(newfile, "/*                            printf(\"...Arrive\\n\");  \n");
   fprintf(newfile, "           trace_eventlist();   */ \n");
   fprintf(newfile, " \n");
   fprintf(newfile, "                         range = prog[tnum(token)].inter_range; \n");
   fprintf(newfile, "                         lower = prog[tnum(token)].inter_time - range; \n");
   fprintf(newfile, "                         upper = prog[tnum(token)].inter_time + range; \n");
   fprintf(newfile, "                          \n");
   fprintf(newfile, "                        xx = prog[tnum(token)].inter_time; \n");
   fprintf(newfile, "                         my_priority = prog[tnum(token)].mypri; \n");
   fprintf(newfile, "  \n");
   fprintf(newfile, "                  \n");
   fprintf(newfile, "                       if (prog[tnum(token)].dist1 == 0) \n");
   fprintf(newfile, "                                  sample = random(lower,upper); \n");
   fprintf(newfile, "                       else  if (prog[tnum(token)].dist1 == 1) \n");
   fprintf(newfile, "                                 sample = normal(xx,yy); \n");
   fprintf(newfile, "                        else  if (prog[tnum(token)].dist1 == 2) \n");
   fprintf(newfile, "                                 sample = expntl(xx); \n");
   fprintf(newfile, "                         else  if (prog[tnum(token)].dist1 == 3) \n");
   fprintf(newfile, "                                 sample = uniform(xx,yy); \n");
   fprintf(newfile, "                        else  if (prog[tnum(token)].dist1 == 4) \n");
   fprintf(newfile, "                                 sample =  erlang(xx,yy); \n");
   fprintf(newfile, "                        else \n");
   fprintf(newfile, "                         sample = random(lower,upper); \n");
   fprintf(newfile, "                         if (prog[tnum(token)].transfer == 1){ \n");
   fprintf(newfile, "                           schedule(BR_ARR_,sample,token);  \n");
   fprintf(newfile, "                         } \n");
   fprintf(newfile, "                         else{ \n");
   fprintf(newfile, "                            if (prog[tnum(token)].serve_text[0] == NIL){ \n");
   fprintf(newfile, "                               schedule(SERVICE_,sample,token); \n");
   fprintf(newfile, "                               if (prog[tnum(token)].parent == 1) \n");
   fprintf(newfile, "                                  schedule(ARRIVE_,sample,token); \n");
   fprintf(newfile, "                            } \n");
   fprintf(newfile, "                            else {  \n");
   fprintf(newfile, "                               if (prog[tnum(token)].parent == 1){ \n");
   fprintf(newfile, "                                  update_arrivals(); \n");
   fprintf(newfile, "                                  schedule(ARRIVE_,sample,token); \n");
   fprintf(newfile, "                               } \n");
   fprintf(newfile, "                               schedule(REQUEST_,0.0,token); \n");
   fprintf(newfile, "                           } \n");
   fprintf(newfile, "                         } \n");
   fprintf(newfile, "                        break; \n");
   fprintf(newfile, "              case REQUEST_: \n");
   fprintf(newfile, "  rcount++; \n");
   fprintf(newfile, "/*                           printf(\"...in REQUEST==>%%d \\n\",rcount); */ \n");
   fprintf(newfile, "                             \n");
   fprintf(newfile, "/*           trace_eventlist();                             */ \n");
   fprintf(newfile, " \n");
   fprintf(newfile, " \n");
   fprintf(newfile, " \n");
   fprintf(newfile, "                         if (request(prog[tnum(token)].id,token,my_priority) != BUSY){ \n");
   fprintf(newfile, "                            schedule(SERVICE_,0.0,token); \n");
   fprintf(newfile, "                         } \n");
   fprintf(newfile, "                      else if (prog[tnum(token)].tran_mode == 1) \n");
   fprintf(newfile, "                             { /* let this token die   */ }                \n");
   fprintf(newfile, "                         else { \n");
   fprintf(newfile, "                               /* schedule(REQUEST_,0.1,a_token); */ \n");
   fprintf(newfile, "			    }; \n");
   fprintf(newfile, "                         break;  \n");
   fprintf(newfile, "              case SERVICE_: \n");
   fprintf(newfile, "/*                            printf(\"...in SERVICE\\n\");  \n");
   fprintf(newfile, "           trace_eventlist();   */ \n");
   fprintf(newfile, " \n");
   fprintf(newfile, "                         range = prog[tnum(token)].serve_range; \n");
   fprintf(newfile, "                         lower = prog[tnum(token)].serve_time - range; \n");
   fprintf(newfile, "                         upper = prog[tnum(token)].serve_time + range; \n");
   fprintf(newfile, "                       /* printf(\" l u r t= %%d %%d %%d %%d\\n\",lower,upper,range,token); */ \n");
   fprintf(newfile, " \n");
   fprintf(newfile, " \n");
   fprintf(newfile, " \n");
   fprintf(newfile, " \n");
   fprintf(newfile, "                          \n");
   fprintf(newfile, "                        \n");
   fprintf(newfile, "                        xx = prog[tnum(token)].serve_time; \n");
   fprintf(newfile, "                         yy = prog[tnum(token)].serve_range ; \n");
   fprintf(newfile, "           \n");
   fprintf(newfile, "                        if (prog[tnum(token)].dist == 0) \n");
   fprintf(newfile, "                                  sample = random(lower,upper); \n");
   fprintf(newfile, "                       else  if (prog[tnum(token)].dist == 1) \n");
   fprintf(newfile, "                                 sample = normal(xx,yy); \n");
   fprintf(newfile, "                        else  if (prog[tnum(token)].dist == 2) \n");
   fprintf(newfile, "                                 sample =  expntl(xx); \n");
   fprintf(newfile, "                         else  if (prog[tnum(token)].dist == 3) \n");
   fprintf(newfile, "                                 sample =  uniform(xx/100,yy/100); \n");
   fprintf(newfile, "                          else  if (prog[tnum(token)].dist == 4) \n");
   fprintf(newfile, "                           sample =  erlang(xx,yy); \n");
   fprintf(newfile, "                         else \n");
   fprintf(newfile, "                            sample = random(lower,upper);  \n");
   fprintf(newfile, " \n");
   fprintf(newfile, " \n");
   fprintf(newfile, " \n");
   fprintf(newfile, "                         /* sample = random(lower,upper) ; */ \n");
   fprintf(newfile, "                         schedule(DEPART_,sample,token); \n");
   fprintf(newfile, "                         break; \n");
   fprintf(newfile, "              case BR_DEP_: \n");
   fprintf(newfile, "  /*                            printf(\"...in BR_DEP\\n\");   \n");
   fprintf(newfile, "           trace_eventlist();                             */ \n");
   fprintf(newfile, "                         release(prog[tnum(token)].id,token); \n");
   fprintf(newfile, "                         num_to_serve -= prog[tnum(token)].quit_factor; \n");
   fprintf(newfile, "                         curr_time = sim_time(); \n");
   fprintf(newfile, "                if ((prog[tnum(token)].br_end == 0)&&(prog[tnum(token)].pu_code != PU_END)){ \n");
   fprintf(newfile, "                            prog[prog[tnum(token)].pu_code].transfer = 1; \n");
   fprintf(newfile, "			    a_token.attr[0] = (float) prog[tnum(token)].pu_code; \n");
   fprintf(newfile, "                            schedule(REQUEST_,0.0,a_token); \n");
   fprintf(newfile, "                      } \n");
   fprintf(newfile, "                         else  \n");
   fprintf(newfile, "                            update_completions();  \n");
   fprintf(newfile, "                         break; \n");
   fprintf(newfile, "              case DEPART_: \n");
   fprintf(newfile, " \n");
   fprintf(newfile, "/*                            printf(\"...in DEPART\\n\");     \n");
   fprintf(newfile, "           trace_eventlist();   */ \n");
   fprintf(newfile, "                         if (prog[tnum(token)].transfer == 1){ \n");
   fprintf(newfile, "                           schedule(BR_DEP_,0.0,token);  \n");
   fprintf(newfile, "                         } \n");
   fprintf(newfile, "                         else{ \n");
   fprintf(newfile, "                            release(prog[tnum(token)].id,token); \n");
   fprintf(newfile, "                            num_to_serve -= prog[tnum(token)].quit_factor; \n");
   fprintf(newfile, "                            curr_time = sim_time(); \n");
   fprintf(newfile, "                            if (prog[tnum(token)].pu_code != PU_END) { \n");
   fprintf(newfile, "			       a_token.attr[0] = (float) prog[tnum(token)].pu_code; \n");
   fprintf(newfile, "                               schedule(ARRIVE_,0.0,a_token); \n");
   fprintf(newfile, "			     } \n");
   fprintf(newfile, "                            else if (prog[tnum(token)].serve_text[0] != NIL) \n");
   fprintf(newfile, "                              update_completions(); \n");
   fprintf(newfile, "                         } \n");
   fprintf(newfile, "              } \n");
   fprintf(newfile, "        } \n");
   fprintf(newfile, "     print_flag = 0; \n");
   fprintf(newfile, "     for(loop=1;loop<=prog_unit;loop++) \n");
   fprintf(newfile, "        if (prog[loop].serve_text[0] != NIL) { \n");
   fprintf(newfile, "           print_flag = 1; \n");
   fprintf(newfile, "       } \n");
   fprintf(newfile, "     if (print_flag) { \n");
   fprintf(newfile, "       /* printf(\"\\nThe C generated code for this simulation is in the file: simgen.c\\n\"); */ \n");
   fprintf(newfile, "       report_stats(); \n");
   fprintf(newfile, "      /*  codgen(); */ \n");
   fprintf(newfile, "     } \n");
   fprintf(newfile, "     }    \n");
   fprintf(newfile, "  } \n");
   fprintf(newfile, "} \n");
   fprintf(newfile, "     \n");
   fprintf(newfile, "int InList(String) \n");
   fprintf(newfile, "   char *String; \n");
   fprintf(newfile, "{ \n");
   fprintf(newfile, "   int loop; \n");
   fprintf(newfile, " \n");
   fprintf(newfile, "   if (fac_list_cnt == 0){ \n");
   fprintf(newfile, "     fac_list_cnt++; \n");
   fprintf(newfile, "     return -1; \n");
   fprintf(newfile, "   } \n");
   fprintf(newfile, "   else { \n");
   fprintf(newfile, "      for (loop=1;loop<=fac_list_cnt;loop++){ \n");
   fprintf(newfile, "          if (strequal(String,fac_list[loop].fname)) { \n");
   fprintf(newfile, "            return fac_list[loop].fid;    \n");
   fprintf(newfile, "          } \n");
   fprintf(newfile, "      } \n");
   fprintf(newfile, "      fac_list_cnt++; \n");
   fprintf(newfile, "      return -1; \n");
   fprintf(newfile, "   } \n");
   fprintf(newfile, "} \n");
   fprintf(newfile, " \n");
   fprintf(newfile, " \n");
   fprintf(newfile, "int tnum(token) \n");
   fprintf(newfile, "TOKEN token; \n");
   fprintf(newfile, "{  \n");
   fprintf(newfile, "  return((int) token.attr[0]); \n");
   fprintf(newfile, "}  \n");
   fprintf(newfile, " \n");
   fprintf(newfile, " \n");
   fprintf(newfile, " \n");
   fprintf(newfile, " \n");
}
