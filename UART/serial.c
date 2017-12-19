/*-----------------------------------------------------------------------------
 *      RL-ARM
 *-----------------------------------------------------------------------------
 *      Name:    Serial.c
 *      Purpose: Serial Input Output for STmicroelectronics STM32F4xx
 *-----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2011 KEIL - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "serial.h"
#include <avr/io.h>

volatile char rData;
//-----------------------------------------------------------------------------------
//UART를 통해 printf, scanf 함수를 사용하기 위한 구문
//-----------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
//UART를 통해 printf, scanf 함수를 사용하기 위한 함수
//-----------------------------------------------------------------------------------
int TxChar(char data, FILE * stream)
{
    while(!(UCSR0A & (1 << UDRE0)));//저 비트가 인지 0인지 확인
    UDR0 = data;
    return 0;
}

char RxChar(FILE * stream)
{
 while((UCSR0A & 0x80) == 0x00);  // 전송된 데이터가 있는지 확인 (폴링방식)
 return UDR0;
}


/*-----------------------------------------------------------------------------
 *       SER_Init:  Initialize Serial Interface
 *----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
  UART1 Config
 *----------------------------------------------------------------------------*/
void SER_Init(void)
{

  UBRR0H = 0;
  UBRR0L = 95;
  UCSR0B = 0x18;
  //SREG  |= 0x80;
  	
}
/*-----------------------------------------------------------------------------
 *       SER_PutChar:  Write a character to Serial Port
 *----------------------------------------------------------------------------*/
char SER_PutChar (char ch) {
	
    while(!(UCSR0A & (1 << UDRE0)));
     UDR0 = ch;

  return (ch);
}


/*-----------------------------------------------------------------------------
 *       SER_GetChar:  Read a character from Serial Port
 *----------------------------------------------------------------------------*/
char SER_GetChar (void) {

 while((UCSR0A & 0x80) == 0x00);  // 전송된 데이터가 있는지 확인 
 return UDR0;
}


/*-----------------------------------------------------------------------------
 *       SER_PutChar:  Write a character to Serial Port
 *----------------------------------------------------------------------------*/
int UARTwrite(const char *pcBuf, uint32_t ui32Len)
{

    unsigned int uIdx;


    //
    // Send the characters
    //
    for(uIdx = 0; uIdx < ui32Len; uIdx++)
    {
        //
        // If the character to the UART is \n, then add a \r before it so that
        // \n is translated to \n\r in the output.
        //
        if(pcBuf[uIdx] == '\n')
        {
            SER_PutChar('\r');
        }

        //
        // Send the character to the UART output.
        //
        SER_PutChar(pcBuf[uIdx]);
    }

    //
    // Return the number of characters written.
    //
    return(uIdx);
}

/*-----------------------------------------------------------------------------
 *       SER_PutChar:  Write a character to Serial Port
 *----------------------------------------------------------------------------*/

int UARTgets(char *pcBuf, uint32_t ui32Len)
{

    uint32_t ui32Count = 0;
    char cChar;
    static int8_t bLastWasCR = 0;


    //
    // Adjust the length back by 1 to leave space for the trailing
    // null terminator.
    //
    ui32Len--;

    //
    // Process characters until a newline is received.
    //
    while(1)
    {
        //
        // Read the next character from the console.
        //
#if 0
	while(rData == 0x00)
	{
           cChar = rData;
        }

        rData = 0x00;
#else
        cChar = SER_GetChar();

#endif			


        //
        // See if the backspace key was pressed.
        //
        if(cChar == '\b')
        {
            //
            // If there are any characters already in the buffer, then delete
            // the last.
            //
            if(ui32Count)
            {
                //
                // Rub out the previous character.
                //
                UARTwrite("\b \b", 3);

                //
                // Decrement the number of characters in the buffer.
                //
                ui32Count--;
            }

            //
            // Skip ahead to read the next character.
            //
            continue;
        }

        //
        // If this character is LF and last was CR, then just gobble up the
        // character because the EOL processing was taken care of with the CR.
        //
        if((cChar == '\n') && bLastWasCR)
        {
            bLastWasCR = 0;
            continue;
        }

        //
        // See if a newline or escape character was received.
        //
        if((cChar == '\r') || (cChar == '\n') || (cChar == 0x1b))
        {
            //
            // If the character is a CR, then it may be followed by a LF which
            // should be paired with the CR.  So remember that a CR was
            // received.
            //
            if(cChar == '\r')
            {
                bLastWasCR = 1;
            }

            //
            // Stop processing the input and end the line.
            //
            break;
        }

        //
        // Process the received character as long as we are not at the end of
        // the buffer.  If the end of the buffer has been reached then all
        // additional characters are ignored until a newline is received.
        //
        if(ui32Count < ui32Len)
        {
            //
            // Store the character in the caller supplied buffer.
            //
            pcBuf[ui32Count] = cChar;

            //
            // Increment the count of characters received.
            //
            ui32Count++;

            //
            // Reflect the character back to the user.
            //
            SER_PutChar(cChar);
        }
    }

    //
    // Add a null termination to the string.
    //
    pcBuf[ui32Count] = 0;

    //
    // Send a CRLF pair to the terminal to end the line.
    //
    UARTwrite("\r\n", 2);

    //
    // Return the count of int8_ts in the buffer, not counting the trailing 0.
    //
    return(ui32Count);
}


/*-----------------------------------------------------------------------------
 * end of file
 *----------------------------------------------------------------------------*/
