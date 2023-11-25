//============================================================================//
// Title: Componente de Máquina de Estados           						  //
// Version: 0.0.1                                                             //
// Author: J. Nilo Rodrigues    I.F.: 9530                                    //
// Date: 27/01/2015                                                           //
// Last Update: 27/01/2015                                                    //
// P/N: xx.xxx.xxx.xx   Rev.: -       Code: xxx.xxx-x    AT: ----/--          //
// Compiler: IAR EWARM V6.40                                                  //
//============================================================================//
#ifndef NFINITESTATEMACHINE_H
    #define NFINITESTATEMACHINE_H

    #include "System.h"
	#include "NFiniteState.h"

//------------------------------------------------------------------------------
namespace nfinitestatemachine_space{

    class NFiniteStateMachine: public NComponent{

        private:
			// constantes internas
			static const int TIMEBASE_DEFAULT = 1000;
			static const int TIMEBASE_MINIMUM = 10;
			
			// elementos da lista de estados
			int listItems;
			HANDLE* listStates;
			
			// propriedades
			bool enabled;
			bool manual;
			int index;
			int turns;
			int interval;
			NFiniteState* tmpState;
			NFiniteState* nxtState;

			// controle interno
			int interval_counter;
			bool interval_enabled;
			bool scheduled;

        private:
			void SetEnabled(bool);
			bool GetEnabled();
			void SetManual(bool);
			bool GetManual();
			void SetState(NFiniteState*);
			NFiniteState* GetState();
			
        private:
		  NFiniteState* FindStatePending();
		  NFiniteState* FindState(int);
		  bool SwitchState();
		  void RepeatState();
		  void NextIndex();
		  void TimeBase_Elapsed();

        //-------------------------------------------
        // MÉTODOS do componente NFiniteStateMachine
        public:
            NFiniteStateMachine();
            ~NFiniteStateMachine();
            unsigned int IncludeState(NFiniteState*);
			void FlushStates();
            void Notify(NMESSAGE*);
			bool ChangeState();

        //-------------------------------------------
        // EVENTOS do componente NFiniteStateMachine				< OCORRÊNCIA >
		void (*OnStateChange)(NFiniteState*);	// notifica a mudança de estado
		
        //-------------------------------------------
        // PROPRIEDADES do componente NFiniteStateMachine    		< DEFAULT VALUES >
		bool Forward;														// true
		property<NFiniteStateMachine, bool, READ_WRITE> Enabled;			// true
		property<NFiniteStateMachine, bool, READ_WRITE> Manual;				// false
		property<NFiniteStateMachine, NFiniteState*, READ_WRITE> State;		// NULL
    };
}
//------------------------------------------------------------------------------
using namespace nfinitestatemachine_space;
#endif

//==============================================================================
