#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <functional>

typedef std::function<void(const String&)> CallbackMensaje;

class ConexionMQTT {
public:
  ConexionMQTT();

  void begin();
  void actualizar();                                   // llamar en cada loop()
  bool conectado();
  bool publicar(const char* topic, const char* payload);
  void suscribir(const char* topic, CallbackMensaje cb);   // llamar antes de begin()

private:
  void iniciarWiFi();
  void conectarMQTT();

  WiFiClient _wifiClient;
  PubSubClient _mqtt;

  const char* _topicSub;
  CallbackMensaje _cbMensaje;

  unsigned long _tInicioWiFi;   // cuándo empezó el intento de WiFi
  unsigned long _tPunto;        // último punto impreso
  unsigned long _tIntentoMQTT;  // último intento MQTT
  bool _wifiOk;
};
