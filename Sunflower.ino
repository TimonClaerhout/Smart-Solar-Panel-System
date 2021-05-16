// LIBRARYS
#include <Wire.h>
#include "MMA7660.h"
#include "config.h"
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <Adafruit_INA260.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Digital_Light_TSL2561.h>

const long utcOffsetInSeconds = 7200;

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
adafruit_bno055_offsets_t calibrationData;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.ugent.be", utcOffsetInSeconds); // UGent because KU Leuven doesn't work correctly

MMA7660 accelemeter;

// JUST FOR TESTING
String incomingCommand = "0"; //NEEDED FOR MOTORS!

//Power sensors
Adafruit_INA260 ina260A = Adafruit_INA260();
Adafruit_INA260 ina260B = Adafruit_INA260();

// VALUES FROM ALGORITHM
int * Elevation_Azimuth;
int elevation;
int azimuth;
int test_elevation = 30;

// Internal memory
int elevation_int;
int azimuth_int;

// STANDARD VALUES FOR CORRECTION
int elevation_corrected; //NEEDED FOR MOTORS! (LATER 3nd commit)
float temp = 0;
bool not_out_of_bounds = true; //NEEDED FOR MOTORS! (LATER 4nd commit)
bool sun_to_low = false; //NEEDED FOR MOTORS! (Later maybe 4 or 5 commit)

// MOTOR PINS
int motor1pin1 = D13; //NEEDED FOR MOTORS!
int motor1pin2 = D12; //NEEDED FOR MOTORS!
int motor2pin1 = D11; //NEEDED FOR MOTORS!
int motor2pin2 = D10; //NEEDED FOR MOTORS!

// ADAFRUIT DELAY
int adaDelay = 50000;
int previousTimeAda;

// POSITIONING DELAY
int posDelay = 20000;
int previousTimePos;

// TIME SYNC
int syncDelay = 1800000;
int previousTimeSync;
bool SYNC = true;

// SECOND TIME
int secondDelay = 1000;
int previousTimeSecond;

// COMPASS CALIBRATION TIME
int compassDelay = 50;
int previousTimeCompass;

//COMPASS
int angleTowardsNorth;
int indexCompass = 0;
int compassValues[20];
bool toMuchTheSame = false;
bool inIf = false;
bool rotating = false;
bool CHRASHED = false;

// ACCELEROMETER
int8_t x; //NEEDED FOR MOTORS! (2nd commit)
int8_t y; //NEEDED FOR MOTORS! (2nd commit)
int8_t z; //NEEDED FOR MOTORS! (2nd commit)

//relay reset compass
bool START = true;
int relayDelay = 10000; // tijd in minuten 
int previousTimerelay;
int relaycompass = D9; //NEEDED FOR resetting compass

// WIFI CREDENTIALS
const char *ssid     = "jonckheere"; //"LAB_02.85";
const char *password = "john-deere"; //"CONNECT2LAB";

// TIME DEFINITIONS WITH NTP SERVER
int hour_int = 0;
int minute_int = 0;
int second_int = 0;
int month_int = 0;
int day_int = 0;
int year_int = 0;

// LOCATION (NOW STATIC)
float Lon=3.055742*DEG_TO_RAD;
float Lat=51.141309*DEG_TO_RAD;

void setup() {
  // put your setup code here, to run once:
  pinMode(relaycompass, OUTPUT); // NEEDED FOR resetting compass
  accelemeter.init();
  Wire.begin();
  TSL2561.init();
  Serial.begin(115200); // NEEDED FOR MOTORS
  digitalWrite(relaycompass, HIGH);
  delay(1000);
  
  if (!bno.begin())
  {
      Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
      while (1)
        ;
  }

  calibrationData.accel_offset_x = 5;
  calibrationData.accel_offset_y = 39;
  calibrationData.accel_offset_z = -2;
  calibrationData.gyro_offset_x = -5;
  calibrationData.gyro_offset_y = -2;
  calibrationData.gyro_offset_z = 0;
  calibrationData.mag_offset_x = -33;
  calibrationData.mag_offset_y = 298;
  calibrationData.mag_offset_z = 430;
  calibrationData.accel_radius = 1000;
  calibrationData.mag_radius = 945;
  bno.setSensorOffsets(calibrationData);
  
  WiFi.begin(ssid, password);

  Serial.println("WIFI connecting");
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.println("");

  timeClient.begin();

  while (! Serial);
  Serial.print("Connecting to Adafruit IO");
  // connect to io.adafruit.com
  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());

  if (!ina260A.begin((uint8_t)64) || !ina260B.begin((uint8_t)68)) {
    Serial.println("Couldn't find all INA260 chips");
    while (true)
      ;
  }
  Serial.println("Found INA260 chip");
  
  pinMode(motor1pin1, OUTPUT); // NEEDED FOR MOTORS
  pinMode(motor1pin2, OUTPUT); // NEEDED FOR MOTORS
  pinMode(motor2pin1, OUTPUT); // NEEDED FOR MOTORS
  pinMode(motor2pin2, OUTPUT); // NEEDED FOR MOTORS
  delay(1500); // NEEDED FOR MOTORS
  Serial.println("Hi welcome to the solar flower!"); // NEEDED FOR MOTORS
}

