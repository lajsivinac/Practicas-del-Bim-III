/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AM 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Practica 4
   Dev: Ludwyn Steven Ajsivinac Alonzo
   Fecha: 24 de julio
   link de la simulacion:   
*/
//Librerias
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          
#define SS_PIN          10
#define ledVerde        A3
#define ledRojo         A4           
#define buzzer          A5

MFRC522 mfrc522(SS_PIN, RST_PIN);   //
MFRC522::MIFARE_Key key;

byte tag1[4] = {0xE3, 0x9D, 0xFF, 0x0D};
byte tagActual[4];

void setup() {
  Serial.begin(9600);
   while (!Serial);    
   SPI.begin();        // inicia la comunicacion SPI
   mfrc522.PCD_Init(); //inicia la comunicacion con el modulo RFID
  salidas();
}

void loop() {
   if ( ! mfrc522.PICC_IsNewCardPresent()) 
        return;
 
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

 Serial.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
       
digitalWrite(ledVerde,LOW);       
digitalWrite(ledRojo,LOW);  
}

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
      Serial.print(buffer[i] < 0x10 ? " 0" : " ");
      Serial.print(buffer[i], HEX);
      tagActual[i] = buffer[i];
    }
          if(compararArray(tagActual,tag1)){              
          Serial.println(" Acceso Permitido...");
          digitalWrite(ledVerde,HIGH);
          digitalWrite(ledRojo,LOW);
          tone(buzzer, 200); 
          delay(4000);
          noTone(buzzer);
          }
          else {
            Serial.println(" Desconocido" );            
           digitalWrite(ledRojo,HIGH);
           digitalWrite(ledVerde,LOW);
           tone(buzzer, 400);
           delay(4000);
           noTone(buzzer);
            }       
}

boolean compararArray(byte array1[], byte array2[]){    

  if(array1[0] != array2[0]) return(false);
  if(array1[1] != array2[1]) return(false);
  if(array1[2] != array2[2]) return(false);
  if(array1[3] != array2[3]) return(false);
  return(true);
}
void salidas(){
     pinMode(ledVerde,OUTPUT);  
   pinMode(ledRojo,OUTPUT);
   pinMode(buzzer, OUTPUT);
}
