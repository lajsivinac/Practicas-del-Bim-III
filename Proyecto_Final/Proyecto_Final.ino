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

// Definición de pines
const int pin_BT_Rx = 11;
const int pin_BT_Tx = 10;
const int pin_Triac = 3;

// Comunicación Serial con el Bluetooth
SoftwareSerial BT(pin_BT_Rx, pin_BT_Tx);

// Variables globales
volatile int contador = 0;
volatile boolean hayCruceCero = false;
int tiempoInterrupcion = 100;
int nivelDimerizado;

void setup() {
  BT.begin(9600);      // Inicialización del Bluetooth
  Serial.begin(9600);  // Inicialización del Serial Monitor

  // Configuración de pines
  pinMode(pin_Triac, OUTPUT);

  // Configuración de interrupciones
  attachInterrupt(digitalPinToInterrupt(2), detectarCruceCero, RISING);  // Pin 2 para interrupción de cruce por cero
  Timer1.initialize(tiempoInterrupcion);  // Inicialización del temporizador
  Timer1.attachInterrupt(controlarDimerizacion, tiempoInterrupcion);  // Asignación de la función de dimmer
}

void detectarCruceCero() {
  hayCruceCero = true;
  contador = 0;  // Reinicio de contador
  digitalWrite(pin_Triac, LOW);  // Apagar Triac en cruce por cero
}

void controlarDimerizacion() {
  if (hayCruceCero) {
    if (contador >= nivelDimerizado) {
      digitalWrite(pin_Triac, HIGH);  // Encender Triac después del tiempo correspondiente
      contador = 0;
      hayCruceCero = false;
    } else {
      contador++;
    }
  }
}

void loop() {
  // Lectura de intensidad desde el módulo Bluetooth
  if (BT.available() > 0) {
    int intensidad = BT.read();  // Leer la intensidad desde Bluetooth
    nivelDimerizado = map(intensidad, 0, 100, 83, 0);  // Mapear intensidad de 0-100 al control del Triac
  }
}
