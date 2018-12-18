#include "ButtonEvent.h"

ButtonEvent::ButtonEvent(int _pin){
	pin = _pin;
}

void ButtonEvent::begin(uint8_t _inputMode, uint8_t _edgeMode){
	pinMode(pin, _inputMode);

	edgeMode = _edgeMode;
}

void ButtonEvent::whenClick(void (*callback)(void)){
	attachInterrupt(digitalPinToInterrupt(pin), callback, edgeMode);
}