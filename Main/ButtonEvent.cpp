#include "ButtonEvent.h"

ButtonEvent::ButtonEvent(int _pin){
	pin = _pin;
}

void ButtonEvent::begin(WiringPinMode _inputMode, ExtIntTriggerMode _edgeMode){
	pinMode(pin, _inputMode);

	edgeMode = _edgeMode;
}

void ButtonEvent::whenClick(voidFuncPtr callback){
	attachInterrupt(digitalPinToInterrupt(pin), callback, edgeMode);
}