/***********************************************************************************************************************************/
/*                         Modulo reposable de tomar la medida humedad y temperatura de la SHILD SHT30                             */
/*                                                  ModuloSHT30 V_18508.0                                                         */
/*                                                                                                                                 */
/***********************************************************************************************************************************/

#include "iSHT30.h"

int8_t offsetTemp =-4;
int8_t offsetHum = 0;

SHT3X sht30(0x45);    // Direccion 0X45

void setupSHT30(){


}


//***********************************************************************
// Funcion informacion de la shield SHT30 en STRING para mostrar en display

String GetTempSHT30 (bool returnONLYTEMP) {
  String sht30Temp = "";
  if(sht30.get()==0){
    //Serial.println(sht30.cTemp);
    sht30Temp = sht30.cTemp+offsetTemp;
    if (returnONLYTEMP) return sht30Temp;
    sht30Temp = "Temp:" + sht30Temp;
  }
  
  else
  {
     sht30Temp =  "Temp:Error!";
  }
  
  return sht30Temp;
  
}//Fin funcion

//***********************************************************************
// Funcion informacion de la shield SHT30 en STRING para mostrar en display

String GetHumdSHT30(bool returnONLYHUMD) {
  String sht30Humd = "";
  
  if(sht30.get()==0){
    //Serial.println(sht30.humidity);
    sht30Humd = sht30.humidity+offsetTemp;
    if (returnONLYHUMD) return sht30Humd;
    sht30Humd = "Humd:" + sht30Humd;
  }
  
  else
  {
     sht30Humd =  "Humd:Error!";
  }
  
  return sht30Humd;
  
}//Fin funcion
