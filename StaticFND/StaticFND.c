#include<avr/io.h>
#include<util/delay.h>

const char Font[15]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,};
const char Port[5]={0x01,0x02,0x04,0x08};

int main(void){

	unsigned int a,b,c,d,i;
	DDRA=0xFF;
	DDRB=0xFF;

	while(1){
		for(i=0;i<=9999;i++){
			a=i/1000;
			b=(i%1000)/100;
			c=(i%100)/10;
			d=i%10;

			PORTB |=0x0F;
			PORTB &=~Port[3];
			PORTA=Font[d];
			_delay_ms(100);

			PORTB |=0x0F;
			PORTB &=~Port[2];
			PORTA=Font[c];
			_delay_ms(100);

			PORTB |=0x0F;
			PORTB &=~Port[1];
			PORTA=Font[b];
			_delay_ms(100);

			PORTB |=0x0F;
			PORTB &=~Port[0];
			PORTA=Font[a];
			_delay_ms(100);

		}
	}

	return 0;
}


