//==============================================================================
/** @file NTimer.h
 *  @brief Software-based timer.
 *  - This component provides basic timer features.
 *  This software-defined timer has an interval property, which is specified in
 *  milliseconds, and can be used as general purpose timer. Many instances of this
 *  component can be used simultaneously since they are not associated with physical
 *  timer of the microcontroller. (TIM1, TIM2, etc.)
 *  @version 1.0.0
 *  @author Joao Nilo Rodrigues - nilo@pobox.com
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
#ifndef NTIMER_H
    #define NTIMER_H

    #include "NComponent.h"

	//--------------------------------------------------------------------------
	/**
	 * @enum tmModes
	 * This enumeration defines the options for the NTimer @ref Mode property.
	 */
    enum tmModes { tmContinuous,	//!< multiple OnTimer events, every "Interval" (ms)
    			   tmSingleRun		//!< single OnTimer event after the first "Interval" (ms)
    			 };

	//--------------------------------------------------------------------------
	/** @brief Software-based timer.
	 * - The NTimer component can be used to generate periodic events at regular intervals.
	 * The interval resolution is milliseconds but for very short intervals the accuracy is compromised due to the
	 * low priority of the NTimer running thread. For time-critical needs, consider @ref NHardwareTimer.
	 */
    class NTimer: public NComponent{
        private:
			#define __NTIMER_TIMEOUT_DEFAULT  ((uint32_t) 100)
			#define __NTIMER_TIMEOUT_MAX 	  ((uint32_t) 360000)

            //-------------------------
            uint32_t interval;
            tmModes mode;
            bool enabled;

            //-------------------------
            uint32_t timeout_counter;
            uint32_t timeout_value;
            bool done;
            bool iDone;

            //------------------------
            void SetEnabled(bool);
            bool GetEnabled();
            bool GetDone();
            void SetMode(tmModes);
            tmModes GetMode();
            void SetInterval(uint32_t);
            uint32_t GetInterval();

        public:
            //-------------------------------------------
            // METHODS
            /**
             * @brief Standard constructor for this component.
             */
            NTimer();

            /**
             * @brief Standard destructor for this component.
             */
            ~NTimer();

            /**
             * @brief This method can be used to start the timer operation.
             * @arg newInterval:
             * required time interval (in milliseconds) between @ref OnTimer events.
             * @note This method updates the value of the @ref Interval property.
             */
            void Start(uint32_t newInterval);

            /**
             * @brief This method can be used to stop the timer operation.
             * @return
            */
            void Stop();

            /**
             * @brief This method is used as a system callback function for message dispatching.
             * @return
             * @note This callback method should not be called by the application.
             */
            virtual void Notify(NMESSAGE*);

            //-------------------------------------------
            // EVENTS
            /**
             * @brief This is the event handler for timing events.
             * - This event handler is called periodically at every interval expiration
             * if property @ref Mode is set to @ref tmContinuos, or just once if property @ref Mode
             * is set to tmSingleRun.
             */
            void (*OnTimer)(void);

            //-------------------------------------------
            // PROPERTIES
            /**
             * @brief This property can be used to start and stop the timer.
             * The Enabled property cannot be used to pause the timer since the timer
             * is reset every time this property is set to false.
             * This property provides READ and WRITE access.
             * - Default value: false
             */
            property<NTimer, bool, propReadWrite> Enabled;

            /**
             * @brief This property is used to set the required time interval between @ref OnTimer events.
             * This property provides READ and WRITE access.
             * - Default value: 100  (ms)
             *
             * @note This property can be changed by the @ref Start method.
             */
            property<NTimer, uint32_t, propReadWrite> Interval;

            /**
             * @brief This property is used to set the operation mode. The available options are
             * detailed in the @ref tmModes enumeration description.
             * This property provides READ and WRITE access.
             * - Default value: @ref tmContinuous
             *
             */
            property<NTimer, enum tmModes, propReadWrite> Mode;

            /**
             * @brief This property can be used in very special cases where the "polling"
             * technique is required. It provides the status of the current operation
             * so that the event handler need not be set and the NTimer can be used in
             * a blocking-timer fashion.
             * This property provides only READ access.
             * - Default value: false
             */
            property<NTimer, bool, propRead> Done;

    };

#endif
//==============================================================================
