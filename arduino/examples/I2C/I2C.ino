#include <Wire.h>
 
#define SLAVE_ADDRESS 0x03 // addresse de l'esclave (arduino)
int nombre = 0;
int numero = 0;
int couleur;
int couleurs[1];
int index = 0;

void setup() {
   // Initialisation du port série
   Serial.begin(9600);
   Serial.println("Arduino n°1 activé");
   
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
//void receiveData(int byteCount){
// 
// while(Wire.available()) {
//  if (numero >= 10){
//    numero=0;
//    Serial.println("");
//    Serial.println("Nouvelle valeurs");
//  }
//  numero++;
//  nombre = Wire.read();
//  Serial.print("Numero ");
//  Serial.print(numero);
//  Serial.print(" recue : " );
//  Serial.println(nombre);
// }
//}

void receiveData(int byteCount) {
  while(Wire.available()){
    couleur = Wire.read();
    index++;
    if (index >= sizeof(couleurs))
        index = 0;
    couleurs[index] = couleur;
  }
  for (int i = 0; i < sizeof(couleurs); i++) {
    Serial.print("Servo ");
    Serial.print(i + 1);
    Serial.print(" = ");
    Serial.println(couleurs[i]);
  }
}
 
// Fonction pour envoyer des données
void sendData(){
}
