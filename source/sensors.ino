// sensors.ino (23/11/2022)      |
// Miguel Hirche & Duarte Casal  |
// Functions for sensors         |
// ______________________________|

// include dht.h library and add DHTlib-0.1.35.zip from source/lib/ to build in Arduino IDE
#include <dht.h>

// readWaterLevel reads the value on the level sensor (analog pin) and maps the value from range [0, HIGHEST] to
// range [0, 100], where HIGHEST is the maximum value obtained during the sensor calibration.
// The mapped value of the level sensor is passed through a pointer. A boolean variable which indicates
// if the water level is below a specific threshold is also passed through as a pointer.
void readWaterLevel(const int waterLevelPin, int threshold, int* waterLevelValue, bool* waterLow) {
    *waterLevelValue = map(analogRead(waterLevelPin), 0, 350, 0, 100); // calibrate sensor to find highest value and replace third parameter
    if(*waterLevelValue < threshold) *waterLow = true;
    else *waterLow = false;
}

// readSoilMoisture reads the value on the soil moisture sensor (analog pin) and maps the value from range 
// [0, HIGHEST] to range [0, 100], where HIGHEST is the maximum value obtained during the sensor calibration.
// The mapped value of the soil moisture sensor is passed through a pointer. A boolean variable which indicates
// if the moisture level is below a specific threshold is also passed through as a pointer.
void readSoilMoisture(const int soilMoisturePin, int threshold, int* soilMoistureValue, bool* moistureLow) {
    *soilMoistureValue = map(analogRead(soilMoisturePin), 0, 350, 0, 100); // calibrate sensor to find highest value and replace third parameter
    if(*soilMoistureValue < threshold) *moistureLow = true;
    else *moistureLow = false;
}

// readTemperature reads the temperature value of the DHT11 sensor, and passes it through a pointer, as well as
// the state of the value, according to the parameters tempMin and tempMax. It also takes the DHT object as
// a pointer to avoid copying the object at every function call (every update cycle).
void readTemperature(DHT* dht, const int dhtPin, int tempMin, int tempMax, int* tempValue, string* tempState){
    int readData = *dht.read11(dhtPin);

    *tempValue = *dht.temperature;

    if(*tempValue < tempMin) *tempState = "LOW";
    else if(*tempValue > tempMax) *tempState = "HIGH";
    else *tempState = "GOOD";
}

// readHumidity reads the humidity value of the DHT11 sensor, and passes it through a pointer, as well as
// the state of the value, according to the parameters humMin and humMax. It also takes the DHT object as
// a pointer to avoid copying the object at every function call (every update cycle).
void readHumidity(DHT* dht, const int dhtPin, int humMin, int humMax, int* humValue, string* humState){
    int readData = *dht.read11(dhtPin);

    *humValue = *dht.humidity;

    if(*humValue < humMin) *humState = "LOW";
    else if(*humValue > humMax) *humState = "HIGH";
    else *humState = "GOOD";
}