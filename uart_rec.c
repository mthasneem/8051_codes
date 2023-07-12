#include <reg51.h>
#include <stdio.h>

void uart_init();
void uart_txchar(char); 
char uart_rxchar(); 

void uart_txchar(char Data)
{
    SBUF = Data;
    while (TI == 0);
    TI = 0;
}

void uart_init()
{
    TMOD = 0x20;  // timer 1, mode 2
    TH1 = 0xFD;   // baud rate 9600
    SCON = 0x50;
    TR1 = 1;
}
 
char uart_rxchar()
{
	char data1;
	while (RI==0);
	RI=0;
	data1 = SBUF;
	return(data1);
}
	
void main(void)
{ 
		char datain;
		uart_init();
    while (1)
    {
			datain = uart_rxchar();
      uart_txchar(datain);
    }
}

