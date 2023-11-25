//==============================================================================
/** @file SysMessages.h
 *  @brief EDROS - System messages definition
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
#ifndef SYSMESSAGES_H
    #define SYSMESSAGES_H

/**
 * @defgroup SysMessages
 * @{
 */
//------------------------------------------------------------------------------
// system messages
// high priority messages (system defined) [> NM_HIGHEST]
#define NM_EXTINGUISH    			((uint32_t)0xFFFFFFFF)

#define NM_EXTINT        			((uint32_t)0xFFFFFFFE)
#define NM_EXECUTE       			((uint32_t)0xFFFFFFFD)
#define NM_PERIPH_RESET  			((uint32_t)0xFFFFFFF0)
#define NM_TIMESLICE     			((uint32_t)0xFFFFFF02)
#define NM_HARDTICK      			((uint32_t)0xFFFFFF01)
#define NM_SYSCLOCKCHANGE_PCLK		((uint32_t)0xFFFFF0A0)

#define NM_HDTIM_BRK     			((uint32_t)0xFFFFF025)
#define NM_HDTIM_UPT     			((uint32_t)0xFFFFF024)
#define NM_HDTIM_TRG     			((uint32_t)0xFFFFF023)
#define NM_HDTIM_COM     			((uint32_t)0xFFFFF022)
#define NM_HDTIM_CCO     			((uint32_t)0xFFFFF021)
#define NM_HDTIM_CC      			((uint32_t)0xFFFFF020)

#define NM_CANERROR      			((uint32_t)0xFFFF0404)
#define NM_CANRX_FAULT   			((uint32_t)0xFFFF0403)
#define NM_CANRX_FULL    			((uint32_t)0xFFFF0402)
#define NM_CANRX         			((uint32_t)0xFFFF0401)
#define NM_CANTX         			((uint32_t)0xFFFF0400)

#define NM_I2CEVENT      			((uint32_t)0xFFFFF012)
#define NM_SPISRXE       			((uint32_t)0xFFFFF010)

// high priority messages (application defined)
#define NM_APPHMSG_LAST  			((uint32_t)0xFFFF0100)
#define NM_APPHMSG_FIRST 			((uint32_t)0xFFFF0000)

// low priority messages (application defined)
#define NM_APPLMSG_LAST  			((uint32_t)0x10000100)
#define NM_APPLMSG_FIRST 			((uint32_t)0x10000000)

// low priority messages (system defined)
#define NM_STATE_ENTRY 				((uint32_t)0x00000912)
#define NM_STATE_LEAVE 				((uint32_t)0x00000910)

#define NM_ITEM_EXCLUDED 			((uint32_t)0x00000812)
#define NM_ITEM_INCLUDED 			((uint32_t)0x00000810)

#define NM_DAC           			((uint32_t)0x00000720)
#define NM_ADC_OK        			((uint32_t)0x00000700)

#define NM_I2CERR        			((uint32_t)0x00000601)
#define NM_I2CERROR      			((uint32_t)0x00000607)
#define NM_I2CMTCR       			((uint32_t)0x00000605)
#define NM_I2CMTC        			((uint32_t)0x00000604)
#define NM_I2CMTXE       			((uint32_t)0x00000603)
#define NM_I2CMRXNE      			((uint32_t)0x00000602)

#define NM_SPIERROR      			((uint32_t)0x00000507)
#define NM_SPITMOUT      			((uint32_t)0x00000506)
#define NM_SPISTXE       			((uint32_t)0x00000505)
#define NM_SPIMTXE       			((uint32_t)0x00000503)
#define NM_SPIMRXNE       			((uint32_t)0x00000502)
#define NM_SPIRX         			((uint32_t)0x00000501)
#define NM_SPITX        			((uint32_t)0x00000500)

#define NM_DMA_ERR      			((uint32_t)0x00000302)
#define NM_DMA_MOK       			((uint32_t)0x00000301)
#define NM_DMA_OK        			((uint32_t)0x00000300)

#define NM_UARTRXIDLE				((uint32_t)0x00000204)
#define NM_UARTCTS       			((uint32_t)0x00000203)
#define NM_UARTERROR     			((uint32_t)0x00000202)
#define NM_UARTRX        			((uint32_t)0x00000201)
#define NM_UARTTX        			((uint32_t)0x00000200)

#define NM_ADCAWD        			((uint32_t)0x00000152)
#define NM_ADCJEOC       			((uint32_t)0x00000151)
#define NM_ADCEOC        			((uint32_t)0x00000150)

#define NM_TIMETICK      			((uint32_t)0x00000110)
#define NM_TIMEOUT       			((uint32_t)0x00000100)
#define NM_KEYS_UPDATE   			((uint32_t)0x000000A2)
#define NM_KEYSCAN       			((uint32_t)0x000000A0)
#define NM_REPAINT       			((uint32_t)0x00000080)
#define NM_KEYDOWN       			((uint32_t)0x00000090)
#define NM_KEYUP         			((uint32_t)0x00000092)
#define NM_NULL          			((uint32_t)0x00000000)

/*
 * @}
 */

//------------------------------------------------------------------------------
#endif

//==============================================================================

