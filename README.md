# mini-cam-esp32
A tiny camera running on an esp32 displaying a live review to a screen.
I want to build a camera using an ESP32, a screen, and a few buttons. I want to use a 2-inch LCD display module because it is about 5 cm in size, has a resolution of 240x320 pixels, and only costs 16 euros. For the ESP, I decided on an ESP32-S3 from Freenove because it has an integrated camera and SD card slot, as well as 8 MB of PSRAM, which will ensure a smooth video stream. Unfortunately, it costs 21 euros, but it already includes almost everything I need. The finished camera should be able to capture photos as well as smooth videos (without sound). Since I have a 3D printer at home and some experience with Tinkercad, making the case shouldn't be a problem. I will connect the parts using wires and my dad's old Weller soldering iron.
<img width="571" height="666" alt="cam_proj1" src="https://github.com/user-attachments/assets/02e6137f-482f-4f65-b644-0db5b9c555a0" />




## Bill of Materials (BOM)

| Item | Quantity | Description | Link | Price |
| --- | --- | --- | --- | --- |
| Freenove ESP32-S3 Board | 1 | ESP32-S3 with Camera & SD Slot | https://www.amazon.de/gp/product/B0BMQ8F7FN/ref=ox_sc_act_image_1_2?smid=A3DM8VCGJL5PKR&th=1 | 16,31€ |
| 2inch LCD Display Module | 1 | 240x320 TFT Display | https://www.amazon.de/gp/product/B0CY7X8TWB/ref=ox_sc_act_title_1_1?smid=A2NY5HB5PZ1W3L&psc=1 | 20,95€ |

<img width="1471" height="772" alt="esp_cam" src="https://github.com/user-attachments/assets/0b5883ac-a0bf-402f-ad9a-376d3271df44" />


In the document "wiring" you can see the needed wiring for intern AND extern components.

There is no PCB design or data because i want to solder it my own. I really like soldering you should try it too.

Currently main.ino is just a test if the screen, sd card and camera works. Im currently working on the rest of the code.

    Wiring:

Display = ESP32

VCC = ESP32 3V3
GND = ESP32 GND
CLK = GPIO 12 (SPI CLK)
DIN = GPIO 11 (SPI MOSI)
RST = GPIO 10
DC = GPIO 9
CS = GPIO 14
BL = 3V3 (Backlight)



Button = ESP32

pin 1 = GPIO 1
pin 2 = GnD


more detailed wiring on the extra file
