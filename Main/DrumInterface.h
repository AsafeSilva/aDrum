#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>

// #include "Encoder.h"
#include "ButtonEvent.h"
#include "_config.h"

#include "aDrum.h"


#define TOTAL_OPTIONS 	3

#define MENU_NAME 		0
#define MENU_PROPERTY 	1
#define MENU_VALUE 		2


class DrumInterface{

private:

	// Encoder* encoder;
	ButtonEvent* btnEnter;
	ButtonEvent* btnBack;
	ButtonEvent* btnStore;
	ButtonEvent* btnStandby;

	LiquidCrystal* display;

	static Pad* pad;

	char s_padName[16], s_padProperty[10], s_padValue[5];

	static volatile int indexMenu; 
	static volatile int indexPadName, indexPadProperty, indexPadValue;

	static void buttonEnterEvent();
	static void buttonBackEvent();
	static void buttonStoreEvent();
	static void buttonStandbyEvent();
	static volatile unsigned long debounceEnterButton;
	static volatile unsigned long debounceBackButton;
	static volatile unsigned long debounceStoreButton;
	static volatile unsigned long debounceStandbyButton;

	static void encoderRotateEvent(boolean direction, long position);

	void print();

	void splashScreen();

	const char* spaces[11] = {"", " ", "  ", "   ", "    ", "     ", "      ",
							"       ", "        ", "         ", "          "};

	// No máximo 8 caracteres
	const char* propertys[TOTAL_PROPERTYS] = {"Note", "Threshold", "ScanTime", "MaskTime", "Gain"};

	static volatile bool storingData;
	static volatile bool storeMenu;

	static volatile bool standby;

	static volatile unsigned long timeWithoutChanges;
	
public:

	DrumInterface();

	void begin();

	void runInterface();

};

extern DrumInterface Interface;