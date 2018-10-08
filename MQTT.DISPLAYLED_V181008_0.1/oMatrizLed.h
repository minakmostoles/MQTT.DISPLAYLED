/***********************************************************************************************************************************/
/*                                                   MATRIZ LED                                                                    */
/*                                             ModeDEBUG V_180204.0                                                                */
/***********************************************************************************************************************************/

#ifndef oMatrizLed_H
#define oMatrizLed_H

#include "Setting.h"        //Archivo de configuracion y funciones generales a todos los modulos

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>   //Pantalla de matriz
#include <ESP8266WiFi.h>    //Libreria necesaria para el ESP8266
//#include <String.h>         //Libreria necesaria para el ESP8266

const int matrizBrillo = 5;  //Valor de 0 a1 15
const int tEspera = 50;  //Valor de espera

//################# CONEXION CON DISPLAY ################
// LED Matrix Pin -> ESP8266 Pin
// Vcc            -> 3v  (3V on NodeMCU 3V3 on WEMOS)
// Gnd            -> Gnd (G on NodeMCU)
// DIN            -> D7  (Same Pin for WEMOS) NARANJA
// CS             -> D4  (Same Pin for WEMOS) AMARILLO //2
// CLK            -> D5  (Same Pin for WEMOS) VERDE


void setupMatrizLed();                  //Configuracion display
void mostrarMensaje(String mensaje);    //Muestra el mensaje en el display
void matrizONOFF(bool aux);
//void corregirMsg(String *,int);         //Funcion para corregir mensaje

#endif //__oMatrizLed_H
