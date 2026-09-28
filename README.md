# ESP8266 + MQTT + OLED I2C + Node-RED

Prototype OT/IT dans lequel un **ESP8266** se connecte au Wi-Fi, s'abonne à un topic **MQTT** et affiche le message reçu sur un écran **OLED SSD1306** via **I2C**. Un flow **Node-RED** permet de publier et de contrôler les messages.

## Compétences illustrées

- intégration d'un objet connecté avec un broker MQTT ;
- communication Wi-Fi et publication/souscription ;
- interface I2C avec un écran OLED ;
- mise en place d'un flow Node-RED ;
- séparation sécurisée des paramètres et des identifiants.

## Contenu du dépôt

| Fichier | Description |
|---|---|
| `esp8266_mqtt_oled.ino` | Firmware Arduino pour l'ESP8266 |
| `config.example.h` | Modèle de configuration sans identifiants |
| `flows.json` | Flow Node-RED importable |
| `.gitignore` | Protection de la configuration locale |

## Matériel

- ESP8266 AzDelivery, NodeMCU ou carte compatible ;
- écran OLED SSD1306 128×64 ;
- liaison I2C ;
- résistances de tirage 4,7 kΩ si elles ne sont pas intégrées au module.

## Câblage

| OLED | ESP8266 |
|---|---|
| VCC | 3,3 V |
| GND | GND |
| SDA | D2 / GPIO4 |
| SCL | D1 / GPIO5 |

L'adresse I2C utilisée par défaut est `0x3C`.

## Dépendances Arduino

- ESP8266 core for Arduino ;
- `PubSubClient` ;
- `Adafruit GFX Library` ;
- `Adafruit SSD1306`.

## Mise en service

1. Copier `config.example.h` vers `config.h`.
2. Renseigner le Wi-Fi, le broker et le topic dans `config.h`.
3. Ouvrir `esp8266_mqtt_oled.ino` dans Arduino IDE.
4. Sélectionner la carte ESP8266 et installer les bibliothèques.
5. Compiler puis téléverser le firmware.
6. Importer `flows.json` dans Node-RED.
7. Déployer le flow et publier un message sur le topic configuré.

## Sécurité

Le fichier `config.h` est volontairement ignoré par Git. Aucun SSID, mot de passe Wi-Fi ou identifiant MQTT ne doit être publié dans le dépôt.

Le broker public indiqué dans l'exemple est réservé aux essais. Pour un usage industriel, utiliser un broker privé avec authentification, chiffrement TLS et contrôle d'accès.
