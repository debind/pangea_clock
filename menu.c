//#include <iostream.h>
#include <time.h>

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

#include <wiringPi.h>

#include "types.h"
#include "seg7.h"
#include "menu.h"
#include "enc.h"
#include "clock.h"

enum eDispState
{
	DISP_CLOCK = 0,
	DISP_RADIO,
	DISP_MENU2,
	DISP_MENU3,
	DISP_MENU4,
	DISP_MENU5,
};

enum eMenuState
{
	MENU_INACTIVE = 0,
	MENU_ACTIVE
};

#define FLASH_COUNTER (500)

UINT8 u8DispState = DISP_CLOCK;
UINT8 u8MenuState = MENU_ACTIVE;

UINT8 u8RadioStation = 0;
UINT8 u8Menu2 = 1;
UINT8 u8Menu3 = 0;
UINT8 u8Menu4 = 0;
UINT8 u8Menu5 = 0;

void SwitchRadioOn(UINT8 u8RadioStation);
void SwitchRadioOff();
void SwitchWlanOn();
void SwitchWlanOff();

void menu_Update()
{
	UINT8 u8Action;
	static UINT16 u16Count=0;

	u16Count++;

	//-----------------------------------
	// get new encoder values
	u8Action = enc_u8Proc();
	//-----------------------------------

	//-----------------------------------
	// Display statemachine
	switch(u8DispState)
	{
		//-----------------------------------
		// clock mode
		case DISP_CLOCK:
			if (ENC_FOREWARD(u8Action))
			{
				u8DispState = DISP_RADIO;
			}
			else if (ENC_BACKWARD(u8Action))
			{
				u8DispState = DISP_MENU5;
			}
			else
			{
				clock_Update();
			}
			break;
		//-----------------------------------
		// radio mode
		case DISP_RADIO:
			//-----------------------------------
			// RADIO MENU IS ACTIVE
			if (u8MenuState == MENU_ACTIVE)
			{
				if (ENC_SWITCH(u8Action))        u8MenuState = MENU_INACTIVE;
				else if (ENC_FOREWARD(u8Action)) u8DispState = DISP_MENU2;
				else if (ENC_BACKWARD(u8Action)) u8DispState = DISP_CLOCK;
				seg7_Set(u8DispState,15,(u8RadioStation%100)/10,u8RadioStation%10);
			}
			//-----------------------------------
			// RADIO MENU IS IN SELECTION MODE
			else
			{
				if (ENC_SWITCH(u8Action)) 
				{
					u8MenuState = MENU_ACTIVE;
					if (u8RadioStation == 0) SwitchRadioOff();
					else                     SwitchRadioOn(u8RadioStation);
				}
				else if (ENC_FOREWARD(u8Action)) 
				{
					u8RadioStation++;
					if (u8RadioStation > 99) u8RadioStation = 0;
				}
				if (ENC_BACKWARD(u8Action)) 
				{
					u8RadioStation--;
					if (u8RadioStation > 99) u8RadioStation = 0;
				} 

				if (u16Count < (FLASH_COUNTER/2)) seg7_Set(u8DispState,15,(u8RadioStation%100)/10,u8RadioStation%10);
				else seg7_Set(u8DispState,15,15,15);
			}

			u16Count++;
			if (u16Count > FLASH_COUNTER) u16Count = 0;
			break;
		case DISP_MENU2:
			//-----------------------------------
			// MENU2 IS ACTIVE
			if (u8MenuState == MENU_ACTIVE)
			{
				if (ENC_SWITCH(u8Action))        u8MenuState = MENU_INACTIVE;
				else if (ENC_FOREWARD(u8Action)) u8DispState = DISP_MENU3;
				else if (ENC_BACKWARD(u8Action)) u8DispState = DISP_RADIO;

				seg7_Set(u8DispState,15,(u8Menu2%100)/10,u8Menu2%10);
			}
			//-----------------------------------
			// MENU2 IS IN SELECTION MODE
			else
			{
				if (ENC_SWITCH(u8Action)) 
				{
					u8MenuState = MENU_ACTIVE;
					if (u8Menu2 == 0) SwitchWlanOff();
					else              SwitchWlanOn();
				}
				else if (ENC_FOREWARD(u8Action)) 
				{
					u8Menu2++;
					if (u8Menu2 > 1) u8Menu2 = 0;

				}
				else if (ENC_BACKWARD(u8Action)) 
				{
					u8Menu2--;
					if (u8Menu2 > 1) u8Menu2 = 1;

				} 

				if (u16Count < (FLASH_COUNTER/2)) seg7_Set(u8DispState,15,(u8Menu2%100)/10,u8Menu2%10);
				else seg7_Set(u8DispState,15,15,15);
			}

			u16Count++;
			if (u16Count > FLASH_COUNTER) u16Count = 0;
			break;
		case DISP_MENU3:
			//-----------------------------------
			// MENU3 IS ACTIVE
			if (u8MenuState == MENU_ACTIVE)
			{
				if (ENC_SWITCH(u8Action))        u8MenuState = MENU_INACTIVE;
				else if (ENC_FOREWARD(u8Action)) u8DispState = DISP_MENU4;
				else if (ENC_BACKWARD(u8Action)) u8DispState = DISP_MENU2;

				seg7_Set(u8DispState,15,(u8Menu3%100)/10,u8Menu3%10);
			}
			//-----------------------------------
			// MENU3 IS IN SELECTION MODE
			else
			{
				if (ENC_SWITCH(u8Action)) 
				{
					u8MenuState = MENU_ACTIVE;
				}
				if (ENC_FOREWARD(u8Action)) 
				{
					u8Menu3++;
					if (u8Menu3 > 99) u8Menu3 = 0;
				}
				if (ENC_BACKWARD(u8Action)) 
				{
					u8Menu3--;
					if (u8Menu3 > 99) u8Menu3 = 99;
				} 

				if (u16Count < (FLASH_COUNTER/2)) seg7_Set(u8DispState,15,(u8Menu3%100)/10,u8Menu3%10);
				else seg7_Set(u8DispState,15,15,15);
			}
			u16Count++;
			if (u16Count > FLASH_COUNTER) u16Count = 0;
			break;
		case DISP_MENU4:
			//-----------------------------------
			// MENU4 IS ACTIVE
			if (u8MenuState == MENU_ACTIVE)
			{
				if (ENC_SWITCH(u8Action))        u8MenuState = MENU_INACTIVE;
				else if (ENC_FOREWARD(u8Action)) u8DispState = DISP_MENU5;
				else if (ENC_BACKWARD(u8Action)) u8DispState = DISP_MENU3;

				seg7_Set(u8DispState,15,(u8Menu4%100)/10,u8Menu4%10);
			}
			//-----------------------------------
			// MENU4 IS IN SELECTION MODE
			else
			{
				if (ENC_SWITCH(u8Action)) 
				{
					u8MenuState = MENU_ACTIVE;
				}
				if (ENC_FOREWARD(u8Action)) 
				{
					u8Menu4++;
					if (u8Menu4 > 99) u8Menu4 = 0;
				}
				if (ENC_BACKWARD(u8Action)) 
				{
					u8Menu4--;
					if (u8Menu4 > 99) u8Menu4 = 99;
				} 

				if (u16Count < (FLASH_COUNTER/2)) seg7_Set(u8DispState,15,(u8Menu4%100)/10,u8Menu4%10);
				else seg7_Set(u8DispState,15,15,15);
			}
			u16Count++;
			if (u16Count > FLASH_COUNTER) u16Count = 0;
			break;
		case DISP_MENU5:
			//-----------------------------------
			// MENU5 IS ACTIVE
			if (u8MenuState == MENU_ACTIVE)
			{
				if (ENC_SWITCH(u8Action))        u8MenuState = MENU_INACTIVE;
				else if (ENC_FOREWARD(u8Action)) u8DispState = DISP_CLOCK;
				else if (ENC_BACKWARD(u8Action)) u8DispState = DISP_MENU4;

				seg7_Set(u8DispState,15,(u8Menu5%100)/10,u8Menu5%10);
			}
			//-----------------------------------
			// MENU5 IS IN SELECTION MODE
			else
			{
				if (ENC_SWITCH(u8Action)) 
				{
					u8MenuState = MENU_ACTIVE;
				}
				if (ENC_FOREWARD(u8Action)) 
				{
					u8Menu5++;
					if (u8Menu5 > 99) u8Menu5 = 0;
				}
				if (ENC_BACKWARD(u8Action)) 
				{
					u8Menu5--;
					if (u8Menu5 > 99) u8Menu5 = 99;
				} 

				if (u16Count < (FLASH_COUNTER/2)) seg7_Set(u8DispState,15,(u8Menu5%100)/10,u8Menu5%10);
				else seg7_Set(u8DispState,15,15,15);
			}
			u16Count++;
			if (u16Count > FLASH_COUNTER) u16Count = 0;
			break;
		default:
			break;
	}
	//-----------------------------------

	return;

}

