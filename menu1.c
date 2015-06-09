#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dispsw.h>

#include "pangea_clock.h"

//******************************************************************************
// Menu1: Radio
//******************************************************************************

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

void funcMenu1(UINT8 u8MenuNumber, UINT8 u8MenuValue, UINT8 u8Cmd)
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
				switch(u8MenuValue)
				{
					case 0: // OFF
						sprintf(txt," ");
						break;
					case 1:
						sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth %s"          , CHANNEL1);
						break;
					case 2:
						sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth %s"          , CHANNEL2);
						break;
					case 3:
						sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth %s"          , CHANNEL3);
						break;
					case 4:
						sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth %s"          , CHANNEL4);
						break;
					case 5:
						sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth -playlist %s", CHANNEL5);
						break;
					case 6:
						sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth %s"          ,CHANNEL6);
						break;
					case 7:
						sprintf(txt, "nice -n-1 mplayer -ao alsa:device=bluetooth %s"          , CHANNEL7);
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
			break;
	}
}
