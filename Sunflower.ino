// JUST FOR TESTING
int incomingCommand = 5;

// MOTOR PINS
int motor1pin1 = D13;
int motor1pin2 = D12;
int motor2pin1 = D11;
int motor2pin2 = D10;

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
  Serial.println("Type the \"motor number\" you want!");
  while(Serial.available() <= 0);
  incomingCommand = Serial.readString().ToInt();

  if (incomingCommand == 0)
{
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

else if (incomingCommand == 1)
{
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

else if (incomingCommand == 2)
{
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

else if (incomingCommand == 3)
{
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

else if (incomingCommand == 4)
{
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

delay(1000);

else 
{
  Serial.println("Not a valid command!");
}
}
