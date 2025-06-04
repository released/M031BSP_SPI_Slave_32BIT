#ifndef __SPI_SLAVE_H__
#define __SPI_SLAVE_H__

/*_____ I N C L U D E S ____________________________________________________*/
#include <stdio.h>
#include "NuMicro.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/

/*  
	template
	typedef struct _peripheral_manager_t
	{
		uint8_t u8Cmd;
		uint8_t au8Buf[33];
		uint8_t u8RecCnt;
		uint8_t bByPass;
		uint16_t* pu16Far;
	}PERIPHERAL_MANAGER_T;

	volatile PERIPHERAL_MANAGER_T g_PeripheralManager = 
	{
		.u8Cmd = 0,
		.au8Buf = {0},		//.au8Buf = {100U, 200U},
		.u8RecCnt = 0,
		.bByPass = FALSE,
		.pu16Far = NULL,	//.pu16Far = 0	
	};
	extern volatile PERIPHERAL_MANAGER_T g_PeripheralManager;
*/

// SPI slave
#define BridgeSpiPortNum				(SPI0)
#define BridgeSpiPort_IRQn				(SPI0_IRQn)
#define BridgeSpiPort_IRQHandler		(SPI0_IRQHandler)
#define BridgeSpiPort_RST				(SPI0_RST)


/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/


void SPI_Slave_Init(void);

#endif //__SPI_SLAVE_H__
