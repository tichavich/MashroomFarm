//Node MCU ESP8266 (ESP-12E Module)

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

//WIFI
const char* ssid = "OPPO A77s";
const char* password = "p3npjs27";

//NETPIE
const char* mqtt_server = "mqtt.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "aea2bd9a-f1fa-4022-ba3b-8d28b1abaa11";   //Client ID
const char* mqtt_username = "nTvXQ2HSNxUNAnpciRgpg6hfcVqBuvi2";     //Token
const char* mqtt_password = "tTJAc1xJWGrnygY2ZaBxF14UcXhzUQgt";     //Secret


WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int set_temp = 33;
float temperature = 0;
int pump_switch = 0;
int switched_state = 0;

//TX,RX
#define tx_pin D2
#define rx_pin D3
#define switched_pin D5
SoftwareSerial com_serial(tx_pin, rx_pin);

void setup() {
  Serial.begin(115200);
  pinMode(switched_pin,OUTPUT);
  digitalWrite(switched_pin,LOW);
  setup_wifi(); 
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {   
  if (!client.connected()){
    reconnect();
  } 
    client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    publishTemp();

    if(switched_state == 0){
      if (temperature >= set_temp) {
        pump_switch = 1;
      }else{
        pump_switch = 0;
      }  
    }
    digitalWrite(switched_pin, pump_switch);    
  }  
}

void setup_wifi() {
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  randomSeed(micros());

  Serial.println("");
  Serial.printf("Connection Status: %d\n", WiFi.status()); 
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message_payload;
  for (int i = 0; i < length; i++) {
    message_payload += (char)payload[i];
  }  
  Serial.println(message_payload);
  if(String(topic) == "@msg/set_temp"){
    //Serial.println("{\"set_temp\":"+message_payload+"}");
    set_temp = message_payload.toInt();
    switched_state = 0;
  }

  if(String(topic) == "@msg/pump_switch"){
    //Serial.print("{\"pump_switch\":"+message_payload+"}");    
    pump_switch = message_payload.toInt();
    switched_state = 1;
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting NETPIE connection...");
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      Serial.println("NETPIE connected");      
      client.subscribe("@msg/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void publishTemp()
{
  DynamicJsonDocument doc(1024); 
  // Sending the request
  if(Serial.available() > 0){
    String input_text = Serial.readString();
    if(input_text.indexOf(';') != -1){    
      JsonDocument json_data;
      deserializeJson(json_data, input_text);
      temperature = json_data["temperature"];
      doc["data"]["temperature"] = temperature;
      doc["data"]["humidity"] = json_data["humidity"];
      //doc["data"]["pump_water"] = json_data["pump_water"];
      doc["data"]["pump_water"] = pump_switch;
      doc["data"]["set_temp"] = set_temp;
            
      char buffer[256];
      serializeJson(doc, buffer);
      
      if (client.publish("@shadow/data/update", buffer)) {
        Serial.println("\nPublish ok");
      }else{
        Serial.println("\nPublish failed");
      }
    }    
  }
  

}