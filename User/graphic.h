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
#include "calculator.h"

#include "tm_stm32f4_lcd.h"
#include "tm_stm32f4_i2c.h"
#include "tm_stm32f4_disco.h"


#define GRAPH_Delete(hObj) WM_DeleteWindow(hObj);

extern char bufferRx[100];
extern char bufferTx[100];



bool graphicInit(Command command);
void intToString(int a,char* str);

