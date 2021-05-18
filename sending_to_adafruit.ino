AdafruitIO_Feed *azimuth1 = io.feed("azimuth"); //het instellen van de naam van je feed
AdafruitIO_Feed *elevation1 = io.feed("hoogte");//het instellen van de naam van je feed

AdafruitIO_Feed *current_first = io.feed("current1"); //het instellen van de naam van je feed
AdafruitIO_Feed *current_second = io.feed("current2");//het instellen van de naam van je feed

AdafruitIO_Feed *voltage_first = io.feed("voltage1"); //het instellen van de naam van je feed
AdafruitIO_Feed *voltage_second = io.feed("voltage2");//het instellen van de naam van je feed

AdafruitIO_Feed *light = io.feed("light_level"); //het instellen van de naam van je feed

AdafruitIO_Feed *power_first = io.feed("power1"); //het instellen van de naam van je feed
AdafruitIO_Feed *power_second = io.feed("power2");//het instellen van de naam van je feed

AdafruitIO_Feed *location = io.feed("location");

bool sendToAdafruit(int elevation, int azimuth,float current1,float current2,float voltage1,float voltage2,float power1,float power2, int light_level, float longitude, float latitude) {
  Serial.print("IN FUNCTION elevation is ");
  Serial.println(elevation);
  elevation1->save(elevation);//waarde versturen naar adafruit
  Serial.print("IN FUNCTION elevation is ");
  Serial.println(azimuth);
  azimuth1->save(azimuth);//waarde versturen naar adafruit

  Serial.print("IN FUNCTION current (solar) is ");
  //Serial.println(current1);
  //current_first->save(current1);//waarde versturen naar adafruit
  Serial.print("IN FUNCTION current (battery) is ");
  Serial.println(current2);
  //current_second->save(current2);//waarde versturen naar adafruit

  Serial.print("IN FUNCTION voltage (solar) is ");
  Serial.println(voltage1);
  voltage_first->save(voltage1);//waarde versturen naar adafruit
  Serial.print("IN FUNCTION voltage (battery) is ");
  Serial.println(voltage2);
   //voltage_second->save(voltage2);//waarde versturen naar adafruit 

  light->save(light_level);//waarde versturen naar adafruit

  Serial.print("IN FUNCTION power (solar) is ");
  Serial.println(power1);
  power_first->save(power1);//waarde versturen naar adafruit
  Serial.print("IN FUNCTION power (battery) is ");
  Serial.println(power2);
  //power_second->save(power2);//waarde versturen naar adafruit

  location->save(1, latitude, longitude, 0);
}
