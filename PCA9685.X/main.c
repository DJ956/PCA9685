#include "mcc_generated_files/mcc.h"

#include <xc.h>
#include "PCA9685.h"

#define SERVO_CH 0

void main(void)
{
    
    SYSTEM_Initialize();
    
    ANSELB = 0xCA;
    WPUB = 0x24;
    
    SSP2ADD = 0x13;
    SSP2CON1 = 0x28;
    SSP2CON2 = 0x0;
    SSP2STAT = 0;
    
    __delay_ms(500);
    
    init();
    
    set_pwm_freq(50);
    
    uint16_t n = 0;
    
    while (1)
    {
        servo_write(SERVO_CH, n);
        n += 10;
        if(n >= 180){ n = 0; }
        
        __delay_ms(500);
    }
}