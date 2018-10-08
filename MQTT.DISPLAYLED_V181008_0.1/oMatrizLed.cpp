/***********************************************************************************************************************************/
/*                                                   MATRIZ LED                                                                    */
/*                                             ModeDEBUG V_180204.0                                                                */
/***********************************************************************************************************************************/

#include "oMatrizLed.h"

/*          PANTALLA          */
int pinCS = 2;                         // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI ) din=11 cs=10 clk=13
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

//String tape = "Bea y Mario"; //String de uso

int spacer = 1;
int width = 5 + spacer; // The font width is 5 pixels

void setupMatrizLed() {
  /*Configuracion pantalla*/

  matrix.setIntensity(matrizBrillo);      // Brillo iluminacion
  matrix.setRotation(0, 1);               // 1 Matriz
  matrix.setRotation(1, 1);               // 2 Matriz
  matrix.setRotation(2, 1);               // 3 Matriz
  matrix.setRotation(3, 1);               // 4 Matriz

}

//***********************************************************************
// Funcion escribir en pantalla

void mostrarMensaje(String mensaje) {
  
    int lgmensj = mensaje.length();
    #if defined(SERIAL_ENABLE) && defined(MODE_DEBUG_SEC) //Solo si esta activado el puerto serie
    Serial.print("DEBUG: Escribiendo mensaje en matriz ->");
    Serial.println(mensaje);
    Serial.print("DEBUG: Tamaño ->");
    Serial.println(lgmensj);
    #endif
//    int lgmensj = mensaje.length();
//    corregirMsg(&mensaje);                                                                  //Funcion que corrige el mensaje si tiene menos de 11 caracteres
  
  for ( int i = 0 ; i < width * mensaje.length() + matrix.width() - 1 - spacer; i++ ) { 

    matrix.fillScreen(LOW);
    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;   // 
    int y = (matrix.height() - 8) / 2;          // Centramos el texto en vertical
   

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < mensaje.length() ) {
        matrix.drawChar(x, y, mensaje[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }

    matrix.write(); // Send bitmap to display
  
    delay(tEspera);
  }
}//Fin funcion


void mostrarBMP(String BMP) {
  
  
}


void matrizONOFF(bool aux) {
  matrix.shutdown (aux);
}//Fin funcion



//***********************************************************************
//Esta funcion corrige el mensaje antes de mostrar si no cumple las dimensiones
/*
void corregirMsg(String *tape) {
  int ltape = tape.length()
  if (tape.length() < 11) {
    for (int i=0; i <= tape.length()-11; i++){ *tape = *tape + " "; //Añado espacios hasta llegar al minimo de espacios
    }
  }//Fin Correccion
}//Fin Funcion
*/
