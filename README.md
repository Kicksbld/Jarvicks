# Jarvicks

Assistant maison (type « Jarvis ») construit autour d'une carte **ESP32-WROVER + caméra**.

L'objectif à terme : une carte qui voit (caméra), entend et parle (speaker), reliée à
un modèle d'intelligence artificielle tournant sur un Mac. Le projet démarre simple et
s'enrichit étape par étape.

> ⚠️ Work in progress — le périmètre évoluera. Ce README décrit l'état actuel.

## Étape actuelle

L'ESP32 se connecte au WiFi et diffuse le flux **vidéo de la caméra** sur une petite
page web. On le consulte depuis n'importe quel appareil du réseau :

- **http://jarvicks.local/** (nom mDNS, pratique)
- ou directement via l'IP affichée dans le moniteur série

## Matériel

- Carte **Freenove ESP32-WROVER** (CAM, capteur OV2640)
- Câble USB (flash + alimentation)
- Alimentation autonome possible : chargeur USB 5V (recommandé pour du continu)

## Structure du code

```
include/
  config.h          Réglages perso (WiFi, nom, qualité caméra) — NON versionné
  config.h.example  Modèle à copier en config.h
  camera_pins.h     Brochage caméra de la carte (figé)
src/
  camera.cpp/.h     Initialisation de la caméra
  net.cpp/.h        Connexion WiFi + mDNS
  stream_server.cpp/.h  Serveur HTTP qui diffuse le flux MJPEG
  main.cpp          Point d'entrée : enchaîne caméra → réseau → serveur
platformio.ini      Configuration PlatformIO (carte, build flags PSRAM)
```

## Démarrage rapide

Projet basé sur [PlatformIO](https://platformio.org/).

```bash
# 1. Créer sa config locale (jamais commitée)
cp include/config.h.example include/config.h
#    puis éditer include/config.h avec son SSID / mot de passe WiFi

# 2. Compiler + flasher la carte
pio run --target upload

# 3. Ouvrir le moniteur série pour voir l'adresse
pio device monitor
```

Puis ouvrir **http://jarvicks.local/** dans un navigateur.

> Le WiFi doit être en **2.4 GHz** (l'ESP32 ne capte pas le 5 GHz).

## Feuille de route (indicative)

- [x] Flux vidéo de la caméra dans le navigateur
- [ ] Sortie audio (speaker) pour faire parler Jarvicks
- [ ] Liaison avec un modèle d'IA sur le Mac
- [ ] Interaction voix / vision
