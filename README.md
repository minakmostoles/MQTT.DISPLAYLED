# MQTT.DISPLAYLED
Prueba conceptual del uso de MQTT y un Display Led con un Wemos. Es un extracto de un proyecto mayor. Parte de los módulos no están compartidos por el momento

Concepto de conexión de una matrix LED como display para mostrar los mensajes que se reciben de un servidor MQTT. También podemos conectar un sensor de humedad y de temperatura SHT30 y que se publique por MQTT sus valores.
Este código pertenece a un proyecto mayor por lo que su optimizacion no es correcta ya que hay muchos módulos no introducidos o que este programa nos lo usa.
Cuando tenga un tiempo publicare mas información. 
Configurar el SSDI Y PASS del wifi en el modulo ioWifi.cpp o configurar lo mediante el modo configuración:
SSDI :ModoConf 
PASS :_loveIOT2018

Configurar los datos de mqtt en ioMQTT.h
