/***********************************************************************************************************************************/
/*                                         FUNCIONES A USAR POR TODOS LAS LIBRERIAS                                                */
/*                                                      v18.05.06                                                                  */
/***********************************************************************************************************************************/

#include "Setting.h"              //Activacion de los diferentes funciones
#include <ESP8266WiFi.h>          //Libreria necesaria para el ESP8266

#ifdef SUPPORT_EEPROM_ENABLE
  #include "ioEEPROM.h"
#endif

#ifdef SUPPORT_WIFI
  #include "ioWIFI.h"
#endif

#ifdef SUPPORT_MQTT
  #include "ioMQTT.h"
#endif //FIN

#ifdef DISPLAY_MATRIZ_LED
  #include "oMatrizLed.h"
#endif //FIN

/**********************************************************************/
/*                          SETUP MODULAR                             */
/*   Esta funcion realiza la llamada a la configuraciones elegidas    */
/**********************************************************************/
void setupModular(){
  
  #ifdef SUPPORT_EEPROM_ENABLE
    mostrarTituloSerial("SUPPORT_EEPROM ENABLE");
    //Serial.println("SUPPORT_EEPROM ENABLE");
    //setupEEPROM();                  //Configura la EEPROM
  #endif

  #ifdef SUPPORT_WIFI
    mostrarTituloSerial("SUPPORT_WIFI ENABLE");
    //Serial.println("WIFI ENABLE");
    inicioWifi();                     //Configuracion ModoWifi
  #endif
  
  //wificonect(); //Anterior
  //delay(1500); //Anterior
  
  #if defined(SUPPORT_WIFI) && defined(SUPPORT_MQTT) //Solo si esta activado el wifi y la opcion MQTT
    Serial.println("SUPPORT_MQTT ENABLE");
    conectarMQTT();
    //publicame();
  #endif
}



/**********************************************************************/
/*                             RESET                                  */
/*          Realizamo un reset por software del dispositivo           */
/**********************************************************************/

extern void kernelPanic(){        
    ESP.restart(); 
    //ESP.reset();
}
/**********************************************************************/
/*                     Programador de evento                          */
/*             Programamos eventos en un tiempo determinado           */
/**********************************************************************/
bool eventoCADAxSEG (int seg, bool flagEVENTO){
 
  long segRUN = (millis()/1000); //Convierto el tiempo en segundos
  
  if((segRUN%seg == 0) and (flagEVENTO == 0)){//Si los que lleva arrancado el sistema es modulo es multiplo de seg ejecuto el evento
    flagEVENTO = 1;
  }
  
  if((segRUN%seg != 0) and (flagEVENTO == 1)){
    flagEVENTO = 0;
  }
  
  return flagEVENTO;
}  //FIN FUNCION
/**********************************************************************/
/*                     Generador de titulos                           */
/*           Funcion para mostra un titulo por puerto serie           */
/**********************************************************************/

void mostrarTituloSerial(String titulo){
    String marco ="";
    for (int x=0 ; x < (titulo.length()+2); x++){marco= marco + "-";}
    Serial.println(" ");
    Serial.println("#" + marco + "#");
    Serial.println("# " + titulo + " #");
    Serial.println("#" + marco + "#");
    Serial.println(" ");
}

