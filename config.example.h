#pragma once

// Copier ce fichier en config.h puis renseigner uniquement la configuration locale.
// Ne jamais publier config.h.

const char* WIFI_SSID = "VOTRE_SSID";
const char* WIFI_PASSWORD = "VOTRE_MOT_DE_PASSE";

const char* MQTT_HOST = "test.mosquitto.org";
const unsigned int MQTT_PORT = 1883;
const char* MQTT_TOPIC = "binome4";

// Laisser vides si le broker n'exige pas d'authentification.
const char* MQTT_USER = "";
const char* MQTT_PASSWORD = "";

const char* MQTT_CLIENT_ID_PREFIX = "esp8266-oled-";
