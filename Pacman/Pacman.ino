/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AM 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Pacman 
   Dev: Ludwyn Steven Ajsivinac Alonzo
   Fecha: 18 de Julio
*/
//Librerias
#include <LedControl.h> //Libreria que me permita usar el IC MAX7219 (matriz led)

//directivas de preprocesador
#define din_matrix  2  //pin2 del arduino conectado al pin DIN de la matriz led
#define cs_matrix   3  //pin2 del arduino conectado al pin CS de la matriz led
#define clk_matrix  4  //pin4 del arduino conectado al pin CLK de la matriz led
#define canal_pot   A1  //A0 del arduino conectado al pin pot




//Constructores
//Voy a controlar con el objeto PacmanMatrix un arreglo de 1 matriz led
LedControl PacmanMatrix = LedControl(din_matrix, clk_matrix, cs_matrix, 1);

//Variable
byte pacman_boca_abierta[8]= {
  B00111100,
  B01000010,
  B10000100,
  B10001000,
  B10001000,
  B10000100,
  B01000010,
  B00111100
};
byte pacman_boca_cerrada[8]= {
  B00111100,
  B01000010,
  B10000001,
  B10000001,
  B10001111,
  B10000001,
  B01000010,
  B00111100
};


void setup() {
   Serial.begin(9600); //Inicio la comunicacion serial a 9600 baudios
   PacmanMatrix.shutdown(0, false);
   PacmanMatrix.setIntensity(0,15);
   PacmanMatrix.clearDisplay(0);
   Serial.println("Uso de la matriz led");
   
}

void loop() {
 int valor_adc_pot = analogRead(canal_pot); 
 int velocidad = map(valor_adc_pot,0,1023,100,5000); 
 pacmanabierto();
 delay(velocidad);
 pacmancerrado();
 delay(velocidad);

}
void pacmanabierto() {
  for(int i=0; i<8; i++)
  {
    PacmanMatrix.setRow(0,i,pacman_boca_abierta[i]);
  }
  
}
void pacmancerrado() {
  for(int i=0; i<8; i++)
  {
    PacmanMatrix.setRow(0,i,pacman_boca_cerrada[i]);
  }
  
}
