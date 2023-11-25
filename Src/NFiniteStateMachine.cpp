//============================================================================//
// Title: Componente Máquina de Estados Finita           					  //
// Version: 0.0.1                                                             //
// Author: J. Nilo Rodrigues    I.F.: 9530                                    //
// Date: 27/01/2015                                                           //
// Last Update: 27/01/2015                                                    //
// P/N: xx.xxx.xxx.xx   Rev.: -       Code: xxx.xxx-x    AT: ----/--          //
// Compiler: IAR EWARM V6.40                                                  //
//----------------------------------------------------------------------------//
// 27/01/2015: iniciado o desenvolvimentoo. (v0.0.1)			              //
//============================================================================//
#include "NFiniteStateMachine.h"

//------------------------------------------------------------------------------
NFiniteStateMachine::NFiniteStateMachine():NComponent(){
  	OnStateChange = NULL;
	listStates = NULL;
	tmpState = NULL;
	listItems = 0;
	Forward = true;
	enabled = true;
	manual = false;
	scheduled = false;
	index = -1;
	turns = 0; 
	interval = TIMEBASE_MINIMUM;
	
    //------------------------------------
    // tratamento da propriedade Enabled
    Enabled.setContainer(this);
    Enabled.setter(&NFiniteStateMachine::SetEnabled);
    Enabled.getter(&NFiniteStateMachine::GetEnabled);

    //------------------------------------
    // tratamento da propriedade Manual
    Manual.setContainer(this);
    Manual.setter(&NFiniteStateMachine::SetManual);
    Manual.getter(&NFiniteStateMachine::GetManual);

    //------------------------------------
    // tratamento da propriedade State
    State.setContainer(this);
    State.setter(&NFiniteStateMachine::SetState);
    State.getter(&NFiniteStateMachine::GetState);
	
    //------------------------------------
	// prepara o timer de controle dos estados
	interval_enabled = enabled;
	interval_counter = interval;
}

//------------------------------------------------------------------------------
NFiniteStateMachine::~NFiniteStateMachine(){}

//------------------------------------------------------------------------------
// atribui nova condição à propriedade Enabled
void NFiniteStateMachine::SetEnabled(bool newEnabled){
	 enabled = newEnabled; if(!manual){ interval_enabled = enabled;}
}

//------------------------------------------------------------------------------
// retorna a condição atual da propriedade Enabled
bool NFiniteStateMachine::GetEnabled(){ return(enabled);}

//------------------------------------------------------------------------------
// atribui nova condição à propriedade Manual
void NFiniteStateMachine::SetManual(bool newManual){
	 manual = newManual; interval_enabled = !manual;
}

//------------------------------------------------------------------------------
// retorna a condição atual da propriedade Manual
bool NFiniteStateMachine::GetManual(){ return(manual);}

//------------------------------------------------------------------------------
// atribui (impõe) novo estado
void NFiniteStateMachine::SetState(NFiniteState* newState){
	if(newState != NULL){
  		nxtState = FindState(newState->Index);
		if(nxtState != NULL){ scheduled = true;}
	}
}

//------------------------------------------------------------------------------
// retorna o estado atual
 NFiniteState* NFiniteStateMachine::GetState(){ return(tmpState);}

//------------------------------------------------------------------------------
// comanda a mudança manual de estado
bool NFiniteStateMachine::ChangeState(){
	bool result = false;
	if(enabled){ 
		if(manual){ TimeBase_Elapsed();} result = true;
	}
	return(result);
}

//------------------------------------------------------------------------------
// registra um novo estado na máquina
unsigned int NFiniteStateMachine::IncludeState(NFiniteState* newState){
  	newState->Index = listItems;
  
    int tmpSize = listItems * sizeof(HANDLE);
	// aumenta uma posição na lista de handlers de estados
  	HANDLE* tmpStates = new HANDLE[listItems+1];
	// reposiciona os handlers da lista "antiga"
    if(tmpSize>0){ memcpy((uint8_t*)tmpStates, (uint8_t*)listStates, tmpSize);}
    // acrescenta o novo estado à lista
	tmpStates[listItems++] = (HANDLE)newState;
	// libera a memória da lista antiga
    delete[] listStates;
	// reposiciona na nova lista
    listStates = tmpStates;
	return(listItems);
}

//------------------------------------------------------------------------------
// limpa todos os estados da máquina
void NFiniteStateMachine::FlushStates(){
	// zera contado de estados  
    listItems = 0;
	// libera a memória dos estados
    delete[] listStates;
}

//------------------------------------------------------------------------------
// encontra estado assíncrono "pendente"
NFiniteState* NFiniteStateMachine::FindStatePending(){
	NFiniteState* result = NULL; int items = listItems;
	for(int i=0; i < items; i++){
		result = (NFiniteState*)listStates[i];
		if(result->Pending){ break;} else { result = NULL;}
	}
	return(result);
}

