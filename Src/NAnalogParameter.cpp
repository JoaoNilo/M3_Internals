//============================================================================//
// Title: EDROS: System analog parameters class						  	  	  //
// Version: 1.0.0                                                             //
// Author: edros.master@pobox.com											  //
// Date: 30/07/2014                                                           //
// Last Update: 22/02/2020                                                    //
// Compiler: Keil MDK-ARM Cortex-M0++ for ST V5.28.0.0                     	  //
//----------------------------------------------------------------------------//
// Development Notes: 													  	  //
//============================================================================//
#include "NAnalogParameter.h"

//------------------------------------------------------------------------------
NAnalogParameter::NAnalogParameter():NParameter(ANALOG_PARAMETER){
    Handle = (HANDLE)this; OnLowerLimit = NULL; OnUpperLimit = NULL;
    value = Scale = LowerLimit = UpperLimit = Bias = 0.0; Offset = 0;
    inRange = false; inLower = false; inUpper = false;
    
    Value.setOwner(this);
    Value.get(&NAnalogParameter::GetValue);
	Value.set(&NAnalogParameter::SetValue);
    InRange.setOwner(this);
    InRange.get(&NAnalogParameter::GetInRange);
    InLower.setOwner(this);
    InLower.get(&NAnalogParameter::GetInLower);
    InUpper.setOwner(this);
    InUpper.get(&NAnalogParameter::GetInUpper);
}

//------------------------------------------------------------------------------
NAnalogParameter::~NAnalogParameter(){}

//------------------------------------------------------------------------------
void NAnalogParameter::CheckLimits(){
    if(value<LowerLimit){
       inLower = true; inRange = false; inUpper = false;
       if(OnLowerLimit!=NULL){ OnLowerLimit();}
    } else if(value>UpperLimit){
        inLower = false; inRange = false; inUpper = true;
        if(OnUpperLimit!=NULL){ OnUpperLimit();}
    } else {
        inLower = false; inRange = true; inUpper = false;
    }
}

//------------------------------------------------------------------------------
void NAnalogParameter::SetValue(float new_value){
	value = new_value;
	CheckLimits();
}

//------------------------------------------------------------------------------
float NAnalogParameter::GetValue(){ return(value);}

//------------------------------------------------------------------------------
bool NAnalogParameter::GetInRange(){ return(inRange);}

//------------------------------------------------------------------------------
bool NAnalogParameter::GetInLower(){ return(inLower);}

//------------------------------------------------------------------------------
bool NAnalogParameter::GetInUpper(){ return(inUpper);}

//------------------------------------------------------------------------------
float NAnalogParameter::UpdateValue(uint16_t v){
    value = (float)((int)v + Offset) * Scale + Bias;
	CheckLimits();
    return(value);
}

//------------------------------------------------------------------------------
float NAnalogParameter::UpdateValue(int16_t v){
    value = (float)((int)v + Offset) * Scale + Bias;
	CheckLimits();
    return(value);
}

//------------------------------------------------------------------------------
uint32_t NAnalogParameter::ValueToInt(){ return(*(uint32_t*)&value);}

//------------------------------------------------------------------------------
bool NAnalogParameter::Export(uint8_t* ext_dat){
	if(ext_dat == NULL){ return(false);}
	*(uint32_t*)ext_dat = *(uint32_t*)&value;	ext_dat += sizeof(value);
	*(uint32_t*)ext_dat = *(uint32_t*)&Offset; ext_dat += sizeof(Offset);
	*(uint32_t*)ext_dat = *(uint32_t*)&Scale; ext_dat += sizeof(Scale);
	*(uint32_t*)ext_dat = *(uint32_t*)&Bias; ext_dat += sizeof(Bias);
	return(true);
}

//------------------------------------------------------------------------------
bool NAnalogParameter::Import(uint8_t* ext_dat){
	if(ext_dat == NULL){ return(false);}
	*(uint32_t*)&value = *(uint32_t*)ext_dat;	ext_dat += sizeof(value);
	*(uint32_t*)&Offset = *(uint32_t*)ext_dat; ext_dat += sizeof(Offset);
	*(uint32_t*)&Scale = *(uint32_t*)ext_dat; ext_dat += sizeof(Scale);
	*(uint32_t*)&Bias = *(uint32_t*)ext_dat; ext_dat += sizeof(Bias);
	return(true);
}

//==============================================================================
