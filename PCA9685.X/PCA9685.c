#include <xc.h>
#include "i2c.h"
#include "PCA9685.h"

#define _XTAL_FREQ 500000

#define PCA_ADDR 0x40
#define SERVO_MIN 150
#define SERVO_MAX 500

/**
 * i2c write data
 * @param addr
 * @param d
 */
void _write(uint8_t addr, uint8_t d){
    i2c_start();
    i2c_write(PCA_ADDR);
    i2c_write(addr);
    i2c_write(d);
    i2c_stop();
}

/**
 * i2c read data
 * @return 
 */
uint8_t _read(){
    uint8_t data;
    i2c_start();
    i2c_write(PCA_ADDR | 0x01);
    data = i2c_read(PCA9685_MODE1);
    
    return data;
}

/**
 * Initialize PCA9685 Device
 */
void init(){
    i2c_start();
    i2c_write(PCA_ADDR);
    
    i2c_write(0x0);
    i2c_write(0x0);
    
    i2c_stop();
}

/**
 * transmission pwm to PCA9685
 * @param num servo channel
 * @param on 
 * @param off angle
 */
void set_pwm(uint8_t num, uint16_t on, uint16_t off){
    i2c_start();
    i2c_write(PCA_ADDR);
    i2c_write(LED_ON_L + 4 * num);
    i2c_write(on);
    i2c_write(on >> 8);
    i2c_write(off);
    i2c_write(off >> 8);
    i2c_stop();
}

/**
 * PCA9685 set pwm freq
 * @param freq
 */
void set_pwm_freq(uint16_t freq){
    uint16_t prescaleval = 6103;
    prescaleval /= freq;
    prescaleval -= 1;
    
    uint8_t prescale = (uint8_t)prescaleval;
    uint8_t oldreg = _read();
    uint8_t newreg = (oldreg | 0x7F) | 0x10;
    _write(PCA9685_MODE1, newreg);
    _write(PCA9685_PRESCALE, prescale);
    _write(PCA9685_MODE1, oldreg);
    __delay_ms(500);
    _write(PCA9685_MODE1, oldreg | 0xA1);
    
}


uint8_t map(uint16_t ang, uint16_t target_min,  uint16_t target_max, uint16_t src_min, uint16_t src_max){
    return (ang - target_min) * (src_max - src_min) / (target_min - target_max) + src_min;
}

/**
 * 
 * @param ch SERVO CHANNEL
 * @param ang ANGLE 0~180
 */
void servo_write(uint8_t ch, uint16_t ang){
    ang = map(ang, 0, 180, SERVO_MIN, SERVO_MAX);
    set_pwm(ch, 0, ang);
}