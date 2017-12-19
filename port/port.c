#include<avr/io.h>
#include<util/delay.h>

int checker(int a){
	if(a)
		return 0;
	else
		return 1;
}

int main(void){
	unsigned char input_data;
	int chk=1;
	DDRD=0x00;
	DDRA=0xFF;

	PORTA=0x01;

	while(1){
		input_data=PIND;
		_delay_ms(1000);
		if(chk==1)
			PORTA*=2;
		else
			PORTA/=2;
		if((input_data&0x10)==0x10){
			chk=checker(chk);
			input_data=0;
		}
		if(chk==1&&PORTA==0)
			PORTA=0x01;
		if(chk==0&&PORTA==0)
			PORTA=0x80;
	}
	return 0;
}

