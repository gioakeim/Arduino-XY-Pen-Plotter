#include "AFMotor.h"
#include <Servo.h>

AF_Stepper Stepper1(200,1);//Μ1 Μ2 Υ ΑΞΟΝΑΣ ΚΑΤΩ 0 
AF_Stepper Stepper2(200,2);//Μ3 Μ4 Χ ΑΞΟΝΑΣ ΔΕΞΙΑ 0
Servo my_servo; 
float x,y, panw, a,b,z;
String command , readString , c ;
float i ,j;

const int penZUp = 85;
const float penZDown = 40;

void setup() {
  
  Stepper1.setSpeed(200);
  Stepper2.setSpeed(200);
  my_servo.attach(10); 
  penUp() ; 
  Serial.begin(9600);

}

void loop() 
{

if (Serial.available())
  {
     
     Serial.println("Give Shape");
     command = Serial.readStringUntil('\n');
  }
     if (command == "square")
  {
    square();
  }
    else if (command == "cross")
  {
    cross();  
    }
    else if (command == "triangle")
    {
    triangle();
      }
     else if (command == "square2")
    {
     square2();
      }
     else if (command == "zero")
    {
     zero();
      }

   else if (command == "line")
  {
    line();  
    }
    command = "";

     

 }



  void line(){

   while(Serial.available() == 0) {}  
    c  = Serial.readString();  
    
    Serial.println( c );
    
      delay(300);
     
   String  x1 = c.substring(5 , 8);        
   String  y1 = c.substring(8 , 11); 
       delay(300);

     float a = x1.toFloat() ;
     float b = y1.toFloat() ;
     
    
   
     if (a <= 36){
        x = (a * 245)/36;
        y = (b * 245)/36;
        delay(900);
        Stepper2.step(x, FORWARD,MICROSTEP);
        Stepper1.step(y, FORWARD,MICROSTEP); 
        Stepper2.step(x, BACKWARD,MICROSTEP);
        Stepper1.step(y, BACKWARD,MICROSTEP); 
     }

     delay(300); 
  
    penUp();
    delay(300);
   
    }






 void square(){

   penDown();
   delay(300);

Serial.println("Give X");
while(Serial.available() == 0) {}   

     panw = Serial.parseFloat();

        
start:
    if (panw <= 36){
        x = (panw * 245)/36;
        Stepper2.step(x, FORWARD,MICROSTEP); // aristera
        
        Stepper1.step(x, FORWARD,MICROSTEP); // panw
        
        Stepper2.step(x,BACKWARD,MICROSTEP); // dexia
        
        Stepper1.step(x,BACKWARD,MICROSTEP); // katw
        
    }
   else {
        Serial.println("Give lower value");
        Serial.println("Give X");
        while(Serial.available() == 0) {}
         panw = Serial.parseFloat();
         goto start;
   }
    
  delay(300); 
  
  penUp();
  delay(300);
 }

 void cross() {
  
  penUp(); 
  delay(300); 
   
  Stepper1.step(125, FORWARD,MICROSTEP); //Υ ΜΕΣΟ
  Stepper2.step(125, FORWARD,MICROSTEP); //Υ ΜΕΣΟ
  cross:
  Serial.println("Give X");
  while(Serial.available() == 0) {}   

  a = Serial.parseFloat();
  penDown();
  delay(300);
   if ( a <= 17) {
     x = (a * 245)/36;
        Stepper2.step(x, FORWARD,MICROSTEP);
        Stepper2.step(x, BACKWARD,MICROSTEP);
        Stepper2.step(x, BACKWARD,MICROSTEP);
        Stepper2.step(x, FORWARD,MICROSTEP);
        delay(300);
      
        Stepper1.step(x, FORWARD,MICROSTEP);
        Stepper1.step(x, BACKWARD,MICROSTEP);
        Stepper1.step(x, BACKWARD,MICROSTEP);
        Stepper1.step(x, FORWARD,MICROSTEP);
   }
   else {
        Serial.println("Give  lower value");
        goto cross;
   }

  
  penUp();
  delay(300);
  
  }

void triangle() {
  
  penDown();
  delay(300);
       
  for( i= 0.001 , j=0.001 ; (i <= 1.06) && (j <= 1.06); i = i + 0.001 , j = j + 0.001){
     Stepper2.step(i, FORWARD,MICROSTEP); //Χ ΑΡΙΣΤΕΡΑ
     Stepper1.step(j, FORWARD,MICROSTEP); //Υ ΠΑΝΩ
  
   } 
   
    for (i=0.001 , j=0.001 ; (i <= 1.06) && (j <= 1.06); i = i + 0.001 , j = j + 0.001){
    Stepper2.step(i, FORWARD,MICROSTEP);
    Stepper1.step(j, BACKWARD,MICROSTEP);
   } 
   
 //Stepper1.step(245, BACKWARD,MICROSTEP);
   Stepper2.step(245, BACKWARD,MICROSTEP);
   delay(300);
 
   penUp(); 
   delay(300);

  }

void square2(){



Serial.println("Give X");

while(Serial.available() == 0) {}   

        panw = Serial.parseFloat();
        

        
start:
for ( int o = 10; o <= 30; o = o + 10){
   Stepper1.step(30, FORWARD,MICROSTEP); 
   Stepper2.step(30, FORWARD,MICROSTEP);
   delay(600);
    if (panw <= 36){
        penDown();
        delay(300);
        x = (panw * 245)/36;
        Stepper2.step(x, FORWARD,MICROSTEP);
        
        Stepper1.step(x, FORWARD,MICROSTEP); 
        
        Stepper2.step(x,BACKWARD,MICROSTEP); 
        
        Stepper1.step(x,BACKWARD,MICROSTEP);

                penUp();
                delay(300);
    }
   else {
        Serial.println("Give lower value");
        Serial.println("Give X");
        while(Serial.available() == 0) {}
         panw = Serial.parseFloat();
         goto start;
   }
}
   
  delay(300);
  Stepper1.step(245, BACKWARD,MICROSTEP); 
   Stepper2.step(245, BACKWARD,MICROSTEP);
  
  penUp();
  delay(300);
  // }
 }

void zero() 
{
  //my_servo.write(28); 
  delay(300); 
// Stepper2.step(245, FORWARD,MICROSTEP);
 // Stepper1.step(245, FORWARD,MICROSTEP);
  Stepper1.step(245,BACKWARD,MICROSTEP);
  Stepper2.step(245,BACKWARD,MICROSTEP);
  delay(300); 
  penUp(); 
  //my_servo.write(70);
  delay(300);

}

  void penUp() { 
 my_servo.write(penZUp); 

  digitalWrite(15, LOW);
    digitalWrite(16, HIGH); 
}


void penDown() { 
  my_servo.write(penZDown); 
   
  digitalWrite(15, HIGH);
    digitalWrite(16, LOW);
  } 
