#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <wiring_private.h>

#include "Pad.h"
#include "DrumInterface.h"
#include "_config.h"

#define MAX_PADS 16

#define FAST_ADC true

class ArduinoDrum{

private:
	
	Pad* pad[MAX_PADS];
	int cachedSize;

#ifdef USING_EEPROM
	// Saves the data in the EEPROM
	void saveData(int id, int property, int value);
	
	// Loads EEPROM data
	void loadData();
	
#endif
	

#ifdef USING_INTERFACE
	// SoftwareSerial* interface;

	// Sends data to interface
	// void sendData();

	// Receives interface data
	// void receiveData();
#endif


public:

	// Constructor
	ArduinoDrum();

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
	// if changeSpeedADC is 'true', set ADC prescaler to 8
	void begin(unsigned long baudRate, bool changePrescalerADC = false);

	// Main function
	// Chooses between reading pads with or without interface
	void play();

	// Performs pad reading process
	void readPads();

};

extern ArduinoDrum Drum;