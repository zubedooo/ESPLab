#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "DrvPWM.h"
#include "DrvSYS.h"

int main ()
{int16_t x=0xffff;
UNLOCKREG();
DrvSYS_Open(48000000);
LOCKREG();
InitPWM();
while(1)
{PWMA->CMR0=x;
x = x - 1;
DrvSYS_Delay(5000);
}
}
