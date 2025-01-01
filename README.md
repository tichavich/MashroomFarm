## Mashroom Farm Project
1. วงจร
2. ติดตั้งโปรแกรม Arduino IDE สำหรับเขียนโค้ด
   - ติดตั้งผ่าน Microsoft Store หรือติดตั้งจากไฟล์ https://www.arduino.cc/en/software
   - เปิดโปรแกรม Arduino IDE ไปที่เมนู File -> Preferences เพิ่ม https://arduino.esp8266.com/stable/package_esp8266com_index.json ลงในช่อง Additional Boards Manager URLs เพื่อติดตั้งบอร์ด Library NodeMCU/ESP8266
4. ติดตั้ง Library ESP8266 and DHT
   - ไปที่ Menu Tools -> Board: "Arduino…" ->  Boards Manager...
   - ค้นหาคำว่า "ESP8266"
   - เลือก esp8266 by ESP8266 community เวอร์ใหม่ล่าสุด
   - กด Install
5. การจัดเตรียมก่อนอัพโหลดโปรแกรมเข้าบอร์ด
   - เลือกชนิดของบอร์ด ESP8266 ไปที่ Tools -> Board: NodeMCU (ESP8266 ESP-12 Module)
   - เลือก Port การเชื่อมต่อ ไปที่ Tools -> Port -> com..