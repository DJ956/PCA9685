/* 
 * File:   PCA9685.h
 * Author: dexte
 *
 * Created on 2021/07/02, 13:23
 */

#ifndef PCA9685_H
#define	PCA9685_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED_ON_L 0x06

void init();
void set_pwm_freq(uint8_t freq);
void set_pwm(uint8_t num, uint16_t on, uint16_t off);

uint8_t map(uint8_t ang, uint8_t target_min,  uint8_t target_max, uint8_t src_min, uint16_t src_max);

void servo_write(uint8_t ch, uint8_t ang);

uint8_t _read(uint8_t address);
void _write(uint8_t addr, uint8_t);

#ifdef	__cplusplus
extern "C" {
#endif
