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

void aDrum::begin(unsigned long baudRate, bool changePrescalerADC){

#ifdef USING_MUX
	MUX_DDR |= MUX_MASK;
#endif

#ifdef USING_EEPROM
	pinMode(SAVE_DATA_PIN, INPUT_PULLUP);
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

	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i] == NULL)
			continue;

		pad[i]->begin();

		#ifdef USING_EEPROM
		if(!digitalRead(SAVE_DATA_PIN)){
			saveData(pad[i]->getID(), NOTE, pad[i]->getNote());
			saveData(pad[i]->getID(), THRESHMIN, pad[i]->getThresholdMin());
			saveData(pad[i]->getID(), THRESHMAX, pad[i]->getThresholdMax());
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
	// interface = new SoftwareSerial(RX_PIN, TX_PIN);
	// interface->begin(9600);

	// sendData();
	Interface.begin();
#endif

}

void aDrum::play(){
	readPads();

#ifdef USING_INTERFACE
	// receiveData();
	
	Interface.runInterface();
#endif
}

void aDrum::readPads(){
	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i] == NULL)	continue;
		
		pad[i]->play();
	}
}

#ifdef USING_EEPROM
void aDrum::saveData(int id, int property, int value){
	EEPROM.put(sizeof(long) * (property + TOTAL_PROPERTYS * id), value);
}

void aDrum::saveAllData(){
	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i] == NULL)
			continue;

			saveData(pad[i]->getID(), NOTE, pad[i]->getNote());
			saveData(pad[i]->getID(), THRESHMIN, pad[i]->getThresholdMin());
			saveData(pad[i]->getID(), THRESHMAX, pad[i]->getThresholdMax());
			saveData(pad[i]->getID(), SCANTIME, pad[i]->getScanTime());
			saveData(pad[i]->getID(), MASKTIME, pad[i]->getMaskTime());
			saveData(pad[i]->getID(), GAIN, pad[i]->getGain());
	}
}

void aDrum::loadData(){
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
				case THRESHMAX:
					pad[id]->setThresholdMax(value);
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

}
#endif


#ifdef USING_INTERFACE
// void aDrum::sendData(){
// 	for(int i = 0; i < MAX_PADS; i++){
// 		if(pad[i] == NULL)	continue;

// 		interface->println(pad[i]->getName());
// 		interface->println(pad[i]->getID());
// 		interface->println(pad[i]->getNote());
// 		interface->println(pad[i]->getThresholdMin());
// 		interface->println(pad[i]->getThresholdMax());
// 		interface->println(pad[i]->getScanTime());
// 		interface->println(pad[i]->getMaskTime());
// 		interface->println(pad[i]->getGain());
// 	}
// 	interface->println("#");
// }

// void aDrum::receiveData(){
// 	while(interface->available()){

// 		unsigned long input = interface->readStringUntil('\n').toInt();

// 		if(input == 0xFFFFFFFF){
// 			for(int i = 0; i < MAX_PADS; i++){
// 				if(pad[i] == NULL)
// 					continue;

// 				#ifdef USING_EEPROM
// 				saveData(pad[i]->getID(), NOTE, pad[i]->getNote());
// 				saveData(pad[i]->getID(), THRESHMIN, pad[i]->getThresholdMin());
// 				saveData(pad[i]->getID(), THRESHMAX, pad[i]->getThresholdMax());
// 				saveData(pad[i]->getID(), SCANTIME, pad[i]->getScanTime());
// 				saveData(pad[i]->getID(), MASKTIME, pad[i]->getMaskTime());
// 				saveData(pad[i]->getID(), GAIN, pad[i]->getGain());
// 				#endif
// 			}

// 			continue;
// 		}

// 		int id = input & 0xF;
// 		int property = (input >> 4) & 0xF;
// 		int value = (input >> 8) & 0xFFF;

// 		switch (property){
// 			case NOTE:
// 				pad[id]->setNote(value);
// 				break;
// 			case THRESHMIN:
// 				pad[id]->setThresholdMin(value);
// 				break;
// 			case THRESHMAX:
// 				pad[id]->setThresholdMax(value);
// 				break;
// 			case SCANTIME:
// 				pad[id]->setScanTime(value);
// 				break;
// 			case MASKTIME:
// 				pad[id]->setMaskTime(value);
// 				break;
// 			case GAIN:
// 				pad[id]->setGain(value);
// 				break;
// 		}
// 	}
// }
#endif

// === Preinstantiate Object === //
aDrum DrumKit = aDrum();
