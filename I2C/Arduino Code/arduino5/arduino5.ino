#include <Wire.h>
 
#define SLAVE_ADDRESS 0x07
int nombre = 0;

void setup() {
 // Initialisation du port série
 Serial.begin(9600);
 Serial.println("Arduino n°5 activé");
 
 // Initilisation I2C de l'Arduino en tant qu'esclave
 Wire.begin(SLAVE_ADDRESS);
 
 // Definition des fonctions pour communiquer en I2C
 Wire.onReceive(receiveData);
 Wire.onRequest(sendData);
}
 
void loop() {
 delay(100);
}
 
// Fonction pour recevoir des données
void receiveData(int byteCount){
 
 while(Wire.available()) {
  nombre = Wire.read();
  Serial.print("Numero recue : ");
  Serial.println(nombre);
 }
}
 
// Fonciton pour envoyer des données
void sendData(){
}
