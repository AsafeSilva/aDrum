#include "aDrum.h"


aDrum::aDrum(){
	cachedSize = 0;

	clear();

	adc = new STM32ADC(ADC1);
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

void aDrum::begin(){

	Serial.begin(BAUD_RATE);

	// Source for negative voltage
	pinMode(NEGATIVE_VOLTAGE, PWM);
	pwmWrite(NEGATIVE_VOLTAGE, 32767);

#ifdef USING_MASTER_VOLUME
	// Potenciometer to master volume
	pinMode(MASTER_VOLUME, INPUT_ANALOG);
#endif

#ifdef USING_EEPROM
	// pinMode(BTN_STORE, INPUT_PULLUP);
#endif

	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i] == NULL)
			continue;

		pad[i]->begin();

		adcPins[pad[i]->getID()] = pad[i]->getPin();

		#ifdef USING_EEPROM
		// if(!digitalRead(BTN_STORE)){
		// 	saveData(pad[i]->getID(), NOTE, pad[i]->getNote());
		// 	saveData(pad[i]->getID(), THRESHMIN, pad[i]->getThresholdMin());
		// 	saveData(pad[i]->getID(), SCANTIME, pad[i]->getScanTime());
		// 	saveData(pad[i]->getID(), MASKTIME, pad[i]->getMaskTime());
		// 	saveData(pad[i]->getID(), GAIN, pad[i]->getGain());
		// }
		#endif
	}

#ifdef USING_MASTER_VOLUME
	// Add master volume pin to the array
	adcPins[cachedSize] = MASTER_VOLUME;
#endif

#ifdef USING_EEPROM
	// loadData();
#endif

	// Setup ADC
	adc->calibrate();

	adc->setSampleRate(ADC_SMPR_1_5);
	adc->setScanMode();
#ifdef USING_MASTER_VOLUME	
	adc->setPins(adcPins, cachedSize+1);
#else
	adc->setPins(adcPins, cachedSize);
#endif
	adc->setContinuous();

#ifdef USING_MASTER_VOLUME	
	adc->setDMA(adcData, cachedSize+1, (DMA_MINC_MODE | DMA_CIRC_MODE), NULL);
#else
	adc->setDMA(adcData, cachedSize, (DMA_MINC_MODE | DMA_CIRC_MODE), NULL);
#endif

	adc->startConversion();
}

void aDrum::play(){
	readPads();
}

void aDrum::readPads(){
	for(int i = 0; i < MAX_PADS; i++){
		if(pad[i] == NULL)	continue;

#ifdef USING_MASTER_VOLUME
		pad[i]->play(adcData[pad[i]->getID()], adcData[cachedSize]);
#else
		pad[i]->play(adcData[pad[i]->getID()], ADC_MAX);
#endif		
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
