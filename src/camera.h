#pragma once
#include "esp_camera.h"

// Initialise la camera selon les reglages de config.h.
// Renvoie ESP_OK si tout va bien, sinon un code d'erreur esp_err_t.
esp_err_t camera_init();
