// main.ino (23/11/2022)         |
// Miguel Hirche & Duarte Casal  |
// Main file                     |
// ______________________________|

#include <dht.h>

// GLOBAL VARIABLES
const int waterLevelPin = A0;
int waterLevelValue;
bool waterLow;

const int soilMoisturePin = A1;
int soilMoistureValue;
bool moistureLow;

const int dhtPin = 2;
int tempValue;
int humValue;
string tempState;
string humState;

DHT* dht;

void setup(){
    Serial.begin(9600);
    pinMode(dhtPin, INPUT);
}

void loop(){

}