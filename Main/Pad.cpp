#include "Pad.h"


Pad::Pad(const char* name, int note, int pin, int type){
	setName(name);
	setNote(note);
	setPin(pin);
	setType(type);
	setThresholdMin(40);
	setThresholdMax(800);
	setScanTime(30);
	setMaskTime(55);
	setGain(0);

	readSensor = 0;
	readNumber = 0;
	readPeak = 0;
	readEnable = true;
	velocity = 0;
	currentTime = 0;
	previousTime = 0;
}

void Pad::begin(){
#ifdef USING_MUX
	if(padPin >= MUX0)
		pinMode(MUX_PIN, INPUT);
	else
		pinMode(padPin, INPUT);
#else
	pinMode(padPin, INPUT);
#endif
}

void Pad::play(){

#ifdef USING_MUX
	if(padPin >= MUX0){
		MUX_PORT = (MUX_PORT & ~(MUX_MASK)) | ((padPin-MUX0) << MUX_BIT);
		delayMicroseconds(5);
		readSensor = analogRead(MUX_PIN);
	}else{
		readSensor = analogRead(padPin);
	}
#else
	readSensor = analogRead(padPin);
#endif

	if((padType == OFF) || (readSensor < padThresholdMin))
		return;

	if(padType == HH_C){
		velocity = map(readSensor, padThresholdMin, padThresholdMax, 1, NOTE_MAX);

		// Send Midi Note
		Serial.write(padType | MIDI_CHANNEL);
		Serial.write(padNote);
		Serial.write(velocity);

		return;
	}

	if(currentTime - previousTime <= padMaskTime){

		currentTime = millis();

		if(readNumber < padScanTime){

			if(readSensor > readPeak)
				readPeak = readSensor;

			readNumber++;

		}else if(readEnable){

			TurnOn(LED_SENDING_DATA);

			readEnable = false;

			// calculate value between 0 and 1
			float masterVolume = analogRead(MASTER_VOLUME);
			masterVolume /= 1023.0;

			readPeak = constrain(readPeak + padGain, padThresholdMin, padThresholdMax);
			velocity = map(readPeak, padThresholdMin, padThresholdMax, 1, NOTE_MAX);
			velocity = (int)(velocity * masterVolume);


			// Send Midi Note
			Serial.write(padType | MIDI_CHANNEL);
			Serial.write(padNote);
			Serial.write(velocity);

			TurnOff(LED_SENDING_DATA);
		}
	} else {
    	readEnable = true;
    	readNumber = 0;
    	readPeak = 0;
    	previousTime = currentTime;
	}
}

// === Getters and Setters === //

void Pad::setName(const char* newName){	strcpy(padName, newName);	}
char* Pad::getName(){	return padName;	}

void Pad::setID(int newID){	padID = newID;	}
int Pad::getID(){	return padID;	}

void Pad::setNote(int newNote){	padNote = newNote;	}
int Pad::getNote(){	return padNote;	}

void Pad::setType(int newType){	padType = newType;	}
int Pad::getType(){	return padType;	}

void Pad::setPin(int newPin){	padPin = newPin;	}
int Pad::getPin(){	return padPin;	}

void Pad::setThresholdMin(int newThresholdMin){	padThresholdMin = constrain(newThresholdMin, 0, ADC_MAX);	}
int Pad::getThresholdMin(){	return padThresholdMin;	}

void Pad::setThresholdMax(int newThresholdMax){	padThresholdMax = constrain(newThresholdMax, 0, ADC_MAX);	}
int Pad::getThresholdMax(){	return padThresholdMax;	}

void Pad::setScanTime(int newScanTime){	padScanTime = constrain(newScanTime, 0, SCANTIME_MAX);	}
int Pad::getScanTime(){	return padScanTime;	}

void Pad::setMaskTime(int newMaskTime){	padMaskTime = constrain(newMaskTime, 0, MASKTIME_MAX);	}
int Pad::getMaskTime(){	return padMaskTime;	}

void Pad::setGain(int newGain){	padGain = constrain(newGain, 0, GAIN_MAX);	}
int Pad::getGain(){	return padGain;	}
