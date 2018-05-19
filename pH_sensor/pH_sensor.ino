/* Luskin Wall Farm
 * Bruin Home Solutions
 * 
 * Editor: Nino Migineishvili
 * 
 * Product: analog pH Meter
 * SKU: SEN0169
 * 
 * Product: analog EC Meter
 * SKU: DRF0300
 */

#include <OneWire.h>

//define PINS
#define sensorOne_PIN 7 // pH Meter Pin
#define sensorTwo_PIN 6 // EC Meter Pin
#define sensorThree_PIN 5

#define offset 0.00
#define length 50 // the number of sample pH readings
double pHArray[length];

#define start_convert 0
const byte num_readings = 20; 

void setup() {
  pinMode(sensorOne_PIN, INPUT);
  pinMode(sensorTwo_PIN, INPUT);
  pinMode(sensorThree_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  static float pH_value;
  static float voltage;
  float output_value;

  for(int i=0; i<length; i++){
    output_value = digitalRead(sensorOne_PIN);
    pHArray[i] = output_value;
  }

  voltage = average_array(pHArray, length)*5.0/1024;
  pH_value = 3.5*voltage+offset;

  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print(" pH Value: ");
  Serial.println(pH_value);

  delay(2000);
}

/*
 * average_array takes in two parameters
 * arr is the array holding pH values
 * len is the length of the pH array
 * 
 * the function returns the average of the values of the array
 * the purpose of this function is to standardize pH measurements and compute accurate values
 */
double average_array(double* arr, int len){
  double arr_max;
  double arr_min;
  double amount = 0.0;

  // make sure function parameter is a valid input
  // the lenth can't be negative
  if(len <=0){
    Serial.print("Error in Array Length!");
    return 0;
  }// end if

  arr_max=arr[0];
  arr_min=arr[0];

  for(int i=0; i<len; i++){
    // check if the value is minimum
    if(arr[i] < arr_min){
      arr_min = arr[i];
    }// end if
    // check if value is maximum
    if(arr[i] > arr_max){
      arr_max = arr[i];
    }// end if
    amount = arr[i] + amount;
  }// end for

  return amount/len;
}// end function

