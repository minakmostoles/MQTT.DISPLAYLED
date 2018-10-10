/***********************************************************************************************************************************/
/*                                  Modulo reposable de la comunicacion Wifi                                                       */
/*                                     ModuloComunicacionWifi V_180516.0                                                           */
/*  Modulo reposable de la comunicacion Wifi, este modulo se regula la comunicacion wifi, habilita un modo programacion y el modo  */
/*  OTA para la actualizacion a distancia.                                                                                         */
/***********************************************************************************************************************************/
/*   inicioWifi() -> modoSoftAP(); -> serverConf(); -> guardarConfWifi();
 *                                                     escanearRedes();
 *                                                     leerConfSSID();
 *                                                     kernelpanic();
 *                -> modoNormal(); -> (Conecta o no) -> Sale
*/
#include "ioWIFI.h"

//Declaracion para SERVIDOR
ESP8266WebServer server(80);   //Instanciamos server como objeto de la clase WiFiServer escuchando el puerto 80

//Configuracion del las redes WIFI
struct confWifi {
   char ssid[longMAXSSID]; 
   char pass[longMAXPASS]; 
} datosConexion[3] = {
    "ModoConf",       /* ssid */  //Red Configuracion
    "loveIOT2018",     /* pass */  //Red Configuracion
    "",               /* ssid1 */ //Red Usuario
    "",               /* pass1 */ //Red Usuario
    "",               /* ssid2 */ //Red Debug
    "",               /* pass2 */ //Red Debug
    };


String mensaje = ""; //Anteriormente mensaje

IPAddress myIP;

/* --------CODIGO HTML PAGINA DE CONFIGURACION--------
*/

String paginaConfInicio = "<!DOCTYPE html>"
"<html>"
"<head>"
"<title>Modo Configuracion WIFI</title>"
"<meta charset='UTF-8'>"
"</head>"
"<body>"
"</form>"
"<form action='guardar_conf' method='get'>"
"SSID:<br><br>"
"<input class='input1' name='ssid' type='text'><br>"
"PASSWORD:<br><br>"
"<input class='input1' name='pass' type='password'><br><br>"
"<input class='boton' type='submit' value='GUARDAR'/><br><br>"
"</form>"
"<a href='escanear'><button class='boton'>ESCANEAR</button></a><br><br>"
"<a href='leerConfSSID'><button class='boton'>Leer Configuracion</button></a><br><br>"
"<a href='wifiNormal'><button class='boton'>Intento de conexion</button></a><br><br>"
"<a href='reset'><button class='boton'>Reiniciar Dispositivo</button></a><br><br>";

String paginaConfFinal = "</body>""</html>";                    //Cierre pagina

//ArduinoOTA.setPassword((const char *)"OTA1987");   //Clave para la OTA

//Configuracion Fija del WIFI AP
//IPAddress ipAP(192,168,1,1);
//IPAddress gwAP(192,168,1,1);
//IPAddress snetAP(255,255,255,0);

//Configuracion Fija del WIFI
//IPAddress ip(192,168,1,220);
//IPAddress subnet(255,255,255,0);
//IPAddress gateway(192,168,1,254);
//IPAddress wifiDNS1(8,8,8,8);
//IPAddress wifiDNS2(8,8,4,4);

/***************************/
/*     Setup del sistema   */
/***************************/
void inicioWifi(){
      pinMode(PulsadorConf, INPUT);                                   //Configuramos un interruptor para entrar en modo programacion
      
      #if defined(SERIAL_ENABLE) && defined(MODE_DEBUG)               //Solo si esta activado el puerto serie
      mostrarTituloSerial("Configurando WiFi");
      //Serial.println("DEBUG: Configurando WiFi");
      Serial.println("ValorPulsador Configuracion: " + PulsadorConf);
      #endif
      
      if (digitalRead(PulsadorConf) == 0) {modoSoftAP();}              //Si esta pulsado el boton con logica negativa entremos en modo configuracion
      else modoNormal();                                               //Realizamos el inicio normal de la conexion

}//Fin funcion
      
/***************************/
/*Funcion de inicio de Wifi*/
/***************************/

