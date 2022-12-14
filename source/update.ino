// update.ino (10/12/2022)       |
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
dht DHT;

// WATER PUMP
const int waterPumpPin = 3; // RELAY PIN

// CYCLE
unsigned long initialTime = 0;
unsigned long currentTime = 0;
int updateTime = 10000;
int numCycles = 60; // START AT 60 SO WATER PUMP CAN BE ACTUATED ASAP

void setup(){
    Serial.begin(9600);
    pinMode(waterPumpPin, OUTPUT);
    digitalWrite(waterPumpPin, LOW);
}

void loop(){
    currentTime = millis();

    // WATER PUMP MANUAL ACTUATION
    char waterPumpActuation = Serial.read();
    if(waterPumpActuation == 'H') digitalWrite(waterPumpPin, HIGH); // ON
    else if(waterPumpActuation == 'L') digitalWrite(waterPumpPin, LOW); // OFF

    // UPDATE CYCLE 
    if(currentTime - initialTime >= updateTime){
        readWaterLevel(waterLevelPin, 35, waterLevelValue, waterLevelState);
        readSoilMoisture(soilMoisturePin, 30, 80, soilMoistureValue, soilMoistureState);
        readTempHum(DHT, dhtPin, 18, 28, 40, 80, tempValue, humValue, tempState, humState);
        
        // SEND DATA TO APP VIA BLUETOOTH
        sendData(tempValue, humValue, soilMoistureValue, waterLevelValue, tempState, humState, soilMoistureState, waterLevelState);

        // ACTUATE WATER PUMP AFTER AT LEAST 10 MINUTES FROM LAST ACTUATION
        if((soilMoistureState == "LOW") && (numCycles >= 60)){
            digitalWrite(waterPumpPin, HIGH);
            delay(800);
            digitalWrite(waterPumpPin, LOW);
            numCycles = 0;
        }

        numCycles++;
        initialTime = currentTime;
    }
}