// the value of the resistor
#define sensor_RESISTOR 220

// the pin sensor is connected to on arduino
#define sensor_PIN A7

void setup() {
  Serial.begin(9600);
}

void loop() {
  // get the raw value from the sensor
  float output_value;
  output_value = analogRead(sensor_PIN);
  
  // convert raw value to resistance
  float resistance;
  resistance = (sensor_RESISTOR) / ((1023/output_value) - 1);
  Serial.print("Analog Reading: ");
  Serial.print(output_value);
  Serial.print(" Resistance: ");
  Serial.println(resistance);

  // convert to volume measurement
  // (max_tank_value (empty tank) - output_value/ (max_tank_value-min_tank_value))*sensor_length

  delay(2000);
}
