// main.ino (23/11/2022)         |
// Miguel Hirche & Duarte Casal  |
// Update cycle and bluetooth    |
// communication                 |
// ______________________________|

#include <dht.h>

// GLOBAL VARIABLES
// WATER LEVEL SENSOR
const int waterLevelPin = A0;
int waterLevelValue;
bool waterLow;

// SOIL MOISTURE SENSOR
const int soilMoisturePin = A1;
int soilMoistureValue;
bool moistureLow;

// DHT11 (TEMPERATURE & HUMIDITY)
const int dhtPin = 2;
int tempValue;
int humValue;
string tempState;
string humState;
DHT* dht;

// CYCLE
int updateTime = 10000;
int numCycles = 0;

void setup(){
    Serial.begin(9600);
    pinMode(dhtPin, INPUT);

    // BLUETOOTH COMMUNICATION

}

void loop(){
    unsigned long initialTime = millis();

    // UPDATE CYCLE
    while(millis() - initialTime < updateTime){
        readWaterLevel(waterLevelPin, 35, &waterLevelValue, &waterLow);
        readSoilMoisture(soilMoisturePin, 30, &soilMoistureValue, &moistureLow);
        readTemperature(dht, dhtPin, 18, 30, &tempValue, &tempState);
        readHumidity(dht, dhtPin, 40, 70, &humValue, &humState);

        // SEND DATA TO APP VIA BLUETOOTH

        // ACTUATE WATER PUMP AFTER AT LEAST 5 MINUTES FROM LAST ACTUATION
        if(moistureLow && numCycles >= 30){


            numCycles = 0;
        }

        numCycles++;
    }
}