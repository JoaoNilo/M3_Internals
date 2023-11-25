//============================================================================//
// Title: EDROS: System analog parameters class						  	  	  //
// Version: 1.0.0                                                             //
// Author: edros.master@pobox.com											  //
// Date: 30/07/2014                                                           //
// Last Update: 22/02/2020                                                    //
// Compiler: Keil MDK-ARM Cortex-M0++ for ST V5.28.0.0                     	  //
//============================================================================//
#ifndef NANALOGPARAMETER_H
    #define NANALOGPARAMETER_H

    #include "NParameter.h"
    #include "GenericTypeDefs.h"

namespace nanalogparameter_space{

	static const uint8_t ANALOG_PARAMETER   = 0x01;
	
    //-----------------------------------
    class NAnalogParameter: private NParameter{

        private:
            float value;
            bool inRange;
            bool inLower;
            bool inUpper;

			void CheckLimits();
            
            float GetValue();
			void SetValue(float);
            bool GetInRange();
            bool GetInLower();
            bool GetInUpper();
            
        public:
            //-------------------------------------------
            // METHODS
            NAnalogParameter();
            ~NAnalogParameter();
            float UpdateValue(uint16_t);
            float UpdateValue(int16_t);
			uint32_t ValueToInt();
			bool Export(uint8_t*);
			bool Import(uint8_t*);

            //-------------------------------------------
            // EVENTS
            void (*OnLowerLimit)();
            void (*OnUpperLimit)();

            //-------------------------------------------
            // PROPERTIES											<DEFAULT VALUES>
            property<NAnalogParameter, float, propReadWrite> Value; // 0.0
            property<NAnalogParameter, bool, propRead> InRange;   	// false
            property<NAnalogParameter, bool, propRead> InLower;   	// false
            property<NAnalogParameter, bool, propRead> InUpper;   	// false
            int Offset;                                        		// 0
            float Scale;                                            // 0.0
			float Bias;                                             // 0.0
            float LowerLimit;                                       // 0.0
            float UpperLimit;                                       // 0.0
			using NParameter::Tag;									// 0
    };
};
    using namespace nanalogparameter_space;
#endif
//==============================================================================
