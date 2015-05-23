//#include <iostream.h>
#include <time.h>

#include "stdio.h"
#include "stdlib.h"

#include <wiringPi.h>

#include "types.h"
#include "enc.h"
#include "seg7.h"
#include "clock.h"
#include "menu.h"


void configIO(void);


int main()
{
	if (wiringPiSetup() == -1) return 1;

	configIO();

	while(1)
	{
		menu_Update ();
		seg7_Update ();
		delay(2);
	}

	return 1;

}




void configIO(void)
{
  pinMode(8,  OUTPUT);
  pinMode(9,  OUTPUT);
  pinMode(7,  OUTPUT);
  pinMode(0,  OUTPUT);
  pinMode(2,  OUTPUT);
  pinMode(3,  OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(1 , INPUT);
}

