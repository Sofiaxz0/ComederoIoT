#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

class ConexionMQTT {
public:
  ConexionMQTT();

  void begin();
  void actualizar();                                   // llamar en cada loop()
  bool conectado();
  bool publicar(const char* topic, const char* payload);

private:
  void iniciarWiFi();
  void conectarMQTT();

  WiFiClient _wifiClient;
  PubSubClient _mqtt;

  unsigned long _tInicioWiFi;   // cuándo empezó el intento de WiFi
  unsigned long _tPunto;        // último punto impreso
  unsigned long _tIntentoMQTT;  // último intento MQTT
  bool _wifiOk;
};
