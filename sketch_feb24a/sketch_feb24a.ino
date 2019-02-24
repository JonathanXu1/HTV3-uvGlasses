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
String host = "uv-glasses.herokuapp.com";
//String host = "192.168.137.1";
int port = 5000;
int localMode = false;

DynamicJsonBuffer jsonBuffer(JSON_OBJECT_SIZE(1));
String JSON;
SocketIOClient socket;
JsonObject& data = jsonBuffer.createObject();

void setup() {
  Serial.begin(115200);
  Serial.println("yeet");
  
  // put your setup code here, to run once:
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  // Set up wifi
  WiFi.begin(ssid, password);
    uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20){
    delay(500);
    Serial.print(".");
  }
  if(i == 21){
    Serial.println("");
    Serial.println("WiFi failed to connect");
  } else {
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

  // Set up socket
  if (localMode){
    if (!socket.connect(host, port)) {
      Serial.println("Not connected to host");
    }
  } else {
    if (!socket.connect(host)) {
      Serial.println("Not connected to host");
    }
  }
  if (socket.connected()) {
    Serial.println("Connected to host");
  }
  else {
    Serial.println("Connection Error");
  }
}

void loop() {
    //Get UV
    double sensorValue = analogRead(A0);
    double uvValue = (((sensorValue/1023)*3.3)/4.3)*10;
    //Display
    display.clear();
    display.drawString(0, 0, "UV Index: ");
    display.drawString(0, 20, String(uvValue, 6));
    display.display();
    delay(500);

    if(socket.connected()){ // Run when connected to wifi and host
      JSON = "";
      data["uv"] = uvValue;
      data.printTo(JSON);
      socket.emit("updateData", JSON);
  }
}
