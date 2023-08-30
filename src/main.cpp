#include <Arduino.h>

// Stromkasten 1 ------------------------------------------------------------
// Set IO-Pins - These are the PINS which are used on the ESP32
const int RED_LED_PIN_1 = 2;
const int SENSOR_SOLAR_PIN_1= 36;
const int SENSOR_WIND_PIN_1 = 33;
const int SENSOR_LOAD_PIN_1_1 = 35;
const int SENSOR_LOAD_PIN_2_1 = 27;
const int SENSOR_LOAD_PIN_3_1 = 26;
const int SENSOR_LOAD_PIN_4_1 = 25;
const int SENSOR_LOAD_PIN_5_1 = 14;
const int SENSOR_LOAD_PIN_6_1 = 12;
// Set Booleans - These are used to determine, if a load is connected to the electrical panel (true, if Pin connected to electrical panel)
bool sensorStateSolar_1;
bool sensorStateWind_1;
bool sensorStateLoad_1_1;
bool sensorStateLoad_2_1;
bool sensorStateLoad_3_1;
bool sensorStateLoad_4_1;
bool sensorStateLoad_5_1;
bool sensorStateLoad_6_1;
// This is used determine, if the electrical panel is overloaded (true, if maxEnergyCapacity_1 > currentEnergyLoad_1)
bool isOverloaded_1;
// These are used for the value of the current load attached to the electrical panel and the Limit it can hold
int currentEnergyLoad_1;
int maxEnergyCapacity_1;
// Sets the value of currentEnergyLoad_1
int getCurrentEnergyLoad_1() {
  int trueCount_1 = 0;
  if (!sensorStateLoad_1_1) {
    trueCount_1++;
  }
  if (!sensorStateLoad_2_1) {
    trueCount_1++;
  }
  if (!sensorStateLoad_3_1) {
    trueCount_1++;
  }
  if (!sensorStateLoad_4_1) {
    trueCount_1++;
  }
  if (!sensorStateLoad_5_1) {
    trueCount_1++;
  }
  if (!sensorStateLoad_6_1) {
    trueCount_1++;
  }
  currentEnergyLoad_1 = trueCount_1;
  return currentEnergyLoad_1;
}

// Stromkasten 2 ------------------------------------------------------------
// Set IO-Pins - These are the PINS which are used on the ESP32
const int RED_LED_PIN_2 = 19;
const int SENSOR_SOLAR_PIN_2= 22;
const int SENSOR_WIND_PIN_2 = 21;
const int SENSOR_LOAD_PIN_1_2 = 34;
const int SENSOR_LOAD_PIN_2_2 = 4;
const int SENSOR_LOAD_PIN_3_2 = 13;
const int SENSOR_LOAD_PIN_4_2 = 32;
const int SENSOR_LOAD_PIN_5_2 = 15;
const int SENSOR_LOAD_PIN_6_2 = 39;
// Set Booleans - These are used to determine, if a load is connected to the electrical panel (true, if Pin connected to electrical panel)
bool sensorStateSolar_2;
bool sensorStateWind_2;
bool sensorStateLoad_1_2;
bool sensorStateLoad_2_2;
bool sensorStateLoad_3_2;
bool sensorStateLoad_4_2;
bool sensorStateLoad_5_2;
bool sensorStateLoad_6_2;
// This is used determine, if the electrical panel is overloaded (true, if maxEnergyCapacity_2 > currentEnergyLoad_2)
bool isOverloaded_2;
// These are used for the value of the current load attached to the electrical panel and the Limit it can hold
int currentEnergyLoad_2;
int maxEnergyCapacity_2;
// Sets the value of currentEnergyLoad_2
int getCurrentEnergyLoad_2() {
  int trueCount_2 = 0;
  if (!sensorStateLoad_1_2) {
    trueCount_2++;
  }
  if (!sensorStateLoad_2_2) {
    trueCount_2++;
  }
  if (!sensorStateLoad_3_2) {
    trueCount_2++;
  }
  if (!sensorStateLoad_4_2) {
    trueCount_2++;
  }
  if (!sensorStateLoad_5_2) {
    trueCount_2++;
  }
  if (!sensorStateLoad_6_2) {
    trueCount_2++;
  }
  currentEnergyLoad_2 = trueCount_2;
  return currentEnergyLoad_2;
}

// This function reads the pins attached to the electrical panel and sets booleans accordingly 
void readSensorStates() {
  //Stromkasten 1
  sensorStateSolar_1 = digitalRead(SENSOR_SOLAR_PIN_1);
  sensorStateWind_1 = digitalRead(SENSOR_WIND_PIN_1);
  sensorStateLoad_1_1 = analogRead(SENSOR_LOAD_PIN_1_1);
  sensorStateLoad_2_1 = analogRead(SENSOR_LOAD_PIN_2_1);
  sensorStateLoad_3_1 = analogRead(SENSOR_LOAD_PIN_3_1);
  sensorStateLoad_4_1 = analogRead(SENSOR_LOAD_PIN_4_1);
  sensorStateLoad_5_1 = analogRead(SENSOR_LOAD_PIN_5_1);
  sensorStateLoad_6_1 = analogRead(SENSOR_LOAD_PIN_6_1);
  //Stromkasten 2
  sensorStateSolar_2 = digitalRead(SENSOR_SOLAR_PIN_2);
  sensorStateWind_2 = digitalRead(SENSOR_WIND_PIN_2);
  sensorStateLoad_1_2 = analogRead(SENSOR_LOAD_PIN_1_2);
  sensorStateLoad_2_2 = analogRead(SENSOR_LOAD_PIN_2_2);
  sensorStateLoad_3_2 = analogRead(SENSOR_LOAD_PIN_3_2);
  sensorStateLoad_4_2 = analogRead(SENSOR_LOAD_PIN_4_2);
  sensorStateLoad_5_2 = analogRead(SENSOR_LOAD_PIN_5_2);
  sensorStateLoad_6_2 = analogRead(SENSOR_LOAD_PIN_6_2);
}

