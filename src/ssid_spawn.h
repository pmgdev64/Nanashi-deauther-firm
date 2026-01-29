#ifndef SSID_SPAWN_H
#define SSID_SPAWN_H

#include <Arduino.h>
#include <esp_wifi.h>

// Danh sách SSID ảo - PROGMEM giúp tiết kiệm RAM [cite: 2026-01-02]
const char* const fake_ssids[] PROGMEM = {
  "🦉 Nanashi System",
  "☠ Hacked by Mumei, nya~",
  "⚠ High Voltage",
  "FREE WIFI! YAHOOOOOOO",
  "FBI OPEN UP!!!!!!!!!!"
};

// Cấu trúc Beacon Frame cơ bản
uint8_t beacon_packet[128] = { 
    0x80, 0x00, 0x00, 0x00, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // Đích: Broadcast
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, // Nguồn (Sẽ được random)
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, // BSSID
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x21, 0x04,
    0x00, 0x00 // SSID Tag
};

void runSsidSpam() {
  for (int i = 0; i < 5; i++) {
    // Random MAC để tạo nhiều AP ảo khác nhau
    for(int j=10; j<16; j++) beacon_packet[j] = random(256);
    
    // Gửi packet thô qua kênh Wi-Fi hiện tại
    esp_wifi_80211_tx(WIFI_IF_AP, beacon_packet, sizeof(beacon_packet), false);
    
    // Nhường CPU để không gây treo Web Server
    yield(); 
  }
}

#endif
