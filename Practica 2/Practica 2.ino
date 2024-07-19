/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AM 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Practica 2
   Dev: Ludwyn Steven Ajsivinac Alonzo
   Fecha: 18 de Julio
   link de la simulacion: 
   
*/
#include <Wire.h>
#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>
#include <SparkFun_ADXL345.h>


#define num1 2
#define num2 3
#define num3 4
#define num4 5
#define num5 6
#define num6 7
#define num7 8
#define num8 9
#define num9 A2
#define num10 A3

ADXL345 acelerometro_ADXL345 = ADXL345();
SoftwareSerial DFPlayerSerial(10, 11); 
DFRobotDFPlayerMini bocina;

int x;
int y;
int z;
float operacion;
float valx; 
float valy; 
float valz; 
float resultante;
int Medidor;
unsigned long lastTime = 0;
unsigned long currentTime = 0;

char PinesLed[] = {num1, num2, num3, num4, num5, num6, num7, num8, num9, num10};

void setup() {
  Serial.begin(9600);    
  Serial.println("Uso del acelerometro ADXL345");
  acelerometro_ADXL345.powerOn();
  acelerometro_ADXL345.setRangeSetting(2);
  DFPlayerSerial.begin(9600);
  bocina.begin(DFPlayerSerial);
  bocina.volume(30);    
  for(int i = 0; i < 10; i++)
  {
    pinMode(PinesLed[i], OUTPUT);
  }
}

void loop() {
  
  acelerometro_ADXL345.readAccel(&x, &y, &z);
  valx = x * 0.04;
  valy = y * 0.04;
  valz = z * 0.04;
  operacion = ((valx*valx) + (valy*valy) + (valz*valz));
  resultante = sqrt(operacion);
  Serial.println(resultante);
  
  Medidor = map(resultante,10.89, 25.10, 0, 10);

  if(Medidor == 1){
    for(int i = 0; i < 1; i++){
      digitalWrite(PinesLed[i], HIGH);}
    actualizacion();}

  if(Medidor == 2){
    for(int i = 0; i < 2; i++){
      digitalWrite(PinesLed[i], HIGH);}
    actualizacion();}

  if(Medidor == 3){
    for(int i = 0; i < 3; i++){
      digitalWrite(PinesLed[i], HIGH);}
    actualizacion();}

  if(Medidor == 4){
    for(int i = 0; i < 4; i++){
      digitalWrite(PinesLed[i], HIGH);}
    actualizacion();}

  if(Medidor == 5){
    for(int i = 0; i < 5; i++){
      digitalWrite(PinesLed[i], HIGH);}
    actualizacion();}

  if(Medidor == 6){
    for(int i = 0; i < 6; i++){
      digitalWrite(PinesLed[i], HIGH);}
    bocina.play(1);
    delay(6000);
    actualizacion();}

  if(Medidor == 7){
    for(int i = 0; i < 7; i++){
      digitalWrite(PinesLed[i], HIGH);}
    bocina.play(1);
    delay(6000);
    actualizacion();}

  if(Medidor == 8){
    for(int i = 0; i < 8; i++){
      digitalWrite(PinesLed[i], HIGH);}
    bocina.play(1);
    delay(6000);
    actualizacion();}

  if(Medidor == 9){
    for(int i = 0; i < 9; i++){
      digitalWrite(PinesLed[i], HIGH);}
     bocina.play(1);
     delay(6000);
     actualizacion();}

  if(Medidor == 10){
    for(int i = 0; i < 10; i++){
      digitalWrite(PinesLed[i], HIGH);}
    bocina.play(1);
    delay(6000);
    actualizacion();}
  delay(200); 
}

void actualizacion(){
  for(int i = 0; i < 10; i++){
      digitalWrite(PinesLed[i], LOW);}
  }
