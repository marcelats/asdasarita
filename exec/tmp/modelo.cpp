/* ----------------------------------------------------------------------- 
C�digo gerado com o ASDA - Ambiente de Simula��o Distribu�da Autom�tico
--------------------------------------------------------------------------*/
#include "queuing.h"

main()
{
 /* definicoes */
  Token Customer(1);
  int Aleatorio;
  
 float Te = 500000;
 float Ta0 = 5, Ts0 = 7;
 int i = 0;

 Facility *CS_0;
 unsigned int Maximo_Entidades = 0, Num_Max_Entidades = 10;

 /* prepara o sistema de simulacao e da nome ao modelo */
 new Future(LINKED);


 /* cria e da nome as facilidades */
 CS_0 = new Facility("CS_0");

 /* escalona a chegada do primeiro cliente */
   for (i = 0; i < 10 ; i++)
      Future::Schedule(1,2.0, Customer);

 while( (Future::SimTime() < Te) && (Maximo_Entidades < Num_Max_Entidades))
 {
    Estatus es = Future::NextEvent();
    switch(es.event_id)
   {
        case 1 : 
         {
          Token Customer = Future::CurrentToken();
          Future::UpdateArrivals();
          Future::Schedule(2,0.0, Customer);
          Customer.Id(Customer.Id() + 1);
         }
          break;

        /*  centro de serviço = CS_0 */
        case 2 : 
         {
          Token Customer = Future::CurrentToken();
          if (CS_0->Request(Customer) == FREE)
             Future::Schedule(3,expntl(Ts0), Customer);
         }
          break;
        case 3 : 
         {
          Token Customer = Future::CurrentToken();
          CS_0->Release( Customer.Id() );
          Maximo_Entidades++;
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