void modoNormal(){
  leerEEPROM(dirSSID).toCharArray(datosConexion[1].ssid, longMAXSSID);               //Extraemos el SSID de la EPROM
  leerEEPROM(dirPASS).toCharArray(datosConexion[1].pass, longMAXPASS);               //Extraemos el PASSWORD
  
  uint8_t flagConexion = 0;
  WiFi.mode(WIFI_STA);            //Fijamos IP Fija
//  WiFi.config(ip, gateway, subnet); //Fijamos los parametros de red

  
  if (conectarSSID(datosConexion[1].ssid,datosConexion[1].pass)){return;}     //Primer intento de conexion
  else if(conectarSSID(datosConexion[2].ssid,datosConexion[2].pass)){return;} //Segundo intento de conexion
  else {                                                                      //Conexion fallada, haz ...
      WiFi.mode (WIFI_OFF);                                                   //Desactiva el WIFI      

      #if defined(SERIAL_ENABLE) && defined(MODE_DEBUG)                       //Solo si esta activado el puerto serie
          Serial.print(" IMPOSIBLE DE CONECTAR");
          Serial.println("");
      #endif //SI NO CONECTO HIZO ESTE ELSE

      #if defined(NEEDCONECTION)                                              //Activo el modo modoSoftAP si el wifi no conecto y el flag de internet necesario existe
          modoSoftAP();                                                          
      #endif
  }

}//Fin funcion  ->> Vuelve a quien llamase a inicioWIFI

/**********************************************************************/
/*                         FUNCION CONECTAR                           */
/*  Esta funcion realiza el intento de conexion con SSDI y PASS que   */
/*           se le entrega y devuelve si lo consiguio o no            */
/**********************************************************************/

bool conectarSSID (String sSSID,String sPASS){

  #if defined(SERIAL_ENABLE) && defined(MODE_DEBUG) //Solo si esta activado el puerto serie
  Serial.println("");
  Serial.println("DEBUG: Probando conexion : Modo Normal");
  Serial.print("DEBUG: SSID_CONEXION:");
  Serial.println(sSSID);
  Serial.print("DEBUG: PASS_CONEXION:");
  Serial.println(sPASS);
  Serial.print("Conectando a... ");
  #endif

  WiFi.begin(sSSID.c_str(), sPASS.c_str());
  uint8_t intentos = 0;
  while (WiFi.status() != WL_CONNECTED && intentos < intentosMAX) {
    intentos++;
    delay(tiempoESPERA);
    #if defined(SERIAL_ENABLE) && defined(MODE_DEBUG)                             //Solo si esta activado el puerto serie
    Serial.print(".");
    #endif
  }
  if (WiFi.status() == WL_CONNECTED) {
     myIP = WiFi.localIP();
     #if defined(SERIAL_ENABLE) && defined(MODE_DEBUG)                     //Solo si esta activado el puerto serie
        Serial.println("");
        Serial.println("CONEXION CORRECTA");
        Serial.print("Direccion IP : ");
        Serial.print(WiFi.localIP());
        Serial.println("/");
     #endif
     return true;
     }
     
  return false;
}//Fin funcion  ->> Devuelve 0-NO CONECTA Y 1- Conectado
 

/**********************************************************************/
/*                         MODO CONFIGURACION                         */
/*  Se muestra la pagina de configuracion con las redes encontradas   */
/**********************************************************************/

void modoSoftAP(){

  WiFi.softAP(datosConexion[0].ssid, datosConexion[0].pass, 1, 1);      //Los datos de inicio son los alojado sobre la estructura en la posicion 0-SoftAP se puede añadir otras opciones (channel, hidden)
//  softAPConfig (ipAP, gwAP, snetAP);
  myIP = WiFi.softAPIP(); 
  
  #if defined(SERIAL_ENABLE) && defined(MODE_DEBUG)               //Solo si esta activado el puerto serie
      Serial.println("DEBUG: MODO CONFIGURACION");
      Serial.println("DEBUG: Wifi en modo SoftAP");
      Serial.print("DEBUG: SSID_APMODE:");
      Serial.println(datosConexion[0].ssid);
      Serial.print("DEBUG: PASS_APMODE:");
      Serial.println(datosConexion[0].pass);
      Serial.print("DEBUG: IP ACESS POINT:");
      Serial.println(myIP);
  #endif
  
  serverConf();                                                   // Configua la pagina de servidor
}


