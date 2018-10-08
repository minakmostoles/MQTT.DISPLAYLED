/***********************************************************************************************************************************/
/*                                        Modulo reposable del control del MQTT                                                    */
/*                                                       V_180506.0                                                                */
/*                                                                                                                                 */
/***********************************************************************************************************************************/

#ifndef ioMQTT_H
#define ioMQTT_H

#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>          //Manejo de DNS  Multicast DNS
#include <WiFiUdp.h>              //Manejo de UDP
#include <PubSubClient.h>         //Manejo de MQTT


/*****************************************************/
/*************CONSTANTES DE CONEXION******************/
const char   serverMQTT[50]   = ""; //Recomiendo coger la ip del servidor
const int    serverMQTTPORT   = 0;
const String userMQTT = ""; 
const char   passMQTT[50] = "";
/*****************************************************/ 
 
/**********************************************************************/
//Prototipos de MQTT
/**********************************************************************/
void callback(char* topic, byte* payload, unsigned int length);
bool conectarMQTT();
void setPublicacion(String topic, String valor);
String getLastTopic();
String getLastValue();


#endif //__ioMQTT_H

