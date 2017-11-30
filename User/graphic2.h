#include "graphic.h"

extern char bufferRx[100];
extern char bufferTx[100];


bool graphic2Init(Command command);
static void cbForegroundWin(WM_MESSAGE* pMsg);