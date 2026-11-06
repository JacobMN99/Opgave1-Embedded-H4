
# My_Project

Embedded C-projekt til **ATmega328PB** (16 MHz), bygget med XC8 i MPLAB for VS Code og debugget via mEDBG.

## Sådan fungerer softwaren

Programmet består af tre moduler. Alt arbejde sker i interrupts, så hovedløkken i `main()` er tom.

**Opstart (`main.c`)**
1. PB3 sættes som output til den grønne LED.
2. Timer 1 startes med et timeout på 500 ms.
3. UART'en initialiseres (9600 baud, 8N1), og `ConvertReceivedChar` registreres som callback.
4. Modtage-interruptet og de globale interrupts slås til, og `UART klar` sendes til terminalen.

**Timer 1 (`timer.c`)**
`Timer1_Init_ms(ms)` sætter Timer 1 op i CTC-mode med prescaler 256 og beregner `OCR1A` ud fra det ønskede antal millisekunder. Ved hvert compare match toggler `ISR(TIMER1_COMPA_vect)` den grønne LED, så den med 500 ms blinker med 1 Hz.

**UART (`uart.c`)**
- `printf()` sender gennem UART'en, fordi `uart_putch` er sat som stdout.
- Hver gang der modtages et tegn, kalder `ISR(USART0_RX_vect)` den registrerede callback-funktion med en pointer til tegnet, og tegnet sendes derefter retur (echo).
- Callback-mekanismen (`SetupUARTFunctionCallbackPointer`) betyder, at UART-driveren ikke kender til, hvad applikationen gør med tegnene. Funktionen kan skiftes ud uden at ændre driveren.

**Bogstavkonvertering (`ConvertReceivedChar` i `main.c`)**
Store og små bogstaver i ASCII adskiller sig kun ved bit 5 (`0x20`), så en XOR med `0x20` bytter dem om: `a` → `A` og `A` → `a`. Intervallerne `0x41–0x5D` og `0x61–0x7D` dækker også `[ \ ]` ↔ `{ | }`, som i dansk 7-bit ASCII er `Æ Ø Å` ↔ `æ ø å`. Andre tegn sendes uændret retur.

**Resultat:** Den grønne LED blinker, og en terminal på 9600 baud viser `UART klar`. Alt, hvad du skriver, kommer tilbage med store og små bogstaver byttet om.

## Structure

| Path                          | Purpose                                                                                                                             |
|-------------------------------|-------------------------------------------------------------------------------------------------------------------------------------|
| src                           | C source files (.c): main.c and module implementations (timer.c, uart.c)                                                            |
| include                       | Header files (.h): module interfaces (timer.h, uart.h) and project-wide defines (ProjectDefines.h). Added as include directory.     |
| _build                        | The [CMake build tree](https://cmake.org/cmake/help/latest/manual/cmake.1.html#introduction-to-cmake-buildsystems), can be deleted. |
| cmake                         | Generated [CMake](https://cmake.org/) files. May be deleted if user.cmake has not been added                                        |
| .vscode                       | See [VSCode](https://code.visualstudio.com/docs/getstarted/settings)                                                                |
| .vscode\settings.json         | Workspace specific settings                                                                                                         |
| .vscode\My_Project.mplab.json | The MPLAB project file, should not be deleted                                                                                       |
| out                           | Final build artifacts                                                                                                               |
