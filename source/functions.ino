// sensors.ino (28/11/2022)      |
// Miguel Hirche & Duarte Casal  |
// Functions for sensors and     |
// bluetooth data transmission   |
// ______________________________|

// include dht.h library and add DHTlib-0.1.35.zip from source/lib/ to build in Arduino IDE
#include <dht.h>

// readWaterLevel reads the value on the level sensor (analog pin) and maps the value from range [0, HIGHEST] to
// range [0, 100], where HIGHEST is the maximum value obtained during the sensor calibration.
// The mapped value of the level sensor is passed by reference. A boolean variable which indicates
// if the water level is below a specific threshold is also passed by reference.
void readWaterLevel(const int waterLevelPin, int threshold, int &waterLevelValue, string &waterLevelState){
    waterLevelValue = map(analogRead(waterLevelPin), 480, 660, 0, 100); // [480, 660] is the range obtained through calibration for the wet sensor
    if(waterLevelValue < threshold) waterLow = true;
    else waterLow = false;
}

// readSoilMoisture reads the value on the soil moisture sensor (analog pin) and maps the value from range 
// [0, HIGHEST] to range [0, 100], where HIGHEST is the maximum value obtained during the sensor calibration.
// The mapped value of the soil moisture sensor is passed by reference. A boolean variable which indicates
// if the moisture level is below a specific threshold is also passed by reference.
void readSoilMoisture(const int soilMoisturePin, int threshold, int &soilMoistureValue, string &soilMoistureState){
    soilMoistureValue = map(analogRead(soilMoisturePin), 0, 1024, 0, 100); // [480, 660] is the range obtained through calibration for the wet sensor
    if(soilMoistureValue < threshold) moistureLow = true;
    else moistureLow = false;
}

// readTemperature reads the temperature value of the DHT11 sensor, and passes it by reference, as well as
// the state of the value, according to the parameters tempMin and tempMax. It also takes the DHT object as
// a pointer to avoid copying the object at every function call (every update cycle).
void readTemperature(DHT* dht, const int dhtPin, int tempMin, int tempMax, int &tempValue, string &tempState){
    int readData = *dht.read11(dhtPin);

    tempValue = *dht.temperature;

    if(tempValue < tempMin) tempState = "LOW";
    else if(tempValue > tempMax) tempState = "HIGH";
    else tempState = "GOOD";
}

// readHumidity reads the humidity value of the DHT11 sensor, and passes it by reference, as well as
// the state of the value, according to the parameters humMin and humMax. It also takes the DHT object as
// a pointer to avoid copying the object at every function call (every update cycle).
void readHumidity(DHT* dht, const int dhtPin, int humMin, int humMax, int &humValue, string &humState){
    int readData = *dht.read11(dhtPin);

    humValue = *dht.humidity;

    if(humValue < humMin) humState = "LOW";
    else if(humValue > humMax) humState = "HIGH";
    else humState = "GOOD";
}

// sendData will send data through the serial port, for the bluetooth module to communicate with the app.
// The function prints the values and statuses for the temperature, humidity, soil moisture and
// reservoir level, respectively. Each piece of data (integer or string) is separated by the "|" delimiter.
void sendData(int tempValue, int humValue, int soilMoistureValue, int waterLevelValue, string tempState,
string humState, string soilMoistureState, string waterLevelState){
    Serial.print(tempValue);
    Serial.print("|");
    Serial.print(humValue);
    Serial.print("|");
    Serial.print(soilMoistureValue);
    Serial.print("|");
    Serial.print(waterLevelValue);
    Serial.print("|");
    Serial.print(tempState);
    Serial.print("|");
    Serial.print(humState);
    Serial.print("|");
    Serial.print(soilMoistureState);
    Serial.print("|");
    Serial.print(waterLevelState);
}