// Sets the value of MaxEnergyCapacity of the electrical panel
void setMaxEnergyCapacity() {
  //Stromkasten 1
  if (sensorStateSolar_1 && sensorStateWind_1) {
    maxEnergyCapacity_1 = 6;
  } else {
    maxEnergyCapacity_1 = (sensorStateSolar_1 || sensorStateWind_1) ? 4 : 3;
  }
  //Stromkasten 2
  if (sensorStateSolar_2 && sensorStateWind_2) {
    maxEnergyCapacity_2 = 6;
  } else {
    maxEnergyCapacity_2 = (sensorStateSolar_2 || sensorStateWind_2) ? 4 : 3;
  }
}
// Check if electrical panel is overloaded (true, if currentEnergyLoad > maxEnergyCapacity)
void checkIfOverloaded() {
  if(getCurrentEnergyLoad_1() > maxEnergyCapacity_1){
    isOverloaded_1 = true;
  } else {
    isOverloaded_1 = false;
  }
  if(getCurrentEnergyLoad_2() > maxEnergyCapacity_2){
    isOverloaded_2 = true;
  } else {
    isOverloaded_2 = false;
  }
}
// Prints to Console all the Values
void printValues() {
  Serial.print(" Capacity_1 = ");
  Serial.print(maxEnergyCapacity_1);
  Serial.print(" Capacity_2 = ");
  Serial.print(maxEnergyCapacity_2);
  Serial.print(" currentLoad_1 = ");
  Serial.print(getCurrentEnergyLoad_1());
  Serial.print(" currentLoad_2 = ");
  Serial.println(getCurrentEnergyLoad_2());
}
void printAnalogValues_1() {
  Serial.print(" Sen_1 = ");
  Serial.print(analogRead(SENSOR_LOAD_PIN_1_1));
  Serial.print(" Sen_2 = ");
  Serial.print(analogRead(SENSOR_LOAD_PIN_2_1));
  Serial.print(" Sen_3 = ");
  Serial.print(analogRead(SENSOR_LOAD_PIN_3_1));
  Serial.print(" Sen_4 = ");
  Serial.print(analogRead(SENSOR_LOAD_PIN_4_1));
  Serial.print(" Sen_5 = ");
  Serial.print(analogRead(SENSOR_LOAD_PIN_5_1));
  Serial.print(" Sen_6 = ");
  Serial.println(analogRead(SENSOR_LOAD_PIN_6_1));
}
void printAnalogValues_2() {
  Serial.print(" Sen_1 = ");
  Serial.print(analogRead(SENSOR_LOAD_PIN_1_2));
  Serial.print(" Sen_2 = ");
  Serial.print(analogRead(SENSOR_LOAD_PIN_2_2));
  Serial.print(" Sen_3 = ");
  Serial.print(analogRead(SENSOR_LOAD_PIN_3_2));
  Serial.print(" Sen_4 = ");
  Serial.print(analogRead(SENSOR_LOAD_PIN_4_2));
  Serial.print(" Sen_5 = ");
  Serial.print(analogRead(SENSOR_LOAD_PIN_5_2));
  Serial.print(" Sen_6 = ");
  Serial.println(analogRead(SENSOR_LOAD_PIN_6_1));
}

//SETUP --------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  //pinMode(INTERNAL_LED,OUTPUT);
  //Stromkasten 1
  pinMode(RED_LED_PIN_1, OUTPUT);
  pinMode(SENSOR_SOLAR_PIN_1, INPUT);
  pinMode(SENSOR_WIND_PIN_1, INPUT);
  pinMode(SENSOR_LOAD_PIN_1_1, INPUT);
  pinMode(SENSOR_LOAD_PIN_2_1, INPUT);
  pinMode(SENSOR_LOAD_PIN_3_1, INPUT);
  pinMode(SENSOR_LOAD_PIN_4_1, INPUT);
  pinMode(SENSOR_LOAD_PIN_5_1, INPUT);
  pinMode(SENSOR_LOAD_PIN_6_1, INPUT);
  //Stromkasten 2
  pinMode(RED_LED_PIN_2, OUTPUT);
  pinMode(SENSOR_SOLAR_PIN_2, INPUT);
  pinMode(SENSOR_WIND_PIN_2, INPUT); 
  pinMode(SENSOR_LOAD_PIN_1_2, INPUT);
  pinMode(SENSOR_LOAD_PIN_2_2, OUTPUT);
  pinMode(SENSOR_LOAD_PIN_3_2, OUTPUT);
  pinMode(SENSOR_LOAD_PIN_4_2, INPUT);
  pinMode(SENSOR_LOAD_PIN_5_2, INPUT);
  pinMode(SENSOR_LOAD_PIN_6_2, INPUT);
  delay(2000);
}

void loop() {
  readSensorStates();
  setMaxEnergyCapacity();
  checkIfOverloaded();
  
  //printValues();
  //printAnalogValues_1();
  //printAnalogValues_2();
  
  if (isOverloaded_1) {
    digitalWrite(RED_LED_PIN_1, HIGH);
  } else {
    digitalWrite(RED_LED_PIN_1, LOW);
  }
  if (isOverloaded_2) {
    digitalWrite(RED_LED_PIN_2, HIGH);
  } else {
    digitalWrite(RED_LED_PIN_2, LOW);
  }

  delay(100);
}
