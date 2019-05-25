/*Instructions:
1. Copy paste InitPWM from:
Sample->NUC1xx..->Sample ADC PWM
2. Rename to InitPWM_A()
*/
#include <stdio.h>
#include "NUC1xx.h"
#include "Driver\DrvSYS.h"
#include "DrvPWM.h"
#include "DrvADC.h"
#include "LCD_Driver.h"

void InitPWM_A()
{
SYS->GPAMFP.PWM0_AD13=1; // Enable PWM0 multi-function pin
SYSCLK->CLKSEL1.PWM01_S = 0; // Select 12Mhz for PWM clock source
SYSCLK->APBCLK.PWM01_EN =1; // Enable PWM0 & PWM1 clock
PWMA->PPR.CP01=1; // Prescaler 0~255, Setting 0 to stop
output clock
PWMA->CSR.CSR0=0; // PWM clock = clock source/(Prescaler + 1)/divider
PWMA->PCR.CH0MOD=1; // 0:One-shot mode, 1:Auto-load mode
// CNR and CMR will be auto-cleared after setting CH0MOD form 0 to 1.
PWMA->CNR0=0xFFFF; // CNR : counting down // PWM output high if CMRx+1 >= CNR
PWMA->CMR0=0xFFFF; // CMR : fix to compare // PWM output low if CMRx+1 < CNR
PWMA->PCR.CH0INV=0; // Inverter->0:off, 1:on
PWMA->PCR.CH0EN=1; // PWM function->0:Disable, 1:Enable
PWMA->POE.PWM0=1; // Output to pin->0:Diasble, 1:Enable
}
int32_t main (void)
{int16_t x=0xffff;
UNLOCKREG();
SYSCLK->PWRCON.XTL12M_EN = 1;
SYSCLK->CLKSEL0.HCLK_S = 0;
LOCKREG();
InitPWM_A();
Initial_panel(); // initialize LCD pannel
clr_all_panel(); // clear LCD panel
print_lcd(0,"variable reistor");
while(1)
{PWMA->CMR0=x;
x = x - 1;
DrvSYS_Delay(5000);
}
}
