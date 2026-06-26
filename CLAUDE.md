# Jarvicks — contexte projet

Assistant maison « type Jarvis » bâti autour d'un **ESP32-WROVER avec caméra**.
Vision long terme : une carte qui voit / entend / parle, pilotée par un modèle d'IA
tournant sur le Mac de l'utilisateur. On avance **par petites étapes**, en gardant le
code propre et modulaire à chaque ajout.

## État actuel

L'ESP32 se connecte au WiFi et diffuse le flux caméra (MJPEG) sur un serveur HTTP,
accessible via `http://jarvicks.local/`. C'est la première brique validée (hardware OK).

## Matériel

- Carte : **Freenove ESP32-WROVER** (CAM, capteur OV2640, PSRAM présente)
- Brochage caméra = modèle **WROVER_KIT** (voir `include/camera_pins.h`, figé)
- Port série Mac : `/dev/cu.usbserial-3120` (peut changer)
- Alim : USB 5V (Mac, chargeur mural ou power bank). La carte a aussi un jack DC —
  NE PAS y mettre du 9V sans avoir vérifié la plage de tension acceptée.

## Build / flash (PlatformIO)

`pio` n'est pas dans le PATH ; binaire à `~/.platformio/penv/bin/pio`.

```bash
~/.platformio/penv/bin/pio run                  # compiler
~/.platformio/penv/bin/pio run --target upload  # flasher
~/.platformio/penv/bin/pio device monitor       # moniteur serie (115200 bauds)
```

## Architecture du code

Une responsabilité par fichier (voir README pour la liste). `main.cpp` reste un simple
chef d'orchestre : `camera_init()` → `net_connect()` → `stream_server_start()`.
Pour ajouter une brique (ex. audio), créer un module `src/xxx.cpp/.h` et l'appeler
depuis `setup()` — ne pas gonfler `main.cpp`.

## Conventions & pièges

- **Secrets** : `include/config.h` contient le mot de passe WiFi → **gitignoré**, jamais
  commité. Le modèle versionné est `include/config.h.example`. Repo GitHub **public**.
- **WiFi 2.4 GHz uniquement** (l'ESP32 ne voit pas le 5 GHz).
- Le flux MJPEG sur `/` est volontairement minimal (pas l'exemple usine de 600 lignes) :
  facile à lire et à étendre.
- Après modif de code : vérifier que `pio run` compile avant de pousser.
- Langue de travail avec l'utilisateur : **français**.

## Prochaines étapes envisagées (non figées)

Sortie audio (speaker, probablement via ampli I2S type MAX98357A), puis liaison vers un
modèle d'IA sur le Mac qui consommera le flux et renverra de la voix. Le détail sera
précisé le moment venu — demander le contexte plutôt que de présumer.
