#include "net.h"
#include "config.h"
#include <WiFi.h>
#include <ESPmDNS.h>

bool net_connect() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.setSleep(false);

  Serial.print("Connexion au WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" OK");

  // mDNS : adresse fixe et lisible http://jarvicks.local/
  if (MDNS.begin(MDNS_HOSTNAME)) {
    MDNS.addService("http", "tcp", HTTP_PORT);
    Serial.println("[OK] mDNS demarre");
  } else {
    Serial.println("[!] Echec mDNS (l'IP reste utilisable)");
  }

  return true;
}

String net_ip() {
  return WiFi.localIP().toString();
}
