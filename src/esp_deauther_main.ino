#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include "web_index.h"

#define LED_PIN 2  // LED xanh trên ESP-12E
ESP8266WebServer server(80);

unsigned long prevT = 0;
int st = 0;
bool fanStatus = false;

void autoSave() {
  EEPROM.write(1, fanStatus);
  EEPROM.commit();
  Serial.println("AutoSaved!");
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  pinMode(LED_PIN, OUTPUT);
  
  // Đọc trạng thái fan cũ
  fanStatus = EEPROM.read(1);
  
  WiFi.softAP("Nanashi_Deauth", "mumei123");
  
  server.on("/", []() { server.send(200, "text/html", INDEX_HTML); });
  
  server.on("/api/fan", []() {
    fanStatus = !fanStatus;
    autoSave(); // [2026-01-02]
    server.send(200, "application/json", "{\"msg\":\"Fan Toggle OK\"}");
  });

  server.on("/api/scan", []() {
    server.send(200, "application/json", "{\"msg\":\"Scanning...\"}");
  });

  server.begin();
}

void loop() {
  server.handleClient();

  // LED nháy kiểu máy bay (Không dùng delay)
  unsigned long cur = millis();
  if (st == 0 && cur - prevT >= 50) { digitalWrite(LED_PIN, 0); prevT = cur; st = 1; }
  else if (st == 1 && cur - prevT >= 50) { digitalWrite(LED_PIN, 1); prevT = cur; st = 2; }
  else if (st == 2 && cur - prevT >= 50) { digitalWrite(LED_PIN, 0); prevT = cur; st = 3; }
  else if (st == 3 && cur - prevT >= 50) { digitalWrite(LED_PIN, 1); prevT = cur; st = 4; }
  else if (st == 4 && cur - prevT >= 1500) { st = 0; prevT = cur; }
}
