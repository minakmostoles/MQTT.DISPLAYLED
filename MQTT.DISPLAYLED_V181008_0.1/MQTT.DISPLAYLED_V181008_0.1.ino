//Libreria
#include "Setting.h"              //Activacion de los diferentes funciones

//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
//#include <ESP8266WiFi.h>
//#include <ESP8266mDNS.h>          //Manejo de DNS  Multicast DNS
//#include <WiFiUdp.h>              //Manejo de UDP
//#include <PubSubClient.h>         //Manejo de MQTT

//#include "Setting.h"              //Activacion de los diferentes funcione

#ifdef SENSOR_HUMD-TEMP_ENABLE
  #include "iSHT30.h"
#endif //FIN

#ifdef SUPPORT_MQTT
  #include "ioMQTT.h"
#endif //FIN

#include "oMatrizLed.h"

//Variable del programa
bool flagEVENTO = false;
extern bool updateFlag;       //Exportamos la variable de ioMQTT.CPP para el evento de actualizacion

void wificonect();

void conectadoMQTT();
void publicame();



/*****************************************************/
//
/*****************************************************/
/*void wificonect(){
  WiFi.begin("Welcome", "Marioybea2018");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Conectado");
}//FIN FUNCION
*/

/*****************************************************/
void  publicame(){
    setPublicacion(getLastTopic(),getLastValue());
    Serial.println(getLastTopic());
    String mensajeDisplay = (getLastTopic() + " -> " +  getLastValue());
    mostrarMensaje(mensajeDisplay);

    
    #ifdef SENSOR_HUMD-TEMP_ENABLE  
      setPublicacion("Temperatura",GetTempSHT30(1));  //TOPIC, DATO
      setPublicacion("Humedad",GetHumdSHT30(1));      //TOPIC, DATO
    #endif
}

/*****************************************************/
/* SETUP                                             */
/*****************************************************/
void setup(){

  #ifdef SERIAL_ENABLE      //¿Puerto serie habilitado?
  
    Serial.begin(Serialbaut);
    Serial.flush();
    String tempName = (nombreSketch + " " + versionSketch);
    
    mostrarTituloSerial(tempName);
    
    //Serial.println(nombreSketch + " " + versionSketch); //Muestra por puerto serie el nombre de proyecto y numero de version
  #endif
  setupModular();

  setupMatrizLed();
  mostrarMensaje("Hola");
  
  publicame(); //FUNCION LOCAL
  
}//FIN FUNCION

/*****************************************************/
/* LOOP                                             */
/*****************************************************/
void loop(){
  
  conectarMQTT();
  
  flagEVENTO = eventoCADAxSEG(60, flagEVENTO);   //60 Segundo  1 min publica la temperatura en el servidor MQTT

  if (flagEVENTO == 1){
    mostrarTituloSerial("Evento por tiempo");    // Genera el titulo
    publicame();                                 // Llama a todo lo que se publicara
  }

  if (updateFlag){                               // Se solicita actualizar
    mostrarTituloSerial("Solitud Actualizacion");// Genera el titulo
    publicame();                                 // Llama a todo lo que se publicara
    updateFlag=false;
  }

}//FIN FUNCION
/*****************************************************/
