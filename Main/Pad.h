#pragma once

#include <Arduino.h>
#include "_config.h"

class Pad{

private:

	char padName[16];
	int padID;
	int padNote;
	int padType;
	int padPin;
	int padThresholdMin;
	int padThresholdMax;
	int padScanTime;
	int padMaskTime;
	int padGain;

	int readSensor;
	int readNumber;
	int readPeak;
	bool readEnable;
	int velocity;
	unsigned long currentTime;
	unsigned long previousTime;
	
public:
	
	// == Constructors == //
	Pad(const char* name, int note, int pin, int type = PIEZO);

	// Initialize pin
	void begin();

	// Read the pins and send the midi note
	void play(uint16_t adcData);

	// === Getters and Setters === //
	void setName(const char* newName);
	char* getName();

	void setID(int newID);	// Do not use this method without knowing what you are doing
	int getID();

	void setNote(int newNote);
	int getNote();

	void setType(int newType);
	int getType();

	void setPin(int newPin);
	int getPin();

	void setThresholdMin(int newThresholdMin);
	int getThresholdMin();

	void setThresholdMax(int newThresholdMax);
	int getThresholdMax();

	void setScanTime(int newScanTime);
	int getScanTime();

	void setMaskTime(int newMaskTime);
	int getMaskTime();

	void setGain(int newGain);
	int getGain();
};