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

 real Ts3 = 7, Ts4 = 8 ;
 int i = 0;
 int info;

 int CS_3, CS_4;
 double lookAhead = 5.9;
 int valor_semente = 1;
 int tid_processo_pai, tid_pl1,tid_pl2;
 FILE *p, *saida;
 saida = fopen("MODELOHIP3CONF01_1.out","w");

 if ((p = sendto(saida)) == NULL)
    printf("Erro na saida \n");


 /* prepara o sistema de simulacao e da nome ao modelo */


  proc_local = PL1;
  clock_canais[PL2] = 0.0;

  smpl(0," MODELOHIP3CONF01_1");
  stream(valor_semente);


 /* cria e da nome as facilidades */
 facility("CS_3",1);
 facility("CS_4",1);

 /* escalona a chegada do primeiro cliente */
   for (i = 0; i < 10 ; i++)
      schedule(1,2.0, Customer, 1);



 while ( !fim )
{
    cause(&Event,&Customer);
    switch(Event)
    {
        case 1 : 
          schedule(2,0.0, Customer, PL0);
          schedule(1,expntl(Ta1), Customer, PL0);
          break;

        /*  centro de serviço = CS_3 */
        case 6 : 
          if (request("CS_3", Event, Customer, 0, PL1) == 0)
             schedule(7,expntl(Ts3), Customer, PL1);
          break;
        case 7 : 
          release("CS_3", Customer);
             schedule(8,0.0, Customer, PL1);
          break;

        /*  centro de serviço = CS_4 */
        case 8 : 
          if (request("CS_4", Event, Customer, 0, PL1) == 0)
             schedule(9,expntl(Ts4), Customer, PL1);
          break;
        case 9 : 
          release("CS_4", Customer);
             schedule(10,0.0, Customer, PL2);
          break;

        /* Término da simulação */
        case 1000 : 
          schedule(1000,0.0, Customer, PL2);
          break;
        case 1001 : 
          schedule(1001,0.0, Customer, PL0);
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
