#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <dispsw.h>

#include "pangea_clock.h"

void setClock();
void menuProcess();

void funcDft(UINT8 u8MenuNumber, UINT8 u8MenuValue, UINT8 u8Cmd);

extern void funcMenu0(UINT8 u8MenuNumber, UINT8 u8MenuValue, UINT8 u8Cmd);
extern void funcMenu1(UINT8 u8MenuNumber, UINT8 u8MenuValue, UINT8 u8Cmd);
extern void funcMenu5(UINT8 u8MenuNumber, UINT8 u8MenuValue, UINT8 u8Cmd);
extern void funcMenu6(UINT8 u8MenuNumber, UINT8 u8MenuValue, UINT8 u8Cmd);
extern void funcMenu7(UINT8 u8MenuNumber, UINT8 u8MenuValue, UINT8 u8Cmd);

void (*afuncptr[100])(UINT8 u8MenuNumber, UINT8 u8MenuValue, UINT8 u8Cmd)={
	funcMenu0, funcMenu1, funcDft, funcDft, funcDft, funcMenu5, funcMenu6, funcMenu7, funcDft   , funcDft,
	funcDft  , funcDft  , funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft,
	funcDft  , funcDft  , funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft,
	funcDft  , funcDft  , funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft,
	funcDft  , funcDft  , funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft,
	funcDft  , funcDft  , funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft,
	funcDft  , funcDft  , funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft,
	funcDft  , funcDft  , funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft,
	funcDft  , funcDft  , funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft,
	funcDft  , funcDft  , funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft, funcDft
};



//******************************************************************************
// main function
//******************************************************************************
int main() 
{

	//--------------------------------------
	// - configure the GPIOs to use the board
	// - start display thread
	dispsw_Start();
	//--------------------------------------

	while(1)
	{
		//--------------------------------------
		// process user inputs and update the
		// menu.
		dispsw_MenuUpdate();
		//--------------------------------------

		//--------------------------------------
		// process the menu
		menuProcess();
		//--------------------------------------

		//--------------------------------------
		// repeat everything after 50ms.
		usleep(50000);
		//--------------------------------------	
	}

	//--------------------------------------
	// stop the display from working. 
	// release CPU power.
	dispsw_Stop();
	//--------------------------------------

	return 0;
}

//******************************************************************************
// Process the menu
//******************************************************************************
void menuProcess()
{
	static UINT8 u8MenuStatus = DISPSW_MENU_STABLE;
	static UINT8 u8MenuNumber = 200;
	static UINT8 u8MenuValue  = 0;

	if (u8MenuNumber != dispsw_u8GetMenu())
	{
		u8MenuNumber = dispsw_u8GetMenu();
		u8MenuValue  = dispsw_u8GetMenuValue(u8MenuNumber);
		afuncptr[u8MenuNumber](u8MenuNumber, u8MenuValue, DISP);
	}
	else if (u8MenuValue != dispsw_u8GetMenuValue(u8MenuNumber))
	{
		u8MenuValue = dispsw_u8GetMenuValue(u8MenuNumber);
		u8MenuStatus = DISPSW_MENU_STABLE;
		afuncptr[u8MenuNumber](u8MenuNumber, u8MenuValue, DISP);
	}
	else if ((u8MenuStatus == DISPSW_MENU_STABLE)   && (dispsw_u8GetMenuState() == DISPSW_MENU_FLASHING))
	{
    	u8MenuStatus = DISPSW_MENU_FLASHING;
		afuncptr[u8MenuNumber](u8MenuNumber, u8MenuValue, FLASH);
	}
	else if ((u8MenuStatus == DISPSW_MENU_FLASHING) && (dispsw_u8GetMenuState() == DISPSW_MENU_STABLE))
	{
    	u8MenuStatus = DISPSW_MENU_STABLE;
		afuncptr[u8MenuNumber](u8MenuNumber, u8MenuValue, SET);
	}
	else
	{
		afuncptr[u8MenuNumber](u8MenuNumber, u8MenuValue, DISP);
	}
}


//******************************************************************************
// default function pointer
//******************************************************************************
void funcDft(UINT8 u8MenuNumber, UINT8 u8MenuValue, UINT8 u8Cmd)
{
	dispsw_Set(u8MenuNumber/10, u8MenuNumber%10, u8MenuValue/10, u8MenuValue%10);
}



