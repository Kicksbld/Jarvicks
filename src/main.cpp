#include <Arduino.h>
#include "config.h"
#include "camera.h"
#include "net.h"
#include "stream_server.h"

// =====================================================================
//  JARVICKS — point d'entree
//  setup() enchaine les briques : camera -> WiFi -> serveur de flux.
// =====================================================================

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println();

  // 1) Camera
  if (camera_init() != ESP_OK) {
    Serial.println("[X] Echec init camera, arret.");
    return;
  }
  Serial.println("[OK] Camera initialisee");

  // 2) Reseau (WiFi + mDNS)
  net_connect();

  // 3) Serveur de flux video
  stream_server_start();

  Serial.println("======================================================");
  Serial.println("  Flux camera pret -> ouvre dans ton navigateur :");
  Serial.println("  http://" MDNS_HOSTNAME ".local/");
  Serial.println("  ou directement : http://" + net_ip() + "/");
  Serial.println("======================================================");
}

void loop() {
  // Le serveur HTTP tourne dans sa propre tache : rien a faire ici pour l'instant.
  // (Plus tard : gestion du speaker, de l'audio, etc.)
  delay(10000);
}
