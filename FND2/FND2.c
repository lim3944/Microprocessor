#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

const char Font[15]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,};
const char Port[5]={0x01,0x02,0x04,0x08};

void FND(unsigned char d,unsigned char c, unsigned char b, unsigned char a){

			PORTG |=0x0F;
			PORTG &=~Port[3];
			PORTB=Font[d];
			_delay_ms(100);

			PORTG |=0x0F;
			PORTG &=~Port[2];
			PORTB=Font[c];
			_delay_ms(100);

			PORTG |=0x0F;
			PORTG &=~Port[1];
			PORTB=Font[b];
			_delay_ms(100);

			PORTG |=0x0F;
			PORTG &=~Port[0];
			PORTB=Font[a];
			_delay_ms(100);
}

SIGNAL(SIG_INTERRUPT0){
	a=-a;
}

int main() {
	unsigned char d0,d1,d2,d3;
	unsigned int temp=0,i;
	int c_value=0;

	DDRB=0xFF;
	DDRG=0xFF;
	PORTB=0x00;
	PORTG=0xFF;

	EICRA=0x03;
	EIMSK=0x01;

	d0=d1=d2=d3=0;

	sei();

	while(1){
		c_value=c_value+a;
		if(c_value>9999) c_value=0;
		if(c_value<0) c_value=9999;

		d3=c_value/1000;
		temp=c_value%1000;
		d2=temp/100;
		temp%=100;
		d1=temp/10;
		d0=temp%10;
		for(i=0;i<20;i++)
			FND(d,b,c,a);
		}
	return 0;
}
		
