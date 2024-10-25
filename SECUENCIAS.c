#include <xc.h>
#include "SECUENCIAS.h"

// Define la frecuencia del oscilador
#define _XTAL_FREQ 8000000//frecuencia del oscilador  

/**
 * \brief Efecto 1: Realiza una secuencia de iluminación en los LEDs conectados a PORTC.
 *
 * Esta función comienza con el valor `V1` en 0x80 y `V2` en 0x01, aplicando una secuencia en PORTC
 * en la que los LEDs se encienden de manera desplazada desde los extremos hacia el centro.
 * Luego, los LEDs se encienden en secuencia inversa.
 *
 * \param void No toma parámetros.
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
 * Esta función comienza encendiendo el LED en la posición 0x80 y lo desplaza hacia la derecha
 * hasta alcanzar la posición 0x08. Luego, invierte la dirección y continúa el desplazamiento 
 * hacia la posición 0x01, mostrando cada patrón en PORTC.
 *
 * \param void No toma parámetros.
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
