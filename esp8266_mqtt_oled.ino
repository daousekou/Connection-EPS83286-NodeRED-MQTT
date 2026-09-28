#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"

namespace {
constexpr uint8_t OLED_WIDTH = 128;
constexpr uint8_t OLED_HEIGHT = 64;
constexpr int8_t OLED_RESET_PIN = -1;
constexpr uint8_t OLED_I2C_ADDRESS = 0x3C;
constexpr unsigned long WIFI_RETRY_DELAY_MS = 500;
constexpr unsigned long MQTT_RETRY_DELAY_MS = 5000;

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET_PIN);
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
unsigned long lastMqttAttempt = 0;

void showMessage(const String& title, const String& message) {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setTextWrap(true);
  display.setCursor(0, 0);
  display.println(title);
  display.println("--------------------");
  display.println(message);
  display.display();
}

void connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  showMessage("Wi-Fi", "Connexion en cours...");

  unsigned int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 40) {
    delay(WIFI_RETRY_DELAY_MS);
    ++attempts;
  }

  if (WiFi.status() == WL_CONNECTED) {
    showMessage("Wi-Fi connecte", WiFi.localIP().toString());
  } else {
    showMessage("Erreur Wi-Fi", "Verifier config.h");
  }
}

void onMqttMessage(char* topic, byte* payload, unsigned int length) {
  String message;
  message.reserve(length);

  for (unsigned int i = 0; i < length; ++i) {
    message += static_cast<char>(payload[i]);
  }

  Serial.printf("Message recu [%s] : %s\n", topic, message.c_str());
  showMessage(String("MQTT: ") + topic, message);
}

bool connectMqtt() {
  const String clientId =
      String(MQTT_CLIENT_ID_PREFIX) + String(ESP.getChipId(), HEX);

  bool connected = false;
  if (strlen(MQTT_USER) > 0) {
    connected = mqttClient.connect(
        clientId.c_str(), MQTT_USER, MQTT_PASSWORD);
  } else {
    connected = mqttClient.connect(clientId.c_str());
  }

  if (!connected) {
    Serial.printf("Echec MQTT, code=%d\n", mqttClient.state());
    return false;
  }

  mqttClient.subscribe(MQTT_TOPIC);
  Serial.printf("Abonne au topic %s\n", MQTT_TOPIC);
  showMessage("MQTT connecte", String("Topic: ") + MQTT_TOPIC);
  return true;
}
}  // namespace

void setup() {
  Serial.begin(115200);
  delay(100);

  Wire.begin(D2, D1);  // SDA = GPIO4 (D2), SCL = GPIO5 (D1)

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println("Ecran OLED introuvable");
    while (true) {
      delay(1000);
    }
  }

  showMessage("ESP8266 IIoT", "Demarrage...");
  connectWifi();

  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCallback(onMqttMessage);
  mqttClient.setBufferSize(512);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWifi();
  }

  if (!mqttClient.connected()) {
    const unsigned long now = millis();
    if (now - lastMqttAttempt >= MQTT_RETRY_DELAY_MS) {
      lastMqttAttempt = now;
      connectMqtt();
    }
  } else {
    mqttClient.loop();
  }
}
