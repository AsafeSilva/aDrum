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

	uint8_t edgeMode;

public:
	ButtonEvent(int _pin);
	
	void begin(uint8_t _inputMode = INPUT, uint8_t _edgeMode = FALLING);

	void whenClick(void (*callback)(void));
};