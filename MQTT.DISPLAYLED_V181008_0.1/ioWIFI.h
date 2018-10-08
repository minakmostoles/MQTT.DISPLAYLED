/***********************************************************************************************************************************/
/*                                  Modulo reposable de la comunicacion Wifi                                                       */
/*                                     ModuloComunicacionWifi V_180516.0                                                           */
/*  Modulo reposable de la comunicacion Wifi, este modulo se regula la comunicacion wifi, habilita un modo programacion y el modo  */
/*  OTA para la actualizacion a distancia.                                                                                         */
/*   * Este modulo usa una entrada y una salida                                                                                    */
/*                                                                                                                                 */
/***********************************************************************************************************************************/

#ifndef ioWIFI_H
#define ioWIFI_H

#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>          //Manejo de DNS  Multicast DNS
#include <WiFiUdp.h>              //Manejo de UDP

//#include <ArduinoOTA.h>           //Manejo de OTA

#include "Setting.h"
#include "ioEEPROM.h"

//Variables y constates WIFI
//Pines usados
//const int LedInfo = D1;                             // LED Indicacion
const uint8_t PulsadorConf = D3;                          // Pulsador

const uint8_t tiempoESPERA = 1000;
const uint8_t intentosMAX = 100;                          // intentosMAX*tiempoESPERA=TiempoEsperaMaximo para conectar. * UN VALOR BAJO DE TiempoEsperaMaximo PUEDE PROVOCAR NO CONECTARSE CON EXITO

const uint8_t longMAXSSID = 25; //Longitud maxima del SSID
const uint8_t longMAXPASS = 25; //Longitud maxima del PASS
const uint8_t dirSSID = 0;      //Direccion en EEPROM SSID conf por el usuario
const uint8_t dirPASS = 50;     //Direccion en EEPROM PASS conf por el usuario

/*******************************************************/
//Funciones WIFI
void inicioWifi();
void modoNormal();
bool conectarSSID (String sSSID,String sPASS);
void modoSoftAP();
void serverConf();
void escanearRedes();
void leerConfSSID();
void paginaConf();
void guardarConfWifi();

void getUpdateOTA();


#endif //__ioWIFI_H


