#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SENSOR_HALL_PIN 2
#define SENSOR_IR_PIN 3
#define POT_PIN A0
#define MOTOR_PIN1 8
#define MOTOR_PIN2 9
#define MOTOR_PIN3 10
#define MOTOR_PIN4 11


#define LCD_ADDR 0x27
#define LCD_ROWS 2
#define LCD_COLS 16
LiquidCrystal_I2C pantalla(LCD_ADDR, LCD_COLS, LCD_ROWS);


unsigned int lecturaPot;
unsigned long cuentaRevoluciones = 0;
unsigned long tiempoPrevio = 0;
bool estadoHall = false;
bool estadoIR = false;
volatile bool bandera = false;

int pasosMotor[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

unsigned int leerADC(int pin) {
  return analogRead(pin);
}

void interrupcionHall() {
  cuentaRevoluciones++;
  bandera = true;
}

void setup() {
  
  Serial.begin(9600);

 
  pinMode(SENSOR_HALL_PIN, INPUT);
  pinMode(SENSOR_IR_PIN, INPUT);
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(SENSOR_HALL_PIN), interrupcionHall, FALLING);

 
  pantalla.init();
  pantalla.backlight();
  pantalla.setCursor(0, 0);
  pantalla.print("Contador de rev.");


  tiempoPrevio = millis();
}

void loop() {
  
  estadoIR = digitalRead(SENSOR_IR_PIN);

  if (estadoIR == LOW) {
    
    lecturaPot = leerADC(POT_PIN);
    int velocidadMotor = map(lecturaPot, 0, 1023, 1, 3);

    
    for (int i = 0; i < 8; i++) {
      digitalWrite(MOTOR_PIN1, pasosMotor[i][0]);
      digitalWrite(MOTOR_PIN2, pasosMotor[i][1]);
      digitalWrite(MOTOR_PIN3, pasosMotor[i][2]);
      digitalWrite(MOTOR_PIN4, pasosMotor[i][3]);
      delay(velocidadMotor);
    }

    if (millis() - tiempoPrevio >= 1000) {
      tiempoPrevio = millis();
      pantalla.setCursor(0, 1);
      pantalla.print("No. De Rev: ");
      pantalla.print(cuentaRevoluciones);
      pantalla.print("    ");
      cuentaRevoluciones = 0; 
    }
  } else {
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, LOW);
    digitalWrite(MOTOR_PIN3, LOW);
    digitalWrite(MOTOR_PIN4, LOW);
    pantalla.setCursor(0, 1);
    pantalla.print("No. De Rev: 0   ");
  }
}
