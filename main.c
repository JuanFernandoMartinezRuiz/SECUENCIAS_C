/*!
\file   main
\date   2024-09-04
\author Juan Fernando Martinez,FRANCES JULLIETH SERRANO GUTIERREZ  <juanfermartinez@unicauca.edu.co><francesser@unicauca.edu.co>

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2024. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/

#include <xc.h>
#include <pic16f887.h>
#include <stdio.h>
#include <string.h>
#include "CONFIG.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "SECUENCIAS.h"

enum Estado { Seguridad, Monitoreo, Bloqueado };
enum Estado Estado = Seguridad;

const char password[5] = { '9', '8', '7', '6', 0 };
char pass_user[5];
unsigned char idx = 0;
unsigned char intentos = 3;

void function_seguridad(void);
void function_Bloqueado(void);

void main() {
    OSCCON = 0x71;
    TRISD = 0x00;
    TRISC = 0x00;
    ANSEL = 0x01;
    TRISE = 0;
    PORTE = 0x00;
     
    LCD_Init();
    keypad_init();

    while (1) {
        switch(Estado){
            case Seguridad:
                function_seguridad();
                break;
            case Bloqueado:
                function_Bloqueado();
                break;
            case Monitoreo:
                LCD_Clear();
                LCD_String_xy(0,0,"Monitoreo Activo");
                __delay_ms(3000);
                Estado = Seguridad;
                break;
        }
    }
}

void function_seguridad(void){
    char key = '0';
    idx = 0;  // Reiniciar idx para un nuevo intento de contraseña

    if (intentos != 0) {
        LCD_String_xy(0,0,"ENTER PASSWORD");
        LCD_Command(0xC0);

        do {
            key = keypad_getkey();
            if (key != 0) {
                LCD_Char('*');
                pass_user[idx++] = key;
            }
            __delay_ms(100);
        } while (idx < 4);

        if (strncmp(pass_user, password, 4) == 0) {
            LCD_Clear();
            LCD_String_xy(0,0,"Clave Correcta");
            for (int i = 0; i < 3; i++) {
                PORTEbits.RE1 = 1;
                __delay_ms(500);
                PORTEbits.RE1 = 0;
                __delay_ms(500);
            }
            intentos = 3;
            Estado = Monitoreo;

            // Ejecutar las secuencias de efectos en los LEDs del PORTC
            secuencia1_Efecto1();
            secuencia1_Efecto2();

        } else {
            LCD_Clear();
            LCD_String_xy(0,0,"Clave Incorrecta");
            for (int i = 0; i < 2; i++) {
                PORTEbits.RE2 = 1;
                __delay_ms(300);
                PORTEbits.RE2 = 0;
                __delay_ms(700);
            }
            intentos--;
        }
    } else {
        Estado = Bloqueado;
    }
    __delay_ms(2000);
    LCD_Clear();
}

void function_Bloqueado(void){
    LCD_Clear();
    LCD_String_xy(0, 0, "Sistema Bloqueado");
    for(int i = 0; i < 8; i++){
        PORTEbits.RE0 = 1;
        __delay_ms(300);
        PORTEbits.RE0 = 0;
        __delay_ms(500);
    }
    LCD_Clear();
    intentos = 3;
    Estado = Seguridad;
}
