#include<avr/io.h>
#include<util/delay.h>

#define LCD_CTRL PORTG
#define LCD_DATA PORTA
#define LCD_RS 0x01
#define LCD_RW 0x02
#define LCD_E 0x04

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

void InitLcd(void){
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

void Locata(int x,int y){
	unsigned char RamAddr;

	if(x==0) RamAddr=0x80+y;
	else RamAddr=0xC0+y;
	sendLCDcommand(RamAddr);
}
void LCDShift(chardir) {
	unsigned char LCD_shift;
	if(dir==LEFT)LCD_shift=0x18; 
	else if(dir==RIGHT) LCD_shift=0x1C; 
	sendLCDcommand(LCD_shift);
}

int main(){
	DDRA=0xFF;
	DDRG=0xFF;
	PORTA=0x00;
	PORTG=0x00;

	InitLcd();

	DispString("Happy Day");
	Locata(1,4);
	DispString("Welcome!");
	while(1);
}
