int compass() {
  static bool initialized = false;
  static int xOffset = 0;
  static int previousX;
  bno.setSensorOffsets(calibrationData);
  delay(100);
    
  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event, Adafruit_BNO055::VECTOR_EULER);
  
  if (true)
  {
    initialized = true;
    // FOR AT HOME (streulestraat 20 Eernegem) xOffset = 2.5425 * event.orientation.x - 242.38;
    // FOR SCHOOL xOffset = 0.0018 * pow(event.orientation.x,2) - 0.6751 * event.orientation.x + 6.0094;
    xOffset = 0.0812 * event.orientation.x  + 24.964; //
    // IN AGAR: xOffset = -0.019 * event.orientation.x  - 8.273;
    previousX = event.orientation.x;
  }

  if(fabs(previousX - event.orientation.x) > 10 && !(event.orientation.x < 10) && !(event.orientation.x > 350) && (previousX > 20) && (previousX < 340))
  {
    Serial.print("X0: ");
    Serial.print(event.orientation.x + xOffset, 4);
    Serial.print("\tX2: ");
    Serial.print(event.orientation.x, 4);
    Serial.println("");

    return previousX + xOffset;
  }
  else
  {
    previousX = event.orientation.x;
  }
  /* Display the floating point data */
  Serial.print("X0 achter IF: ");
  Serial.print(event.orientation.x + xOffset, 4);
  Serial.print("\tX2: ");
  Serial.print(event.orientation.x, 4);
  Serial.println("");

  return event.orientation.x + xOffset;
}
