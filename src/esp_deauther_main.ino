#include <WiFi.h>
#include <WebServer.h>
#include "web_index.h"

#define LED_PIN 8
WebServer server(80);

// Biến này nằm trên RAM, sẽ luôn là false khi Reset/Mất điện
bool attackActive = false; 

unsigned long prevLED = 0;
int strobeStep = 0;
const int strobePattern[] = {50, 100, 50, 5000}; 

void handleLED() {
    unsigned long current = millis();
    if (attackActive) {
        if (current - prevLED >= 40) { 
            digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
            prevLED = current; 
        }
    } else {
        if (current - prevLED >= strobePattern[strobeStep]) {
            prevLED = current;
            strobeStep = (strobeStep + 1) % 4;
            digitalWrite(LED_PIN, (strobeStep == 0 || strobeStep == 2) ? LOW : HIGH);
        }
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH); // Tắt LED lúc mới boot

    // KHÔNG gọi prefs.begin() ở đây [cite: 2026-01-02]
    attackActive = false; 

    WiFi.softAP("Nanashi-C3-SuperMini", "mumei123");
    
    server.on("/", []() { server.send(200, "text/html", INDEX_HTML); });
    
    server.on("/api/attack", []() {
        attackActive = !attackActive; 
        // KHÔNG có lệnh putBool, trạng thái sẽ mất khi Reset
        server.send(200, "text/plain", attackActive ? "ON" : "OFF");
    });

    server.begin();
}

void loop() {
    server.handleClient();
    handleLED();
    
    if (attackActive) {
        // Gọi hàm từ ssid_spawn.c nhưng phải có delay cực nhỏ
        // runSsidSpam(); 
        delay(1); 
    }
} 
