//============================================================================//
// Title: Componente "Estado" para o componente "NFiniteStateMachine"         //
// Version: 0.0.1                                                             //
// Author: J. Nilo Rodrigues    I.F.: 9530                                    //
// Date: 27/01/2015                                                           //
// Last Update: 27/01/2015                                                    //
// P/N: xx.xxx.xxx.xx   Rev.: -       Code: xxx.xxx-x    AT: ----/--          //
// Compiler: IAR EWARM V6.40                                                  //
//============================================================================//
#ifndef NFINITESTATE_H
    #define NFINITESTATE_H

    #include "System.h"

//------------------------------------------------------------------------------
// NOTAS:
// Pending: torna o estado priorit�rio, sendo executado antes dos demais. Quando
// o n�mero de vezes (Turns) se esgotar, ele p�ra de ser executado automaticamente.
// Turns: n�mero de vezes que o estado ser� repetido.
//------------------------------------------------------------------------------

namespace nfinitestate_space{

    //---------------------------------------------------
	// defini��o da classe NFiniteState
    class NFiniteState {

		private:
            //-------------------------------------------
			// constantes internas
			static const int INTERVAL_MAX = 10000;
			static const int TURNS_MAX = 10;
			
            //-------------------------------------------
			uint8_t turns;                      // n�mero de repeti��es antes de avan�ar
			int interval;                  		// intervalo a ser aguardado nesse estado

        private:
            //-------------------------------------------
            // fun��es de manipula��o das propriedades
            void SetTurns(uint8_t);
            uint8_t GetTurns();
            void SetInterval(int);
            int GetInterval();

        public:
            //-------------------------------------------
            // M�TODOS do componente NFiniteState             < APLICABILIDADE >
            NFiniteState(NComponent*);
            ~NFiniteState();
            virtual void Notify(NMESSAGE*);

            //-------------------------------------------
            // EVENTOS do componente NFiniteState             < OCORR�NCIA >
            void (*OnStateEntry)();		                   		// notifica a entrada
			void (*OnStateLeave)();		                   		// notifica a sa�da
			
            //-------------------------------------------
            // PROPRIEDADES do componente NFiniteState        < DEFAULT VALUES >
            bool Enabled;                                       // true
			bool Pending;                                       // false
			int Index;											// -1
            property<NFiniteState, uint8_t, READ_WRITE> Turns;	// 1
			property<NFiniteState, int, READ_WRITE> Interval; 	// 100

    };
    //---------------------------------------------------
};
    using namespace nfinitestate_space;
#endif
//==============================================================================
