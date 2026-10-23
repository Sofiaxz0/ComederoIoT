#include "ConexionMQTT.h"
#include "Config.h"

static const unsigned long INTERVALO_PUNTO = 500;     // ms entre puntos en el monitor
static const unsigned long TIMEOUT_WIFI    = 15000;   // ms antes de reintentar WiFi
static const unsigned long INTERVALO_MQTT  = 5000;    // ms entre intentos MQTT

ConexionMQTT::ConexionMQTT()
  : _mqtt(_wifiClient), _topicSub(nullptr), _tInicioWiFi(0), _tPunto(0), _tIntentoMQTT(0), _wifiOk(false) {}

void ConexionMQTT::begin() {
  _mqtt.setServer(MQTT_SERVER, MQTT_PORT);
  _mqtt.setSocketTimeout(3);   // no esperar más de 3 s al broker

  _mqtt.setCallback([this](char* topic, byte* payload, unsigned int length) {
    if (!_cbMensaje) return;
    String msg;
    for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];
    msg.trim();
    _cbMensaje(msg);
  });

  iniciarWiFi();
}

void ConexionMQTT::iniciarWiFi() {
  Serial.print("Conectando a WiFi: ");
  Serial.println(WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  _tInicioWiFi = millis();
  _tPunto = _tInicioWiFi;
  _wifiOk = false;
}

void ConexionMQTT::conectarMQTT() {
  Serial.print("Conectando a MQTT... ");
  bool ok;
  if (strlen(MQTT_USER) > 0) {
    ok = _mqtt.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS);
  } else {
    ok = _mqtt.connect(MQTT_CLIENT_ID);
  }

    if (ok) {
    Serial.println("conectado");
    if (_topicSub) {
      _mqtt.subscribe(_topicSub, 1);
      Serial.print("Suscrito a: ");
      Serial.println(_topicSub);
    }
  } else {
    Serial.print("fallo, rc=");
    Serial.println(_mqtt.state());
  }
}

void ConexionMQTT::actualizar() {
  unsigned long ahora = millis();

  // ---------- WiFi (sin bloquear) ----------
  if (WiFi.status() != WL_CONNECTED) {
    if (_wifiOk) {                       // estaba conectado y se perdió
      Serial.println("WiFi perdido, reconectando...");
      iniciarWiFi();
      return;
    }

    if (ahora - _tPunto >= INTERVALO_PUNTO) {
      _tPunto = ahora;
      Serial.print(".");
    }

    if (ahora - _tInicioWiFi >= TIMEOUT_WIFI) {
      Serial.println();
      Serial.print("Fallo WiFi, estado = ");
      Serial.println(WiFi.status());
      iniciarWiFi();
    }
    return;                              // sin WiFi no hay MQTT
  }

  if (!_wifiOk) {                        // acaba de conectar
    _wifiOk = true;
    Serial.println();
    Serial.print("WiFi conectado, IP: ");
    Serial.println(WiFi.localIP());
    _tIntentoMQTT = ahora - INTERVALO_MQTT;   // intenta MQTT de inmediato
  }

  // ---------- MQTT (sin bloquear) ----------
  if (!_mqtt.connected()) {
    if (ahora - _tIntentoMQTT >= INTERVALO_MQTT) {
      _tIntentoMQTT = ahora;
      conectarMQTT();
    }
  } else {
    _mqtt.loop();
  }
}

bool ConexionMQTT::conectado() {
  return _mqtt.connected();
}

bool ConexionMQTT::publicar(const char* topic, const char* payload) {
  if (!_mqtt.connected()) return false;
  return _mqtt.publish(topic, payload);
}

void ConexionMQTT::suscribir(const char* topic, CallbackMensaje cb) {
  _topicSub = topic;
  _cbMensaje = cb;
}
