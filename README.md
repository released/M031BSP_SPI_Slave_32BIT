# M031BSP_SPI_Slave_32BIT
M031BSP_SPI_Slave_32BIT

update @ 2025//06/04

1. use M032SE EVB , to test SPI0 slave TX , RX function (width : 32 bit)
	- PA0(MOSI)		
	
	- PA1(MISO)		
	
	- PA2(CLK)	
	
	- PA3(SS)

2. when receive data from SPI master (ex:0x5A01025B) , will store bit23~bit8  , and packet with 0x6A _ _ _ _ 6B for next TX data

![image](https://github.com/released/M031BSP_SPI_Slave_32BIT/blob/main/LA_SPI_32bit.jpg)

3. below is UART log and timing measurement , when UART bytes is 32bit + CR + LF (10 BYTES = 868us)

![image](https://github.com/released/M031BSP_SPI_Slave_32BIT/blob/main/LA_gpio_measurement.jpg)

![image](https://github.com/released/M031BSP_SPI_Slave_32BIT/blob/main/Log_gpio_measurement.jpg)

