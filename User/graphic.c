#include "graphic.h"

float scaleFactor;
int graphOffset;
char valueStr[10];


bool graphicInit(Command command){
	
	/*settings depend on command*/
	switch(command.id){
		case 4:
			scaleFactor=0.55;
			graphOffset=0;
			break;
		case 5:
			scaleFactor=1.5;
			graphOffset=40;
			break;
		case 12:
			scaleFactor=51;
			graphOffset=0;
			break;
		case 13:
			scaleFactor=1.28;
			graphOffset=0;
			break;
		case 15:
			scaleFactor=1.5;
			graphOffset=40;
			break;
		case 70:
			scaleFactor=1.5;
			graphOffset=40;
			break;
		case 92:
			scaleFactor=1.5;
			graphOffset=40;
			break;
		case 94:
			scaleFactor=14.7;
			graphOffset=0;
			break;
		
		
	}
	
	//BUTTON_SetDefaultSkinClassic(); // Sets the default skin for new widgets
	/*back button8 handle*/
	BUTTON_Handle backButton;
	
	
	/* Graph handle */
	GRAPH_Handle hGraph;
	GRAPH_DATA_Handle hData;
	GRAPH_SCALE_Handle hScale;
	
	/* Create button with GUI_ID_OK ID number */
  backButton = BUTTON_CreateEx(0, 210, 200, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON0);
	BUTTON_SetText(backButton, "BACK");
	BUTTON_SetFont(backButton, &GUI_Font8x15B_ASCII);
	GUI_Exec();
	
	/* Create graph through all LCD screen */
	hGraph = GRAPH_CreateEx(0, 0, 320, 210, 0, WM_CF_SHOW, 0, GUI_ID_GRAPH0);
	
	/* Set grids and border */
	GRAPH_SetGridVis(hGraph, 1);
	GRAPH_SetBorder(hGraph, 28, 2, 2, 2);
	GRAPH_SetColor(hGraph, 0x00202020, GRAPH_CI_GRID);
	GRAPH_SetVSizeX(hGraph, 100);
	GRAPH_SetVSizeY(hGraph, 100);
	
	
	/* Create a curve for graph */
	hData = GRAPH_DATA_YT_Create(GUI_DARKRED, 300, 0, 0); 
	
	
	/* Attach curve to graph */
  GRAPH_AttachData(hGraph, hData);
	
	/* Create scale for graph */
	hScale = GRAPH_SCALE_Create(3, GUI_TA_LEFT, GRAPH_SCALE_CF_VERTICAL, 25);
	GRAPH_SCALE_SetFactor(hScale, scaleFactor );
	GRAPH_SCALE_SetTextColor(hScale, GUI_BLUE);
	GRAPH_SCALE_SetOff(hScale, graphOffset);
	
	/* Attach it to graph */
	GRAPH_AttachScale(hGraph, hScale);
	
	/*set font*/
	GUI_SetFont(&GUI_Font8x16x1x2);
	
	/* Change layers for LTDC, show layer 2 on LCD */
	GUI_SetBkColor(GUI_BLACK);
	
	BluetoothSend(command.request);
	while(1){
		
		if(GUI_GetKey()==GUI_ID_BUTTON0){
				GRAPH_Delete(hGraph);
				BUTTON_Delete(backButton);
				GUI_ClearRect(0, 0, 320, 240);
				
				/*welcome singh8*/
				GUI_SetFont(&GUI_Font8x12_ASCII);
				GUI_DispStringAt("What parameter do you want to see?",30,5);
				break;
		}
		
		
		if(BluetoothGet(bufferRx)){
			
			TM_USART_Puts(USART1, bufferRx);
			command.response=bufferRx;
			int value = calculateValue(command);
			
			intToString(value,valueStr);																			
			GUI_ClearRect(200, 200, 320, 240);																//refreshing screen
			GUI_DispStringAt(strcat(valueStr, command.units),230,212);        //adding stringvalue and proper unit  strcat(valueStr, command.units)
			
			GRAPH_DATA_YT_AddValue(hData,value/scaleFactor+graphOffset);			//adding new sample to curve

		}
			GUI_Delay(500);
			BluetoothSend(command.request); 
			
		
		if (TM_EMWIN_Exec()) {
			/* Toggle RED led if non-zero value is returned from GUI_Exec() */
			TM_DISCO_LedToggle(LED_RED);
			}
	}

}

void intToString(int a,char* str){
	sprintf(str, "%d",a); 
}


