//============================================================================//
// Title: Kalman Filter (SiSo)                       			              //
// Version: 1.0.0                                                             //
// Author: edros.master@pobox.com							  				  //
// Date: 15/04/2020                                                           //
// Last Update: 15/04/2020                                                    //
// Compiler: Keil MDK-ARM Cortex-M0++ for ST V5.28.0.0                     	  //
//============================================================================//
// Development History: 												      //
//		15/04/2020 - Version 1.0.0							  				  //
//============================================================================//
#include "NKalman.h"

//------------------------------------------------------------------------------
// recalcula o ganho
void NKalman::Gain(){
    gain = uncertainty/(uncertainty + error);
}

//------------------------------------------------------------------------------
// recalcula o valor estimado
void NKalman::Estimate(float new_measurement){
    estimate = estimate + gain * (new_measurement - estimate);
}

//------------------------------------------------------------------------------
// recalcula o erro estimado
void NKalman::Error(){
    uncertainty = (1- gain) * uncertainty;
}

//------------------------------------------------------------------------------
// inicializa os parâmetros da classe NKalman
void NKalman::Initialize(float initial_estimate, float initial_uncertainty){
    uncertainty = initial_uncertainty;
    estimate = initial_estimate;
}

//------------------------------------------------------------------------------
// contrutora "default" da classe NKalman
NKalman::NKalman(void){
    error = 1;
    uncertainty = error;
    estimate = 0;
}

//------------------------------------------------------------------------------
// contrutora parametrizada da classe NKalman
NKalman::NKalman(float initial_estimate, float initial_uncertainty, float sensor_error){
    Value.setOwner(this);
    Value.get(&NKalman::GetValue);

    error = sensor_error;
    uncertainty = initial_uncertainty;
    estimate = initial_estimate;
}

//------------------------------------------------------------------------------
float NKalman::GetValue(){ return(estimate);}

//------------------------------------------------------------------------------
// destrutora da classe NKalman
NKalman::~NKalman(void){}

//------------------------------------------------------------------------------
// retorna um novo valor  "estimado" (requer uma nova amostra "não filtrada")
float NKalman::Filter(float new_sample){
    Gain(); 
    Estimate(new_sample); 
    Error();
    return(estimate);
}

//==============================================================================
