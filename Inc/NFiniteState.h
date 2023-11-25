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
// Pending: torna o estado prioritário, sendo executado antes dos demais. Quando
// o número de vezes (Turns) se esgotar, ele pára de ser executado automaticamente.
// Turns: número de vezes que o estado será repetido.
//------------------------------------------------------------------------------

namespace nfinitestate_space{

    //---------------------------------------------------
	// definição da classe NFiniteState
    class NFiniteState {

		private:
            //-------------------------------------------
			// constantes internas
			static const int INTERVAL_MAX = 10000;
			static const int TURNS_MAX = 10;
			
            //-------------------------------------------
			uint8_t turns;                      // número de repetições antes de avançar
			int interval;                  		// intervalo a ser aguardado nesse estado

        private:
            //-------------------------------------------
            // funções de manipulação das propriedades
            void SetTurns(uint8_t);
            uint8_t GetTurns();
            void SetInterval(int);
            int GetInterval();

        public:
            //-------------------------------------------
            // MÉTODOS do componente NFiniteState             < APLICABILIDADE >
            NFiniteState(NComponent*);
            ~NFiniteState();
            virtual void Notify(NMESSAGE*);

            //-------------------------------------------
            // EVENTOS do componente NFiniteState             < OCORRÊNCIA >
            void (*OnStateEntry)();		                   		// notifica a entrada
			void (*OnStateLeave)();		                   		// notifica a saída
			
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
