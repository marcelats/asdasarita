/* ----------------------------------------------------------------------- */
#include <dir.h>
#include <stdio.h>
#include <conio.h>
#include "parsmpl.h"
#include "randpar.h"
#include "declaracoes.h"
#include <pvm3.h>



main()
{
 /* definicoes */
 int Event = 1, Customer = 1, Aleatorio;
 int tid_processo_pai;

 real Ts5 = 2, Ts6 = 7 ;
 int i = 0;
 int info;

 int CS_5, CS_6;
 double lookAhead = 7.89;
 int valor_semente = 1;
 int tid_processo_pai, tid_pl1,tid_pl2;
 FILE *p, *saida;
 saida = fopen("MODELOHIP3CONF01_2.out","w");

 if ((p = sendto(saida)) == NULL)
    printf("Erro na saida \n");


 /* prepara o sistema de simulacao e da nome ao modelo */


  proc_local = PL2;
  clock_canais[PL1] = 0.0;

  smpl(0," MODELOHIP3CONF01_2");
  stream(valor_semente);


 /* cria e da nome as facilidades */
 facility("CS_5",1);
 facility("CS_6",1);

 /* escalona a chegada do primeiro cliente */
   for (i = 0; i < 10 ; i++)
      schedule(1,2.0, Customer, 2);



 while ( !fim )
{
    cause(&Event,&Customer);
    switch(Event)
    {

        /*  centro de serviço = CS_5 */
        case 10 : 
          if (request("CS_5", Event, Customer, 0, PL2) == 0)
             schedule(11,expntl(Ts5), Customer, PL2);
          break;
        case 11 : 
          release("CS_5", Customer);
             schedule(12,0.0, Customer, PL2);
          break;

        /*  centro de serviço = CS_6 */
        case 12 : 
          if (request("CS_6", Event, Customer, 0, PL2) == 0)
             schedule(13,expntl(Ts6), Customer, PL2);
          break;
        case 13 : 
          release("CS_6", Customer);
          break;

        /* Término da simulação */
        case 1000 : 
          schedule(1001,0.0, Customer, PL1);
          fim = 1;
          break;
 }
}


/* gera o relatorio da simulacao */
   report();
   fclose(saida);
 parsmpl_pvm_exit();
}
/* ----------------------------------------------------------------------- */
