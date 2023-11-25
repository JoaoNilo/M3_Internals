//============================================================================//
// Title: EDROS: System parameters interface class						  	  //
// Version: 1.0.0                                                             //
// Author: edros.master@pobox.com											  //
// Date: 30/07/2014                                                           //
// Last Update: 22/02/2020                                                    //
// Compiler: Keil MDK-ARM Cortex-M0++ for ST V5.28.0.0                     	  //
//============================================================================//
#ifndef NPARAMETER_H
    #define NPARAMETER_H
    #include "Property.h"
    #include "GenericTypeDefs.h"
namespace nparameter_space{

    //-----------------------------------
    class NParameter{

        private:
            static const uint8_t __STANDARD_PARAMETER = 0x01;
            uint8_t type;
            uint8_t GetType();
            
        public:
            //-------------------------------------------
            // METHODS
            NParameter(uint8_t);
            NParameter();
            ~NParameter();

            //-------------------------------------------
            // PROPERTIES									<DEFAULT VALUES>
            HANDLE  Handle;                                     // ?
            uint32_t Id;                                        // 0x01
            uint32_t Tag;                                       // 0
            property<NParameter, uint8_t, propRead> Type;      // 0.0
    };
};
    using namespace nparameter_space;
#endif
//==============================================================================
