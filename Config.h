#pragma once

// ---------- WiFi (solo 2.4 GHz) ----------
#define WIFI_SSID      "--"
#define WIFI_PASSWORD  "--"

// ---------- Broker EMQX ----------
#define MQTT_SERVER    "--"   // IPv4 de tu PC (ipconfig)
#define MQTT_PORT      1883
#define MQTT_CLIENT_ID "--"
#define MQTT_USER      "--"           // deja "" si EMQX no tiene autenticación
#define MQTT_PASS      "--"
#define MQTT_TOPIC     "--"

// ---------- Sensor IR ----------
#define PIN_SENSOR_IR  18
#define IR_ACTIVO_BAJO true              // true: el módulo da LOW al detectar (FC-51). Cambia a false si sale invertido
#define IR_DEBOUNCE_MS 50

// ---------- Servo SG90 / Compuerta ----------
#define MQTT_TOPIC_SERVO   "--"
#define PIN_SERVO          19       
#define SERVO_ANGULO_CERRADO  0
#define SERVO_ANGULO_ABIERTO  90
#define TIEMPO_ABIERTO_MS  10000UL   // 10 segundos
