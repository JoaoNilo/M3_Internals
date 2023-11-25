//============================================================================//
// Title: FIR Filter                      			                          //
// Author: edros.master@pobox.com                                             //
//----------------------------------------------------------------------------//
// Copyright (c) 2020 EDROS TEAM                                              //
//                     All rights reserved.                                   //
// This software component is licensed by "EDROS TEAM" under BSD 3-Clause li- //
// cense, the "License"; You may not use this file except in compliance with  //
// the License. You may obtain a copy of the License at:                      //
//               opensource.org/licenses/BSD-3-Clause                         //
//============================================================================//
#include "NFirFilter.h"

//------------------------------------------------------------------------------
// redimensiona o comprimento do filtro da classe NFirFilter
void NFirFilter::Resize(){
    filter_last = filter_size-1;
    filter_first = __DEFAULT_FIRST;
    filter_index = filter_first;
    samples = new float[filter_size];
    coeficients = new float[filter_size];
    float cf = 1.0/filter_size;
    for(int i=0; i< filter_size; i++){ coeficients[i]= cf;}
}

//------------------------------------------------------------------------------
// contrutora "default" da classe NFirFilter
NFirFilter::NFirFilter(void){
    filter_size = __DEFAULT_SIZE;

    // tratamento da propriedade Value
    Value.setOwner(this);
    Value.get(&NFirFilter::Filter);

    Resize();
    for(uint16_t c=0; c < filter_size; c++){  samples[c] = 0.0;}
    last_filtered = 0.0;
    ScalingFactor = 1.0;
}

//------------------------------------------------------------------------------
// contrutora da classe NFirFilter "dimensionável"
NFirFilter::NFirFilter(uint8_t filterSize){
    filter_size = filterSize;

    // tratamento da propriedade Value
    Value.setOwner(this);
    Value.get(&NFirFilter::Filter);

    Resize();
    for(uint16_t c=0; c < filter_size; c++){  samples[c] = 0.0;}
    last_filtered = 0.0;
    ScalingFactor = 1.0;
}

//------------------------------------------------------------------------------
// contrutora da classe NFirFilter "dimensionável" e "inicializável"
NFirFilter::NFirFilter(uint8_t filterSize, uint16_t initialValue){
    filter_size = filterSize;

    // tratamento da propriedade Value
    Value.setOwner(this);
    Value.get(&NFirFilter::Filter);

    Resize();
    for(uint16_t c=0; c < filter_size; c++){  samples[c] = initialValue;}
    last_filtered = initialValue;
    ScalingFactor = 1.0;
}

//------------------------------------------------------------------------------
// contrutora da classe NFirFilter "dimensionável" e "inicializável"
NFirFilter::NFirFilter(uint8_t FilterSize, uint16_t initialValue, float* ext_coefs){
    filter_size = FilterSize;

    // tratamento da propriedade Value
    Value.setOwner(this);
    Value.get(&NFirFilter::Filter);

    Resize();
    for(uint16_t c=0; c < filter_size; c++){
      samples[c] = initialValue; 
      if(ext_coefs != NULL){ coeficients[c] = ext_coefs[c];}
    }
    last_filtered = initialValue;
    ScalingFactor = 1.0;
}

//------------------------------------------------------------------------------
// destrutora da classe NFirFilter
NFirFilter::~NFirFilter(void){
    Flush();
}

//------------------------------------------------------------------------------
// limpa a "linha de atraso"
void NFirFilter::Flush(){
    for(uint16_t i=0; i<filter_size; i++) samples[i] = 0x0000;
    last_filtered = 0;
}

//------------------------------------------------------------------------------
// preenche o filtro com um valor arbitrário "value"
void NFirFilter::Fill(float value){
    for(uint16_t i=0; i<filter_size; i++){ samples[i] = value;}
    last_filtered = value;
}

//------------------------------------------------------------------------------
// preenche a matriz de coeficientes do filtro
void NFirFilter::LoadCoeficients(float* ext_coefs){
    for(uint16_t c=0; c < filter_size; c++){ coeficients[c] = ext_coefs[c];}
}

//------------------------------------------------------------------------------
// retorna a nova amostra "filtrada" (requer uma nova amostra "não filtrada")
float NFirFilter::Filter(float new_sample){
    last_filtered = 0.0;

    samples[filter_index] = new_sample;
    for(uint16_t i = 0; i < filter_size; i++){
        last_filtered += (coeficients[filter_index]*samples[filter_index]);
        if(++filter_index > filter_last){ filter_index = filter_first;}
    }
    if(++filter_index>filter_last){ filter_index = filter_first;}
    return(last_filtered);
}

//------------------------------------------------------------------------------
// retorna a nova amostra "filtrada" (requer uma nova amostra "não filtrada")
template<typename T>
T NFirFilter::NewFilter(T sample){
    T result = sample * 2;
    return(result);
}

//------------------------------------------------------------------------------
// retorna a última amostra "filtrada"
float NFirFilter::Filter(){  return(last_filtered);}

//==============================================================================
