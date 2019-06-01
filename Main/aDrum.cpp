#include "aDrum.h"


aDrum::aDrum(){
	cachedSize = 0;

	clear();
}


bool aDrum::addPad(Pad* newPad){
	// Check if the Pad already exists on the array
	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i] != NULL && pad[i]->getPin() == newPad->getPin())
			return true;
	}

	// Find an empty space to put the new Pad
	for(int i = 0; i < MAX_PADS; i++){
		if(!pad[i]){
			// Add new Pad
			pad[i] = newPad;
			pad[i]->setID(i);
			cachedSize++;
			return true;
		}
	}

	// Array is full
	return false;
}

void aDrum::remove(int id){
	// Find a Pad with ID, and removes
	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i]->getID() == id){
			pad[i] = NULL;
			cachedSize--;
			return;
		}
	}
}

void aDrum::remove(Pad* pad){
	remove(pad->getID());
}

void aDrum::clear(){
	for(int i = 0; i < MAX_PADS; i++)
		pad[i] = NULL;

	cachedSize = 0;
}

int aDrum::size(){
	return cachedSize;
}

Pad* aDrum::get(int id){

	if(id >= MAX_PADS) return NULL;

	int pos = -1;
	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i] != NULL){
			pos++;

			if(pos == id)
				return pad[i];
		}
	}

	return NULL;
}

void aDrum::begin(unsigned long baudRate, bool changePrescalerADC){/*

#ifdef USING_MUX
	MUX_DDR |= MUX_MASK;
#endif

	Serial.begin(baudRate);

	if(changePrescalerADC){
		// set prescale to 8
		cbi(ADCSRA, ADPS2);
		sbi(ADCSRA, ADPS1);
		sbi(ADCSRA, ADPS0);
		// 8,52us		prescaler 8
		// 113us		prescaler 128
	}

	// Potenciometer to master volume
	pinMode(MASTER_VOLUME, INPUT);

#ifdef USING_EEPROM
	pinMode(BTN_STORE, INPUT_PULLUP);
#endif

	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i] == NULL)
			continue;

		pad[i]->begin();

		#ifdef USING_EEPROM
		if(!digitalRead(BTN_STORE)){
			saveData(pad[i]->getID(), NOTE, pad[i]->getNote());
			saveData(pad[i]->getID(), THRESHMIN, pad[i]->getThresholdMin());
			saveData(pad[i]->getID(), SCANTIME, pad[i]->getScanTime());
			saveData(pad[i]->getID(), MASKTIME, pad[i]->getMaskTime());
			saveData(pad[i]->getID(), GAIN, pad[i]->getGain());
		}
		#endif

	}

#ifdef USING_EEPROM
	loadData();
#endif

#ifdef USING_INTERFACE
	Interface.begin();
#endif

*/}

void aDrum::play(){
	readPads();
}

void aDrum::readPads(){
	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i] == NULL)	continue;
		
		pad[i]->play();
	}
}

#ifdef USING_EEPROM
void aDrum::saveData(int id, int property, int value){
	// EEPROM.put(sizeof(long) * (property + TOTAL_PROPERTYS * id), value);
}

void aDrum::saveAllData(){
	/*for(int i = 0; i < MAX_PADS; i++){
		if(pad[i] == NULL)
			continue;

			saveData(pad[i]->getID(), NOTE, pad[i]->getNote());
			saveData(pad[i]->getID(), THRESHMIN, pad[i]->getThresholdMin());
			saveData(pad[i]->getID(), SCANTIME, pad[i]->getScanTime());
			saveData(pad[i]->getID(), MASKTIME, pad[i]->getMaskTime());
			saveData(pad[i]->getID(), GAIN, pad[i]->getGain());
	}*/
}

void aDrum::loadData(){/*
	int value;

	for (int id = 0; id < MAX_PADS; id++){
		if(pad[id] == NULL)
			continue;

		for (int property = 0; property < TOTAL_PROPERTYS; property++){

			EEPROM.get(sizeof(long) * (property + TOTAL_PROPERTYS * id), value);

			switch (property){
				case NOTE:
					pad[id]->setNote(value);
					break;
				case THRESHMIN:
					pad[id]->setThresholdMin(value);
					break;
				case SCANTIME:
					pad[id]->setScanTime(value);
					break;
				case MASKTIME:
					pad[id]->setMaskTime(value);
					break;
				case GAIN:
					pad[id]->setGain(value);
					break;
			}			
		}
	}

*/}
#endif


// === Preinstantiate Object === //
aDrum DrumKit = aDrum();
