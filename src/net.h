#pragma once
#include <Arduino.h>

// Connecte l'ESP32 au WiFi (config.h) puis demarre le mDNS.
// Bloque jusqu'a connexion. Renvoie true si connecte.
bool net_connect();

// Renvoie l'adresse IP locale sous forme de texte (ex: "192.168.0.106").
String net_ip();
