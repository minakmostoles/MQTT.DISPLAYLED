/***********************************************************************************************************************************/
/*                         Modulo reposable de tomar la medida humedad y temperatura de la SHILD SHT30                             */
/*                                                     ModuloSHT30 V_171225.0                                                      */
/*                                                                                                                                 */
/***********************************************************************************************************************************/

#ifndef iSHT30_H
#define iSHT30_H

#include <WEMOS_SHT3X.h>

void setupSHT30();              //No se utiliza
String GetTempSHT30(bool);      //0. TEMP : String(Temperatura) / 1.String(Temperatura)
String GetHumdSHT30(bool);      //0. HUMD : String(Humedad)     / 1.String(Humedad)

#endif //__SoporteSHT30_H

