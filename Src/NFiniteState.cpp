//============================================================================//
// Title: Componente "Estado" para o componente "NFiniteStateMachine"         //
// Version: 0.0.1                                                             //
// Author: J. Nilo Rodrigues    I.F.: 9530                                    //
// Date: 27/01/2015                                                           //
// Last Update: 27/01/2015                                                    //
// P/N: xx.xxx.xxx.xx   Rev.: -       Code: xxx.xxx-x    AT: ----/--          //
// Compiler: IAR EWARM V6.40                                                  //
//----------------------------------------------------------------------------//
// 27/01/2015: iniciado o desenvolvimentoo. (v0.0.1)			              //
//============================================================================//
#include "NFiniteState.h"

//------------------------------------------------------------------------------
// construtora da classe base NFiniteState
NFiniteState::NFiniteState(NComponent* Owner){
    //------------------------------------
    OnStateEntry = NULL; OnStateLeave = NULL;

    //------------------------------------
    // tratamento da propriedade Turns
    Turns.setContainer(this);
    Turns.setter(&NFiniteState::SetTurns);
    Turns.getter(&NFiniteState::GetTurns);

    //------------------------------------
    // tratamento da propriedade Interval
    Interval.setContainer(this);
    Interval.setter(&NFiniteState::SetInterval);
    Interval.getter(&NFiniteState::GetInterval);
	
    //------------------------------------
    Enabled = true;
	Pending = false;
	Index = -1;
	turns = 1;
	interval = 100;
	
	//------------------------------------
	// cria temporariamente uma mensagem
	NMESSAGE Msg;
	Msg.message = NM_ITEM_INCLUDED;
	Msg.lparam = (uint32_t)this;

    //------------------------------------
    // registra o estado na máquina
    Owner->Notify(&Msg);
}

//------------------------------------------------------------------------------
// destrutora da classe base NFiniteState
NFiniteState::~NFiniteState(){ }

//------------------------------------------------------------------------------
// atribui novo número de repetições do estado
void NFiniteState::SetTurns(uint8_t newTurns){
  	if(newTurns > TURNS_MAX){ newTurns = TURNS_MAX;}
	turns = newTurns;
}

//------------------------------------------------------------------------------
// retorna o número de repetições do estado
uint8_t NFiniteState::GetTurns(){ return(turns);}

//------------------------------------------------------------------------------
// atribui novo intervalo do estado
void NFiniteState::SetInterval(int newInterval){
  	if(newInterval > INTERVAL_MAX){ newInterval = INTERVAL_MAX;}
	interval = newInterval;
}

//------------------------------------------------------------------------------
// retorna o intervalo do estado
int NFiniteState::GetInterval(){ return(interval);}

//------------------------------------------------------------------------------
// notifica mensagens para a classe NFiniteState
void NFiniteState::Notify(NMESSAGE* msg){
    if(Enabled){
	  	switch(msg->message){
			case NM_STATE_ENTRY:
	  			if(OnStateEntry != NULL){ OnStateEntry();} break;
			case NM_STATE_LEAVE:
	  			if(OnStateLeave != NULL){ OnStateLeave();} break;
		}
    }
	msg->message = NM_NULL;
}

//==============================================================================