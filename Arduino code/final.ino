
#include<NewPing.h>
#include<Servo.h>
#include<SoftwareSerial.h>
#include<AFMotor.h>
#define led A5
#define led2 A1


#define RIGHT A4
#define LEFT A3
#define TRIGGER_PIN A1
#define ECHO_PIN A0    
//#define distance 100
#define LRIGHT A4//FOR LINE FOLLOWER
#define LLEFT  A1//FOR LINE FOLLOWER
#define RX A5//FFOR BLUETOOTH
#define TX A2 


int  mode;//for changing the mode

int lvalue,rvalue;

SoftwareSerial MyBlue(RX,TX);
String flag="0";

//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


AF_DCMotor Motor1(1,MOTOR12_1KHZ);
AF_DCMotor Motor2(2,MOTOR12_1KHZ);
AF_DCMotor Motor3(3,MOTOR34_1KHZ);
AF_DCMotor Motor4(4,MOTOR34_1KHZ);

Servo myservo;
 
int pos =0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 
   pinMode(led2,OUTPUT);
myservo.attach(10);
{
for(pos = 90; pos <= 180; pos += 1){
  myservo.write(pos);
  delay(15);
} for(pos = 180; pos >= 0; pos-= 1) {
  myservo.write(pos);
  Serial.println(pos);
  delay(15);
}for(pos = 0; pos<=120; pos += 1) {
  myservo.write(pos);
  delay(15);
}
}

MyBlue.begin(9600);
Serial.println("ready to connect");

//FOR MAN FOLLOER
pinMode(RIGHT, INPUT);
pinMode(LEFT, INPUT);
//FOR LINE FOLLOWER
pinMode(LRIGHT, INPUT);
pinMode(LLEFT, INPUT);
//pinMode(led,OUTPUT);

pinMode(TRIGGER_PIN,OUTPUT);
pinMode(ECHO_PIN,INPUT);

}


void forward()
{
     
  Motor1.setSpeed(250);
  Motor1.run(FORWARD);
  Motor2.setSpeed(250);
  Motor2.run(FORWARD);
  Motor3.setSpeed(250);
  Motor3.run(FORWARD);
  Motor4.setSpeed(250);
  Motor4.run(FORWARD);  
  
}

void backward()
{
  Motor1.setSpeed(200);
  Motor1.run(BACKWARD);
  Motor2.setSpeed(200);
  Motor2.run(BACKWARD);
  Motor3.setSpeed(200);
  Motor3.run(BACKWARD);
  Motor4.setSpeed(200);
  Motor4.run(BACKWARD);
}

void stop_car()
{
  Motor1.setSpeed(0);
  Motor1.run(RELEASE);
  Motor2.setSpeed(0);
  Motor2.run(RELEASE);
  Motor3.setSpeed(0);
  Motor3.run(RELEASE);
  Motor4.setSpeed(0);
  Motor4.run(RELEASE);
}
void turn_left()
{
   
  Motor1.setSpeed(150);
  Motor1.run(BACKWARD);
  Motor2.setSpeed(150);
  Motor2.run(BACKWARD);
  Motor3.setSpeed(250);
  Motor3.run(FORWARD);
  Motor4.setSpeed(250);
  Motor4.run(FORWARD);
  
}
void right_turn()
{
  
  Motor1.setSpeed(250);
  Motor1.run(FORWARD);
  Motor2.setSpeed(250);
  Motor2.run(FORWARD);
  Motor3.setSpeed(150);
  Motor3.run(BACKWARD);
  Motor4.setSpeed(150);
  Motor4.run(BACKWARD);
  
}

//=================//ultrasonic readf




