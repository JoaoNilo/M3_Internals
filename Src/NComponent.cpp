//==============================================================================
/**
 * @file NComponent.cpp
 * @title: EDROS: System components interface class
 * @version: 1.0.0
 * @author: J. Nilo Rodrigues - nilo@pobox.com
 * @date: 19/10/2019
 * @brief: Base class for EDROS "components"
 *
 * @note: This is an interface class so its not supposed to be instantiated.
 *
 */
//==============================================================================
#include "NComponent.h"

//------------------------------------------------------------------------------
NComponent::NComponent(){
    Handle = (HANDLE)this;
	Tag = 0;
	Priority = nRelaxed;
	SSR_IncludeComponent((uint32_t)Handle);
}

//------------------------------------------------------------------------------
NComponent::~NComponent(){
	SSR_ExcludeComponent((uint32_t)Handle);
}

//------------------------------------------------------------------------------
void NComponent::Notify(NMESSAGE* pmsg){}

//------------------------------------------------------------------------------
void NComponent::InterruptCallBack(NMESSAGE* msg){}

//==============================================================================
