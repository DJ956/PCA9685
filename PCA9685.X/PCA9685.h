/* 
 * File:   PCA9685.h
 * Author: dexte
 *
 * Created on 2021/07/02, 13:23
 */

#ifndef PCA9685_H
#define	PCA9685_H

#include <xc.h> // include processor files - each processor file is guarded.  

void init();
void set_pwm_freq(uint8_t freq);
void set_pwm(uint8_t num, uint16_t on, uint16_t off);

uint8_t map(uint8_t ang, uint8_t target_min,  uint8_t target_max, uint8_t src_min, uint16_t src_max);

void servo_write(uint8_t ch, uint8_t ang);

#ifdef	__cplusplus
extern "C" {
#endif
