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
//#include "stm32f4xx.h"
/* Include my libraries here */
//#include "defines.h"
//#include "tm_stm32f4_delay.h"
//#include "graphic2.h"
#include "mainMenu.h"
//#include "test.h"



#define ILI9341_PIXEL				76800
/* Starting buffer address in RAM */
/* Offset for Layer 1 = SDRAM START ADDRESS + FRAME_BUFFER */
#define ILI9341_FRAME_BUFFER		SDRAM_START_ADR
/* Offset for Layer 2 */
#define ILI9341_FRAME_OFFSET		(uint32_t)ILI9341_PIXEL * 2



int main(void) {
	//uint8_t i = 0;
	//uint32_t LastTime;
	


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
	
	menuInit();
	//MainTask();
	
}
		
		
		
	

void TM_DELAY_1msHandler(void) {
	/* Update touch for EMWIN */
	TM_EMWIN_UpdateTouch();
}