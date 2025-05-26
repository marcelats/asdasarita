/* ----------------------------------------------------------------------- 
C�digo gerado com o ASDA - Ambiente de Simula��o Distribu�da Autom�tico
--------------------------------------------------------------------------*/
#include "queuing.h"

main()
{
 /* definicoes */
  int Event;
  TOKEN Customer;
  
 float Te = 50000;
 float Ta0 = 10, Ts0 = 10;
 int i = 0;

 int CS_0;

 /* prepara o sistema de simulacao e da nome ao modelo */
 init_simpack(LINKED);


 /* cria e da nome as facilidades */
 CS_0 = create_facility("CS_0",1);

 /* escalona a chegada do primeiro cliente */
   schedule(1,0.0, Customer);

 while ( (time() < Te) )
 {
    next_event(&Event,&Customer);
    switch(Event)
   {
        case 1 : 
          update_arrivals();
          schedule(2,0.0, Customer);
          stream(1);
          schedule(1,expntl(Ta0), Customer);
          break;

        /*  centro de serviço = CS_0 */
        case 2 : 
          stream(1);
          if (request(CS_0, Customer,0) == FREE)
             schedule(3,expntl(Ts0), Customer);
          break;
        case 3 : 
          release(CS_0, Customer);
           update_completions();
          break;
   }
 }


/* gera o relatorio da simulacao */
   report_stats();
  end_simpack();
}
/* ----------------------------------------------------------------------- */
