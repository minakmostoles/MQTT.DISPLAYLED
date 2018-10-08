/***********************************************************************************************************************************/
/*                                            Modulo de lectura/escritura en la eeprom                                             */
/*                                                     Soporte EEPROM V_171225.0                                                   */
/*                                                                                                                                 */
/***********************************************************************************************************************************/

#ifndef ioEEPROM_H
#define ioEEPROM_H

#include <ESP8266WiFi.h>  //Libreria necesaria para el ESP8266
#include <EEPROM.h>       //Libreria para el uso de la EEPROM

#include "Setting.h"

#define E2END 512

void setupEEPROM();            // Setup EEPROM 
extern void grabarEEPROM(int, String); //ARG int, ADDR String Datos
extern String leerEEPROM(int);         //ARG int, ADDR
void volcadorEEPROM();                 //SIRVE PARA EXTRAER LA MEMORIA EEPROM
void printASCII(char * buffer);

#endif //__SoporteEEPROM_H

