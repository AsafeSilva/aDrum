#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#include "Encoder.h"
#include "_config.h"

#include "ArduinoDrum.h"


#define TOTAL_OPTIONS 	3
#define TOTAL_PROPERTYS 6

#define MENU_NAME 		0
#define MENU_PROPERTY 	1
#define MENU_VALUE 		2


class DrumInterface{

private:

	Encoder* encoder;
	LiquidCrystal* display;
	static SoftwareSerial* interface;
	static Pad* pad;

	void loadData();

	char s_padName[16], s_padProperty[10], s_padValue[5];

	static volatile int indexMenu; 
	static volatile int indexPadName, indexPadProperty, indexPadValue;

	static void encoderClick();
	static void encoderRotate(boolean direction, long position);

	void print();

	const char* spaces[11] = {"", " ", "  ", "   ", "    ", "     ", "      ",
							"       ", "        ", "         ", "          "};

	// No máximo 8 caracteres
	const char* propertys[TOTAL_PROPERTYS] = {"Note", "ThreshMn", "ThreshMx",
												"ScanTime", "MaskTime", "Gain"};

	static bool savingData;
	
public:

	DrumInterface();

	void begin();

	void runInterface();

};

extern DrumInterface Interface;