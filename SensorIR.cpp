#include "SensorIR.h"

SensorIR::SensorIR(uint8_t pin, bool activoBajo, unsigned long debounceMs)
  : _pin(pin), _activoBajo(activoBajo), _debounceMs(debounceMs),
    _estadoEstable(false), _ultimaLectura(false), _cambio(false), _tUltimoCambio(0) {}

void SensorIR::begin() {
  pinMode(_pin, INPUT);
  _ultimaLectura = _estadoEstable = (digitalRead(_pin) == (_activoBajo ? LOW : HIGH));
  _cambio = true;  // fuerza a publicar el estado inicial
}

void SensorIR::actualizar() {
  bool lectura = (digitalRead(_pin) == (_activoBajo ? LOW : HIGH));

  if (lectura != _ultimaLectura) {
    _tUltimoCambio = millis();
    _ultimaLectura = lectura;
  }

  if ((millis() - _tUltimoCambio) >= _debounceMs && lectura != _estadoEstable) {
    _estadoEstable = lectura;
    _cambio = true;
  }
}

bool SensorIR::hayObjeto() const {
  return _estadoEstable;
}

bool SensorIR::huboCambio() {
  if (_cambio) {
    _cambio = false;
    return true;
  }
  return false;
}

void SensorIR::forzarPublicacion() {
  _cambio = true;
}
