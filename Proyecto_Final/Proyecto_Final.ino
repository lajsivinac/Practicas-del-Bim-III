/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AM 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Final
   Dev: Ludwyn Steven ajsivinac Alonzo
   Fecha: 1/10/24
   link de la simulacion: 
   
*/
#include <SoftwareSerial.h>
#include <TimerOne.h>

int pinRx = 11;
int pinTx = 10;
int pinTriac = 3;

SoftwareSerial BT(pinRx, pinTx);


volatile int contador = 0;
volatile boolean hayCruceCero = false;
int tiempoInterrupcion = 100;
int nivelDimerizado;

void setup() {
  BT.begin(9600);      
  Serial.begin(9600);  

 
  pinMode(pinTriac, OUTPUT);

  // Configuración de interrupciones
  attachInterrupt(digitalPinToInterrupt(2), detectarCruceCero, RISING);  
  Timer1.initialize(tiempoInterrupcion);  
  Timer1.attachInterrupt(controlarDimerizacion, tiempoInterrupcion);  
}

void detectarCruceCero() {
  hayCruceCero = true;
  contador = 0;  
  digitalWrite(pinTriac, LOW);  
}

void controlarDimerizacion() {
  if (hayCruceCero) {
    if (contador >= nivelDimerizado) {
      digitalWrite(pinTriac, HIGH);  
      contador = 0;
      hayCruceCero = false;
    } else {
      contador++;
    }
  }
}

void loop() {
  if (BT.available() > 0) {
    int intensidad = BT.read();  
    nivelDimerizado = map(intensidad, 0, 100, 83, 0);  
  }
}
