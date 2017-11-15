#include "tm_stm32f4_usart.h"
#include <stdbool.h>

//define proper uart, USART1-internal uart/USART5-TX: PC12, RX: PD2
#define USART USART1



void Bluetooth_Init();
void BluetoothSend(char *buffer);
bool BluetoothGet(char *buffer);