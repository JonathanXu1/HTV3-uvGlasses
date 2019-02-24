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
int port = 5000;
int localMode = true;

DynamicJsonBuffer jsonBuffer(JSON_OBJECT_SIZE(3));
String JSON;
SocketIOClient socket;
JsonObject& data = jsonBuffer.createObject();

void setup() {
  // put your setup code here, to run once:
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  Serial.begin(115200);
  while(!Serial);

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
    int sensorValue = analogRead(A0);
    
    //Display
    display.clear();
    display.drawString(0, 0, "UV: " + String(sensorValue));
    display.display();
    delay(500);

    if(socket.connected()){ // Run when connected to wifi and host
      JSON = "";
      data["uv"] = sensorValue;
      data.printTo(JSON);
      socket.emit("updateData", JSON);
  }
}
