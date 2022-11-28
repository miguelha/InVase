// main.ino (28/11/2022)         |
// Miguel Hirche & Duarte Casal  |
// Update cycle and bluetooth    |
// communication                 |
// ______________________________|

#include <dht.h>

// GLOBAL VARIABLES
// WATER LEVEL SENSOR
const int waterLevelPin = A0;
int waterLevelValue;
String waterLevelState;

// SOIL MOISTURE SENSOR
const int soilMoisturePin = A1;
int soilMoistureValue;
String soilMoistureState;

// DHT11 (TEMPERATURE & HUMIDITY)
const int dhtPin = 2;
int tempValue;
int humValue;
String tempState;
String humState;
dht* DHT;

// CYCLE
unsigned long initialTime = 0;
unsigned long currentTime = 0;
int updateTime = 10000;
int numCycles = 0;

void setup(){
    Serial.begin(9600);
    pinMode(dhtPin, INPUT);

    // BLUETOOTH COMMUNICATION

}

void loop(){
    currentTime = millis();

    // UPDATE CYCLE 
    if(currentTime - initialTime >= updateTime){
        readWaterLevel(waterLevelPin, 35, waterLevelValue, waterLevelState);
        readSoilMoisture(soilMoisturePin, 30, soilMoistureValue, soilMoistureState);
        readTemperature(DHT, dhtPin, 18, 30, tempValue, tempState);
        readHumidity(DHT, dhtPin, 40, 70, humValue, humState);

        // SEND DATA TO APP VIA BLUETOOTH
        sendData(tempValue, humValue, soilMoistureValue, waterLevelValue, tempState, humState, soilMoistureState, waterLevelState);

        // ACTUATE WATER PUMP AFTER AT LEAST 5 MINUTES FROM LAST ACTUATION
        /*if(moistureLow && numCycles >= 30){


            numCycles = 0;
        }

        numCycles++;*/
        initialTime = currentTime;
    }
}