#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>

class CompuertaServo {
public:
  CompuertaServo(uint8_t pin, int anguloCerrado, int anguloAbierto,
                 uint8_t repeticiones, unsigned long intervaloMs, unsigned long pausaMs);

  void begin();
  bool iniciar();            // arranca la secuencia; false si está ocupada o en pausa
  void actualizar();         // llamar en cada loop()
  bool estaMoviendo() const;
  bool huboListo();          // true una sola vez cuando terminó y pasó la pausa

private:
  Servo _servo;
  uint8_t _pin;
  int _anguloCerrado;
  int _anguloAbierto;
  uint8_t _repeticiones;
  unsigned long _intervaloMs;
  unsigned long _pausaMs;

  bool _moviendo;
  bool _esperandoPausa;
  bool _listo;
  uint8_t _paso;             // 0 = abrir, 1 = cerrar, 2 = abrir, ...
  unsigned long _tPaso;
  unsigned long _tFin;
};