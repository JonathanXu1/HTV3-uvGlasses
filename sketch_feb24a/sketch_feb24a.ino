#include <OLEDDisplay.h>
#include <OLEDDisplayFonts.h>
#include <OLEDDisplayUi.h>

#include <Wire.h>
#include <SSD1306.h>
#include <SocketIOClient.h>
#include <ArduinoJson.h>

// Initialize the OLED display using Wire library
SSD1306  display(0x3c, D3, D5);

// Networking variables
const char* ssid = "nO wiReLEsS hOTsPoTs";
const char* password = "ZuccMe123";
String host = "superjunction.herokuapp.com";
int port = 5000;
DynamicJsonBuffer jsonBuffer(JSON_OBJECT_SIZE(3));
String JSON;
SocketIOClient socket;

void setup() {
  // put your setup code here, to run once:
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

}

void loop() {
    //Get UV
    int sensorValue = analogRead(A0);
    
    //Display
    display.clear();
    display.drawString(0, 0, "UV: " + String(sensorValue));
    display.display();
    delay(500);
}
