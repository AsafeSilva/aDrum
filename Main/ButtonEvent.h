#pragma once

#include <Arduino.h>

#define DEBOUNCE_50	50
#define DEBOUNCE_100	100
#define DEBOUNCE_200	200
#define DEBOUNCE_300	300
#define DEBOUNCE_400	400

class ButtonEvent{

private:
	int pin;

	ExtIntTriggerMode edgeMode;

public:
	ButtonEvent(int _pin);
	
	void begin(WiringPinMode _inputMode = INPUT, ExtIntTriggerMode _edgeMode = FALLING);

	void whenClick(voidFuncPtr callback);
};