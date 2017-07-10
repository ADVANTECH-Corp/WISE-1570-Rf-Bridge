
#include "mbed.h"

//*****************************************************************************
//                 MACROs and needed structures
//*****************************************************************************


//*****************************************************************************
//                 Global variables
//*****************************************************************************
DigitalOut power(CB_PWR_ON);
Serial MCUDebug(SERIAL_TX, SERIAL_RX);
Serial RFMainPort(LPUART1_TX, LPUART1_RX);

// The below command is only for demo (Request Manufacturer Identification)
char cmd[] = "AT+CGMI";

//*****************************************************************************
//                 Local functions
//*****************************************************************************
void UART_MCUDebugCb(void)
{
	RFMainPort.putc(MCUDebug.getc());
}

void UART_MainPortCb(void)
{
	MCUDebug.putc(RFMainPort.getc());
}



//*****************************************************************************
//                 Main process
//*****************************************************************************
int main() 
{	
    power = 1;

	MCUDebug.baud(9600);
	MCUDebug.format();
    MCUDebug.attach(&UART_MCUDebugCb);
	
	RFMainPort.baud(9600);
	RFMainPort.format();
	RFMainPort.attach(&UART_MainPortCb);
	
	while(1)
	{
		//
		// Run this command per 5 seconds
		//
		//RFMainPort.printf("%s\r", cmd);
		wait_ms(5000);
	}
}