//------------------------------------------------------------------------------
// encontra estado pelo índice
NFiniteState* NFiniteStateMachine::FindState(int stateIndex){
	NFiniteState* result = NULL; int items = listItems;
	for(int i=0; i < items; i++){
		result = (NFiniteState*)listStates[i];
		if(result->Index == stateIndex){ break;} else { result = NULL;}
	}
	return(result);
}

//------------------------------------------------------------------------------
// trata a mudança de estado
bool NFiniteStateMachine::SwitchState(){
	bool result = false;
	
	if(listItems>0){
	  	// busca o índice do próximo estado
		NextIndex();
	  	// checa se deve notificar a saída do estado
	  	if(tmpState != NULL){
			// notifica a saída do estado
			NMESSAGE msg; msg.message = NM_STATE_LEAVE;
			tmpState->Notify(&msg);
		}
		// anula o estado anterior
		tmpState = NULL;
		// procura pendências assíncronas
		tmpState = FindStatePending();
		
		if((tmpState != NULL)&&(tmpState->Enabled)){
			// checa se deve temporizar o estado
			if(manual){ interval_enabled = false;}
			// carrega as propriedades do estado
			interval_counter = tmpState->Interval;
			turns = tmpState->Turns;
			// atualiza propriedades do estado
			tmpState->Pending = false;
			// notifica a entrada no estado
			NMESSAGE msg; msg.message = NM_STATE_ENTRY;
			tmpState->Notify(&msg);
			// sinaliza a mudança de estado
			if(OnStateChange != NULL) { OnStateChange(tmpState);}
			// debita uma execução
			if(turns > 1){ turns--;}
			else {
				turns = 0; tmpState->Pending = false; tmpState->Enabled = false;
			}
			result = true;
		} else {
			// encontra o próximo estado válido
			tmpState = FindState(index);
			if((tmpState != NULL)&&(tmpState->Enabled)){
				// checa se deve temporizar o estado
				if(manual){ interval_enabled = false;}
				// carrega as propriedades do estado
				interval_counter = tmpState->Interval;
				turns = tmpState->Turns;
				// notifica sua execução
				NMESSAGE msg; msg.message = NM_STATE_ENTRY;
				tmpState->Notify(&msg);
				// sinaliza a mudança de estado
				if(OnStateChange != NULL) { OnStateChange(tmpState);}
				// debita uma execução
				if(turns > 0){ turns--;}
				result = true;
			} else {
				interval_counter = TIMEBASE_MINIMUM;
				if(manual){ interval_enabled = true;}
			}
		}
	}
	return(result);
}

//------------------------------------------------------------------------------
// trata a repetição do processamento do estado
void NFiniteStateMachine::RepeatState() {
  	NMESSAGE msg;
	
	// notifica a saída do estado
	msg.message = NM_STATE_LEAVE;
	tmpState->Notify(&msg);
	
	// notifica a reentrada no estado
	msg.message = NM_STATE_ENTRY;
	tmpState->Notify(&msg);
	
	// debita uma execução
	if(turns>0){ turns--;} 
	else {
		if(tmpState->Pending){
			tmpState->Pending = false; tmpState->Enabled = false;
		}
	}
}

//------------------------------------------------------------------------------
// encontra o próximo índice
void NFiniteStateMachine::NextIndex(){
	if(scheduled){ index = nxtState->Index; scheduled = false;}
	else {
		if(Forward){ if(++index >= listItems){ index = 0;}}
		else { if(index > 0){ index--;} else {index = listItems-1;}}
	}
}

//------------------------------------------------------------------------------
// trata a mudança de estado por tempo
void NFiniteStateMachine::TimeBase_Elapsed(){
	if(enabled){
		if(turns > 0){ RepeatState();}
		else {  SwitchState();}
	}
}

//------------------------------------------------------------------------------
// recebe notificação de "timetick" do sistema (1ms)
void NFiniteStateMachine::Notify(NMESSAGE* msg){
    if(enabled){
        switch(msg->message){
            case NM_TIMETICK:
			  	if(interval_enabled){
					if(interval_counter>0){ interval_counter--;}
				  	else {
						interval_counter = TIMEBASE_DEFAULT;
						TimeBase_Elapsed();
					}
				}
                msg->message = NM_NULL;
                break;
			case NM_ITEM_INCLUDED:
				IncludeState((NFiniteState*)msg->lparam);
				msg->message = NM_NULL;
		  		break;
            default: msg->message = NM_NULL; break;
		}
    } else { msg->message = NM_NULL;}
}

//==============================================================================