/*_____ I N C L U D E S ____________________________________________________*/
#include <stdio.h>
#include "NuMicro.h"

#include "misc_config.h"
#include "spi_slave.h"

/*_____ D E C L A R A T I O N S ____________________________________________*/

/*_____ D E F I N I T I O N S ______________________________________________*/
uint32_t g_au32SlaveTxBuffer = 0;
uint32_t g_au32SlaveRxBuffer = 0;
uint8_t g_au8SlaveRxFlag = 0;

// #define SPI_DATA_WIDTH				(16)
#define SPI_DATA_WIDTH				(32)

/*_____ M A C R O S ________________________________________________________*/

/*_____ F U N C T I O N S __________________________________________________*/


void SPI_Slave_Tx_Enable(void)
{
    uint8_t header = 0x6A;
    uint8_t tail = 0x6B;

	SPI_ClearTxFIFO(BridgeSpiPortNum);
    g_au32SlaveTxBuffer = 0;

    g_au32SlaveTxBuffer = g_au32SlaveRxBuffer;

    g_au32SlaveTxBuffer &= 0x00FFFF00;
    g_au32SlaveTxBuffer |= header << 24;
    g_au32SlaveTxBuffer |= tail;
	    
    SPI_WRITE_TX(BridgeSpiPortNum, g_au32SlaveTxBuffer);
    // printf("tx1--0x%08X\r\n",g_au32SlaveTxBuffer);
}

void SPI_Slave_Rx_Enable(void)
{
    g_au32SlaveRxBuffer = SPI_READ_RX(BridgeSpiPortNum);
    // printf("[rx1]0x%08X\r\n",g_au32SlaveRxBuffer);
}

void BridgeSpiPort_IRQHandler(void)
{
    if(SPI_GetIntFlag(BridgeSpiPortNum, SPI_SSINACT_INT_MASK))
    {
        // BridgeSpiPortNum ->FIFOCTL |= SPI_FIFOCTL_TXRST_Msk | SPI_FIFOCTL_RXRST_Msk;
        
		SPI_Slave_Rx_Enable();
		SPI_Slave_Tx_Enable();
        g_au8SlaveRxFlag = 1;

        SPI_ClearIntFlag(BridgeSpiPortNum, SPI_SSINACT_INT_MASK);
    }  

}

/*
	SPI slave SPI0 : PA0(MOSI)/PA1(MISO)/PA2(CLK)/PA3(SS)
*/
void SPI_Slave_Init(void)
{
	g_au32SlaveRxBuffer = 0;
	g_au32SlaveTxBuffer = 0;

	SYS_ResetModule(BridgeSpiPort_RST);
    SPI_Open(BridgeSpiPortNum, SPI_SLAVE, SPI_MODE_0, SPI_DATA_WIDTH, (uint32_t)NULL);

	SPI_ClearRxFIFO(BridgeSpiPortNum);
	SPI_ClearTxFIFO(BridgeSpiPortNum);
	SPI_SetFIFO(BridgeSpiPortNum , 2 , 2);

	SPI_EnableInt(BridgeSpiPortNum,SPI_SSINACT_INT_MASK );
    SPI_WRITE_TX(BridgeSpiPortNum, 0xFFFFFFFF);    /* Dummy Write to prevent TX under run */
    NVIC_EnableIRQ(BridgeSpiPort_IRQn);
}


