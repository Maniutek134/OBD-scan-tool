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

#define ILI9341_PIXEL				76800
/* Starting buffer address in RAM */
/* Offset for Layer 1 = SDRAM START ADDRESS + FRAME_BUFFER */
#define ILI9341_FRAME_BUFFER		SDRAM_START_ADR
/* Offset for Layer 2 */
#define ILI9341_FRAME_OFFSET		(uint32_t)ILI9341_PIXEL * 2



extern char bufferRx[100];
extern char bufferTx[100];
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
	
	TM_EMWIN_MemoryEnable();
	
	/* Create graph through all LCD screen */
	hGraph = GRAPH_CreateEx(0, 0, 320, 240, 0, WM_CF_SHOW, 0, GUI_ID_GRAPH0);
	
	/* Set grids and border */
	GRAPH_SetGridVis(hGraph, 1);
  GRAPH_SetBorder(hGraph, 25, 5, 5, 5);
	GRAPH_SetColor(hGraph, 0x00202020, GRAPH_CI_GRID);
	GRAPH_SetVSizeX(hGraph, 100);
	GRAPH_SetVSizeY(hGraph, 100);
	
	/* Create a curve for graph */
	hData = GRAPH_DATA_YT_Create(GUI_DARKRED, 300, 0, 0); 
	hData2 = GRAPH_DATA_YT_Create(GUI_DARKGREEN, 200, 0, 0); 
	hData3 = GRAPH_DATA_YT_Create(GUI_YELLOW, 200, 0, 0); 
	
	/* Attach curve to graph */
    GRAPH_AttachData(hGraph, hData);
    GRAPH_AttachData(hGraph, hData2);
    GRAPH_AttachData(hGraph, hData3);
	
	/* Create scale for graph */
	hScale = GRAPH_SCALE_Create(3, GUI_TA_LEFT, GRAPH_SCALE_CF_VERTICAL, 25);
	GRAPH_SCALE_SetTextColor(hScale, GUI_BLUE);
	/* Attach it to graph */
	GRAPH_AttachScale(hGraph, hScale);
	

	
	/* Change layers for LTDC, show layer 2 on LCD */
	GUI_SetBkColor(GUI_RED);
	//TM_USART_Puts(UART5, "123");

	
	while (1) {
	//TM_USART_Puts(USART1, "1");
	//Delay(1000);
		if(BluetoothGet()){
			int size=sizeof(bufferRx);
			char str[12];
			sprintf(str,"%d",size);
			BluetoothSend(str);
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

