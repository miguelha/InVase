// functions.ino (10/12/2022)    |
// Miguel Hirche & Duarte Casal  |
// Functions for sensors and     |
// bluetooth data transmission   |
// ______________________________|

// include dht.h library and add DHTlib-0.1.35.zip from source/lib/ to build in Arduino IDE

// readWaterLevel reads the value on the level sensor (analog pin) and maps the value from range [400, 850] to
// range [0, 100]. The mapped value of the level sensor is passed by reference. A 
// boolean variable which indicates if the water level is below a specific threshold 
// is also passed by reference.
void readWaterLevel(const int waterLevelPin, int threshold, int &waterLevelValue, String &waterLevelState){
    int waterLevelReading = analogRead(waterLevelPin);
    waterLevelReading = constrain(waterLevelReading, 400, 850); // make sure no value is out of range for mapping
    waterLevelValue = map(waterLevelReading, 400, 850, 0, 100); // [400, 850] is the range obtained through calibration for the wet sensor
    if(waterLevelValue < threshold) waterLevelState = "LOW";
    else waterLevelState = "GOOD";
}

// readSoilMoisture reads the value on the soil moisture sensor (analog pin) and maps the value from range 
// [480, 105] to range [0, 100]. The mapped value of the soil moisture sensor is 
// passed by reference. A boolean variable which indicates if the moisture level is 
// below a specific threshold is also passed by reference.
void readSoilMoisture(const int soilMoisturePin, int smMin, int smMax, int &soilMoistureValue, String &soilMoistureState){
    int soilMoistureReading = analogRead(soilMoisturePin);
    soilMoistureReading = constrain(soilMoistureReading, 105, 480); // make sure no value is out of range for mapping
    soilMoistureValue = map(soilMoistureReading, 480, 105, 0, 100); // [480, 105] is the range obtained through calibration for the wet sensor
    if(soilMoistureValue < smMin) soilMoistureState = "LOW";
    else if(soilMoistureValue > smMax) soilMoistureState = "HIGH";
    else soilMoistureState = "GOOD";
}

// readTempHum reads the temperature value of the DHT11 sensor, and passes it by reference, as well as
// the state of the value, according to the parameters tempMin and tempMax. It also reads the humidity value
// of the DHT11 sensor in the same function (to avoid reading twice faster than the polling rate), and passes
// it by reference, as well as the state of the value, according to the parameters humMin and humMax.
void readTempHum(dht DHT, const int dhtPin, int tempMin, int tempMax, int humMin, int humMax, int &tempValue, int &humValue, String &tempState, String &humState){
    int readData = DHT.read11(dhtPin);

    tempValue = DHT.temperature;
    humValue = DHT.humidity;

    if(tempValue < tempMin) tempState = "LOW";
    else if(tempValue > tempMax) tempState = "HIGH";
    else tempState = "GOOD";

    if(humValue < humMin) humState = "LOW";
    else if(humValue > humMax) humState = "HIGH";
    else humState = "GOOD";
}

// sendData will send data through the serial port, for the bluetooth module to communicate with the app.
// The function prints the values and statuses for the temperature, humidity, soil moisture and
// reservoir level, respectively. Each piece of data (integer or string) is separated by the "|" delimiter.
// The newline character indicates the end of the data stream for the current update cycle.
void sendData(int tempValue, int humValue, int soilMoistureValue, int waterLevelValue, String tempState,
String humState, String soilMoistureState, String waterLevelState){
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
    Serial.println("|");
}