#include <Wire.h>

#define n 8 //longitud de la palabra de entrada (challenge)

int X[n] = {0,1,0,1,1,0,1,0}; //CHallenge de entrada para la PUF
int Y;

void setup() {
  
   Serial.begin(9600); 

   pinMode(A3, OUTPUT); //pines para los challenges
   pinMode(10, OUTPUT);
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);
   pinMode(4, OUTPUT);
   pinMode(5, OUTPUT);
   pinMode(6, OUTPUT);
   pinMode(7, OUTPUT);
    
   pinMode(13, INPUT); //pin para la respuesta
}

void loop() {

 digitalWrite(A3,X[0]);
 digitalWrite(10,X[1]); 
 digitalWrite(2,X[2]);
 digitalWrite(3,X[3]);
 digitalWrite(4,X[4]);
 digitalWrite(5,X[5]);
 digitalWrite(6,X[6]);
 digitalWrite(7,X[7]);
 

 Serial.println("------------------------------------------------------");
 Serial.print("OUT: ");
 Serial.println(digitalRead(13)); //salida de la puf (response)
 
}
