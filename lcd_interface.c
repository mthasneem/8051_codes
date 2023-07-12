#include <reg51.h>
sfr ldata = 0x090;	//p1 = lcd data pins
sbit rs = P2^0;
sbit rw = P2^1;
sbit en = P2^2;
sbit busy = P1^7;

void lcdcmd(unsigned char value);
void lcddata(unsigned char value);
void lcdready();
void MSDelay(unsigned int itime);


void main(){
	lcdcmd(0x38);
	lcdcmd(0x0E);
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcdcmd(0x86);
	lcddata('T');
	lcddata('H');
	lcddata('A');
	lcddata('s');

}

void MSDelay(unsigned int itime){
	unsigned int i , j ;
	for(i=0;i<itime;i++)
		for(j=0;j<1275;j++);
}

void lcdready(){
	busy = 1;		//make the busy pin an input
	rs = 0;			//select command register
	rw = 1;
	while(busy==1){		//wait here for busy flag
		en=0;		// L-to-H enable pin for read
		MSDelay(1);
		en = 1;
	}
	return;
}

void lcddata(unsigned char value){
	lcdready();
	ldata = value;
	rs= 1;			//select data register
	rw= 0;
	en = 1;			// H-to-L enable pin for write
	MSDelay(1);
	en=0;
	return;
}

void lcdcmd(unsigned char value){
	lcdready();
	ldata = value;
	rs= 0;			//select command register
	rw =0;
	en = 1;
	MSDelay(1);
	en = 0;
	return;
}
















