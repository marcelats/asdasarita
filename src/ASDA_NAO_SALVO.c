/* ----------------------------------------------------------------------- 
C�digo gerado com o ASDA - Ambiente de Simula��o Distribu�da Autom�tico
--------------------------------------------------------------------------*/
#include "smpl.h"

main()
{
 /* definicoes */
 float Te = 100;
 int Event = 1, Customer = 1, Aleatorio;
 float Ta0 = 1, Ts0 = 1;
 int i = 0;

 char flag_reset = 0;
 float timeWarmUp = 5.0;
 int CS_0;
 unsigned int Maximo_Entidades = 0, Num_Max_Entidades = 1;
 float TBatch = 0;
 int r = 0;
 FILE *p, *saida;
 saida = fopen("ASDA_NAO_SALVO.out","w");

 if ((p = sendto(saida)) == NULL)
    printf("Erro na saida \n");


 /* prepara o sistema de simulacao e da nome ao modelo */
 smpl(0," ASDA_NAO_SALVO");


 /* cria e da nome as facilidades */
 CS_0 = facility("CS_0",1);

 /* escalona a chegada do primeiro cliente */
   schedule(1,1.0, Customer);



 while( (time() < Te) && (Maximo_Entidades < Num_Max_Entidades)&& (r== 0) )
{
   if ( (!flag_reset) && (time() > timeWarmUp) )
   {
      reset();
      flag_reset = 1;
      Maximo_Entidades = 0;
   }
    cause(&Event,&Customer);
    switch(Event)
    {
        case 1 : 
          schedule(2,0.0, Customer);
          stream(1);
          schedule(1,expntl(Ta0), Customer);
          break;

        /*  centro de servi   o = CS_0 */
        case 2 : 
          stream(1);
          if (request(CS_0, Customer,0) == 0)
          {
             TBatch = expntl(Ts0);
              r = obs(TBatch);
             schedule(3,TBatch, Customer);
          }
          break;
        case 3 : 
          release(CS_0, Customer);
          Maximo_Entidades++;
          break;
 }
}


/* gera o relatorio da simulacao */
   report();
   fclose(saida);
}
/* ----------------------------------------------------------------------- */
