//==============================================================================
/** @file NFifo.h
 *  @brief General purpose first-in first-out buffer.
 *  This component provides FIFO buffer functionality.
 *  @version 1.0.0
 *  @author   J. Nilo Rodrigues  -  nilo@pobox.com
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
#ifndef NFIFO_H
    #define NFIFO_H

    #include <stdint.h>

    //------------------------------------------------
	/** @brief General purpose first-in first-out buffer.
	 */
	class NFifo{
	public:
		//--------------------------------------------
		/**
		 * @struct PARAMS
		 * This structure defines the control data for the buffer
		 */
	    struct PARAMS{
	        uint32_t head;		//!< insertion pointer (used by Put)
	        uint32_t tail;		//!< extraction pointer (used by Get)
	        uint32_t counter;	//!< number of lines currently in use
	        uint32_t tag;		//!< auxiliary variable (sometimes used as index)
	    };

		//--------------------------------------------
		/**
		 * @struct FLAGS
		 * This structure defines the control flags
		 */
	    struct FLAGS{
	        uint32_t overflow:  1; 	//!< overflow condition detected when true.
	        uint32_t reserved: 31;	//!< Reserved: not in use.
	    };

		private:

			//-----------------------------------
			uint8_t* data;

		protected:
			uint32_t line_size;
			uint32_t lines;
			PARAMS params;
            FLAGS flags;

		private:
			void LocateLineDepth();
			void AllocateMemory(uint32_t LineSize, uint32_t Lines);

		public:
			//-----------------------------------
			// METHODS

            /**
             * @brief Standard constructor for this class.
             * If this constructor is used the resultant NFifo organization defaults to:\n
             * Lines = 10, LineSize = 65 (bytes)\n
             * @note Keep in mind that RAM memory space is usually very limited when dealing with microcontrollers.\n
             * As good practice, try to keep these values as low as possible.
             */
			NFifo(void);

            /**
             * @brief Constructor for this class.
             * This constructor is requires the following parameters assignment:
             * @arg LineSize
             * - maximum number of bytes expected for a single line (packet)
             * @arg Lines
             * - number of lines
             * @note Keep in mind that RAM memory space is usually very limited when dealing with microcontrollers.\n
             * As good practice, try to keep these values as low as possible.
             */
			NFifo(uint32_t LineSize, uint32_t Lines);

            /**
             * @brief Standard destructor for this class.
             */
			~NFifo(void);

            /**
             * @brief This method is used to insert data in the NFifo buffer.
             * @arg xData:
             * pointer to the external data buffer to be inserted.
             * @arg xSize
             * number of bytes in the external data buffer
             * @return
             * true: if data was successfully inserted in the NFifo buffer.\n
             * false: when property LockOnOverflow is true and the NFifo is full.\n
             */
			bool Put(uint8_t* xData, uint32_t xSize);

            /**
             * @brief This method is used to extract data from the NFifo buffer.
             * @arg xData:
             * pointer to the external data buffer to receive the extracted data.
             * @return
             * the number of bytes extracted from the NFifo buffer line.\n
             */
			uint32_t Get(uint8_t* xData);

            /**
             * @brief This method is used to access the internal control parameters.
             * @arg FifoParams:
             * pointer to a data structure to receive control parameters. Please refer to PARAMS definition for further details.
             * @return
             * The NFifo control data is returned through the FifoParams passed as argument.\n
             */
			void GetControl(PARAMS* FifoParams);

            /**
             * @brief This method is used to reset the NFifo buffer to its original state.
             * All the data in the buffer lines is lost. Flags, pointers and counter are all cleared.
             * @note The memory layout of the internal buffers is preserved, i.e. both line size and number of lines are not lost.
             */
			void Flush();

            /**
             * @brief This method is used to reset the internal "overflow" flag.
             * The "overflow" flag is set when the method Put is called with the NFifo already full, i.e. all its lines filled with data.
             * @return
             */
			void ClearOverflow();

            /**
             * @brief This method is used to retrieve the internal "counter".
             * The internal "counter" incremented on every Put and decremented on every Get. The resulting count should not exceed the lines number of the NFifo buffer.
             * @return
             * The number of buffer lines in use. (normally, {Puts - Gets})
             */
            uint32_t Counter();

            /**
             * @brief This method is used to retrieve the "line size" (in bytes) of next extracted line.
             * It is used for memory allocation of the buffer to be used in the next Get call.
             * @return
             * The number of bytes to be returned by the next Get call.
             */
            uint32_t GetSize();

            //-----------------------------------
            // PROPERTIES
            /**
             * @property LockOnOverflow
             * This property controls the component behavior in the event of an "overflow".
             * When an overflow condition is detected the NFifo component will do the following:\n
             * if LockOnOverflow is false: the oldest line of the buffer will be overwritten with the new data.
             * if LockOnOverflow is true: the new data (last Put) will be discarded to preserve the current data in the buffer lines.
             * This property provides READ and WRITE access.
             * - Default value: false
             *
             * @note It is important to notice that, in both cases data is being lost. In this case, one should really consider increasing the lines number.
             */
            bool LockOnOverflow;
	};
	//-------------------------------------------

#endif
//==============================================================================