//-----------------------------------
// Switch Wlan On/Off
//-----------------------------------
void SwitchWlanOn()
{
	int pid;
	pid = fork();
	if (pid == 0)
	{
		system("sudo /home/pi/start_wlan");
		exit(0);
	}
}

void SwitchWlanOff()
{
	int pid;
	pid = fork();
	if (pid == 0)
	{
		system("sudo /home/pi/stop_wlan");
		exit(0);
	}
}

//-----------------------------------
// Turn the radio on
//-----------------------------------
#define CHANNEL1  "http://stream.dradio.de/7/728/142684/v1/gnl.akacast.akamaistream.net/dradio_mp3_dwissen_m"
#define CHANNEL2  "http://stream.dradio.de/7/249/142684/v1/gnl.akacast.akamaistream.net/dradio_mp3_dlf_m"
#define CHANNEL3  "http://217.151.152.245:80/bigfm-mp3-96"
#define CHANNEL4  "http://toronto.etn.fm:8230"   
#define CHANNEL5  "http://abc.net.au/res/streaming/audio/mp3/triplej.pls"
#define CHANNEL6  "http://energyradio.de/berlin"
#define CHANNEL7  "http://edge.live.mp3.mdn.newmedia.nacamar.net/klassikradio128/livestream.mp3"
#define CHANNEL8  "http://mp3-live.swr.de/swr1bw_m.m3u"
#define CHANNEL9  "http://mp3-live.swr.de/swr2_m.m3u"
#define CHANNEL10 "http://mp3-live.swr3.de/swr3_m.m3u"
#define CHANNEL11 "http://mp3-live.dasding.de/dasding_m.m3u"
#define CHANNEL12 "http://mp3-live.dasding.de/dasdingraka01_m.m3u"
#define CHANNEL13 "http://mp3-live.dasding.de/dasdingraka02_m.m3u"
#define CHANNEL14 "http://mp3-live.dasding.de/dasdingraka03_m.m3u"

