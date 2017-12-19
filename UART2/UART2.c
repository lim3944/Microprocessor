#include<avr/io.h>
#include<avr/interrupt.h>
#define NULL 16

const char Font[17]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00};

volatile unsigned char ReceiveData, digit0;

void init_UART(void){
	UBRR0L=95;
	UCSR0B=0x90;
}

SIGNAL(SIG_USART0_RECV){
	ReceiveData=UDR;
	digit0=ReceiveData-0x30;

	if(digit0>=10) digit0=NULL;

	PORTB=Font[digit0];
}

int main(){
	DDRB=0xFF;
	PORTB=Font[NULL];
	init_URT();
	sei();

	while(1){
	}
	return 0;
}

