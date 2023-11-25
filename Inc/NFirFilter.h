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
#ifndef NFIRFILTERH
    #define NFIRFILTERH
    #include "stdint.h"
	#include "property.h"

//------------------------------------------------------------------------------
namespace nfirfilter_space{

    //-------------------------------------------
    // definição da classe NFirFilter
    class NFirFilter{

        private:
            // constantes utilizadas
            static const uint16_t __DEFAULT_SIZE = 4;
            static const uint16_t __DEFAULT_FIRST = 0;
            
            //-----------------------------------
            // campos privados
            uint16_t filter_size;               // default 4
            uint16_t filter_first;              // default 0
            uint16_t filter_last;               // filter_size-1
            uint16_t filter_index;              // default 0

            float* samples;                     // samples[filter_size];
            float* coeficients;                 // coeficients[filter_size];
            float last_filtered;             // última amostra filtrada

            
            //-----------------------------------
            // métodos privados
            void Resize();

        public:

            //-----------------------------------
            // métodos públicos da classe NFirFilter
            NFirFilter(void);
            NFirFilter(uint8_t);
            NFirFilter(uint8_t, uint16_t);
            NFirFilter(uint8_t, uint16_t, float*);

            ~NFirFilter(void);
            float Filter(float);
            float Filter();
            template<typename T>
            T NewFilter(T);
            
            void Flush();
			void Fill(float);
            void LoadCoeficients(float*);
            
            //-----------------------------------
			
            //--------------------------------------
            // PROPRIEDADES do componente NFirFilter    	< DEFAULT VALUES >
            property<NFirFilter, float, propRead> Value;    // 0
            float ScalingFactor;

    };
    //-------------------------------------------
}
    using namespace nfirfilter_space;

#endif
//==============================================================================

