#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // Set WiFi mode to station (client)
}

void loop() {
  int num_networks = WiFi.scanNetworks();
  Serial.println("WiFi Network Scan Results:");
  Serial.println("----------------------------------------------------------------------------------------------------------------");
  Serial.printf("%-32s%-20s%-8s%-12s%-24s%-10s\n", "Wifi Name", "MAC Address", "Signal", "Security", "Connected Users", "Disconnected Users");
  Serial.println("----------------------------------------------------------------------------------------------------------------");
  
  for (int i = 0; i < num_networks; i++) {
    String ssid = WiFi.SSID(i);
    String mac = WiFi.BSSIDstr(i);
    int rssi = WiFi.RSSI(i);
    int sec_type = WiFi.encryptionType(i);
    String sec_str = "";
    int num_connected = get_num_connected_devices(mac);
    int num_disconnected = get_num_disconnected_devices(mac);
    String connected_str = "";
    String disconnected_str = "";
    
    switch (sec_type) {
      case ENC_TYPE_NONE:
        sec_str = "Open";
        break;
      case ENC_TYPE_WEP:
        sec_str = "WEP";
        break;
      case ENC_TYPE_TKIP:
      case ENC_TYPE_CCMP:
      case ENC_TYPE_AUTO:
        sec_str = "WPA/WPA2";
        break;
      default:
        sec_str = "Unknown";
        break;
    }
    
    for (int j = 0; j < num_connected; j++) {
      String client_mac = get_connected_device_mac(mac, j);
      String client_name = get_client_name(client_mac);
      connected_str += client_name + " (" + client_mac + ")\n";
    }
    
    for (int j = 0; j < num_disconnected; j++) {
      String client_mac = get_disconnected_device_mac(mac, j);
      String client_name = get_client_name(client_mac);
      disconnected_str += client_name + " (" + client_mac + ")\n";
    }
    
    Serial.printf("%-32s%-20s%-8d%-12s%-24s%-10s\n", ssid.c_str(), mac.c_str(), rssi, sec_str.c_str(), connected_str.c_str(), disconnected_str.c_str());
  }
  
  Serial.println("------------------------------------------------------------------------");
  delay(10000); // Wait for 10 seconds before scanning again
}

String get_client_name(String mac_address) {
  // TODO: Implement a function to get the client name from its MAC address
  return "Unknown";
}

int get_num_connected_devices(String mac_address) {
  // TODO: Implement a function to get the number of connected devices for a given MAC address
  return 0;
}

String get_connected_device_mac(String mac_address, int index) {
  // TODO: Implement a function to get the MAC address of a connected device by index
  return "";
}

int get_num_disconnected_devices(String mac_address) {
  // TODO: Implement a function to get the number of disconnected devices for a given MAC address
  return 0;
}

String get_disconnected_device_mac(String mac_address, int index) {
  // TODO: Implement a function to get the MAC address of a disconnected device by index
  return "";
}
