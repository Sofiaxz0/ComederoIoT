#include "Config.h"
#include "SensorIR.h"
#include "ConexionMQTT.h"

SensorIR sensor(PIN_SENSOR_IR, IR_ACTIVO_BAJO, IR_DEBOUNCE_MS);
ConexionMQTT mqtt;

void setup() {
  Serial.begin(115200);
  sensor.begin();
  mqtt.begin();
}

void loop() {
  mqtt.actualizar();
  sensor.actualizar();

  // Publica solo cuando el estado cambia y hay conexión con el broker.
  // Si no hay conexión, el cambio queda pendiente y se envía al reconectar.
  if (mqtt.conectado() && sensor.huboCambio()) {
    bool hay = sensor.hayObjeto();
    if (mqtt.publicar(MQTT_TOPIC, hay ? "true" : "false")) {
      Serial.println(hay ? "Objeto detectado -> true" : "Sin objeto -> false");
    }
  }
}
