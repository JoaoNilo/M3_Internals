//==============================================================================
#ifndef PROPERTY_H
    #define PROPERTY_H

    #ifndef NULL
        #define NULL        0
    #endif

    enum propAccess { propRead=1, propWrite=2, propReadWrite=3};
    
//------------------------------------------------------------------------------
template<typename Owner, typename PropType, propAccess PropAccess> class property{
    
    private:
        Owner* ParentObject;
        void (Owner::*Setter)(PropType value);
        PropType (Owner::*Getter)();

    public:
    property(){
        ParentObject = NULL;
        Setter = NULL;
        Getter = NULL;
    };

    void setOwner(Owner* cObject){
        ParentObject = cObject;
    };

    void set(void(Owner::*SetterAddr)(PropType value)){
        if((PropAccess == propWrite) || (PropAccess == propReadWrite)) Setter = SetterAddr;
        else Setter = NULL;
    };

    void get(PropType (Owner::*GetterAddr)()){
        if((PropAccess == propRead)||(PropAccess == propReadWrite)) Getter = GetterAddr;
        else Getter = NULL;
    };

    PropType operator = (const PropType& value){
        if((ParentObject != NULL)&&(Setter != NULL))
            (ParentObject->*Setter)(value);
        return value;        
    };

    operator PropType(){
        if((ParentObject != NULL)&&(Getter != NULL)){
            return(ParentObject->*Getter)();
        } else return((PropType)-1);            
    };
};

#endif
//==============================================================================
