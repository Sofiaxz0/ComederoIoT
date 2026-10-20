#pragma once
#include <Arduino.h>

class SensorIR {
public:
  SensorIR(uint8_t pin, bool activoBajo = true, unsigned long debounceMs = 50);

  void begin();
  void actualizar();          // llamar en cada loop()
  bool hayObjeto() const;     // estado estable actual
  bool huboCambio();          // true una sola vez cuando el estado cambió

private:
  uint8_t _pin;
  bool _activoBajo;
  unsigned long _debounceMs;

  bool _estadoEstable;
  bool _ultimaLectura;
  bool _cambio;
  unsigned long _tUltimoCambio;
};