/**********************************************************************/
/*                         SERVER CONFIGURACION                       */
/*  Se muestra la pagina de configuracion con las redes encontradas   */
/**********************************************************************/
void serverConf(){

  //Mostrar pagina
  server.on("/", paginaConf);                   //Esta es la pagina de configuracion 
  //Opciones posibles
  server.on("/guardar_conf", guardarConfWifi);  //Graba en la eeprom la configuracion
  server.on("/escanear", escanearRedes);        //Escanean las redes wifi disponibles
  server.on("/leerConfSSID", leerConfSSID);     //Sirve para leer las conf de SSDI actual
  server.on("/wifiNormal", modoNormal);         //Sirve para leer las conf de SSDI actual
  server.on("/UpdateOTA", getUpdateOTA);        //El sistema se prepara para recibir una OTA por WIFI
  server.on("/reset",kernelPanic);              //Reiniciamos el sistema  
  //Cargamos el server
  server.on("/tools/volcadoEPROMMtoSERIAL", volcadorEEPROM);     //Herramientas de comprobacion del codigo
  server.begin();

  #if defined(SERIAL_ENABLE) && defined(MODE_DEBUG) //Solo si esta activado el puerto serie
      Serial.println("DEBUG: WebServer iniciado...");
  #endif
  
  while (true) {
      server.handleClient();                    //Eschucha las conexiones entrantes
  }
}

/**********************************************************************/
/*                    ESCANEAR REDES WIFI                             */
/*     Se bucan las redes disponibles a la distancia del dispotivo    */
/**********************************************************************/

void escanearRedes(){  
  int n = WiFi.scanNetworks(); //devuelve el nÃºmero de redes encontradas
  Serial.println("escaneo terminado");
  if (n == 0) { //si no encuentra ninguna red
    Serial.println("no se encontraron redes");
    mensaje = "no se encontraron redes";
  }  
  else
  {
    Serial.print(n);
    Serial.println(" redes encontradas");
    mensaje = "";
    for (int i = 0; i < n; ++i)
    {
      // agrega al STRING "mensaje" la informaciÃ³n de las redes encontradas 
      mensaje = (mensaje) + "<p>" + String(i + 1) + ": " + WiFi.SSID(i) + " (" + WiFi.RSSI(i) + ") Ch: " + WiFi.channel(i) + " Enc: " + WiFi.encryptionType(i) + " </p>\r\n";
      //WiFi.encryptionType 5:WEP 2:WPA/PSK 4:WPA2/PSK 7:open network 8:WPA/WPA2/PSK
      delay(10);
    }
    Serial.println(mensaje);
    paginaConf();
  }
}

/**********************************************************************/
/*                    Leer la SSID Y PASS                             */
/*        Lee los datos guardados en la epromm y los muestra          */
/**********************************************************************/

void leerConfSSID(){
      leerEEPROM(dirSSID).toCharArray(datosConexion[1].ssid, longMAXSSID);               //Extraemos el SSID de la EPROM
      leerEEPROM(dirPASS).toCharArray(datosConexion[1].pass, longMAXPASS);               //Extraemos el PASSWORD
     
      Serial.print("ssid : *");
      Serial.println(datosConexion[1].ssid);
      mensaje = (mensaje) + "<p>" + "ssid :" + (datosConexion[1].ssid) + " Password: " + (datosConexion[1].pass) + " </p>\r\n";
      paginaConf();
}//Fin funcion

/**********************************************************************/
/*                    PAGINA DE CONFIGURACION                         */
/*             Se confecciona la pagina a mostrar                     */
/**********************************************************************/

void paginaConf(){
  server.send(200, "text/html", paginaConfInicio + mensaje + paginaConfFinal); //Inicio pag + mensaje + cierre pagina
}//Fin funcion

/**********************************************************************/
/*               Grabar en la EEPROM SSID Y PASS                      */
/*                                                                    */
/**********************************************************************/

void guardarConfWifi(){
  
//  Serial.println(server.arg("ssid"));//Recibimos los valores que envia por GET el formulario web
    grabarEEPROM(dirSSID,server.arg("ssid"));
//  Serial.println(server.arg("pass"));
    grabarEEPROM(dirPASS,server.arg("pass"));

  mensaje = "Configuracion Guardada...";
  paginaConf();
}

/**********************************************************************/
/*                        Actualizacion OTA                           */
/*                                                                    */
/**********************************************************************/

void getUpdateOTA() {
  #ifdef SUPPORT_UPDATE_OTA                                  //DESABILITA EL SOPORTE OTA HACIENDO QUE NO SE COMPILE POR EL RIESGO QUE ENTRAÑA
  ArduinoOTA.onStart([]() {Serial.println("Start");});
  ArduinoOTA.onEnd([]() {Serial.println("\nEnd");});
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {Serial.printf("Progress: %u%%\r", (progress / (total / 100)));});
  ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  
  Serial.println("Esperando OTA");
  
  while (1){
      Serial.print(".");
      ArduinoOTA.handle();
  }
#endif  
}//FIN FUNCION


