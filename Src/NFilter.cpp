//============================================================================//
// Title: EDROS: General purpose moving average filter (M.A. Filter)		  //
// Version: 1.0.0                                                             //
// Author: edros.master@pobox.com											  //
// Date: 28/02/2012                                                           //
// Last Update: 23/02/2020                                                    //
// Compiler: Keil MDK-ARM Cortex-M0++ for ST V5.28.0.0                     	  //
//----------------------------------------------------------------------------//
// Development Notes: 												          //
//============================================================================//
#include "NFilter.h"

//------------------------------------------------------------------------------
void NFilter::Resize(uint32_t size){
	filter_size = size;
    filter_last = filter_size-1;
    filter_first = 0;
    filter_index = filter_first;
	//if(samples != NULL){ delete[] samples;}
    samples = new unsigned short[filter_size];
}

//------------------------------------------------------------------------------
NFilter::NFilter(void){
    //filter_size = __DEFAULT_SIZE;
	
    Value.setOwner(this);
    Value.get(&NFilter::Filter);

    Resize(__DEFAULT_SIZE);
    Flush();
}

//------------------------------------------------------------------------------
NFilter::NFilter(uint8_t filterSize){
    //filter_size = filterSize;

    Value.setOwner(this);
    Value.get(&NFilter::Filter);

    Resize(filterSize);
    Flush();
}

//------------------------------------------------------------------------------
NFilter::NFilter(uint8_t filterSize, uint16_t initialValue){
    //filter_size = filterSize;

    Value.setOwner(this);
    Value.get(&NFilter::Filter);

    Resize(filterSize);
    for(uint16_t c=0; c<filter_size; c++){ samples[c] = initialValue;}
    last_filtered = initialValue;
}

//------------------------------------------------------------------------------
NFilter::~NFilter(void){
    Flush();
}

//------------------------------------------------------------------------------
void NFilter::Flush(){
    for(unsigned short i=0; i<filter_size; i++) samples[i] = 0x0000;
    last_filtered = 0;
}

//------------------------------------------------------------------------------
void NFilter::Fill(uint16_t value){
    for(unsigned short i=0; i<filter_size; i++) samples[i] = value;
    last_filtered = value;
}

//------------------------------------------------------------------------------
unsigned int NFilter::Filter(unsigned int new_sample){
    unsigned int result=0;

    samples[filter_index]=new_sample;
    for(unsigned short i=0L; i<filter_size; i++){
        result += samples[filter_index++];
        if(filter_index>filter_last) filter_index = filter_first;
    }
    if(++filter_index>filter_last) filter_index = filter_first;
    result /= filter_size; last_filtered = result;
    return(result);
}

//------------------------------------------------------------------------------
/*int16_t NFilter::Filter(int16_t new_sample){
    int16_t result=0;

    samples[filter_index] = (uint16_t)new_sample;
    for(unsigned short i=0L; i<filter_size; i++){
        result += (int16_t)samples[filter_index++];
		if(filter_index>filter_last){ filter_index = filter_first;}
    }
	if(++filter_index>filter_last){ filter_index = filter_first;}
    result /= filter_size; last_filtered = (unsigned int)result;
    return(result);
}*/

//------------------------------------------------------------------------------
unsigned int NFilter::Filter(unsigned short* new_samples, unsigned int new_size){
    unsigned int result=0;

	for( unsigned int c=0; c< new_size; c++){
    	result = Filter((unsigned)*new_samples);
		new_samples++;
	}
	last_filtered = result;
    return(result);
}

//------------------------------------------------------------------------------
unsigned int NFilter::Filter(unsigned short* new_samples, unsigned int whole_size, 
							 unsigned int new_step){
    unsigned int result=0;

	for( unsigned int c=0; c< whole_size; c+=new_step){
    	result = Filter((unsigned)*new_samples);
		new_samples+=new_step;
	}
	last_filtered = result;	
    return(result);
}

//------------------------------------------------------------------------------
unsigned int NFilter::Filter(){  return(last_filtered);}

//==============================================================================
