#include <xc.h>
#include "SECUENCIAS.h"

// Define la frecuencia del oscilador
#define _XTAL_FREQ 8000000//frecuencia del oscilador  

/**
 * \brief Efecto 1: Realiza una secuencia de iluminaci�n en los LEDs conectados a PORTC.
 *
 * Esta funci�n comienza con el valor `V1` en 0x80 y `V2` en 0x01, aplicando una secuencia en PORTC
 * en la que los LEDs se encienden de manera desplazada desde los extremos hacia el centro.
 * Luego, los LEDs se encienden en secuencia inversa.
 *
 * \param void No toma par�metros.
 * \return void No devuelve un valor.
 */
void secuencia1_Efecto1(void) {
    unsigned char V1 = 0x80;
    unsigned char V2 = 0x01;

    while (V1 != 0) { 
        PORTC = V1 | V2;
        __delay_ms(50);
        V1 >>= 1;
        V2 += 0x02;
    }

    V1 = 0x10;

    while (V1 != 0x80) {
        PORTC = V1 | V2;
        __delay_ms(50);
        V1 <<= 1;
        V2 += 0x02;
    }
}

/**
 * \brief Efecto 2: Realiza una secuencia de desplazamiento en los LEDs conectados a PORTC.
 *
 * Esta funci�n comienza encendiendo el LED en la posici�n 0x80 y lo desplaza hacia la derecha
 * hasta alcanzar la posici�n 0x08. Luego, invierte la direcci�n y contin�a el desplazamiento 
 * hacia la posici�n 0x01, mostrando cada patr�n en PORTC.
 *
 * \param void No toma par�metros.
 * \return void No devuelve un valor.
 */
void secuencia1_Efecto2(void) {
    unsigned char TEMP = 0x80;

    while (TEMP != 0x08) {
        PORTC = TEMP;
        __delay_ms(50);
        TEMP >>= 1;
    }

    TEMP = 0x08;
    while (TEMP != 0x01) {
        PORTC = TEMP;
        __delay_ms(50);
        TEMP >>= 1;
    }

    PORTC = TEMP;
    __delay_ms(50);
}
