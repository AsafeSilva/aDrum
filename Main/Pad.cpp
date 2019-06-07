#include "Pad.h"


Pad::Pad(const char* name, int note, int pin, int type){
	setName(name);
	setNote(note);
	setPin(pin);
	setType(type);
	setThresholdMin(18);
	setScanTime(30);
	setMaskTime(60);
	setGain(0);

	readSensor = 0;
	readNumber = 0;
	readPeak = 0;
	readEnable = true;
	velocity = 0;
	maskPreviousTime = millis();
	scanPreviousTime = millis();
}

void Pad::begin(){
	pinMode(padPin, INPUT_ANALOG);
}

void Pad::play(uint16_t adcData, uint16_t masterVolume){

	// Maps values ​​for the range 0 to 127
	readSensor = (int) (adcData * float(VELOCITY_MAX) / float(ADC_MAX));


	if((padType == OFF) || (readSensor < padThresholdMin))
		return;

	if(padType == HH_C){
		velocity = constrain(readSensor, 0, VELOCITY_MAX);

		// Send Midi Note
		Serial.write(padType | MIDI_CHANNEL);
		Serial.write(padNote);
		Serial.write(velocity);

		return;
	}

	if(padType != PIEZO)
		return;


	if(millis() - maskPreviousTime <= padMaskTime){

		if(millis() - scanPreviousTime <= padScanTime){

			if(readSensor > readPeak)
				readPeak = readSensor;

		}else if(readEnable){

			// TurnOn(LED_SENDING_DATA);

			readEnable = false;

			// calculate value between 0 and 1
			float master = masterVolume / float(ADC_MAX);

			velocity = constrain(readPeak + padGain, 0, VELOCITY_MAX);
			velocity = (int)(velocity * master);

			// Send Midi Note
			Serial.write(padType | MIDI_CHANNEL);
			Serial.write(padNote);
			Serial.write(velocity);

			// TurnOff(LED_SENDING_DATA);
		}
	} else {
    	readEnable = true;
    	readPeak = 0;
    	maskPreviousTime = scanPreviousTime = millis();
	}
}

// === Getters and Setters === //

void Pad::setName(const char* newName){	strcpy(padName, newName);	}
char* Pad::getName(){	return padName;	}

void Pad::setID(int newID){	padID = newID;	}
int Pad::getID(){	return padID;	}

void Pad::setNote(int newNote){	padNote = constrain(newNote, 0, NOTE_MAX);	}
int Pad::getNote(){	return padNote;	}

void Pad::setType(int newType){	padType = newType;	}
int Pad::getType(){	return padType;	}

void Pad::setPin(int newPin){	padPin = newPin;	}
int Pad::getPin(){	return padPin;	}

void Pad::setThresholdMin(int newThresholdMin){	padThresholdMin = constrain(newThresholdMin, 0, VELOCITY_MAX);	}
int Pad::getThresholdMin(){	return padThresholdMin;	}

void Pad::setThresholdMax(int newThresholdMax){	padThresholdMax = constrain(newThresholdMax, 0, VELOCITY_MAX);	}
int Pad::getThresholdMax(){	return padThresholdMax;	}

void Pad::setScanTime(uint32 newScanTime){	padScanTime = constrain(newScanTime, 0, SCANTIME_MAX);	}
uint32 Pad::getScanTime(){	return padScanTime;	}

void Pad::setMaskTime(uint32 newMaskTime){	padMaskTime = constrain(newMaskTime, 0, MASKTIME_MAX);	}
uint32 Pad::getMaskTime(){	return padMaskTime;	}

void Pad::setGain(int newGain){	padGain = constrain(newGain, 0, GAIN_MAX);	}
int Pad::getGain(){	return padGain;	}
