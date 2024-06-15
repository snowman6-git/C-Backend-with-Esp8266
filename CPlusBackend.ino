#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiServer.h>
#include <U8g2lib.h> 
#include <Wire.h>

int port = 44
const char* ssid = "";
const char* password = "";
ESP8266WebServer server(port);
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 12, 14, U8X8_PIN_NONE); 

void setup() {
  u8g2.begin(); 
  Serial.begin(115200);
  u8g2.setFont(u8g2_font_ncenB08_tr);

  WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
  for (int i = 0; i <= 100; i++) {
    if (WiFi.status() == WL_CONNECTED){break;}
		delay(500);
	}
  refresh("Listen...");
	server.on("/", htmlmain);
	server.begin();

  refresh("Listen...OK");
  refresh("ALL...OK!");
}

void loop() {
  server.handleClient();
}

void htmlmain() {
	server.send(200, "text/html", "html");
}

void refresh(char* text) {
  u8g2.clearBuffer();
  u8g2.drawStr(1, 10, ("SSID: %d", ssid));
  u8g2.drawStr(1, 20, "=====================");
  u8g2.drawStr(1, 30, ("%d", WiFi.localIP().toString().c_str()));
  u8g2.drawStr(1, 40, (WiFi.macAddress().c_str()));
  u8g2.drawStr(1, 50, text);
  u8g2.sendBuffer();
}