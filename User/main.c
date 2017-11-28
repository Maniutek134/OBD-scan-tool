/**
 * Keil project template for EMWIN testing GUI_Exec function
 *
 * What should be seen:
 *   If RED LED toggles on F429-DIscovery board, GUI_Exec returns non-zero value
 *   If GREEN LED is ON, then GUI_Exec returned non-zero value FIRST time it was called
 *
 * Function TM_EMWIN_Exec is the same as GUI_Exec function.
 *
 * @author    Tilen Majerle
 * @email     tilen@majerle.eu
 * @website   http://stm32f4-discovery.com
 * @ide       Keil uVision 5
 * @conf      PLL parameters are set in "Options for Target" -> "C/C++" -> "Defines"
 * @packs     STM32F4xx Keil packs version 2.4.0 or greater required
 * @stdperiph STM32F4xx Standard peripheral drivers version 1.5.0 or greater required
 */
/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "graphic.h"

/*Button handles*/
BUTTON_Handle rpmButton,speedButton,inAirTempButton, fuelPressureButton, engineLoadButton, engineCollTempButton;
BUTTON_Handle mafAirFlowRateButton, throttlePosition, controlModuleVoltageButton, engineOilTempButton, fuelTankLvlButton, runTimeButton;

#define ILI9341_PIXEL				76800
/* Starting buffer address in RAM */
/* Offset for Layer 1 = SDRAM START ADDRESS + FRAME_BUFFER */
#define ILI9341_FRAME_BUFFER		SDRAM_START_ADR
/* Offset for Layer 2 */
#define ILI9341_FRAME_OFFSET		(uint32_t)ILI9341_PIXEL * 2



/*extern char bufferRx[100];
extern char bufferTx[100];
extern char* data;*/

int buffer_int[100];
int main(void) {
	uint8_t i = 0;
	uint32_t LastTime;
	


	/* Initialize system */
	SystemInit();
	
	/* Initialize delay */
	TM_DELAY_Init();
	
	/* Initialize leds on board */
	TM_DISCO_LedInit();
	
	/* Init EMWIN */
	TM_EMWIN_Init();
	
	/* Rotate LCD */
	TM_EMWIN_Rotate(TM_EMWIN_Rotate_270);
	
	/* Init DMA2D graphic acceleration */
	TM_DMA2DGRAPHIC_Init();
	
	
	Bluetooth_Init();
	
	
	/* 
	   Enable memory for EMWIN 
	   This features allows you to update screen very fast without flickering, because EMWIN draws on LCD layer 1 (LTDC) 
	   but layer 2 (LTDC) is shown on LCD. After all drawings from EMWIN are done, layer 1 is copied to layer 2 
	   and everything is shown to user at same time, without flickering.
	   You have to use @ref TM_EMWIN_Exec() to execute all EMWIN pending tasks in future or memory does not have effect here
	*/
	
	/* Create button with GUI_ID_OK ID number */
  rpmButton = BUTTON_CreateEx(5, 30, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON1);
	speedButton= BUTTON_CreateEx(5, 60, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON2);
	inAirTempButton = BUTTON_CreateEx(5, 90, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON3);
	fuelPressureButton=BUTTON_CreateEx(5, 120, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON4);
	engineLoadButton = BUTTON_CreateEx(5, 150, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON5);
	engineCollTempButton=BUTTON_CreateEx(5, 180, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON6);
	mafAirFlowRateButton = BUTTON_CreateEx(165, 30, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON7);
	throttlePosition= BUTTON_CreateEx(165, 60, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON8);
	controlModuleVoltageButton = BUTTON_CreateEx(165, 90, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON9);
	engineOilTempButton=BUTTON_CreateEx(165, 120, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON10);
	fuelTankLvlButton = BUTTON_CreateEx(165, 150, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON11);
	runTimeButton=BUTTON_CreateEx(165, 180, 150, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON12);
	
	BUTTON_SetText(rpmButton, "RPM");
	BUTTON_SetText(speedButton, "Speed");
	BUTTON_SetText(inAirTempButton, "Intake Temperature");
	BUTTON_SetText(fuelPressureButton, "Fuel Pressure");
	BUTTON_SetText(engineLoadButton, "Engine Load");
	BUTTON_SetText(engineCollTempButton, "Engine Coll Temperature");
	BUTTON_SetText(mafAirFlowRateButton, "Air Flow");
	BUTTON_SetText(controlModuleVoltageButton, "Voltage");
	BUTTON_SetText(engineOilTempButton, "Oil Temp");
	BUTTON_SetText(throttlePosition, "Throttle Pos");
	BUTTON_SetText(fuelTankLvlButton, "Fuel Lvl");
	BUTTON_SetText(runTimeButton, "Run Time");
	
	BUTTON_SetFont(rpmButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(speedButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(inAirTempButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(fuelPressureButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(engineLoadButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(engineCollTempButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(mafAirFlowRateButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(throttlePosition, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(controlModuleVoltageButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(engineOilTempButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(fuelTankLvlButton, &GUI_Font8x15B_ASCII);
	BUTTON_SetFont(runTimeButton, &GUI_Font8x15B_ASCII);
	
	/*welcome singh8*/
	GUI_DispStringAt("What parameter do you want to see?",70,3);
	
	
	GUI_Exec();
	
	TM_EMWIN_MemoryEnable();
	
	
	
	
	
	

	
	Command speedCommand = {.id=13,
													.name = "speed",
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
													.name = "AirTemp",
													.request = "010F\r\n",
													.response = "",
													.responseType=0,
													.units = " C"};
	
	Command fuelPressureCommand= {.id=10,
															.name = "FuelPressure",
															.request = "0109\r\n",
															.response = "",
															.responseType=0,
															.units = " kPa"};
	
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
					graphicInit(fuelPressureCommand);
					break;
				case GUI_ID_BUTTON5:
					graphicInit(engineLoadCommand);
					break;
				case GUI_ID_BUTTON6:
					graphicInit(engCollTempCommand);
					break;
				
			}
			
			if (TM_EMWIN_Exec()) {
			/* Toggle RED led if non-zero value is returned from GUI_Exec() */
			TM_DISCO_LedToggle(LED_RED);
			}
	}
	
}
		
		
		
	

void TM_DELAY_1msHandler(void) {
	/* Update touch for EMWIN */
	TM_EMWIN_UpdateTouch();
}

