#ifndef ENC_H_
#define ENC_H_



#define ENC_FOREWARD(x)       ((x) & 0x01)
#define ENC_BACKWARD(x)       ((x) & 0x02)
#define ENC_SWITCH(x)         ((x) & 0x04)


enum ENCODER_STATE
{
	ENC_IDLE  = 0,
	ENC_FOREW = 1,
	ENC_BACKW = 2,
	ENC_EQUAL = 3
};




UINT8 enc_u8Proc(void);





#endif
