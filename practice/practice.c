#include<avr/io.h>
#include<inttypes.h>
#include<util/delay.h>

int main(){
	DDRA=0xFF;//define the direction of port A

	while(1){
		PORTA=0x00;
		_delay_ms(1000);
		PORTA=0xFF;
		_delay_ms(1000);
	}
	return 0;
}
