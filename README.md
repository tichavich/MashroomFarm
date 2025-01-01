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
6. โค้ดโปรแกรมบอร์ด 
   [Code Arduino Uno](https://github.com/tichavich/MashroomFarm/blob/master/broad_arduino.c)
8. โค้ดโปรแกรมบอร์ด 
   [Code ESP8266](https://github.com/tichavich/MashroomFarm/blob/master/broad_esp8266.c)
10. หน้า Dashboard ควบคุมการทำงานบน [NETPIE.](https://netpie.io/)

![Screenshot 2024-12-21 212726](https://github.com/user-attachments/assets/aaea5e39-c7bd-4de2-93d6-d8b633f8a38d)
![Screenshot 2024-12-21 212813](https://github.com/user-attachments/assets/5cd857ad-e9dc-43e4-9213-be556dbc862a)
![Screenshot 2024-12-21 212842](https://github.com/user-attachments/assets/da605f33-652e-4ad8-a457-fc1c1da4178a)
![Screenshot 2024-12-21 212922](https://github.com/user-attachments/assets/9f6cd67b-f4d7-4e97-95a8-b7ddac235645)
