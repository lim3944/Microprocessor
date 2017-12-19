#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#define TRUE 1
#define FALSE 0

#define S0 0x01
#define S1 0x02

#define FND_C0 0x01
#define FND_C1 0x02
#define FND_C2 0x04
#define FND_C3 0x08

#define START 1
#define STOP 0

const char Font[17]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00};

volatile unsigned int t2_100=0;
volatile unsigned char state=STOP;

SIGNAL(SIG_OVERFLOW0){
	TCNT0=112;
	if(state==START)
	t2_100++;

	if(t2_100>=9999) t2_100=0;
}

void Init_Timer(void){
	TCCR0=0x07;
	TCNT0=112;
	TIMSK=0x01;
}

void FND_Display(unsigned char digit0,unsigned char digit1,unsigned char digit2,unsigned char digit3){
	PORTG |= 0x0F;
	PORTG &= ~FND_C3;
	PORTB = Font[digit0];
	_delay_ms(50);

	PORTG |= 0x0F;
	PORTG &= ~FND_C2;
	PORTB = Font[digit1];
	_delay_ms(50);

	PORTG |= 0x0F;
	PORTG &= ~FND_C1;
	PORTB = Font[digit2];
	_delay_ms(50);

	PORTG |= 0x0F;
	PORTG &= ~FND_C0;
	PORTB = Font[digit3];
	_delay_ms(50);
}

int main(void){
	unsigned char digit0,digit1,digit2,digit3;
	unsigned int temp=0;
	unsigned char key=0,past_key=0;

	DDRB=0xFF;
	DDRG=0xFF;
	DDRD=0x00;

	PORTB=0x00;
	PORTG=0xFF;

	digit0 = digit1 = digit2 = digit3 = 0;
	Init_Timer();
	sei();

	while(1) {
		key=PIND&0x03;
		if((past_key==0x00)&&(key!=0x00)) {
			switch(key) {
				case S0:
					if(state==START) state=STOP;
					else state=START;
					break;
				
				case S1:
					state=STOP;
					t2_100=0;
					break;
			}
		}

		past_key=key;
		digit3=t2_100/1000;
		temp=t2_100%1000;
		digit2=temp/100;
		temp=temp%100;
		digit1=temp/10;
		digit0=temp%10;

		FND_Display(digit0,digit1,digit2,digit3);
		
	}
	return 0;
}
