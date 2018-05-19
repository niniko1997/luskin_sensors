/* Temperature and Humidity Sensor (DHT-22)
    Arduino Nano
    Luskin Wall Farm Project
*/

//Libraries
#include <DHT.h>

//Constants
#define DHTPIN 5 // the pin we're connected to
#define DHTTYPE DHT22 // the sensor

DHT dht(DHTPIN, DHTTYPE); // create sensor object using input pin and sensor type

//Variables
int chk;
float humidity; // stores humidity values
float temperature; // stores temperature values

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  humidity = dht.readHumidity(); // get the humidity
  temperature = dht.readTemperature(); // get the temperature

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("Temperature: ");
  Serial.print(temperature);

  delay(2000); // wait two seconds

}
