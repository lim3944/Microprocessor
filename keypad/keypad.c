#include<avr/io.h>
#include<util/delay.h>

int main(){

	unsigned char led=0; 
	unsigned char input_data=0; 
	unsigned char key=0;

	DDRF=0xFF;
	DDRA=0xFF;
	DDRD=0x00;

	while(1){
		key=0;
		
		PORTF= 0x01;
		_delay_ms(1);
		input_data=PIND & 0x07;
		if(input_data!=0) key=(input_data/2)+1;

		PORTF=0x02;
		_delay_ms(1);
		input_data=PIND & 0x07;
		if(input_data !=0) key=(input_data/2)+4;

		PORTF= 0x04;
		_delay_ms(1);
		input_data=PIND & 0x07;
		if(input_data!=0) key=(input_data/2)+7;
		
		PORTF=0x08;
		_delay_ms(1);
		input_data=PIND & 0x07;
		if(input_data != 0) key=(input_data/2)+10;

		led=0x01;
		if(key==0) led=0x00;
		else if(key<9) led=led<<(key-1);
		else if(key==9) led=0x81;
		else if(key==10) led=0x0F;
		else if(key==11) led = 0xFF;
		else if(key==12) led = 0xF0;
		PORTA=led;
	}
	return 0;
}
