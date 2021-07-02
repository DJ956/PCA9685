
#include <xc.h>
#include "i2c.h"

void i2c_wait(){
    while((SSP2CON2 & 0x1F) || (SSP2STAT & 0x04));
}

void i2c_start(){
    i2c_wait();
    SSP2CON2bits.SEN = 1;
    while(SSP2CON2bits.SEN);
}

void i2c_stop(){
    SSP2CON2bits.PEN = 1;
    while(SSP2CON2bits.PEN);
}

void i2c_repeated_start(){
    i2c_wait();
    SSP2CON2bits.RSEN = 1;
    while(SSP2CON2bits.RSEN);
}

void i2c_write(uint8_t data){
    SSP2BUF = data;
    while(SSP2STATbits.BF);
    while(SSP2CON2bits.ACKSTAT);
    i2c_wait();
}

uint8_t i2c_read(uint8_t ack){
    uint8_t data;
    
    SSP2CON2bits.ACKDT = ack;
    SSP2CON2bits.RCEN = 1;
    while(!SSP2STATbits.BF);
    SSP2CON2bits.ACKEN = 1;
    data = SSP2BUF;
    SSP2CON1bits.SSPOV = 0;
    i2c_wait();
    
    return data;
}

