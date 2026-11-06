/**
 * @file timer.h
 * @author jma
 * @date 2026-11-05
 * @brief Timer 1 - initialisering og interrupt
 */
#ifndef TIMER_H
#define TIMER_H

#ifndef F_CPU
#define F_CPU 16000000UL  // Antager 16 MHz krystal (ret hvis din kører med f.eks. 8 MHz)
#endif

#include <stdint.h>

#define GreenLedBit PORTB3  // Den grønne LED er tilsluttet pin PB3

// Initialiseringsfunktion til Timer 1 med dynamisk millisekund-beregning
void Timer1_Init_ms(uint16_t timeout_ms);

#endif // TIMER_H
