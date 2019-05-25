#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"
// External Interrupt Handler (INT button to trigger GPB15)
void EINT1Callback(void)
{
DrvGPIO_Open(E_GPC, 12, E_IO_OUTPUT);
DrvGPIO_ClrBit(E_GPC, 12);
DrvSYS_Delay(100000);
DrvGPIO_SetBit(E_GPC, 12);
DrvSYS_Delay(100000);
}
void EINT0Callback(void)
{
DrvGPIO_Open(E_GPA, 12, E_IO_OUTPUT);
DrvGPIO_ClrBit(E_GPA, 12);
DrvSYS_Delay(100000);
DrvGPIO_SetBit(E_GPA, 12);
DrvSYS_Delay(100000);
}
int main (void)
{
UNLOCKREG();
DrvSYS_SetOscCtrl(E_SYS_XTL12M, 1);
DrvSYS_Delay(5000);
DrvSYS_SelectHCLKSource(0);
LOCKREG();
DrvGPIO_Open(E_GPA, 12, E_IO_OUTPUT);
DrvGPIO_Open(E_GPC, 12, E_IO_OUTPUT);
DrvGPIO_Open(E_GPA, 12, E_IO_INPUT);
DrvGPIO_Open(E_GPC, 12, E_IO_INPUT);
DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE, E_MODE_EDGE, EINT1Callback);
DrvGPIO_EnableEINT0(E_IO_BOTH_EDGE, E_MODE_EDGE, EINT0Callback);
while(1) {}
}
