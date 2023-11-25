//============================================================================//
// Title: EDROS: NCounter - General purpose counter        	  				  //
// Version: 1.0.0                                                             //
// Author: edros.master@pobox.com											  //
// Date: 09/09/2015                                                           //
// Last Update: 14/03/2020                                                    //
// Compiler: Keil MDK-ARM Cortex-M0++ for ST V5.28.0.0                     	  //
//----------------------------------------------------------------------------//
// Development Notes:                                                         //
//============================================================================//
#include "NCounter.h"
//------------------------------------------------------------------------------
// construtora
NCounter::NCounter(){

    OnMinimum = NULL; OnMaximum = NULL;
	OnUpper = NULL; OnLower = NULL;

    // tratamento da propriedade Enabled
    Enabled.setOwner(this);
    Enabled.set(&NCounter::SetEnabled);
    Enabled.get(&NCounter::GetEnabled);

    // tratamento da propriedade Counter
    Count.setOwner(this);
    Count.get(&NCounter::GetCount);

    // tratamento da propriedade Mode
    Mode.setOwner(this);
    Mode.set(&NCounter::SetMode);
    Mode.get(&NCounter::GetMode);

    // tratamento da propriedade Minimum
    Minimum.setOwner(this);
    Minimum.set(&NCounter::SetMinimum);
    Minimum.get(&NCounter::GetMinimum);

    // tratamento da propriedade Lower
    Lower.setOwner(this);
    Lower.set(&NCounter::SetLower);
    Lower.get(&NCounter::GetLower);

    // tratamento da propriedade Upper
    Upper.setOwner(this);
    Upper.set(&NCounter::SetUpper);
    Upper.get(&NCounter::GetUpper);

    // tratamento da propriedade Maximum
    Maximum.setOwner(this);
    Maximum.set(&NCounter::SetMaximum);
    Maximum.get(&NCounter::GetMaximum);

    //---------------------------
    // configuração "default" das propriedades
    enabled = false;
    mode = cnUp;
    minimum = NCOUNTER_MIN;
	maximum = NCOUNTER_MAX;
	upper = NCOUNTER_UPPER;
	lower = NCOUNTER_LOWER;
	Tag = 0;
	
    //---------------------------
    // inicializa as variáveis
    Reset(); //counter = 0;
}

//------------------------------------------------------------------------------
// destrutora
NCounter::~NCounter(){}

//------------------------------------------------------------------------------
// restaura os valores iniciais
void NCounter::Reset(){ counter = 0; CheckBounds(); CheckThresholds();}

//------------------------------------------------------------------------------
// checa se o contador está entre o máximo e o mínimo
void NCounter::CheckBounds(){
	if(enabled){
		if(counter>= maximum){
			counter = maximum; if(OnMaximum != NULL){ OnMaximum();}
		} else if (counter <= minimum){
			counter = minimum; if(OnMinimum != NULL){ OnMinimum();}
		}
	}
}

//------------------------------------------------------------------------------
// checa se o contador está entre os limiares superior
void NCounter::CheckThresholds(){
	if(enabled){
		if(counter>= upper){ if(OnUpper != NULL){ OnUpper();}
		} else if (counter <= lower){ if(OnLower != NULL){ OnLower();}}
	}
}

//------------------------------------------------------------------------------
// atribui nova condição
void NCounter::SetEnabled(bool tE){
	enabled = tE;
	CheckBounds();
	CheckThresholds();
}

//------------------------------------------------------------------------------
// retorna estado operacional
bool NCounter::GetEnabled(){ return(enabled);};

//------------------------------------------------------------------------------
// retorna estado da contagem
unsigned int NCounter::GetCount(){ return(counter);};

//------------------------------------------------------------------------------
// atribui novo modo de operação
void NCounter::SetMode(cnMode cM){ mode = cM;}

//------------------------------------------------------------------------------
// devolve modo de operação em uso
cnMode NCounter::GetMode(){ return(mode);};

//------------------------------------------------------------------------------
// atribui novo valor de máximo
void NCounter::SetMaximum(unsigned int max){
	if(max < counter){ 
		counter = maximum = max;
		if(OnMaximum != NULL){ OnMaximum();}
	} else { maximum = max;}
}

//------------------------------------------------------------------------------
// retorna o valor atual do mínimo
unsigned int NCounter::GetMaximum(){ return(maximum);}

//------------------------------------------------------------------------------
// atribui novo valor de limite superior
void NCounter::SetUpper(unsigned int up){
	upper = up;
	if(upper <= counter){ if(OnUpper != NULL){ OnUpper();}}
}

//------------------------------------------------------------------------------
// retorna o valor atual do limite superior
unsigned int NCounter::GetUpper(){ return(upper);}

//------------------------------------------------------------------------------
// atribui novo valor de limite inferior
void NCounter::SetLower(unsigned int lo){
	lower = lo;
	if(lower >= counter){ if(OnLower != NULL){ OnLower();}}
}

//------------------------------------------------------------------------------
// retorna o valor atual do limite inferior
unsigned int NCounter::GetLower(){ return(upper);}

//------------------------------------------------------------------------------
// atribui novo valor de mínimo
void NCounter::SetMinimum(unsigned int min){
	if(min > counter){ 
		counter = minimum = min;
		if(OnMinimum != NULL){ OnMinimum();}
	} else { minimum = min;}
}

//------------------------------------------------------------------------------
// retorna o valor atual do mínimo
unsigned int NCounter::GetMinimum(){ return(minimum);};

//------------------------------------------------------------------------------
// incrementa o contador 
unsigned int NCounter::Increment(){
	if(enabled){ counter++; CheckBounds(); CheckThresholds();}
	return(counter);
}

//------------------------------------------------------------------------------
// decrementa o contador
unsigned int NCounter::Decrement(){
	if(enabled){ if(counter>0){ counter--;}; CheckBounds(); CheckThresholds();}
	return(counter);
}

//==============================================================================
