//#include <iostream.h>
#include <time.h>

#include "stdio.h"
#include "stdlib.h"

#include <wiringPi.h>

#include "types.h"
#include "enc.h"

#define PIN_ENCA        (15)
#define PIN_ENCB        (16)


UINT8 u8EncoderState = ENC_IDLE;
UINT8 u8SwitchD1 = 0;


UINT8 enc_u8Proc(void)
{
	UINT8 u8Action=ENC_IDLE;
	UINT8 u8Encoder=0;
	UINT8 u8Rising;
	UINT8 u8Switch;
	u8Encoder  = digitalRead(15)<<1;
	u8Encoder |= digitalRead(16);

	switch (u8EncoderState)
	{
		case ENC_IDLE:
			if      (u8Encoder == 2) u8EncoderState = ENC_FOREW;
			else if (u8Encoder == 1) u8EncoderState = ENC_BACKW;			   
			break;
		case ENC_FOREW:
			if      (u8Encoder == 3) 
			{
				u8EncoderState = ENC_EQUAL;
				u8Action = ENC_FOREW;
			}
			else if (u8Encoder == 0) u8EncoderState = ENC_IDLE;			   
			break;
		case ENC_BACKW:
			if      (u8Encoder == 3)
			{
				u8EncoderState = ENC_EQUAL;
				u8Action = ENC_BACKW;
			}
			else if (u8Encoder == 0) u8EncoderState = ENC_IDLE;			   
			break;
		case ENC_EQUAL:
			if      (u8Encoder == 0) u8EncoderState = ENC_IDLE;
			break;
	}

	u8Switch = digitalRead(1);
	u8Rising = ((u8Switch == 1) && (u8SwitchD1 == 0)) ? 1 : 0;

	u8SwitchD1 = u8Switch;
	return u8Action | (u8Rising<<2);
}

