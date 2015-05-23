#include <time.h>
#include "stdio.h"
#include "stdlib.h"

#include <wiringPi.h>

#include "types.h"

#include "seg7.h"


UINT8 u8A;
UINT8 u8B;
UINT8 u8C;
UINT8 u8D;

UINT8 u8Ziffer0, u8Ziffer1, u8Ziffer2, u8Ziffer3;


void SetABCD(UINT8 u8Ziffer);
void SetBCD(UINT8 u8A, UINT8 u8B, UINT8 u8C, UINT8 u8D);
void latch(UINT8 u8Value);
void SetZ0toZ3(UINT8 u8Z0, UINT8 u8Z1, UINT8 u8Z2, UINT8 u8Z3);


void seg7_Set(UINT8 u8N3, UINT8 u8N2, UINT8 u8N1, UINT8 u8N0)
{
	u8Ziffer0 = u8N0;
	u8Ziffer1 = u8N1;
	u8Ziffer2 = u8N2;
	u8Ziffer3 = u8N3;
}

void seg7_Update(void)
{
	static UINT8 u8Update=0;

	if      (u8Update == 0)
	{
		SetABCD(u8Ziffer3);
		SetBCD(u8A, u8B, u8C, u8D);
		latch(0);
		SetZ0toZ3(1,0,0,0);  
		latch(1);
	}
	else if (u8Update == 1)
	{
			SetABCD(u8Ziffer2);
			SetBCD(u8A, u8B, u8C, u8D);
			latch(0);
			SetZ0toZ3(0,1,0,0);  
			latch(1);
	}
	else if (u8Update == 2)
	{
		SetABCD(u8Ziffer1);
		SetBCD(u8A, u8B, u8C, u8D);
		latch(0);
		SetZ0toZ3(0,0,1,0);  
		latch(1);
	}	
	else if (u8Update == 3)
	{
		SetABCD(u8Ziffer0);
		SetBCD(u8A, u8B, u8C, u8D);
		latch(0);
		SetZ0toZ3(0,0,0,1);  
		latch(1);
	}
	u8Update++;
	u8Update %= 4;
}


void latch(UINT8 u8Value)
{
  digitalWrite(7, u8Value);
}


void SetABCD(UINT8 u8Ziffer)
{
	u8D = (u8Ziffer>>3) & 0x01;
	u8C = (u8Ziffer>>2) & 0x01;
	u8B = (u8Ziffer>>1) & 0x01;
	u8A = (u8Ziffer   ) & 0x01;
}

void SetZ0toZ3(UINT8 u8Z0, UINT8 u8Z1, UINT8 u8Z2, UINT8 u8Z3)
{
	digitalWrite(14, u8Z3);
	digitalWrite(13, u8Z0);
	digitalWrite(12, u8Z1);
	digitalWrite(3 , u8Z2);
}

void SetBCD(UINT8 u8A, UINT8 u8B, UINT8 u8C, UINT8 u8D)
{
	digitalWrite(8, u8A);
	digitalWrite(2, u8B);
	digitalWrite(0, u8C);
	digitalWrite(9, u8D);
}
