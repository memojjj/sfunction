/*
 * gpio_driver_mali.h
 *
 *  Created on: Jun 26, 2025
 *      Author: memoj
 */

#ifndef GPIO_DRIVER_MALI_H_
#define GPIO_DRIVER_MALI_H_

#include <stdint.h>

typedef enum {
    OUTPUT = 0x01,
    INPUT  = 0x00
} GPIOMode;

typedef enum {
    HS_OUT = 0x00,  // Push-pull
    LS_OUT = 0x01   // Open-drain
} GPIOOType;

typedef enum {
    NOPULL   = 0x00,
    PULLUP   = 0x01,
    PULLDOWN = 0x02
} GPIOPull;

void GPIO_Init(char port, uint8_t pin, GPIOMode mode, GPIOOType otype, GPIOPull pull);
void GPIO_Write(char port, uint8_t pin, uint8_t value);
uint8_t GPIO_Read(char port, uint8_t pin);

#endif /* GPIO_DRIVER_MALI_H_ */
