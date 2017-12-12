#include "mainMenu.h"

/*Button handles*/
BUTTON_Handle rpmButton,speedButton,inAirTempButton, externTempButton, engineLoadButton, engineCollTempButton;
BUTTON_Handle ethanolFuelButton, engFuelRateButton, controlModVolButton, engineOilTempButton, fuelTankLvlButton, runTimeButton;

void menuInit(){

	/* 
	   Enable memory for EMWIN 
	   This features allows you to update screen very fast without flickering, because EMWIN draws on LCD layer 1 (LTDC) 
	   but layer 2 (LTDC) is shown on LCD. After all drawings from EMWIN are done, layer 1 is copied to layer 2 
	   and everything is shown to user at same time, without flickering.
	   You have to use @ref TM_EMWIN_Exec() to execute all EMWIN pending tasks in future or memory does not have effect here
	*/
	
	
	//BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX); // Sets the default skin for new widgets
	/* Create button with GUI_ID_OK ID number */
	
  rpmButton = BUTTON_CreateEx(5, 30, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON1);
	speedButton= BUTTON_CreateEx(5, 60, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON2);
	inAirTempButton = BUTTON_CreateEx(5, 90, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON3);
	externTempButton=BUTTON_CreateEx(5, 120, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON4);
	engineLoadButton = BUTTON_CreateEx(5, 150, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON5);
	engineCollTempButton=BUTTON_CreateEx(5, 180, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON6);
	ethanolFuelButton = BUTTON_CreateEx(165, 30, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON7);
	engFuelRateButton= BUTTON_CreateEx(165, 60, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON8);
	controlModVolButton = BUTTON_CreateEx(165, 90, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON9);
	engineOilTempButton=BUTTON_CreateEx(165, 120, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON10);
	fuelTankLvlButton = BUTTON_CreateEx(165, 150, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON11);
	runTimeButton=BUTTON_CreateEx(165, 180, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON12);
	
	BUTTON_SetText(rpmButton, "RPM");
	BUTTON_SetText(speedButton, "Speed");
	BUTTON_SetText(inAirTempButton, "Intake Temperature");
	BUTTON_SetText(externTempButton, "Extern Temperature");
	BUTTON_SetText(engineLoadButton, "Engine Load");
	BUTTON_SetText(engineCollTempButton, "Eng Coll Temp");
	BUTTON_SetText(ethanolFuelButton, "Ethanol fuel");
	BUTTON_SetText(controlModVolButton, "Voltage");
	BUTTON_SetText(engineOilTempButton, "Oil Temp");
	BUTTON_SetText(engFuelRateButton, "Engine Fuel Rate");
	BUTTON_SetText(fuelTankLvlButton, "Fuel Lvl");
	BUTTON_SetText(runTimeButton, "Run Time");
	
	BUTTON_SetFont(rpmButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(speedButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(inAirTempButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(externTempButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(engineLoadButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(engineCollTempButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(ethanolFuelButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(engFuelRateButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(controlModVolButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(engineOilTempButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(fuelTankLvlButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(runTimeButton, &GUI_Font8x15B_ASCII);
	
	//BUTTON_SetDefaultSkinClassic();

	
	/*welcome singh8*/
	GUI_SetFont(&GUI_Font8x12_ASCII);
	GUI_DispStringAt("What parameter do you want to see?",30,5);
	
	
	GUI_Exec();
	
	TM_EMWIN_MemoryEnable();
	
	
	Command speedCommand = {.id=13,
													.name = "Speed",
													.request = "010D\r\n",
													.response = "",
													.responseType=0,
													.units = " km/h"};
	
	Command rpmCommand = {.id=12,
												.name = "RPM",
												.request = "010C\r\n",
												.response = "",
												.responseType=1,
												.units = " rpm"};
	
	Command inAirTempCommand = {.id=15,
													.name = "Air Temp",
													.request = "010F\r\n",
													.response = "",
													.responseType=0,
													.units = " C"};
	
	Command externTempCommand= {.id=70,
															.name = "External Temp",
															.request = "0170\r\n",
															.response = "",
															.responseType=0,
															.units = " C"};
	
	Command engineLoadCommand= {.id=4,
															.name = "EngineLoad",
															.request = "0104\r\n",
															.response = "",
															.responseType=0,
															.units = " %"};
	
	Command engCollTempCommand= {.id=5,
															.name = "EngineCoolantTemp",
															.request = "0105\r\n",
															.response = "",
															.responseType=0,
															.units = " C"};
	
	Command ethanolFuelCommand = {.id=82,
																.name = "Ethanol Fuel",
																.request = "0152\r\n",
																.response = "",
																.responseType=0,
																.units = " %"};
	
	Command engFuelRateCommand = {.id=94,
																.name = "EngineFuelRate",
																.request = "015E\r\n",
																.response = "",
																.responseType=1,
																.units = " L/h"};
	
	Command controlModVolCommand = {.id=66,
																	.name = "Voltage",
																	.request = "0142\r\n",
																	.response = "",
																	.responseType=1,
																	.units = " V"};
	
	Command engineOilTempCommand= {.id=92,
																.name = "FuelPressure",
																.request = "015C\r\n",
																.response = "",
																.responseType=0,
																.units = " C"};
	
	Command fuelTankLvlCommand= {.id=47,
																.name = "FuelLvl",
																.request = "012F\r\n",
																.response = "",
																.responseType=0,
																.units = " %"};
	
	Command runTimeCommand= {.id=31,
													 .name = "RunTime",
													 .request = "011f\r\n",
													 .response = "",
													 .responseType=1,
													 .units = " min"};
	

	/*main loop*/
	while (1) {
	
		/* Check if button was pressed */
			switch(GUI_GetKey()){
				case GUI_ID_BUTTON1:
					graphicInit(rpmCommand);	
					break;
				case GUI_ID_BUTTON2:
					graphicInit(speedCommand);
					break;
				case GUI_ID_BUTTON3:
					graphicInit(inAirTempCommand);
					break;
				case GUI_ID_BUTTON4:
					graphicInit(externTempCommand);
					break;
				case GUI_ID_BUTTON5:
					graphicInit(engineLoadCommand);
					break;
				case GUI_ID_BUTTON6:
					graphicInit(engCollTempCommand);
					break;
				case GUI_ID_BUTTON7:
					graphic2Init(ethanolFuelCommand);	
					break;
				case GUI_ID_BUTTON8:
					graphicInit(engFuelRateCommand);
					break;
				case GUI_ID_BUTTON9:
					graphic2Init(controlModVolCommand);
					break;
				case GUI_ID_BUTTON10:
					graphicInit(engineOilTempCommand);
					break;
				case GUI_ID_BUTTON11:
					graphic2Init(fuelTankLvlCommand);
					break;
				case GUI_ID_BUTTON12:
					graphic2Init(runTimeCommand);
					break;
			}
			
			if (TM_EMWIN_Exec()) {
			/* Toggle RED led if non-zero value is returned from GUI_Exec() */
			TM_DISCO_LedToggle(LED_RED);
			}
	}
	
}

