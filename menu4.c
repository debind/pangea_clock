#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dispsw.h>

#include "pangea_clock.h"

//******************************************************************************
// Menu4: Raffael
//******************************************************************************


void funcMenu4(UINT8 u8MenuNumber, UINT8 u8MenuValue, UINT8 u8Cmd)
{
	char txt[500]={0};
	int pid;
	switch(u8Cmd)
	{
		case DISP:
		case FLASH:
			dispsw_Set(u8MenuNumber/10, u8MenuNumber%10, u8MenuValue/10, u8MenuValue%10);
			break;
		case SET:
			pid = fork();
			if (pid == 0)
			{
				sprintf(txt, "/home/pi/musik/playmusic4 %d", u8MenuValue);
				system(txt);
				exit (1);
			}
			break;
	}
}
