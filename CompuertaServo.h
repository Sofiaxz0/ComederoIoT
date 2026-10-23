#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>

class CompuertaServo {
public:
  CompuertaServo(uint8_t pin, int anguloCerrado, int anguloAbierto, unsigned long tiempoAbiertoMs);

  void begin();
  void abrir();               // ignora la orden si ya está abierta
  void actualizar();          // llamar en cada loop()
  bool estaAbierta() const;
  bool huboCierre();          // true una sola vez cuando se cerró

private:
  void cerrar();

  Servo _servo;
  uint8_t _pin;
  int _anguloCerrado;
  int _anguloAbierto;
  unsigned long _tiempoAbiertoMs;

  bool _abierta;
  bool _cierre;
  unsigned long _tApertura;
};