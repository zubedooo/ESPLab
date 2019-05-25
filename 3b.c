#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvGPIO.h"
#include "Driver\DrvSYS.h"
#include "LCD_Driver.h"
void EINT1Callback()
{
print_lcd(1, "Interrupt");
}
int main()
{
char TEXT[16];
UNLOCKREG();
DrvSYS_Open(48000000);
LOCKREG();
Initial_panel();
clr_all_panel();
print_lcd(0, "Smpl_GPIO_Intr");
DrvGPIO_Open(E_GPB, 15, E_IO_INPUT);
DrvGPIO_EnableEINT1(E_IO_BOTH_EDGE, E_MODE_EDGE, EINT1Callback);
while(1){}
}
