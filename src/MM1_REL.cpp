/* ----------------------------------------------------------------------- 
Código gerado com o ASDA - Ambiente de Simulação Distribuída Automático
--------------------------------------------------------------------------*/
#include "queuing.h"

main()
{
 /* definicoes */
  Token Customer(1);
  
 float Te = 100000000;
 float Ta1 = 1.25, Ts1 = 1;
 int i = 0;

 Facility *CS_1;

 /* prepara o sistema de simulacao e da nome ao modelo */
 new Future(LINKED);


 /* cria e da nome as facilidades */
 CS_1 = new Facility("CS_1");

 /* escalona a chegada do primeiro cliente */
   Future::Schedule(1,1.0, Customer);

 while ( (Future::SimTime() < Te) )
 {
    Estatus es = Future::NextEvent();
    switch(es.event_id)
   {
        case 1 : 
         {
          Token Customer = Future::CurrentToken();
          Future::UpdateArrivals();
          Future::Schedule(2,0.0, Customer);
          stream(10);
          Customer.Id(Customer.Id() + 1);
          Future::Schedule(1,expntl(Ta1), Customer);
         }
          break;

        /*  centro de serviço = CS_1 */
        case 2 : 
         {
          Token Customer = Future::CurrentToken();
          if (CS_1->Request(Customer) == FREE)
             Future::Schedule(3,expntl(Ts1), Customer);
         }
          break;
        case 3 : 
         {
          Token Customer = Future::CurrentToken();
          CS_1->Release( Customer.Id() );
           Future::UpdateDepartures();
         }
          break;
      default: ErrXit(1,"bad event id");
   }
 }


/* gera o relatorio da simulacao */
   Future::ReportStats();
 return 0;
}
/* ----------------------------------------------------------------------- */
