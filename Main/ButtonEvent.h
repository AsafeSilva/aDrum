#pragma once

#include <Arduino.h>

class ButtonEvent{

private:
	int pin;

	uint8_t edgeMode;

public:
	ButtonEvent(int _pin);
	
	void begin(uint8_t _inputMode = INPUT, uint8_t _edgeMode = FALLING);

	void whenClick(void (*callback)(void));
};