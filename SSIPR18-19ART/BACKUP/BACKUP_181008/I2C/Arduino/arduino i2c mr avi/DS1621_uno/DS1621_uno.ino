#include <Wire.h>

#define DS1621_ID 0x90 >> 1      
    
void setup() {
   Serial.begin(9600); 
   Wire.begin();
   Wire.beginTransmission(DS1621_ID);           // connection DS1621 (#0)
   Wire.write(0xAC);                            // Access Config
   Wire.write(0x01);                            // one shot
   Wire.endTransmission();
}
   
void loop() {
   int val = 0;                                 //
   int valafd= 0;                                //
   Wire.beginTransmission(DS1621_ID);           // restart
   Wire.write(0xEE);                            // start conversion
   Wire.endTransmission();
   delay(800);   // give time for measurement
  
   Wire.beginTransmission(DS1621_ID);
   Wire.write(0xAA);                          // read temp
   Wire.endTransmission();
   Wire.requestFrom(DS1621_ID, 2);            // request one byte from DS1621
   val = Wire.read(); 
   valafd = Wire.read();                      // get whole degrees reading
   Wire.endTransmission();
   float valafe= int(val);
   if (valafd==0x80)
      valafe+=0.5;  
     
   //  plus précis...
   Wire.beginTransmission(DS1621_ID);
   Wire.write(0xA8);                          
   Wire.endTransmission();
   Wire.requestFrom(DS1621_ID, 1);              // request one byte from DS1621
   float Count_Remain = Wire.read(); 
   Wire.endTransmission();
   Wire.beginTransmission(DS1621_ID);
   Wire.write(0xA9);                        
   Wire.endTransmission();
   Wire.requestFrom(DS1621_ID, 1);              // request one byte from DS1621
   float Count_Per_C = Wire.read(); 
   Wire.endTransmission();
   
   float valr = float(val)-0.25+((Count_Per_C - Count_Remain) / Count_Per_C);
 
    Serial.print("sensor = " );  
    Serial.print(valafe);  
    Serial.print("  -->  " );
    Serial.println(valr);      

  delay(1000); 
}
