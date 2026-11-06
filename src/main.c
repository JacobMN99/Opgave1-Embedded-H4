/**
 * @file main.c
 * @author jma
 * @date 2026-11-05
 * @brief Main function
 */
#include "timer/timer.h"
#include "uart/uart.h"

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Forskellen på et stort og et lille bogstav i ASCII er netop bit 5 (0x20),
// fx 'A' = 0x41 og 'a' = 0x61.
#define Upper_Lower_Bit_Value 0x20

// Kaldes fra UART-modtage-interruptet (via callback) med hvert modtaget tegn.
// Intervallerne går til 0x5D/0x7D, så de danske 7-bit tegn [\] <-> {|}
// (Æ Ø Å <-> æ ø å) også byttes.
void ConvertReceivedChar(char *ReceivedChar)
{
	// Den smarte måde at få konverteret små bogstaver om til store bogstaver og
	// modsat er ved brug af Xor, som vi tidligere har set. Så kan vi klare det i
	// én linje kode.
	if ( ((*ReceivedChar >= 0x41) && (*ReceivedChar <= 0x5D)) ||
	     ((*ReceivedChar >= 0x61) && (*ReceivedChar <= 0x7D)))
	{
		*ReceivedChar = *ReceivedChar ^ Upper_Lower_Bit_Value;
	}
}

int main(void) {
    DDRB |= (1 << GreenLedBit);  // Sæt PB3 som output for den grønne LED

    // Eksempel 1: Sæt timeout til 500 ms
    Timer1_Init_ms(500);

    // Hvis du vil skifte til 250ms eller 1000ms, kalder du blot funktionen igen:
    // Timer1_Init_ms(250);
    // Timer1_Init_ms(1000);

    // Initialisér UART (9600 baud, 8N1) og slå modtage-interrupt til (samler beskeder i en buffer)
    RS232Init();
    SetupUARTFunctionCallbackPointer(ConvertReceivedChar); // Byt store/små bogstaver i echo
    Enable_UART_Receive_Interrupt();

    // Aktivér globale interrupts
    sei();

    printf("UART klar\r\n");

    while (1) {
        // Hovedloop kan køre her uafhængigt
    }
}
