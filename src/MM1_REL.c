/* ----------------------------------------------------------------------- 
Código gerado com o ASDA - Ambiente de Simulação Distribuída Automático
--------------------------------------------------------------------------*/
#include <stdio.h>
#include "smpl.h"

main()
{
 /* definicoes */
 float Te = 100000000;
 int Event = 1, Customer = 1, Aleatorio;
 float Ta1 = 1.25, Ts1 = 1;
 int i = 0;

 FILE *p, *saida;
 saida = fopen("MM1_REL.out","w");

 if ((p = sendto(saida)) == NULL)
    printf("Erro na saida \n");


 /* prepara o sistema de simulacao e da nome ao modelo */
 smpl(0," MM1_REL");


 /* cria e da nome as facilidades */
 facility("CS_1",1);

 /* escalona a chegada do primeiro cliente */
   stream(0);

   schedule(1,1.0, Customer);



 while ( (time() < Te) )
{
    cause(&Event,&Customer);
    switch(Event)
    {
        case 1 : 
          schedule(2,0.0, Customer);
          schedule(1,expntl(Ta1), Customer);
          break;

        /*  centro de serviço = CS_1 */
        case 2 : 
          if (request("CS_1", Event, Customer, 0) == 0)
             schedule(3,expntl(Ts1), Customer);
          break;
        case 3 : 
          release("CS_1", Customer);
          break;
 }
}


/* gera o relatorio da simulacao */
  fprintf(saida,"TempoSimulado: %f\n", time() );

  fprintf(saida,"Utilizacao (\"CS_1\") = %g\n", utilizacao_recurso("CS_1"));
  fprintf(saida,"Comprimento medio fila (\"CS_1\") = %g\n", comprimento_medio_fila("CS_1"));
  fprintf(saida,"Periodo medio ocupado (\"CS_1\") = %g\n", periodo_medio_ocupado("CS_1"));

   fclose(saida);
}
/* ----------------------------------------------------------------------- */
