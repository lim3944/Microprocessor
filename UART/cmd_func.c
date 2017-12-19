#include <stdio.h>                      /* Standard I/O .h-file               */
#include <ctype.h>                      /* Character functions                */
#include <string.h>                     /* String and memory functions        */

#include <avr/io.h>
#include "cmdline.h"
#include "cmd_func.h"




//*****************************************************************************
//
// The buffer that holds the command line.
//
//*****************************************************************************
char g_pcCmdBuf[CMD_BUF_SIZE];


/* Command function prototypes */
int cmd_help    (int argc, char *argv[]);
int cmd_on      (int argc, char *argv[]);
int cmd_off     (int argc, char *argv[]);
int cmd_inv     (int argc, char *argv[]);
int cmd_allon   (int argc, char *argv[]);
int cmd_alloff  (int argc, char *argv[]);
int cmd_shift   (int argc, char *argv[]);





//*****************************************************************************
//
// This is the table that holds the command names, implementing functions, and
// brief description.
//
//*****************************************************************************
tCmdLineEntry g_psCmdTable[] =
{
    { "help",     cmd_help,     "Display list of commands" },
    { "h",        cmd_help,     "alias for help" },
    { "?",        cmd_help,     "alias for help" },
    { "on",       cmd_on,       "LED ON" },		
    { "off",      cmd_off,      "LED OFF" },
    { "inv",      cmd_inv,      "LED Toggle" },
    { "allon",	  cmd_allon,    "LED ALL On" },
    { "alloff",	  cmd_alloff,   "LED ALL Off" },
    { "shift",	  cmd_shift,    "LED Shift On/Off" },	
    { 0, 0, 0 }
};


unsigned long
atoul(char *str)
{
	unsigned long ret = 0;
	int multi;
	char c;

	if (!strncmp(str, "0X", 2) || !strncmp(str, "0x", 2))
	{
		str += 2;	// skip "0x"
		multi = 16;
	} else
		multi = 10;

	while (c = *str++)
	{
		if (c >= '0' && c <= '9')
			ret = ret * multi + c - '0';
		else if (c >= 'a' && c <= 'f')
			ret = ret * multi + c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			ret = ret * multi + c - 'A' + 10;
		else
			return ret;
	}
	return ret;
}



int cmd_inv      (int argc, char *argv[]){
	
  unsigned char led_num = 0;
	
	
  if(argc != 2 )
  {
     printf(" inv  [num]\n\r");
     return 0;
  }	
	
  led_num = (unsigned char)(atoul(argv[1]));
	

	
  //
  // Return success.
  //
  return(0);	
	
};



int cmd_on(int argc, char *argv[]) {

  unsigned char led_num = 0;
	
	
  if(argc != 2 )
  {
     printf(" on  [num]\n\r");
     return 0;
  }
	
  led_num = (unsigned char)(atoul(argv[1]));


  PORTA = PORTA | (0x01 << led_num);

	
  //
  // Return success.
  //
  return(0);	
	
}


int cmd_off(int argc, char *argv[]) {

  unsigned char led_num = 0;
		
  if(argc != 2 )
  {
     printf(" off  [num]\n\r");
     return 0;
  }
	
  led_num = (unsigned char)(atoul(argv[1]));

  //Fixme	
  PORTA = PORTA & ~(0x01 << led_num);
	
  //
  // Return success.
  //
  return(0);	
	
}

int cmd_allon(int argc, char *argv[]) {
	
   if(argc != 1 )
  {
     printf(" allon\n\r");
     return 0;
  }
	
  //Fixme
   PORTA = 0xFF;
	
  //
  // Return success.
  //
  return(0);	
	
}


int cmd_alloff(int argc, char *argv[]) {

	
  if(argc != 1 )
  {
    printf(" allon\n\r");
    return 0;
  }
	  
  //Fixme 
  PORTA = 0x00;

	
  //
  // Return success.
  //
  return(0);	
	
}

int cmd_shift(int argc, char *argv[]) {

	

  //
  // Return success.
  //
  return(0);	  

	
}

/*-----------------------------------------------------------------------------
 *        Display Command Syntax help
 *----------------------------------------------------------------------------*/
//*****************************************************************************
//
// This function implements the "help" command.  It prints a simple list of the
// available commands with a brief description.
//
//*****************************************************************************
int cmd_help(int argc, char *argv[]){
	
    tCmdLineEntry *psEntry;

    //
    // Print some header text.
    //
    printf("\nAvailable commands\n\r");
    printf("------------------\n\r");

    //
    // Point at the beginning of the command table.
    //
    psEntry = &g_psCmdTable[0];

    //
    // Enter a loop to read each entry from the command table.  The end of the
    // table has been reached when the command name is NULL.
    //
    while(psEntry->pcCmd)
    {
        //
        // Print the command name and the brief description.
        //
        printf("%6s: %s\n\r", psEntry->pcCmd, psEntry->pcHelp);

        //
        // Advance to the next entry in the table.
        //
        psEntry++;
    }

    //
    // Return success.
    //
    return(0);
}
