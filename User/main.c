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
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_lcd.h"
#include "tm_stm32f4_i2c.h"
//#include "tm_stm32f4_usart.h"
//#include "command.h"
#include "calculator.h"

#include "stdio.h"
#include "tm_stm32f4_dma2d_graphic.h"
#include "tm_stm32f4_emwin.h"
#include "GUI.h"
#include "bluetooth.h"
#include "PROGBAR.h"
#include "BUTTON.h"
#include "GRAPH.h"
#include "DIALOG.h"
#include "math.h"

/* Graph handle */
GRAPH_Handle hGraph;
GRAPH_DATA_Handle hData;
GRAPH_DATA_Handle hData2;
GRAPH_DATA_Handle hData3;
GRAPH_SCALE_Handle hScale;
BUTTON_Handle hButton;

#define ILI9341_PIXEL				76800
/* Starting buffer address in RAM */
/* Offset for Layer 1 = SDRAM START ADDRESS + FRAME_BUFFER */
#define ILI9341_FRAME_BUFFER		SDRAM_START_ADR
/* Offset for Layer 2 */
#define ILI9341_FRAME_OFFSET		(uint32_t)ILI9341_PIXEL * 2



extern char bufferRx[100];
extern char bufferTx[100];
extern char* data;
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
	/* Init ILI9341 with LTDC on STM32F429 Discovery board */
	//TM_ILI9341_Init();
	
	/* Initialize UART5 at 9600 baud, TX: PC12, RX: PD2 */
	//TM_USART_Init(USART1, TM_USART_PinsPack_2, 9600);
	//TM_USART_Init(UART5, TM_USART_PinsPack_1, 9600);
	
	/* 
	   Enable memory for EMWIN 
	   This features allows you to update screen very fast without flickering, because EMWIN draws on LCD layer 1 (LTDC) 
	   but layer 2 (LTDC) is shown on LCD. After all drawings from EMWIN are done, layer 1 is copied to layer 2 
	   and everything is shown to user at same time, without flickering.
	   You have to use @ref TM_EMWIN_Exec() to execute all EMWIN pending tasks in future or memory does not have effect here
	*/
	
	/* Create button with GUI_ID_OK ID number */
  hButton = BUTTON_CreateEx(10, 50, 219, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON0);
	BUTTON_SetText(hButton, "Click me to continue..");
	BUTTON_SetFont(hButton, &GUI_Font8x15B_ASCII);
	GUI_Exec();
	
	TM_EMWIN_MemoryEnable();
	
	
	
	

	
	Command speedCommand = {.id=13,
													.name = "speed",
													.request = "010D\r\n",
													.answer = ""};
	Command rpmCommand = {.id=12,
												.name = "RPM",
												.request = "010C\r\n",
												.answer = ""};
	

	
	while (1) {
	//TM_USART_Puts(USART1, "1");
	//Delay(1000);
		/* Check if button was pressed */
    if (GUI_GetKey() == GUI_ID_BUTTON0) {
			
      BluetoothSend(rpmCommand.request);
			
			while(1){
				if(BluetoothGet(bufferRx)){
					rpmCommand.answer=bufferRx;
					int value=calculateValue(rpmCommand);
					char str[10];
					char str2[2]="\r\n";
					sprintf(str,"%d",value);
					strcat(str,str2);
					BluetoothSend(str);
					GUI_DispStringAt(str, 2, 3);
					GUI_Exec();
				break;
			}
		}
		
		
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

