int periode = 20000; 
int pinServo = 2; 
int tempsTransition = 5;

void setup() {
  pinMode(pinServo, OUTPUT); 
  digitalWrite(pinServo, LOW); 
}

void loop() {
  
  for (int angle = 0; angle <= 180; angle += 1) { 
    setAngle(angle);
    delay(tempsTransition);
  }
  
  for (int angle = 0; angle <= 180; angle += 1) { 
    setAngle(180 - angle); 
    delay(tempsTransition);
  }
}

void setAngle(int angle) {

  int duree = map(angle, 0, 180, 545, 2500); // on transforme l'angle en microsecondes et on stocke dans la variable duree (180, 545, 2500)

  digitalWrite(pinServo, LOW); //on met le pin à l'état bas

  digitalWrite(pinServo, HIGH); // on envoie l'impulsion

  delayMicroseconds(duree); // pendant la bonne durée

  digitalWrite(pinServo, LOW); // on stoppe l'impulsion

  delayMicroseconds(periode - duree); // on attend le temps restant pour atteindre la période

}
