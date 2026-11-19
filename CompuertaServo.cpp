#include "CompuertaServo.h"

CompuertaServo::CompuertaServo(uint8_t pin, int anguloCerrado, int anguloAbierto,
                               uint8_t repeticiones, unsigned long intervaloMs, unsigned long pausaMs)
  : _pin(pin), _anguloCerrado(anguloCerrado), _anguloAbierto(anguloAbierto),
    _repeticiones(repeticiones), _intervaloMs(intervaloMs), _pausaMs(pausaMs),
    _moviendo(false), _esperandoPausa(false), _listo(false),
    _paso(0), _tPaso(0), _tFin(0),
    _cambio(false), _angulo(anguloCerrado) {}

// Todos los movimientos del servo pasan por aquí: así se registra cada ángulo
void CompuertaServo::mover(int grados) {
  _servo.write(grados);
  _angulo = grados;
  _cambio = true;
}

void CompuertaServo::begin() {
  _servo.setPeriodHertz(50);
  _servo.attach(_pin, 500, 2400);
  mover(_anguloCerrado);   // posición inicial; también se publica
}

bool CompuertaServo::iniciar() {
  // Mientras se mueve (o en pausa) se ignora cualquier orden
  if (_moviendo || _esperandoPausa) return false;

  _moviendo = true;
  _paso = 0;
  _tPaso = millis();
  mover(_anguloAbierto);
  Serial.println("Secuencia de compuerta: INICIO");
  return true;
}

void CompuertaServo::actualizar() {
  unsigned long ahora = millis();

  if (_moviendo && (ahora - _tPaso) >= _intervaloMs) {
    _paso++;
    _tPaso = ahora;

    if (_paso >= _repeticiones * 2) {
      // Terminó: el último paso ya dejó el servo cerrado
      _moviendo = false;
      _esperandoPausa = true;
      _tFin = ahora;
      Serial.println("Secuencia de compuerta: FIN");
    } else {
      // Pasos pares abren, impares cierran
      mover((_paso % 2 == 0) ? _anguloAbierto : _anguloCerrado);
    }
  }

  if (_esperandoPausa && (ahora - _tFin) >= _pausaMs) {
    _esperandoPausa = false;
    _listo = true;
  }
}

bool CompuertaServo::estaMoviendo() const {
  return _moviendo;
}

bool CompuertaServo::huboListo() {
  if (_listo) {
    _listo = false;
    return true;
  }
  return false;
}

// Devuelve true una vez por cada movimiento del servo
bool CompuertaServo::huboMovimiento() {
  if (_cambio) {
    _cambio = false;
    return true;
  }
  return false;
}

int CompuertaServo::angulo() const {
  return _angulo;
}