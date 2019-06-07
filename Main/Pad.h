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
	uint32 padScanTime;
	uint32 padMaskTime;
	int padGain;

	int readSensor;
	int readNumber;
	int readPeak;
	bool readEnable;
	int velocity;
	uint32 maskPreviousTime;
	uint32 scanPreviousTime;
	
public:
	
	// == Constructors == //
	Pad(const char* name, int note, int pin, int type = PIEZO);

	// Initialize pin
	void begin();

	// Read the pins and send the midi note
	void play(uint16_t adcData, uint16_t masterVolume);

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

	void setScanTime(uint32 newScanTime);
	uint32 getScanTime();

	void setMaskTime(uint32 newMaskTime);
	uint32 getMaskTime();

	void setGain(int newGain);
	int getGain();
};