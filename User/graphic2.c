#include "graphic2.h"



extern char valueStr[10];
char *commandName;
bool graphic2Init(Command command){

	
	/*back button8 handle*/
	BUTTON_Handle backButton;
	/*window handle*/
	GUI_HWIN hWnd;
	
	/*creating new window*/
	hWnd = WM_CreateWindow(0, 0, 320, 210, WM_CF_SHOW, cbForegroundWin, 0);

	/*creating a title singh*/
	commandName=command.name;
	
	/* Create button with GUI_ID_OK ID number */
  backButton = BUTTON_CreateEx(0, 210, 320, 30, 0, WM_CF_SHOW, 0, GUI_ID_BUTTON0);
	BUTTON_SetText(backButton, "BACK");
	BUTTON_SetFont(backButton, &GUI_Font8x15B_ASCII);
	GUI_Exec();
	
	while(1){
		
		if(GUI_GetKey()==GUI_ID_BUTTON0){
				//GRAPH_Delete(hGraph);
				WM_DeleteWindow(hWnd);
				BUTTON_Delete(backButton);
				GUI_ClearRect(0, 0, 320, 240);
				
				/*welcome singh8*/
				GUI_SetFont(&GUI_Font8x12_ASCII);
				GUI_DispStringAt("What parameter do you want to see?",30,5);
				break;
		}
		
		
		if(BluetoothGet(bufferRx)){
			TM_USART_Puts(USART1,bufferRx);
			command.response=bufferRx;
			int value = calculateValue(command);
			
			intToString(value,valueStr);																			
			strcat(valueStr, command.units);      //adding stringvalue and proper unit  strcat(valueStr, command.units)
			WM_Paint(hWnd);		                          //callign callback for screen

		}
			GUI_Delay(500);
			BluetoothSend(command.request); 
			
		
		if (TM_EMWIN_Exec()) {
			/* Toggle RED led if non-zero value is returned from GUI_Exec() */
			TM_DISCO_LedToggle(LED_RED);
			}
	}

}

	static void cbForegroundWin(WM_MESSAGE* pMsg) {
		switch (pMsg->MsgId) {
			case WM_PAINT:
				GUI_SetBkColor(GUI_BLACK);
				GUI_SetFont(&GUI_Font8x16x3x3);
				GUI_Clear();
				GUI_RECT rClient;
				GUI_GetClientRect(&rClient);
				GUI_DispStringInRect(valueStr, &rClient, GUI_TA_HCENTER | GUI_TA_VCENTER);
				GUI_DispStringInRect(commandName, &rClient, GUI_TA_HCENTER);
				//GUI_DispStringAt(valueStrOnScr,200,100);
			
			break;
			default:
		WM_DefaultProc(pMsg);
 }
		}



	
	



