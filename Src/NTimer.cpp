//============================================================================//
// Title: EDROS: Software timer component						  	  		  //
// Version: 1.0.0                                                             //
// Author: edros.master@pobox.com											  //
// Date: 01/10/2012                                                           //
// Last Update: 20/02/2020                                                    //
// Compiler: Keil MDK-ARM Cortex-M0++ for ST V5.28.0.0                     	  //
//----------------------------------------------------------------------------//
// Development Notes:                                                         //
//============================================================================//

#include "NTimer.h"
//------------------------------------------------------------------------------
NTimer::NTimer(){

    OnTimer = NULL;

    Mode.setOwner(this);
    Mode.set(&NTimer::SetMode);
    Mode.get(&NTimer::GetMode);

    Interval.setOwner(this);
    Interval.set(&NTimer::SetInterval);
    Interval.get(&NTimer::GetInterval);

    Done.setOwner(this);
    Done.get(&NTimer::GetDone);

    Enabled.setOwner(this);
    Enabled.set(&NTimer::SetEnabled);
    Enabled.get(&NTimer::GetEnabled);

    //---------------------------
    interval = __NTIMER_TIMEOUT_DEFAULT;
    enabled = false;
    mode = tmContinuous;

    //---------------------------
    timeout_counter = 0;
    iDone = done = false;
}

//------------------------------------------------------------------------------
NTimer::~NTimer(){}

//------------------------------------------------------------------------------
void NTimer::SetEnabled(bool tE){
    if(tE) Start(interval);
    else Stop();
}

//------------------------------------------------------------------------------
bool NTimer::GetEnabled(){return(enabled);};

//------------------------------------------------------------------------------
bool NTimer::GetDone(){return(iDone);};

//------------------------------------------------------------------------------
void NTimer::SetMode(tmModes tM){ mode = tM;}

//------------------------------------------------------------------------------
tmModes NTimer::GetMode(){return(mode);};

//------------------------------------------------------------------------------
void NTimer::SetInterval(uint32_t tI){
    if(tI==0) tI = 1;
    if(tI>__NTIMER_TIMEOUT_MAX){ tI = __NTIMER_TIMEOUT_MAX;}
    interval = tI;
};

//------------------------------------------------------------------------------
uint32_t NTimer::GetInterval(){return(interval);};

//------------------------------------------------------------------------------
void NTimer::Start(uint32_t T){
    SetInterval(T);
    timeout_counter = 0;
    enabled = true;
    iDone = done = false;
}

//------------------------------------------------------------------------------
void NTimer::Stop(){
    enabled = false;
    iDone = done = false;
}

//------------------------------------------------------------------------------
void NTimer::Notify(NMESSAGE* tmsg){

    if(enabled){
        switch(tmsg->message){
            case NM_TIMETICK:
                tmsg->message = NM_NULL;
                if(!done){
                    if(++timeout_counter >= interval){
                        timeout_counter = 0; done = true;
                        if(OnTimer != NULL){ OnTimer();}
                        if(mode == tmContinuous) done = false;
                    }
                }
                break;

            default: tmsg->message = NM_NULL; break;
        }
        iDone = done;
    } else tmsg->message = NM_NULL;
}

//==============================================================================
