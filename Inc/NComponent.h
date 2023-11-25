//==============================================================================
/** @file NComponent.h
 *  @brief System components interface class
 *  @version 1.0.0
 *  @author J. Nilo Rodrigues - nilo@pobox.com
 *
 *------------------------------------------------------------------------------
 *
 * <h2><center>&copy; Copyright (c) 2020 Joao Nilo Rodrigues </center></h2>
 * <h2><center> All rights reserved. </center></h2>
 *
 * This software component is licensed by "Joao Nilo Rodrigues" under BSD 3-Clause
 * license, the "License".
 * You may not use this file except in compliance with the License.
 *               You may obtain a copy of the License at:
 *                 opensource.org/licenses/BSD-3-Clause
 *
 *///---------------------------------------------------------------------------
#ifndef NCOMPONENT_H
    #define NCOMPONENT_H
	
    #include "DRV_SSR.h"
    #include "SysMessages.h"
    #include "Priorities.h"
    #include "Property.h"

	/**
	 * @enum nPriorities
	 * This enumeration defines three options for the NComponent @ref Priority property.
	 * @note This is one of the most important enumerations in the whole framework.
	 * Extreme care must be taken when assigning one of its values to a Priority property,
	 * for it may lead to unpredictable behavior or even system instability of operation.
	 *
	 */
  	enum nPriorities { nTimeCritical,	/*!< Highest priority\n
  	 	 	 	 	 	 	 	 	 	 	 The system message dispatcher will send event-messages directly
  	 	 	 	 	 	 	 	 	 	 	 to the component by calling its InterruptCallback method.
  	 	 	 	 	 	 	 	 	 	*/

  						nNormal,		/*!< Intermediate priority\n
  	 	 	 	 	 	 	 	 	 	 	 The system message dispatcher will schedule event-messages in the
  	 	 	 	 	 	 	 	 	 	 	 message queue and the component will be notified as soon as no other
  	 	 	 	 	 	 	 	 	 	 	 interrupt service is being executed, by calling its InterruptCallback method.
  						 	 	 	 	*/

					 	nRelaxed		/*!< Lowest priority\n
  	 	 	 	 	 	 	 	 	 	 	 The event-messages are inserted in the message queue as standard broadcast messages.
  	 	 	 	 	 	 	 	 	 	 	 In this case, the message queue is periodically purged by the dispatcher which extracts
  	 	 	 	 	 	 	 	 	 	 	 the messages and notify all the registered components by calling their Notify method.
					 	 	 	 	 	 */
  					 };
	
    //-----------------------------------
  	/**
  	 * @brief Base-class for all other system classes called "components".
  	 * - The NComponent class is a special case in the EDROS Framework since it is not a REAL
  	 * component but, instead, an interface class with the basic set of features needed by the
  	 * system kernel to treat its descendant classes as EDROS components.
  	 * @note Note that the NComponent itself should never be instantiated in the application since
  	 * it is useless but consumes the same system resources as a useful component.
  	 */
    class NComponent{

        private:

        protected:

        public:
            HANDLE  Handle;		//!< pointer to the base-address
            uint32_t Tag;		//!< general purpose 32-bit variable (sometimes used as index)

        public:
            /**
             * @brief Standard constructor for the component.
             * This method is automatically called by the descendant classes during their
             * initialization process.
             */
            NComponent();

            /**
             * @brief Standard destructor for the component.
             * Likewise the constructor, this method is to be called exclusively by the descendant classes.
             */
            ~NComponent();

            /**
             * @brief This method is used as a system callback function for message dispatching.
             */
            virtual void Notify(NMESSAGE*);

            /**
             * @brief This method is used as a system callback function for time critical
             * events dispatching.
             */
            virtual void InterruptCallBack(NMESSAGE*);

            /**
             * @brief This property is used by the descendant classes to adjust to their
             * responsiveness constraints, as can be seen in @ref nPriorities.
             * @note This property is not usually changed from the application.
             * Care should be taken to avoid unpredictable behavior.
             */
			nPriorities Priority;
    };

#endif
//==============================================================================
