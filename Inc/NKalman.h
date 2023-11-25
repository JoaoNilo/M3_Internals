//============================================================================//
// Title: Kalman Filter (SiSo)                       			              //
// Version: 1.0.0                                                             //
// Author: edros.master@pobox.com							  				  //
// Date: 15/04/2020                                                           //
// Last Update: 15/04/2020                                                    //
// Compiler: Keil MDK-ARM Cortex-M0++ for ST V5.28.0.0                     	  //
//============================================================================//
#ifndef NKALMANH
    #define NKALMANH
    #include "stdint.h"
	#include "Property.h"
    
namespace nkalman_space{

    //-------------------------------------------
    // defini��o da classe NKalman
    class NKalman{

        private:

            //-----------------------------------
            // campos privados
            float error;                    // processs dependent
            float gain;
            float estimate;
            float uncertainty;

            //-----------------------------------
            // m�todos privados
            void Gain();                    // 1 - recalcula o ganho
            void Estimate(float);           // 2 - recalcula o valor estimado
            void Error();                   // 3 - recalcula o erro
        
            float GetValue();

        public:
            //-----------------------------------
            // m�todos p�blicos da classe NKalman
            NKalman(void);
            NKalman(float, float, float);
            ~NKalman(void);
            void Initialize(float, float);
			float Filter(float);
			
            //--------------------------------------
            // PROPRIEDADES do componente NKalman            		< DEFAULT VALUES >
            //--------------------------------------
            property<NKalman, float, propRead> Value;               // 0
        

    };
    //-------------------------------------------
}
    using namespace nkalman_space;

#endif
//==============================================================================