void SwitchRadioOn(UINT8 u8RadioStation)
{
	char txt[500]={0};
	int pid;
	pid = fork();
	if (pid == 0)
	{
		switch(u8RadioStation)
		{
			case 1:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth %s", CHANNEL1);
				break;
			case 2:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth %s", CHANNEL2);
				break;
			case 3:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth %s", CHANNEL3);
				break;
			case 4:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth %s", CHANNEL4);
				break;
			case 5:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth -playlist %s", CHANNEL5);
				break;
			case 6:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth %s", CHANNEL6);
				break;
			case 7:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth %s", CHANNEL7);
				break;
			case 8:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth -playlist %s", CHANNEL8);
				break;
			case 9:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth -playlist %s", CHANNEL9);
				break;
			case 10:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth -playlist %s", CHANNEL10);
				break;
			case 11:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth -playlist %s", CHANNEL11);
				break;
			case 12:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth -playlist %s", CHANNEL12);
				break;
			case 13:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth -playlist %s", CHANNEL12);
				break;
			case 14:
				sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth -playlist %s", CHANNEL12);
				break;
		}
		system("nice -n-2 killall mplayer");
		system(txt);
		exit (1);
	}
}


//-----------------------------------
// Turn the radio on
//-----------------------------------
void SwitchRadioOff()
{
	int pid;
	pid = fork();
	if (pid == 0)
	{
		printf("killall running\n");
		system("killall mplayer");
		printf("killall exiting\n");
		exit (1);
	}
}


	
