/*
 * gpio_driver_mali.c
 *
 *  Created on: Jun 26, 2025
 *      Author: memoj
 */

#include "gpio_driver_mali.h"

#define RCC_BASE_ADDR		0x40023800UL
#define RCC_AHB1ENR_ADDR  (*(volatile uint32_t*)(RCC_BASE_ADDR + 0x30))

#define GPIO_BASE(port_char) (\
		(port_char == 'A') ? 0x40020000UL : \
		(port_char == 'B') ? 0x40020400UL : \
		(port_char == 'C') ? 0x40020800UL : \
		(port_char == 'D') ? 0x40020C00UL : \
		(port_char == 'E') ? 0x40021000UL : \
		(port_char == 'F') ? 0x40021400UL : \
		(port_char == 'G') ? 0x40021800UL : \
		(port_char == 'H') ? 0x40021C00UL : \
		(port_char == 'I') ? 0x40022000UL : \
		(port_char == 'J') ? 0x40022400UL : \
		(port_char == 'K') ? 0x40022800UL : 0)


void GPIO_Init(char port, uint8_t pin, GPIOMode mode, GPIOOType otype, GPIOPull pull)

{
    uint32_t base = GPIO_BASE(port);
    if (base == 0) return; // Geçersiz port harfi

    // Clock Enable
    RCC_AHB1ENR_ADDR |= (1 << (port - 'A'));

    // MODER
    volatile uint32_t* MODER = (uint32_t*)(base + 0x00);
    *MODER &= ~(0x3 << (pin * 2));
    *MODER |= ((mode & 0x3) << (pin * 2));

    // OTYPER (sadece output için anlamlı)
    volatile uint32_t* OTYPER = (uint32_t*)(base + 0x04);
    *OTYPER &= ~(1 << pin);
    *OTYPER |= (otype << pin);

    // PUPDR
    volatile uint32_t* PUPDR = (uint32_t*)(base + 0x0C);
    *PUPDR &= ~(0x3 << (pin * 2));
    *PUPDR |= (pull << (pin * 2));
}

void GPIO_Write(char port, uint8_t pin, uint8_t value)
{
    uint32_t base = GPIO_BASE(port);
    if (base == 0) return;

    volatile uint32_t* ODR = (uint32_t*)(base + 0x14);
    if (value)
        *ODR |= (1 << pin);
    else
        *ODR &= ~(1 << pin);
}

uint8_t GPIO_Read(char port, uint8_t pin)
{
    uint32_t base = GPIO_BASE(port);
    if (base == 0) return 0;

    volatile uint32_t* IDR = (uint32_t*)(base + 0x10);
    return ((*IDR >> pin) & 0x1);
}
