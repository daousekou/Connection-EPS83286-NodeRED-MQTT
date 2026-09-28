# ESP8266 + MQTT + OLED (I2C) + Node-RED

Petit projet OT/IT : un ESP8266 (AzDelivery) se connecte au Wi-Fi, s’abonne à un topic MQTT, puis affiche le message reçu sur un écran OLED (SSD1306) via I2C.  
Node-RED peut publier les messages MQTT (ou n’importe quel client MQTT).

## Objectifs
- Connexion Wi-Fi sur ESP8266
- Abonnement MQTT (broker public ou local)
- Affichage d’un message reçu sur un OLED SSD1306 en I2C
- Intégration simple avec Node-RED (publish sur un topic)

## Matériel
- ESP8266 AzDelivery (type NodeMCU / compatible ESP8266)
- Écran OLED I2C (SSD1306 128x64) — adresse fréquente : `0x3C`
- (Optionnel) résistances pull-up 4.7kΩ sur SDA/SCL si ton module n’en a pas

## Câblage (I2C)
> Sur ESP8266 : SDA = GPIO4 (D2) ; SCL = GPIO5 (D1)

| OLED | ESP8266 AzDelivery |
|------|---------------------|
| VCC  | 3.3V                |
| GND  | GND                 |
| SDA  | D2 (GPIO4)          |
| SCL  | D1 (GPIO5)          |

Pull-ups (si nécessaire) :
- 4.7kΩ entre SDA et 3.3V
- 4.7kΩ entre SCL et 3.3V

## Logiciel / dépendances# ESP8266 + MQTT + OLED I2C + Node-RED

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
### Arduino IDE
- Ajouter la carte ESP8266 via Boards Manager (ESP8266 by ESP8266 Community)
- Sélectionner la carte (ex : NodeMCU 1.0 / Wemos D1 mini selon ton modèle)
- Installer les bibliothèques :
  - `PubSubClient` (MQTT)
  - `Adafruit SSD1306`
  - `Adafruit GFX`

## Configuration (IMPORTANT : ne pas commiter tes identifiants)
Crée un fichier `config.h` (non versionné) basé sur `config.example.h` :
- SSID / mot de passe Wi-Fi
- Broker MQTT (ex : test.mosquitto.org)
- Topic MQTT

## Exécution
1) Brancher l’ESP8266 en USB
2) Ouvrir `src/esp8266_mqtt_oled.ino` dans Arduino IDE
3) Vérifier l’adresse I2C de l’écran OLED (`0x3C` souvent, sinon `0x3D`)
4) Compiler / Téléverser
5) Publier un message MQTT sur le topic (ex : `binome4`)
6) Le message s’affiche sur l’OLED

## Tester avec Node-RED
- Ajouter un node **mqtt out**
- Configurer le broker : `test.mosquitto.org:1883`
- Topic : `binome4`
- Injecter un texte (string) → le message apparaît sur l’écran

## Tester avec la ligne de commande (optionnel)
Si tu as Mosquitto installé :
```bash
mosquitto_pub -h test.mosquitto.org -t binome4 -m "Hello OLED"
