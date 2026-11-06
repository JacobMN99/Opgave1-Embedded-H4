/*
 * uart.h
 *
 * Created: 15-01-2018 09:45:07
 *  Author: ltpe
 */ 


#ifndef UART_H_
#define UART_H_

//#include "Arduino.h"
#include <stdio.h>
#include <stdint.h>
#include "ProjectDefines.h"  // F_CPU og Function_Pointer_With_One_CharPointer_Parameter
#define BAUD 9600UL

#define UART_RX_BUFFER_SIZE 64  // Maks. længde på en modtaget besked (inkl. '\0')

#define UART_NORMAL_MODE
#ifdef UART_NORMAL_MODE
#define MyUBRR (unsigned int)(F_CPU/(16*BAUD) -1)   // normal mode
#else
#define MyUBRR (unsigned int)(F_CPU/(8*BAUD) -1)   // *2 mode
#endif

extern void RS232Init( void);
extern int uart_getch(FILE* stream);
extern int uart_putch(char ch, FILE* stream);
extern void Enable_UART_Receive_Interrupt();
extern void Disable_UART_Receive_Interupt();

// Henter en modtaget besked (afsluttet med \r eller \n) til dest.
// Returnerer beskedens længde, eller 0 hvis ingen hel besked er modtaget endnu.
extern uint8_t Uart_ReadLine(char *dest, uint8_t maxLen);

// Registrerer en funktion, som modtage-interruptet kalder med hvert modtaget tegn,
// inden tegnet sendes retur (echo). Funktionen må gerne ændre tegnet.
extern void SetupUARTFunctionCallbackPointer(Function_Pointer_With_One_CharPointer_Parameter
                                             Function_To_Callback);

#endif /* UART_H_ */