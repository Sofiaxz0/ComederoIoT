#include "CompuertaServo.h"

CompuertaServo::CompuertaServo(uint8_t pin, int anguloCerrado, int anguloAbierto, unsigned long tiempoAbiertoMs)
  : _pin(pin), _anguloCerrado(anguloCerrado), _anguloAbierto(anguloAbierto),
    _tiempoAbiertoMs(tiempoAbiertoMs), _abierta(false), _cierre(false), _tApertura(0) {}

void CompuertaServo::begin() {
  _servo.setPeriodHertz(50);
  _servo.attach(_pin, 500, 2400);
  _servo.write(_anguloCerrado);
}

void CompuertaServo::abrir() {
  if (_abierta) return;            // mientras está abierta se ignora cualquier orden
  _servo.write(_anguloAbierto);
  _abierta = true;
  _tApertura = millis();
  Serial.println("Compuerta ABIERTA");
}

void CompuertaServo::cerrar() {
  _servo.write(_anguloCerrado);
  _abierta = false;
  _cierre = true;
  Serial.println("Compuerta CERRADA");
}

void CompuertaServo::actualizar() {
  if (_abierta && (millis() - _tApertura) >= _tiempoAbiertoMs) {
    cerrar();
  }
}

bool CompuertaServo::estaAbierta() const {
  return _abierta;
}

bool CompuertaServo::huboCierre() {
  if (_cierre) {
    _cierre = false;
    return true;
  }
  return false;
}