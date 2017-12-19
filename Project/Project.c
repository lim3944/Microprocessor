//LED -> A0~A7
//LCD -> B0~B7(D), F0(E), F1(RS)
//Keypad -> C0~C2(C), C4~C7(R)
//UART -> E0(Tx), E1(Rx)
//Push -> D0~D3

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrypt.h>
#include <avr/wdt.h>
#include <string.h>
#include <stdio.h>

#include "serial.h"
#include "cmdline.h"
#include "cmd_func.h"

#define START 0x01
#define END   0x02
#define PAUSE 0x04

#define LCD_CTRL PORTF
#define LCD_DATA PORTB
#define LCD_RS   0x01
#define LCD_RW   0x02
#define LCD_E    0x04

#define Keypad_C 0x07
#define Keypad_R 0xF0

volatile unsigned int time_100=0;
volatile unsigned char state=END;
unsigned char Life=8;

unsigned char key_input[4]={0,};
unsigned char input_data=0;
unsigned char input_num=0;
unsigned char key=0;

unsigned char ans[5];

FILE device = FDEV_SETUP_STREAM(TxChar, NULL, _FDEV_SETUP_WRITE);
FILE device2 = FDEV_SETUP_STREAM(NULL, RxChar, _FDEV_SETUP_READ);

//Timer
SIGNAL(SIG_OVERFLOW0){
	TCNT0=112;
	if(state==START)
	time_100++;

	if(time_100>=9999) time_100=0;
}

void Init_Timer(void){
	TCCR0=0x07;
	TCNT0=112;
	TIMSK=0x01;
}

//LCD
void EnablePulse(void){
	LCD_CTRL |= LCD_E;
	asm("NOP");
	LCD_CTRL &=~LCD_E;
}

void sendLCDcommand(unsigned char command){
	LCD_CTRL &=~LCD_RS;
	LCD_DATA=command;
	EnablePulse();
	_delay_ms(20);
}

void Init_Lcd(void){
	_delay_ms(20000);
	LCD_CTRL &=~LCD_RW;
	sendLCDcommand(0x38);
	sendLCDcommand(0x0C);
	sendLCDcommand(0x01);
	_delay_ms(1000);
}

void sendLCDdata(unsigned char data){
	LCD_CTRL |= LCD_RS;
	LCD_DATA =data;
	EnablePulse();
	_delay_ms(20);
}

void DispString(char *str){
	while(*str){
		sendLCDdata(*str);
		str++;
	}
}

void Locate(int x,int y){
	unsigned char RamAddr;

	if(x==0) RamAddr=0x80+y;
	else RamAddr=0xC0+y;
	sendLCDcommand(RamAddr);
}
void LCDShift(chardir) {
	unsignedcharLCD_shift;
	if(dir==LEFT)LCD_shift=0x18; 
	elseif(dir==RIGHT) LCD_shift=0x1C; 
	sendLCDcommand(LCD_shift);
}

//Answer
void Answer(){
	unsigned int i;
	for(i = 0 ;i<3; i++) {


}

//Interrupt
SIGNAL(SIG_INTERRUPT0){
	state=PIND;
}

int main(){

	//Push
	DDRD=0x00;
	//Keypad
	DDRC=0xF0;
	//LCD
	DDRB=0xFF;
	DDRG=0xFF;

	PORTB=0x00;
	PORTF=0x00;	

	EICRA=0x03;
	EIMSK=0x01;

	sei();

	while(1){

		Init_Timer();
		Init_LCD();
		
		while(state==START){
				key=0;
		
			PORTC= 0x10;
			_delay_ms(10);
			input_data=PINC & 0x07;
			if(input_data!=0) key=(input_data/2)+1;
	
			PORTC=0x20;
			_delay_ms(10);
			input_data=PINC & 0x07;
			if(input_data !=0) key=(input_data/2)+4;
	
			PORTC= 0x40;
			_delay_ms(10);
			input_data=PINC & 0x07;
			if(input_data!=0) key=(input_data/2)+7;
			
			PORTC=0x80;
			_delay_ms(10);
			input_data=PINC & 0x07;
			if(input_data != 0) key=(input_data/2)+10;

			if(key<9){
				input_num++;
				key_input[input_num]=key;
			}

			if(key==11){
				input_num++;
				key_input[input_num]=key;
			}

			if((key==10)&&(input_num>0)){
				input_num--;
			}

			if(key==12){
				Answer();
			}

		}

		if(state==END){
			input_num=0;
			life=8;
		}


	}
}


		





