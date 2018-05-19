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
#define num_readings 20 // number of sample EC readings
double ECArray[num_readings];

void setup() {
  pinMode(sensorOne_PIN, INPUT);
  pinMode(sensorTwo_PIN, INPUT);
  pinMode(sensorThree_PIN, INPUT);
  Serial.begin(9600);

  // initialize array with empty values
  for(int i=0; i<length; i++){
    pHArray[i]=0;
  }

  // initialize array with empty values
  for(int i=0; i< num_readings; i++){
    ECArray[i]=0;
  }
}

void loop() {
  static float pH_value; // the calculated pH value
  static float voltage; // voltage from pH
  float output_value; // output from the pH sensor

  static float ec_value; // calculated ec value
  static float ec_voltage; // voltage from ec
  float reading_value; // output from the EC sensor

  // read from the pH meter
  for(int i=0; i<length; i++){
    output_value = digitalRead(sensorOne_PIN);
    pHArray[i] = output_value;
  }

  // calculate the voltage using average pH readings
  voltage = average_array(pHArray, length)*5.0/1024;
  // calculate pH
  pH_value = 3.5*voltage+offset;

  // print pH information on Serial
  Serial.print("Voltage (pH): ");
  Serial.print(voltage);
  Serial.print(" pH Value: ");
  Serial.println(pH_value);

  // read from the EC meter
  for(int i=0; i<num_readings; i++){
    reading_value = digitalRead(sensorTwo_PIN);
    ECArray[i] = reading_value;
  }
  
  ec_voltage = average_array(ECArray, num_readings)*5.0/1024;

  Serial.print("Voltage (EC): ");
  Serial.print(ec_voltage);
  Serial.print(" EC Value: ");
  Serial.println(ec_value);
  
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

