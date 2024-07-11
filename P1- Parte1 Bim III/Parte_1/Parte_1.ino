/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AM 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Contador de aforo
   Dev: Ludwyn Steven ajsivinac Alonzo
   Fecha: 20 de Junio
   link de la simulacion: 
   
*/
#include <Adafruit_NeoPixel.h> 
#define PIN 4
#define NUMPIXELS 1

Adafruit_NeoPixel pixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int Trigger = 3;
int Echo = 2;
long Sensor;
long Distancia;
int Deteccion = 0;
int num = 0;
int maxPersonas = 9; 

int numero9 [] = {5, 6, 7, 10, 11};
int numero8 [] = {5, 6, 7, 8, 9, 10, 11};
int numero7 [] = {5, 6, 7};
int numero6 [] = {5, 10, 11, 7, 8, 9};
int numero5 [] = {5, 10, 11, 8, 7};
int numero4 [] = {6, 7, 10, 11};
int numero3 [] = {5, 6, 7, 8, 11};
int numero2 [] = {5, 6, 11, 9, 8};
int numero1 [] = {6, 7};
int numero0 [] = {5, 6, 7, 8, 10, 9};
int pines[] = {5, 6, 7, 8, 9, 10, 11};

void setup() {
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);            
  pinMode(Echo, INPUT);
  salidas();
  pixel.begin();
  pixel.setPixelColor(0, 0, 255, 0); // Verde
  pixel.show();
}

void loop() {
  medirDistancia();
  Personas();
  conteo();
  delay(1000);
}

void medirDistancia() {
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  Sensor = pulseIn(Echo, HIGH);
  Distancia = Sensor / 59;
  Serial.print("Distancia: ");
  Serial.print(Distancia);
  Serial.print("cm ");
  Serial.println();
  
}

void pinesdesalida() {
  for (int i = 0; i < 7; i++) {
    pinMode(pines[i], OUTPUT);
  }
}

void Personas() {
  if (Distancia >= 6 && Distancia <= 10) {
    Serial.println("Entrada detectada");
    Deteccion++;
    if (Deteccion <= maxPersonas) {
      pixel.setPixelColor(0, 0, 255, 0); // Verde
    }
    pixel.show();
  }
}

void conteo() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(pines[i], LOW);
  }
  if (Deteccion > maxPersonas){
    digitalWrite(11, HIGH);
}

 else {
    switch (Deteccion) {
      case 0:
        for (int i = 0; i < 6; i++)
          digitalWrite(numero0[i], HIGH);
        break;
      case 1:
        for (int i = 0; i < 2; i++)
          digitalWrite(numero1[i], HIGH);
        break;
      case 2:
        for (int i = 0; i < 5; i++)
          digitalWrite(numero2[i], HIGH);
        break;
      case 3:
        for (int i = 0; i < 5; i++) 
          digitalWrite(numero3[i], HIGH);
        break;
      case 4:
        for (int i = 0; i < 4; i++) 
          digitalWrite(numero4[i], HIGH);
        break;
      case 5:
        for (int i = 0; i < 5; i++) 
          digitalWrite(numero5[i], HIGH);
        break;
      
      case 6:
        for (int i = 0; i < 6; i++) 
          
          digitalWrite(numero6[i], HIGH);
        break;
      case 7:
        for (int i = 0; i < 3; i++) 
          digitalWrite(numero7[i], HIGH);
        break;
      case 8:
        for (int i = 0; i < 7; i++) 
          digitalWrite(numero8[i], HIGH);
        break;
      case 9:
        for (int i = 0; i < 5; i++) 
          digitalWrite(numero9[i], HIGH);  
        delay(100);
        pixel.setPixelColor(0, 255, 0, 0); // Rojo
        pixel.show();
        break; 
    
    }
  }
}

void salidas() {
  for (int p = 0; p < 7; p++) {
    pinMode(pines[p], OUTPUT);
  }
}

