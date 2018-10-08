/***********************************************************************************************************************************/
/*                                        CONFIGURACION GENERAL DEL PROYECTO                                                       */
/*                                             Setting V_180313.0                                                           */
/***********************************************************************************************************************************/

#ifndef Setting_H
#define Setting_H

#include <ESP8266WiFi.h>

/*********CONSTANTES DEL PROYECTO********/

const String nombreSketch = "DISPLAY-MATRIZLED-MQTT";//Indica el proyecto
const String versionSketch = "V:181008.0.1";         //Indica la version del sketch

/*****PINES DEL DISPOSITIVO ES WEMOS D1***/
/*
 * PINES SONOFF PIN12 RELE PLACA
 *              PIN13 LED PLACA
 *              PIN14 SALIDA/ENTRADA EN PINES
 *              
 */              
/*****DEFINICION DE PUERTOS (NO ES NECESARIO DEFIRLOS TODOS)*****/
//#define D0 16
//#define D1 5 // I2C Bus SCL (clock)
//#define D2 4 // I2C Bus SDA (data)
//#define D3 0
//#define D4 2 // LED_BUILTIN, led interno azul con logica invertida.
//#define D5 14 // SPI Bus SCK (clock)
//#define D6 12 // SPI Bus MISO
//#define D7 13 // SPI Bus MOSI
//#define D8 15 // SPI Bus SS (CS)
//#define D9 3 // RX0 (Serial console)
//#define D10 1 // TX0 (Serial console)

/******CONFIGURACION PUERTO SERIAL******/
#define SERIAL_ENABLE                          // HABILITAR PUERTO SERIE *ACTUALMENTE DESABILITARLO DARIA PROBLEMAS
#ifdef SERIAL_ENABLE                           // ¿Puerto serie habilitado?
#define Serialbaut 115200                      // 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200
#endif

/******MODOS DE DEBUG******/
#define MODE_DEBUG                             // HABILITAR MODO DEBUG INFORMACION BASICA
//#define MODE_DEBUG_FES                         // HABILITAR EL MODO DEBUG FUNCIONALIDADES MUY ESPECIALES
#define MODE_DEBUG_SEC                         // HABILITAR EL MODO DEBUG EN FUNCIONES MUY CICLICAS QUE PROVOCAN UNA GRAN CANTIDAD DE LINEAS SOBRE TERMINAL POR EJEMPLO BUFFER PANTALLA

/******HERRAMIENTAS PARA ANALISIS DE SISTEMAS******/
//#define TOOLS-I2C_ENABLE                     // HABILITA EL ESCANEO DE PUERTOS I2C (inestable)

/******FUNCIONES CONEXION Y INTERNET******/
#define SUPPORT_WIFI                           //  ACTIVAMOS WIFI
//#define SUPPORT_UPDATE_OTA                     //  HABILITA LA UPDATE OTA (***NO ESTA PROBADO***)
#define NEEDCONECTION                        //  SI SE NECESITA IMPRESCINDIBLEMENTE CONEXION USAR ESTA OPCION, SI NO CONECTA ENTRA EN MODO CONFIGURACION AUTOMATICAMENTE

#define SUPPORT_MQTT                           //  ACTIVAMOS EL SOPORTE PARA MQTT ES OBLIGATORIO TENER SUPORT_WIFI ACTIVADO (SU FUNCIONAMIENTO ESTA DENTRO DE SUPPORT WIFI)
//const String clientId ="";
//#define SUBSCRIBE_MQTT                         //  ACTIVAMOS LAS SUBCRIPCIONES
//const String subcripcionTOPIC = "#";           //  TEMA AL QUE NOS SUBCRIBIMOS


//#define TIME_WEATHER                           //  ACTIVAMOS FUNCION PARA OPTENER EL HORA FECHA Y TIEMPO DE LA ZONA DADA

//#define SUPPORT_EEPROM_ENABLE                  // HABILITAR LA EEPROM GRABAR Y LEER UNA POSICION DE MEMORIA (SE USA PARA MODULO COMUNICACION WIFI)
//#define SUPPORT_SD_ENABLE                      // HABILITAR LA SD

/******FUNCIONES DE DISPOSITIVOS DISPLAYS******/
//#define  DISPLAY_OLED_ENABLE                   // HABILITAR DISPLAY OLED SHIELD 0.66" inch 64X48 IIC I2C Oled shield
#define  DISPLAY_MATRIZ_LED                    // HABILITAR DISPLAY MATRIZ LED

/******FUNCIONES DE SENSORES******/
//#define  SENSOR_HUMD-TEMP_ENABLE               // HABILITAR SENSOR TEMP & HUMEDAD

/******RUTINA DE RESET DEL SISTEMA******/
void setupModular();                           // CONFIGURAMOS EL SISTEMA COMO HEMOS DECLARADO ARRIBA
extern void kernelPanic();                     // PROVOCAMOS EL RESET DEL SISTEMA POR SOFTWARE
bool eventoCADAxSEG (int , bool);              // SIRVE PARA PROGRAMAR EVENTOS NO CRITICOS EJECUTADOS POR TIEMPO MAXIMO 49,71 dias DEVUELVE UN FLAG QUE ES EL RESPONSABLE DE EJECUTAR O NO LAS TAREAS
void mostrarTituloSerial(String titulo);       // SIRVE PARA IMPRIMIR POR PUERTO SERIE UN TITULO Y REALIZAR UNA SEPARCION EN LO QUE SE MUESTRA

#endif //__Setting_H