void loop() {
//

   
  
    if (MyBlue.available())
    {

      flag=MyBlue.readString();
      Serial.println("message from the phone ");
      Serial.println(flag);
       
      
    }

//================================================================//set mode//===========================================================


    if(flag=="ZS"){mode=1;}//remote control
    if(flag=="voice mode"){mode=2;}//voice mode
     if(flag=="Y"){mode=3;}
   if(flag=="y"){mode=4;}//object follower
   if(flag=="stop"){mode=5;}

        
//======================BLUETOOTH CONTROLL===========================
      switch(mode)
      {
        case 1: 
//        digitalWrite(led2,HIGH);
//delay(50);
//digitalWrite(led2,LOW);
//delay(50);
//

       /* */ 
       if(flag=="FS")
          {
           forward();
           
          }
          //backard directi'on
          else if(flag=="BS")
          {
         
            
            backward();
            
          }

          //for turn left
           else if(flag=="LS")
          {
            
              turn_left();
              
            
          }
        //turn right side
          else if(flag=="RS")
          {
           
           right_turn();
          }
          //for stop the car

          else if(flag=="ZS")
          {
            stop_car();
          }

          case 2:
          
//====================================== //now for VOICE controll ==========================================================
            

           
           
           if(flag=="forward")
          {

            forward();
          }
          else if(flag=="backward")
          {
            backward();
            
          }
          else if(flag=="turn right")
          {
           right_turn();
          }
          else if(flag=="turn left")
          {
            turn_left();
          }
          else if(flag=="stop")
          {
            stop_car();
          }
          
         




//======================Line follower===============================

       case 3:

             digitalWrite(led2,HIGH);
    


       
             if(lvalue==0&& rvalue==0)
          {
            //forward direction
           
            Motor1.setSpeed(70);
            Motor1.run(FORWARD);
            Motor2.setSpeed(70);
            Motor2.run(FORWARD);
            Motor3.setSpeed(70);
            Motor3.run(FORWARD);
            Motor4.setSpeed(70);
            Motor4.run(FORWARD);

          }
        
          //for turn left
           else if(lvalue==0 && rvalue==1)
          {
              Motor1.setSpeed(0);
              Motor1.run(RELEASE);
              Motor2.setSpeed(250);
              Motor2.run(BACKWARD);
              Motor3.setSpeed(250);
              Motor3.run(FORWARD);
              Motor4.setSpeed(0);
              Motor4.run(RELEASE);
  

             
              
            
          }
            //turn right side
          else if(lvalue==1 && rvalue==0)
          {
           
           
             Motor1.setSpeed(0);
            Motor1.run(RELEASE);
            Motor2.setSpeed(250);
            Motor2.run(FORWARD);
            Motor2.setSpeed(250);
            Motor3.run(BACKWARD);
            Motor4.setSpeed(0);
            Motor4.run(RELEASE);
          }
          //Stop the car
          else if(lvalue==1 && rvalue==1)
          {
            Motor1.setSpeed(0);
            Motor1.run(RELEASE);
            Motor2.setSpeed(0);
            Motor2.run(RELEASE);
            Motor3.setSpeed(0);
            Motor3.run(RELEASE);
            Motor4.setSpeed(0);
            Motor4.run(RELEASE);

          }
          break;
         
          
          
          
     case 4:
            

  
    //==========================Man follower============================

         digitalWrite(led2,HIGH);
    





long duration,distance;
  digitalWrite(TRIGGER_PIN,HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIGGER_PIN,LOW);
  duration=pulseIn(ECHO_PIN,HIGH);
  distance=((duration/2)/29.1);
  Serial.println("the distance is "+distance);
  Serial.print(distance);
  Serial.println("cm");
 


int Right_Value = digitalRead(RIGHT);
int Left_Value = digitalRead(LEFT);

Serial.print("RIGHT");
Serial.println(Right_Value);
Serial.print("LEFT");
Serial.println(Left_Value);

if( (Right_Value==0)&&(distance > 15) && (distance < 20) &&(Left_Value==0)){
  
  forward();
 
}else if((Right_Value==0) && (Left_Value==1)) {
   digitalWrite(led,LOW);
  right_turn();
  
}else if((Right_Value==1)&&(Left_Value==0)) {
   digitalWrite(led,LOW);
 turn_left();
 
}else if((Right_Value==1)&&(distance > 15) &&(Left_Value==1)) {
  //stop
 stop_car();
}
                         

  }
 }
