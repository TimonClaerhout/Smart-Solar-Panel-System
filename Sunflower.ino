#include "MMA7660.h"

MMA7660 accelerometer;

// JUST FOR TESTING
int incomingCommand = 0;

// MOTOR PINS
int motor1pin1 = D13;
int motor1pin2 = D12;
int motor2pin1 = D11;
int motor2pin2 = D10;

// ACCELEROMETER
int8_t x;
int8_t y;
int8_t z;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  delay(1000);
  Serial.println("Hi welcome to the testing of the motors!");
}

void loop()
{ 
  Serial.println("Type the \"radius\" you want!");
  while(Serial.available() <= 0);
  incomingCommand = Serial.readString().toInt();

  while(x != incomingCommand)
    {
      Serial.println(x);
      Serial.println(incomingCommand);
      if(x <= incomingCommand)
      {
        digitalWrite(motor1pin1, HIGH);
        digitalWrite(motor1pin2, LOW);
        digitalWrite(motor2pin1, LOW);
        digitalWrite(motor2pin2, LOW);
      }
      else
      {
        digitalWrite(motor1pin1, LOW);
        digitalWrite(motor1pin2, HIGH);
        digitalWrite(motor2pin1, LOW);
        digitalWrite(motor2pin2, LOW);
      }
      delay(100);
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);
      digitalWrite(motor2pin1, LOW);
      digitalWrite(motor2pin2, LOW);
      accelerometer.getXYZ(&x, &y, &z); 
   }
}
