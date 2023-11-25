//============================================================================//
// Title: EDROS: Properties template class						  	  		  //
// Version: 1.0.0                                                             //
// Author: edros.master@pobox.com											  //
// Date: 19/10/2019                                                           //
// Last Update: 04/04/2020                                                    //
// Compiler: Keil MDK-ARM Cortex-M0++ for ST V5.28.0.0                     	  //
//----------------------------------------------------------------------------//
// Development Notes:                                                         //
//============================================================================//
#define NULL            0L
#include <assert.h>
enum propAccess { propRead=1, propWrite=2, propReadWrite=3};

//------------------------------------------------------------------------------
template<typename Owner, typename PropType, propAccess PropAccess>

class property{
    public:
        property(){
            ParentObject = NULL;
            Setter = NULL;
            Getter = NULL;
        }
        
        void setOwner(Owner* cObject){
            ParentObject = cObject;
        }
        
        void set(void(Owner::*SetterAddr)(PropType value)){
            if((PropAccess == propWrite) || (PropAccess == propReadWrite))
                Setter = SetterAddr;
            else 
                Setter = NULL;
        }

        void get(PropType (Owner::*GetterAddr)()){
            if((PropAccess == propRead)||(PropAccess == propReadWrite))
                Getter = GetterAddr;
            else 
                Getter = NULL;
        }

        PropType operator = (const PropType& value){
            assert(ParentObject !=NULL);
            assert(Setter != NULL);
            (ParentObject->*Setter)(value);
            return value;
        }
        
        operator PropType(){
            assert(ParentObject != NULL);
            assert(Getter != NULL);
            return(ParentObject->Getter)();
        }

    private:
        Owner* ParentObject;
        void (Owner::*Setter)(PropType value);
        PropType (Owner::*Getter)();
};

//==============================================================================
