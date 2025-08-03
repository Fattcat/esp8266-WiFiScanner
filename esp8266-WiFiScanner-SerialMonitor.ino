#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // Klientský mód, nehostuje vlastnú WiFi
  delay(100);          // Krátke oneskorenie pre stabilitu
}

void loop() {
  Serial.println("\nScanning for WiFi networks...");
  int num_networks = WiFi.scanNetworks();

  if (num_networks == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.println("------------------------------------------------------------------------------------------");
    Serial.printf("%-32s%-20s%-8s%-12s\n", "WiFi Name", "MAC Address", "Signal", "Security");
    Serial.println("------------------------------------------------------------------------------------------");

    for (int i = 0; i < num_networks; ++i) {
      String ssid = WiFi.SSID(i);
      String mac = WiFi.BSSIDstr(i);
      int rssi = WiFi.RSSI(i);
      String sec_str = get_security_type(WiFi.encryptionType(i));

      Serial.printf("%-32s%-20s%-8d%-12s\n", ssid.c_str(), mac.c_str(), rssi, sec_str.c_str());
    }
  }

  Serial.println("------------------------------------------------------------------------------------------");
  delay(10000); // čaká 10 sekúnd pred ďalším scanom
}

String get_security_type(uint8_t enc_type) {
  switch (enc_type) {
    case ENC_TYPE_NONE:  return "Open";
    case ENC_TYPE_WEP:   return "WEP";
    case ENC_TYPE_TKIP:  return "WPA (TKIP)";
    case ENC_TYPE_CCMP:  return "WPA2 (AES)";
    case ENC_TYPE_AUTO:  return "WPA/WPA2";
    default:             return "Unknown";
  }
}
