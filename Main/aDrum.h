#pragma once

#include <Arduino.h>
#include <STM32ADC.h>
// #include <EEPROM.h>
// #include <wiring_private.h>

#include "Pad.h"
#include "DrumInterface.h"
#include "_config.h"

#define MAX_PADS 9

class aDrum{

private:
	
	Pad* pad[MAX_PADS];
	int cachedSize;

#ifdef USING_EEPROM
	// Saves the data in the EEPROM
	void saveData(int id, int property, int value);
	
	// Loads EEPROM data
	void loadData();
	
#endif

	// Performs pad reading process
	void readPads();

	STM32ADC* adc;

#ifdef USING_MASTER_VOLUME
	uint16_t adcData[MAX_PADS+1];
	uint8_t adcPins[MAX_PADS+1];
#else
	uint16_t adcData[MAX_PADS];
	uint8_t adcPins[MAX_PADS];
#endif

public:

	// Constructor
	aDrum();

	// Adds a Pad in the first available slot
	// Returns if a Pad could be added or not, though reading is optional
	bool addPad(Pad* newPad);

	// Remove the Pad (given the ID or Pad*)
	void remove(int id);
	void remove(Pad* pad);

	// Remove all Pads
	void clear();

	// Return the quantity of Pads
	int size();

	// Return the Pad with ID = id
	// Return NULL if none found
	Pad* get(int id);

	// Initializes Serial Communication
	void begin();

	// Main function
	// Call this function to read the pads
	void play();

#ifdef USING_EEPROM
	// Saves all data in the EEPROM
	void saveAllData();
#endif


};

extern aDrum DrumKit;