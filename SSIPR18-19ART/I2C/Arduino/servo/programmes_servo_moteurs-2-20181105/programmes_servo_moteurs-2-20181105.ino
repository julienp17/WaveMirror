/*

  Commande de servo-moteur par impulsion

  Nanomaître 2015

  Le servo est connecté au pin 8 de l'arduino

*/

int periode = 20000; // période entre chaque début d'impulsion en microsecondes

int pinServo = 8; // variable pour le pin connecté à la commande du servo

int angle = 180;
int tempsMemoire = 0;

void setup() {

  pinMode(pinServo, OUTPUT); // on prépare le pin en mode OUTPUT

  digitalWrite(pinServo, LOW); // on l'initialise à l'état bas
  Serial.begin(9600);
}


//boucle principale

void loop() {

  //for (int angle = 0; angle <= 180; angle += 10) { //on fait varier l'angle de 0 à 180° par tranche de 20°

  setAngle(angle);// on appelle la fonction setAngle définie plus bas
  //delay(80);
  //}
  /*for (int angle = 0; angle <= 180; angle += 10) { //on fait varier l'angle de 0 à 180° par tranche de 20°

    setAngle(180 - angle); // on appelle la fonction setAngle définie plus bas
    //delay(80);
    }*/
}


//fonction setAngle pour envoyer les impulsions

void setAngle(int a) {

  int duree = map(a, 0, 180, 1000 , 2000); // on transforme l'angle en microsecondes et on stocke dans la variable duree (180, 545, 2500)

  digitalWrite(pinServo, LOW); //on met le pin à l'état bas



  // la boucle qui suit est nécessaire

  // pour laisser le temps au servo d'aller à sa position

  //for (int t = 0; t < 20; t++) {

  tempsMemoire = micros();
  Serial.print  ("micros1 : ");
  Serial.println  (micros());
  Serial.print  ("tempsMemoire : ");
  Serial.println  (tempsMemoire);
  do
  {
    digitalWrite(pinServo, HIGH); // on envoie l'impulsion

    // statement block

  } while (micros() <= tempsMemoire + duree);
  Serial.print  ("tempsMemoire : ");
  Serial.println  (tempsMemoire);
  Serial.print  ("micros2 : ");
  Serial.println  (micros());
  do
  {
    digitalWrite(pinServo, LOW); //

    // statement block

  } while (micros() <= (tempsMemoire + (20000 - duree)));
  Serial.print  ("dif : ");
  Serial.println  ((20000 - duree));
  Serial.print  ("micros3 : ");
  Serial.println  (micros());

  //delayMicroseconds(periode - duree); // on attend le temps restant pour atteindre la période
  /*Serial.print  ("duree : ");
    Serial.print  (duree);
    Serial.print  (" - temps restant : ");
    Serial.println  (periode - duree);*/
}


