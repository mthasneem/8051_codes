#include <reg51.h>
#include <stdio.h>

void uart_init();
void uart_txchar(char); 
void uart_sendstring(char *);

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
 
void uart_sendstring(char *str)
{
    int i;
    for (i = 0; str[i] != 0; i++)
    {
        uart_txchar(str[i]);
    }
}

void main(void)
{ 
    uart_init();
    while (1)
    {
        uart_sendstring("THASNEEM\n\r");
    }
}

