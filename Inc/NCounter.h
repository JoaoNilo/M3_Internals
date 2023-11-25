//==============================================================================
#ifndef NCOUNTER_H
    #define NCOUNTER_H

   #include "NComponent.h"

namespace ncounter_space{

    //-----------------------------------
    enum cnMode { cnUp=0, cnDown=1, cnUpDown=2};

    class NCounter {
        private:
            static const unsigned int NCOUNTER_MAX = 100;
			static const unsigned int NCOUNTER_UPPER = 75;
			static const unsigned int NCOUNTER_LOWER = 25;
			static const unsigned int NCOUNTER_MIN = 0;

            //-------------------------
            bool enabled;
			unsigned int maximum;
            unsigned int counter;
			unsigned int upper;
			unsigned int lower;
			unsigned int minimum;
            cnMode mode;

            //-------------------------
            bool done;
            bool iDone;

            //-------------------------------------------
            void SetEnabled(bool);
            bool GetEnabled();
            void SetMode(cnMode);
            cnMode GetMode();
            unsigned int GetCount();
            void SetMaximum(unsigned int);
            unsigned int GetMaximum();
            void SetUpper(unsigned int);
            unsigned int GetUpper();
            void SetLower(unsigned int);
            unsigned int GetLower();
            void SetMinimum(unsigned int);
            unsigned int GetMinimum();

            //-------------------------------------------
			void CheckBounds();
			void CheckThresholds();    

        //-----------------------------------------------
        public:
            NCounter();
            ~NCounter();

            //-------------------------------------------
            // METHODS
			void Reset();
            unsigned int Increment();
            unsigned int Decrement();
            //virtual void Notify(NMESSAGE*);

            //-------------------------------------------
            // EVENTS
            void (*OnMaximum)(void);
			void (*OnMinimum)(void);
			void (*OnUpper)(void);
			void (*OnLower)(void);
			
            //-------------------------------------------
            // PROPERTIES											< DEFAULT PARAMETERS>
            property<NCounter, bool, propReadWrite> Enabled;          	// false
            property<NCounter, enum cnMode, propReadWrite> Mode;        // cnUp
            property<NCounter, unsigned int, propReadWrite> Count;      // 0
            property<NCounter, unsigned int, propReadWrite> Maximum;    // 100
			property<NCounter, unsigned int, propReadWrite> Upper;    	// 75
			property<NCounter, unsigned int, propReadWrite> Lower;    	// 25
			property<NCounter, unsigned int, propReadWrite> Minimum;    // 0
			unsigned int Tag;											// 0
    };
};

using namespace ncounter_space;
#endif
//==============================================================================
