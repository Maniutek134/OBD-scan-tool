#include "bluetooth.h"

char bufferRx[100];
char bufferTx[100];


void Bluetooth_Init(){
	/* Initialize UART5 at 9600 baud, TX: PC12, RX: PD2 */
	TM_USART_Init(USART, TM_USART_PinsPack_1, 38400);
	//TM_USART_Init(UART5, TM_USART_PinsPack_1, 9600);
	TM_USART_Init(USART1, TM_USART_PinsPack_1, 38400);
}

void BluetoothSend(char *buffer){
	TM_USART_Puts(USART, buffer);
}

bool BluetoothGet(char* buffer){
	if(TM_USART_Gets(USART, buffer, sizeof(bufferRx))){
		return true;
	}
	else{
	return false;
	}
}