void loop()
{ 
  // CALLING THE ALGORITHM EVERY 25 SECONDS (POSDELAY)
  if((millis() - previousTimePos) > posDelay || previousTimePos == 0)
  {
    // SYNCING THE TIME EVERY 30 MINUTES
    if((millis() - previousTimeSync) > syncDelay || SYNC)
    {
      Serial.println("SYNCING THE TIME");
      if(SYNC)
        SYNC = false;
      timeClient.update();
      unsigned long epoch_time = timeClient.getEpochTime();
      hour_int = hour(epoch_time);
      minute_int = minute(epoch_time);
      second_int = second(epoch_time);
      day_int = day(epoch_time);
      month_int = month(epoch_time);
      year_int = year(epoch_time);
      previousTimeSync = millis();
      Serial.printf("%d:%d:%d\r\n", hour_int, minute_int, second_int);
    }

    
    Elevation_Azimuth = GetElevationAndAzimuth(hour_int, minute_int, second_int, month_int, day_int, year_int, Lon, Lat);
    // NEEDED FOR MOTORS
    /*Serial.println("Type de \"Elevation\" you want!");
    while(Serial.available() <= 0)
      ;
    incomingCommand = Serial.readString();
    elevation = incomingCommand.toInt();*/
    // NEEDED FOR MOTORS
    elevation = Elevation_Azimuth[0] + 6;
    //elevation = test_elevation - 1;
    Serial.println(test_elevation);
    azimuth = (Elevation_Azimuth[1]+20)%360;
    temp = (90 - elevation)/3.5; //The accelerometer has a step of 3.5 degrees
    elevation_corrected = -temp;
    if(temp < 30)
    {
      sun_to_low = true;
    }
    if(elevation < 30 && not_out_of_bounds)
    {
      not_out_of_bounds = false;
      Serial.println("Sun is under reach for the solar flower... (No electricity for you!)");
      delay(500);
      Serial.println("Going to sleep mode....");
    }
    else if(not_out_of_bounds || elevation < 30)
    {
      not_out_of_bounds = true;
      Serial.print("Elevation (from user): ");
      Serial.println(elevation);
      Serial.print("Elevation (for correction): ");
      Serial.println(elevation_corrected);
      accelemeter.getXYZ(&x, &y, &z); 
    }
    else
    {
      Serial.println("LET ME SLEEP PLEASE!!");
    }
    previousTimePos = millis();
  }
  
  // TESTING IF NEW DATA IS NOT THE SAME AS THE OLD DATA
  if(!(elevation_int == elevation && azimuth_int == azimuth) || x != elevation_corrected || angleTowardsNorth < azimuth + 1 || angleTowardsNorth > azimuth - 1)
  {
    elevation_int = elevation;
    azimuth_int = azimuth;
    if(!(elevation < 30) && (x != elevation_corrected && not_out_of_bounds))
    {
      Serial.println(x);
      Serial.println(elevation_corrected);
      Serial.println(sun_to_low);
      if(x <= elevation_corrected)
      {
        digitalWrite(motor1pin1, HIGH);
        digitalWrite(motor1pin2, LOW);
      }
      else
      {
        digitalWrite(motor1pin1, LOW);
        digitalWrite(motor1pin2, HIGH);
      }
      delay(100);
      digitalWrite(motor1pin1, LOW);  // NEEDED FOR MOTORS
      digitalWrite(motor1pin2, LOW);  // NEEDED FOR MOTORS
      accelemeter.getXYZ(&x, &y, &z); 
   }
   if(angleTowardsNorth < azimuth - 3 || angleTowardsNorth > azimuth + 3)
    {
      rotating = true;
      Serial.println(angleTowardsNorth);
      Serial.println(azimuth);
      if(angleTowardsNorth < azimuth)
      {
        digitalWrite(motor2pin1, HIGH);
        digitalWrite(motor2pin2, LOW);
      }
      else
      {
        digitalWrite(motor2pin1, LOW);
        digitalWrite(motor2pin2, HIGH);
      }
      delay(100);
   } else
   {
      rotating = false;
      digitalWrite(motor2pin1, LOW);  // NEEDED FOR MOTORS
      digitalWrite(motor2pin2, LOW);  // NEEDED FOR MOTORS
   }
  }
  else
  {
    rotating = false;
    digitalWrite(motor2pin1, LOW);  // NEEDED FOR MOTORS
    digitalWrite(motor2pin2, LOW);  // NEEDED FOR MOTORS
  }

  // SENDING DATA TO ADAFRUIT EVERY 20 SECONDS
  if((millis() - previousTimeAda) > adaDelay)
  {
    rotating = false;
    digitalWrite(motor1pin1, LOW);  // NEEDED FOR MOTORS
    digitalWrite(motor1pin2, LOW);  // NEEDED FOR MOTORS
    digitalWrite(motor2pin1, LOW);  // NEEDED FOR MOTORS
    digitalWrite(motor2pin2, LOW);  // NEEDED FOR MOTORS
    
      while (! Serial);
    Serial.print("Connecting to Adafruit IO");
    // connect to io.adafruit.com
    io.connect();
  
    while (io.status() < AIO_CONNECTED)
      yield();
    Serial.println("SENDING TO ADAFRUIT");
    float* temp_values = getPower(&ina260A, &ina260B);
    sendToAdafruit(elevation, azimuth, temp_values[0], temp_values[1], temp_values[2], temp_values[3], temp_values[4], temp_values[5], getLux(), Lon/DEG_TO_RAD, Lat/DEG_TO_RAD);
    previousTimeAda = millis();
  }

  // UPDATING TIME EVERY SECOND WITHOUT CONNECTION
  if((millis() - previousTimeSecond) > secondDelay)
  {
    second_int = second_int + 1;
    if(second_int >= 60)
    {
      minute_int = minute_int + 1;
      second_int = second_int % 60;
      if(minute_int >= 60)
      {
        hour_int = hour_int + 1;
        minute_int = minute_int % 60;
        if(hour_int >= 24)
          SYNC = true;
      }
    }
    previousTimeSecond = millis(); 
  }


  if((millis() - previousTimeCompass) > compassDelay)
  {
    angleTowardsNorth = fabs(compass()%360);
    if(rotating)
    {
      compassValues[indexCompass] = angleTowardsNorth;
      if(indexCompass >= (sizeof(compassValues)/2) - 2)
      {
        indexCompass = 0;
        memset(compassValues, 0, sizeof(compassValues));
      }
      else
      {
        indexCompass++;
      }
      inIf = false;
      for(int i = 0; i < (sizeof(compassValues)/2) - 2;i++)
      {
        if(compassValues[i] != compassValues[i+1])
        {
          inIf = true;
          toMuchTheSame = false;
        }
      }
      if(!inIf)
        toMuchTheSame = true;
      if(toMuchTheSame)
        CHRASHED = true;
    }
    previousTimeCompass = millis(); 
  }


if(CHRASHED || START)
  {
    digitalWrite(motor1pin1, LOW);  // NEEDED FOR MOTORS
    digitalWrite(motor1pin2, LOW);  // NEEDED FOR MOTORS
    digitalWrite(motor2pin1, LOW);  // NEEDED FOR MOTORS
    digitalWrite(motor2pin2, LOW);  // NEEDED FOR MOTORS
    
    Serial.println("SWITCHING RELAY");
    digitalWrite(relaycompass, LOW);
    delay (1000);
    digitalWrite(relaycompass, HIGH);
    delay (2500);
    previousTimerelay = millis();
  }
  START = false;

  

/*if (!bno.begin()) {
    Serial.println("Couldn't find all INA260 chips");
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
      digitalWrite(relaycompass, LOW);
      delay (1000);
      digitalWrite(relaycompass, HIGH);
      delay (1500);
    while (true)
      ;
  }
*/
  
}
