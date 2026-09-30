#include <Arduino.h>
#include "esp_camera.h"   // cam
#include "FS.h"           // data system
#include "SD_MMC.h"      // SD slot
#include <TFT_eSPI.h>     // Display

#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM     15
#define SIOD_GPIO_NUM     4
#define SIOC_GPIO_NUM     5
#define Y9_GPIO_NUM       16
#define Y8_GPIO_NUM       17
#define Y7_GPIO_NUM       18
#define Y6_GPIO_NUM       12
#define Y5_GPIO_NUM       10
#define Y4_GPIO_NUM       8
#define Y3_GPIO_NUM       9
#define Y2_GPIO_NUM       11
#define VSYNC_GPIO_NUM    6
#define HREF_GPIO_NUM     7
#define PCLK_GPIO_NUM     13

#define BUTTON_PIN        1 //button

TFT_eSPI tft = TFT_eSPI();  //Display objekt

void setupCamera() {      //init the cam
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0       = Y2_GoIO_NUM;
  config.pin_d1       = Y3_GPIO_NUM;
  config.pin_d2       = Y4_GPIO_NUM;
  config.pin_d3       = Y5_GPIO_NUM;
  config.pin_d4       = Y6_GPIO_NUM;
  config.pin_d5       = Y7_GPIO_NUM;
  config.pin_d6       = Y8_GPIO_NUM;
  config.pin_d7       = Y9_GPIO_NUM;
  config.pin_xclk     = XCLK_GPIO_NUM;
  config.pin_pclk     = PCLK_GPIO_NUM;
  config.pin_vsync    = VSYNC_GPIO_NUM;
  config.pin_href     = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn     = PWDN_GPIO_NUM;
  config.pin_reset    = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
if (psramFound()) {
    config.frame_size   = FRAMESIZE_QVGA; // 320x240
    config.jpeg_quality = 10;
    config.fb_count     = 2;
  } else {
    config.frame_size   = FRAMESIZE_QQVGA;
    config.jpeg_quality = 12;
    config.fb_count     = 1;
  }
esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Kamera-Fehler: 0x%x\n", err);
  }
}

void setupSD() {    init the sd card
  SD_MMC.setPins(39, 38, 40); // CLK=39, CMD=38, D0=40
  if (!SD_MMC.begin("/sdcard", true)) {
    Serial.println("SD-Karte konnte nicht gestartet werden!");
    return;
  }
  Serial.println("SD-Karte erfolgreich verbunden.");
}

void savePhoto() {    //for saving the pictures on the sd
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Kamera-Aufnahme fehlgeschlagen!");
    return;
  }

  String path = "/photo_" + String(millis()) + ".jpg";
  File file = SD_MMC.open(path.c_str(), FILE_WRITE);

  if (!file) {
    Serial.println("Fehler beim Öffnen der Datei auf SD!");
  } else {
    file.write(fb->buf, fb->len);
    Serial.printf("Foto gespeichert: %s\n", path.c_str());
    
    // Kurze Rückmeldung auf dem Display
    tft.fillScreen(TFT_GREEN);
    delay(100);
  }

  file.close();
  esp_camera_fb_return(fb);
}

void setup() {
  Serial.begin(115200);

  tft.init();    //starting the display
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("Mini Cam Startet...", 10, 10, 2);

  pinMode(BUTTON_PIN, INPUT_PULLUP);  //configure the button

  setupCamera();  //starting the cam
  setupSD();  //starting the sd

  tft.fillScreen(TFT_BLACK);
  tft.drawString("Bereit!", 10, 10, 2);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {   //if the button is pressed it takes a picture
    tft.drawString("Speichere...", 10, 40, 2);
    savePhoto();
    delay(500);
  }
}
