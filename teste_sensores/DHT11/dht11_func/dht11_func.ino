#include <dht.h>

dht DHT;

void setup(){
  Serial.begin(9600);
}

void loop(){
  int readData = DHT.read11(2);


  switch(readData)
  {
    case DHTLIB_OK: 
                Serial.println("OK"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.println("Checksum error"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.println("Time out error"); 
                break;
    default: 
                Serial.println("Unknown error"); 
                break;
  }
  
  float t = DHT.temperature;
  float h = DHT.humidity;

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("C");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("%");

  delay(5000);
}