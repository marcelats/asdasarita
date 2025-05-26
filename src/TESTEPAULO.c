/* ----------------------------------------------------------------------- 
C digo gerado com o ASDA - Ambiente de Simula  o Distribu da Autom tico
--------------------------------------------------------------------------*/
#include "smpl.h"

main()
{
 /* definicoes */
 float Te = 5000;
 int Event = 1, Customer = 1, Aleatorio;
 float Ta0 = 10, Ts0 = 5, Ts2 = 3, Ts3 = 12;
 int i = 0;

 char flag_reset = 0;
 float timeWarmUp = 250.0;
 int FE, proc, DF;
 unsigned int Maximo_Entidades = 0, Num_Max_Entidades = 10;
 FILE *p, *saida;
 saida = fopen("TESTEPAULO.out","w");

 if ((p = sendto(saida)) == NULL)
    printf("Erro na saida \n");


 /* prepara o sistema de simulacao e da nome ao modelo */
 smpl(0," TESTEPAULO");


 /* cria e da nome as facilidades */
 FE = facility("FE",1);
 proc = facility("proc",1);
 DF = facility("DF",1);

 /* escalona a chegada do primeiro cliente */
   for (i = 0; i < 10 ; i++)
      schedule(1,0.0, Customer);



 while( (time() < Te) && (Maximo_Entidades < Num_Max_Entidades))
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
          break;

        /*  centro de serviço = FE */
        case 2 : 
          if (request(FE, Customer,0) == 0)
             schedule(3,expntl(Ts0), Customer);
          break;
        case 3 : 
          release(FE, Customer);
          Aleatorio = randomX(1,10000);
          if (( 1 <= Aleatorio) && ( Aleatorio <= 10000) )
           schedule(4,0.0, Customer);
          if (( 10001 <= Aleatorio) && ( Aleatorio <= 10000) )
             Maximo_Entidades++;
          break;

        /*  centro de serviço = proc */
        case 4 : 
          if (request(proc, Customer,0) == 0)
             schedule(5,expntl(Ts2), Customer);
          break;
        case 5 : 
          release(proc, Customer);
          Aleatorio = randomX(1,10000);
          if (( 1 <= Aleatorio) && ( Aleatorio <= 5000) )
           schedule(6,0.0, Customer);
          if (( 5001 <= Aleatorio) && ( Aleatorio <= 10000) )
           schedule(2,0.0, Customer);
          break;

        /*  centro de serviço = DF */
        case 6 : 
          if (request(DF, Customer,0) == 0)
             schedule(7,expntl(Ts3), Customer);
          break;
        case 7 : 
          release(DF, Customer);
             schedule(4,0.0, Customer);
          break;
 }
}


/* gera o relatorio da simulacao */
   report();
   fclose(saida);
}
/* ----------------------------------------------------------------------- */
