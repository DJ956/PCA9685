#include <xc.h> // include processor files - each processor file is guarded.  

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED_ON_L 0x06

uint8_t _read();
void _write(uint8_t addr, uint8_t);

void init();
void set_pwm_freq(uint16_t freq);
void set_pwm(uint8_t num, uint16_t on, uint16_t off);

uint8_t map(uint16_t ang, uint16_t target_min,  uint16_t target_max, uint16_t src_min, uint16_t src_max);

void servo_write(uint8_t ch, uint16_t ang);