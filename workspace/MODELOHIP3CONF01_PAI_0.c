/* ----------------------------------------------------------------------- */
#include <stdio.h>
#include <conio.h>
#include "smpl.h"
#include "rand.h"

#define PL0   0
#define PL1   1
#define PL2   2
#define SLAVENAME1   TESTEFILHO_PL1
#define SLAVENAME2   TESTE_FILHO_PL2

main()
{
 /* definicoes */
 float Te = 25000;
 int Event = 1, Customer = 1, Aleatorio;
 real Ta1 = 3;
 real Ts1 = 5, Ts2 = 2 ;
 int i = 0;
 int info;

 int CS_1, CS_2;
 double lookAhead = 16.0;
 int valor_semente = 1;
 int tid_processo_pai, tid_pl1,tid_pl2;
 FILE *p, *saida;
 saida = fopen("MODELOHIP3CONF01_0.out","w");

 if ((p = sendto(saida)) == NULL)
    printf("Erro na saida \n");


 /* prepara o sistema de simulacao e da nome ao modelo */

  /* identifica processo pai */
  tid_processo_pai = pvm_mytid();

 /* para prepara a tabela */

  /* inicializa tabela de tids */
  for (i=0; i < 3; i++)
  {
      tabela_tids[i] = 0;
  }
  info = pvm_spawn(SLAVENAME1, (char**)0, nomeMaquina, 1, &tid_pl1);
  if ( info < 1)
  {
       printf("Trouble spawning slaves. Aborting. Error codes are:\n");
       printf("TID %d\n", tid_pl1);
       pvm_kill( tid_pl1);
       pvm_exit();
       exit(1);
  }
  info = pvm_spawn(SLAVENAME2, (char**)0, nomeMaquina, 1, &tid_pl2);
  if ( info < 1)
  {
       printf("Trouble spawning slaves. Aborting. Error codes are:\n");
       printf("TID %d\n", tid_pl2);
       pvm_kill( tid_pl2);
       pvm_kill( tid_pl1);
       pvm_exit();
       exit(1);
  }
  tabela_tids[PL0] = tid_processo_pai;
  tabela_tids[PL0] = tid_pl0;
  tabela_tids[PL1] = tid_pl1;
  tabela_tids[PL2] = tid_pl2;
  
  pvm_initsend(PvmDataRaw);
 /* pai envia a tabela para os filhos */
  pvm_pkint(tabela_tids,3, 1);

 /*  Envia o valor da semente para os processos filhos  */
  pvm_pkint(&valor_semente,1,1);
  pvm_send(tid_pl1, 0);
  pvm_send(tid_pl2, 0);

 /* inicia os canais de clock - variáveis do ParSMPL */
  proc_local = PL0;
  clock_canais[PL1] = 0.0;
  clock_canais[PL2] = 0.0;


  smpl(0," MODELOHIP3CONF01_0");
  stream(valor_semente);


 /* cria e da nome as facilidades */
 facility("CS_1",1);
 facility("CS_2",1);

 /* escalona a chegada do primeiro cliente */
   for (i = 0; i < 10 ; i++)
      schedule(1,2.0, Customer, 0);



 while ( !fim )
{

      /* verificando o tempo de simulação */
    if (clock_sim() > Te)
       schedule(1000,0.0, Customer, PL1);

    cause(&Event,&Customer);
    switch(Event)
    {

        /*  centro de serviço = CS_1 */
        case 2 : 
          if (request("CS_1", Event, Customer, 0, PL0) == 0)
             schedule(3,expntl(Ts1), Customer, PL0);
          break;
        case 3 : 
          release("CS_1", Customer);
             schedule(4,0.0, Customer, PL0);
          break;

        /*  centro de serviço = CS_2 */
        case 4 : 
          if (request("CS_2", Event, Customer, 0, PL0) == 0)
             schedule(5,expntl(Ts2), Customer, PL0);
          break;
        case 5 : 
          release("CS_2", Customer);
             schedule(6,0.0, Customer, PL1);
          break;

        /* Término da simulação */
        case 1001 : 
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
