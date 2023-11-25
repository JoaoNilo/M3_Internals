//============================================================================//
// Title: EDROS: System parameters interface class						  	  //
// Version: 1.0.0                                                             //
// Author: edros.master@pobox.com											  //
// Date: 30/07/2014                                                           //
// Last Update: 22/02/2020                                                    //
// Compiler: Keil MDK-ARM Cortex-M0++ for ST V5.28.0.0                     	  //
//----------------------------------------------------------------------------//
// Development Notes:														  //
//============================================================================//
#include "NParameter.h"

//------------------------------------------------------------------------------
NParameter::NParameter(uint8_t t){
    Handle = (HANDLE)this; type = t; Tag = Id = 0;
    
    Type.setOwner(this);
    Type.get(&NParameter::GetType);
}

//------------------------------------------------------------------------------
NParameter::NParameter(){ NParameter(__STANDARD_PARAMETER);}

//------------------------------------------------------------------------------
NParameter::~NParameter(){}

//------------------------------------------------------------------------------
uint8_t NParameter::GetType(){ return type;}

//==============================================================================
