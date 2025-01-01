//Aruduino Uno

#include "DHT.h"
#include <ArduinoJson.h>
#include <SoftwareSerial.h>


//Sensor DHT22
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//Relay
int relay_pin = 7;

//TX,RX
#define rx_pin 2
#define tx_pin 3
SoftwareSerial com_serial(rx_pin, tx_pin);

#define switched_pin 5

void setup() {    
  pinMode(relay_pin,OUTPUT); 
  pinMode(switched_pin,INPUT);
  digitalWrite(relay_pin,1);
  Serial.begin(115200);
  dht.begin();
}

void loop() {    
  delay(2000);
  if(digitalRead(switched_pin) == 1){    
    digitalWrite(relay_pin, 0);
  }else{
    digitalWrite(relay_pin, 1);
  }   
  // Read temperature as Celsius (the default)  
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  DynamicJsonDocument doc(1024);
  doc["temperature"] = t;
  doc["humidity"] = h;
  doc["switched_state"] = digitalRead(switched_pin);
  doc["relay_state"] = digitalRead(relay_pin);
        
  char buffer[256];
  serializeJson(doc, buffer);
  //  output json string 
  Serial.println(buffer+String(";"));  
}