#pragma once

// ---------- WiFi (solo 2.4 GHz) ----------
#define WIFI_SSID      "Redmi 13C"
#define WIFI_PASSWORD  "Redmi.com01"

// ---------- Broker EMQX ----------
#define MQTT_SERVER    "10.221.169.71"   // IPv4 de tu PC (ipconfig)
#define MQTT_PORT      1883
#define MQTT_CLIENT_ID "ComederoIoT"
#define MQTT_USER      "Admin"           // deja "" si EMQX no tiene autenticación
#define MQTT_PASS      "emqx.com01"
#define MQTT_TOPIC     "comedero/sensor_ir"

// ---------- Sensor IR ----------
#define PIN_SENSOR_IR  18
#define IR_ACTIVO_BAJO true              // true: el módulo da LOW al detectar (FC-51). Cambia a false si sale invertido
#define IR_DEBOUNCE_MS 50
