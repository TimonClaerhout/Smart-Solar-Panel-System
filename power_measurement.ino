float* getPower(Adafruit_INA260* sensorA, Adafruit_INA260* sensorB)
{
  float values[6] = {fabs(sensorA->readCurrent()), fabs(sensorB->readCurrent()), sensorA->readBusVoltage(), sensorB->readBusVoltage(), sensorA->readPower(), sensorB->readPower()};
  return values;

}
