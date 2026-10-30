#include "Config.h"
#include "SensorIR.h"
#include "ConexionMQTT.h"
#include "CompuertaServo.h"

SensorIR sensor(PIN_SENSOR_IR, IR_ACTIVO_BAJO, IR_DEBOUNCE_MS);
ConexionMQTT mqtt;
CompuertaServo compuerta(PIN_SERVO, SERVO_ANGULO_CERRADO, SERVO_ANGULO_ABIERTO, SERVO_REPETICIONES, SERVO_INTERVALO_MS, SERVO_PAUSA_ENTRE_MS);

void setup() {
  Serial.begin(115200);
  sensor.begin();
  compuerta.begin();

  mqtt.suscribir(MQTT_TOPIC_SERVO, [](const String& msg) {
    Serial.print("Comando recibido: ");
    Serial.println(msg);
    if (msg == "0") {
      if (!compuerta.iniciar()) {
        Serial.println("Ignorado: compuerta ocupada");
      }
    Serial.println("________________________________________________________________________");
    }
  });
  mqtt.begin();
}

void loop() {
  mqtt.actualizar();
  sensor.actualizar();
  compuerta.actualizar();

  // Al terminar la secuencia y la pausa, vuelve a publicar el estado del sensor
  // para que Node-RED decida de nuevo si repite o no.
  if (compuerta.huboListo()) {
    sensor.forzarPublicacion();
  }

  // Publica solo cuando el estado cambia y hay conexión con el broker.
  if (mqtt.conectado() && sensor.huboCambio()) {
    bool hay = sensor.hayObjeto();
    if (mqtt.publicar(MQTT_TOPIC, hay ? "true" : "false")) {
      Serial.println(hay ? "Objeto detectado -> true" : "Sin objeto -> false");
      Serial.println("________________________________________________________________________");
    }
  }
}