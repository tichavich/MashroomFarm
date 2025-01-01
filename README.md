## Mashroom Farm Project
1. วงจร
2. ติดตั้งโปรแกรม Arduino IDE สำหรับเขียนโค้ด
   - ติดตั้งผ่าน Microsoft Store หรือติดตั้งจากไฟล์ https://www.arduino.cc/en/software
   - เปิดโปรแกรม Arduino IDE ไปที่เมนู File -> Preferences เพิ่ม https://arduino.esp8266.com/stable/package_esp8266com_index.json ลงในช่อง Additional Boards Manager URLs เพื่อติดตั้งบอร์ด Library NodeMCU/ESP8266
4. ติดตั้ง Library ESP8266 and DHT
   - ไปที่ Menu Tools -> Board: "Arduino…" ->  Boards Manager...
   - ค้นหาคำว่า *"ESP8266"*
   - เลือก **esp8266 by ESP8266 community** เวอร์ใหม่ล่าสุด
   - กด Install
5. ติดตั้ง Library DHT
   - ไปที่ Menu Tools -> Board: "Arduino…" ->  Boards Manager...
   - ค้นหาคำว่า *"dht"*
   - เลือก **DHT sensor library by Adafruit** เวอร์ใหม่ล่าสุด
   - กด Install
6. การจัดเตรียมก่อนอัพโหลดโปรแกรมเข้าบอร์ด
   - เลือกชนิดของบอร์ด ESP8266 ไปที่ Tools -> Board: NodeMCU (ESP8266 ESP-12 Module)
   - เลือก Port การเชื่อมต่อ ไปที่ Tools -> Port -> com..
7. โค้ดโปรแกรมบอร์ด 
   [Code Arduino Uno](https://github.com/tichavich/MashroomFarm/blob/master/board_arduino.c)
   - อ่านค่าความชื้นและอุณหภูมิ Senser และส่งค่าผ่าน Serial Port
        ```
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
        ```
8. โค้ดโปรแกรมบอร์ด 
   [Code ESP8266](https://github.com/tichavich/MashroomFarm/blob/master/board_esp8266.c)
   - กำหนดค่าที่สำคัญ
      ```
      //WIFI
      const char* ssid = "...";
      const char* password = "...";

      //NETPIE
      const char* mqtt_server = "mqtt.netpie.io";
      const int mqtt_port = 1883;
      const char* mqtt_Client = "...";   //Client ID
      const char* mqtt_username = "...";     //Token
      const char* mqtt_password = "..";     //Secret
      ```
   - ฟังก์ชั่นสำหรับส่งข้อมูลขึ้น mqtt.netpie.io ด้วย publish "@shadow/data/update" รูปแบบ JSON
      ```
      void publishTemp(){
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
      ```
   - ฟังก์ชั่นสำหรับรับข้อมูลจาก mqtt.netpie.io ด้วย topic "@msg/..." รูปแบบ String
      ```
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
      ```
9. หน้า Dashboard ควบคุมการทำงานของวงจร ด้วย [NETPIE.io](https://netpie.io/)

![Screenshot 2024-12-21 212726](https://github.com/user-attachments/assets/aaea5e39-c7bd-4de2-93d6-d8b633f8a38d)
![Screenshot 2024-12-21 212813](https://github.com/user-attachments/assets/5cd857ad-e9dc-43e4-9213-be556dbc862a)
![Screenshot 2024-12-21 212842](https://github.com/user-attachments/assets/da605f33-652e-4ad8-a457-fc1c1da4178a)
![Screenshot 2024-12-21 212922](https://github.com/user-attachments/assets/9f6cd67b-f4d7-4e97-95a8-b7ddac235645)


แหล่งข้อมูลเพิ่มเติม
[Arduino IDE Document](https://docs.arduino.cc/built-in-examples/)
[คู่มือการใช้งาน NETPIE](https://netpie.io/guide)
[DHT11, DHT22 and AM2302 Sensors by adafruit](https://learn.adafruit.com/dht)
