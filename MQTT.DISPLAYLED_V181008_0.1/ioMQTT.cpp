/***********************************************************************************************************************************/
/*                                        Modulo reposable del control del MQTT                                                    */
/*                                                       V_180506.0                                                                */
/*                                                                                                                                 */
/***********************************************************************************************************************************/

#include "ioMQTT.h"

/*****************************************************/
bool updateFlag=false;                     //Flag de update
String globalUpdate = "UpdateAllMQTT";     //Valor del UPDATE global

//extern long lastReconnectAttempt = 0;    //NO SE USA
String lastTopic = "outTopic";            
String lastPayload = "hello world";
/*****************************************************/

//Declaracion para MQTT
WiFiClient mqttClient;
PubSubClient client(serverMQTT, serverMQTTPORT, callback, mqttClient);

/**********************************************************************/
//Funciones de MQTT
/**********************************************************************/

/**********************************************************************/
/*                  CALLBACK RECEPCION MENSAJE MQTT                   */
/*                                                                    */
/**********************************************************************/
void callback(char* topic, byte* payload, unsigned int length) {

 char PAYLOAD[50] = "           ";    //Testeado hasta 15
  
  Serial.print("Mensaje Recibido: [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
      PAYLOAD[i] = (char)payload[i];
  }
  Serial.println(PAYLOAD);

  String evTopic = topic;
  lastTopic = topic;//Asigno el ultimo topic
  lastPayload = PAYLOAD;//Asigno el ultimo payload
  
  if (evTopic == "Update"){
    String evPayload = PAYLOAD;
    Serial.println("Update -> " + evPayload);
    if ((evPayload == globalUpdate) || (evPayload == userMQTT)
    
    ){  
      Serial.println("Activando flag");
      updateFlag=true;
    }
  }
  /*
  else if(evTopic != "evTopic"){
    lastTopic = topic;//Asigno el ultimo topic
    lastPayload = PAYLOAD
  }
    */
}//FIN FUNCION

/**********************************************************************/
/*                      Conectando con MQTT                           */
/*                                                                    */
/**********************************************************************/
bool conectarMQTT(){
  uint8_t retries = 3;                     //Número entero sin signo de 1 byte 
  char userMQTTtemp[50];
  char clientIdtemp[50];
  if (WiFi.status() == WL_CONNECTED) {     //ESTAMOS CONECTADOS AL WIFI? WiFi.status() == WL_CONNECTED
    
    while (!client.connected()) {          //ESTAMOS DESCONECTADOS DEL MQTT?
      
        Serial.print("Intentando conexion MQTT...");
        
        // Crea un ID de cliente al azar
        // CString clientId = "test";
        // CclientId += String(random(0xffff), HEX);

        userMQTT.toCharArray(userMQTTtemp, 50);
        //clientId.toCharArray(clientIdtemp, 50);
        
        if (client.connect(userMQTTtemp, userMQTTtemp, passMQTT)) {
          Serial.println("conectado");
          Serial.println("Nombre de cliente MQTT :" + userMQTT);
          delay(100);
          
          setPublicacion(userMQTTtemp,"Conectado");//Conectamos realizamos un post de conexion
        } 
        
        else {
            Serial.print("fallo, rc=");
            Serial.print(client.state());
            Serial.println(" intenta nuevamente en 5 segundos");
            // espera 5 segundos antes de reintentar
            delay(5000);
        }
            
        retries--;                                            //UN REINTENTO MENOS
        
        if (retries == 0) {                                   //NO MAS REINTENTOS PUES HAZ LO SIGUIENTE
            Serial.println("MQTT NO POSIBLE DE CONECTAR");
            break;
        }//FIN DE INTENTOS CONEXION A MQTT (ROMPE BUCLE
        
      }//FIN CONECTANDO A MQTT
      
      client.loop();
      
    }//FIN CONEXION DISPONIBLE
    
    return client.connected();
  }//FIN FUNCION
  
/**********************************************************************/
/*                         PUBLICAR ELEMENTO                          */
/*                                                                    */
/**********************************************************************/
void setPublicacion(String topic, String valor){
    
    if (!client.connected()) {
        conectarMQTT();
    }
    else {
    // Cliente conectado 
    client.loop();
    }   
    
    if (client.connected()) {
      char publicacion[50];
      char valorstr[15];
  //    topic = "/" + userMQTT + "/" + topic;
      Serial.println("Enviando: [" +  topic + "] " + valor);
  //    Serial.println("Qos: " +  pubQOS);
  //    Serial.println("Retain : " + retain);
      topic.toCharArray(publicacion, 50);// preparamos la ruta de publicacion // /usuario/
      valor.toCharArray(valorstr, 15);
      client.publish(publicacion, valorstr); // true means retain);

      client.subscribe("#");
//      client.subscribe("Update");
//      lastReconnectAttempt = 0;
    }
}//FIN FUNCION

//POR IMPLANTAR CORRECTAMENTE
bool MqttIsConnected()
{
  return client.connected();
}//FIN FUNCION

void MqttDisconnect()
{
  client.disconnect();
}//FIN FUNCION

void MqttSubscribeLib(char *topic)
{
  client.subscribe(topic);
  client.loop(); 
}//FIN FUNCION
/*
bool MqttPublishLib(const char* topic, boolean retained)
{
  return client.publish(topic, mqtt_data, retained);
}//FIN FUNCION

*/
/**GETTERs**/
String getLastTopic(){
  return lastTopic;
  }
String getLastValue(){
  return lastPayload;
}

