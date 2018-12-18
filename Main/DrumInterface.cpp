#include "DrumInterface.h"

volatile int DrumInterface::indexMenu; 
volatile int DrumInterface::indexPadName;
volatile int DrumInterface::indexPadProperty;
volatile int DrumInterface::indexPadValue;

volatile bool DrumInterface::savingData;
volatile unsigned long DrumInterface::timeWithoutChanges;

volatile unsigned long DrumInterface::lastTimeDebounceEnter;
volatile unsigned long DrumInterface::lastTimeDebounceBack;

Pad* DrumInterface::pad;
// SoftwareSerial* DrumInterface::interface;

DrumInterface::DrumInterface(){}

void DrumInterface::begin(){

	encoder = new Encoder(ENC_A, ENC_B);
	btnEnter = new ButtonEvent(BTN_ENTER);
	btnBack = new ButtonEvent(BTN_BACK);
	display = new LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
	// interface = new SoftwareSerial(RX_PIN, TX_PIN);

	// Initialize the Encoder
	encoder->begin(INPUT, RISING);
	encoder->whenRotate(this->encoderRotate);

	// Initialize buttons
	btnEnter->begin(INPUT_PULLUP, FALLING);
	btnEnter->whenClick(this->buttonEnter);
	btnBack->begin(INPUT_PULLUP, FALLING);
	btnBack->whenClick(this->buttonBack);

	// Initialize serial communication
	// interface->begin(9600);
	// loadData();

	// Initialize the LCD
	display->begin(16, 2);
	display->clear();

	strcpy(s_padName, "");
	strcpy(s_padProperty, "");
	strcpy(s_padValue, "");

	indexMenu = 0;
	indexPadName = 0;
	indexPadProperty = 0;
	indexPadValue = 0;

	savingData = false;
}

void DrumInterface::runInterface(){

	if(indexMenu == MENU_NAME){

		if(indexPadName == -1){

			strcpy(s_padName, "SAVE DATA");
			strcpy(s_padProperty, "");
			strcpy(s_padValue, "");

		    if(savingData){
		    	display->setCursor(1, 0);
				display->print("SAVING...     ");

		    	// interface->println((unsigned long)0xFFFFFFFF);

			#ifdef USING_EEPROM
				Drum.saveAllData();
			#endif

		    	indexPadName = 0;
		    	savingData = false;
		    	timeWithoutChanges = millis();
		    }

		}else{
		    pad = Drum.get(indexPadName);

		    indexPadProperty = NOTE;

		    strcpy(s_padName, pad->getName());
			strcpy(s_padProperty, propertys[indexPadProperty]);
			sprintf(s_padValue, "%d", pad->getNote());
		}

	} else if(indexMenu == MENU_PROPERTY){

	    strcpy(s_padProperty, propertys[indexPadProperty]);

	    if(indexPadProperty == NOTE){
	    	sprintf(s_padValue, "%d", pad->getNote());
	    	indexPadValue = pad->getNote();
	    }else if(indexPadProperty == THRESHMIN){
	    	sprintf(s_padValue, "%d", pad->getThresholdMin());
	    	indexPadValue = pad->getThresholdMin();
	    }else if(indexPadProperty == THRESHMAX){
	    	sprintf(s_padValue, "%d", pad->getThresholdMax());
	    	indexPadValue = pad->getThresholdMax();
	    }else if(indexPadProperty == SCANTIME){
	    	sprintf(s_padValue, "%d", pad->getScanTime());
	    	indexPadValue = pad->getScanTime();
	    }else if(indexPadProperty == MASKTIME){
	    	sprintf(s_padValue, "%d", pad->getMaskTime());
	    	indexPadValue = pad->getMaskTime();
	    }else if(indexPadProperty == GAIN){
	    	sprintf(s_padValue, "%d", pad->getGain());
	    	indexPadValue = pad->getGain();
	    }
	    
	} else if(indexMenu == MENU_VALUE){

		sprintf(s_padValue, "%d", indexPadValue);

	    if(indexPadProperty == NOTE)			pad->setNote(indexPadValue);
	    else if(indexPadProperty == THRESHMIN)	pad->setThresholdMin(indexPadValue);
	    else if(indexPadProperty == THRESHMAX)	pad->setThresholdMax(indexPadValue);
	    else if(indexPadProperty == SCANTIME)	pad->setScanTime(indexPadValue);
	    else if(indexPadProperty == MASKTIME)	pad->setMaskTime(indexPadValue);
	    else if(indexPadProperty == GAIN)		pad->setGain(indexPadValue);

	}

	if(millis() - timeWithoutChanges < 500)
		print();

}

void DrumInterface::buttonEnter(){
	timeWithoutChanges = millis();

	if(millis() - lastTimeDebounceEnter >= 200){

		if(savingData)
			return;

		if(indexPadName == -1){
			savingData = true;
			return;
		}

		indexMenu++;
		if (indexMenu >= TOTAL_OPTIONS)	indexMenu = 0;


		lastTimeDebounceEnter = millis();
	}
}

void DrumInterface::buttonBack(){
	if(savingData)
		return;

	if(indexPadName == -1)
		return;

	timeWithoutChanges = millis();


	if(millis() - lastTimeDebounceBack >= 200){

		indexMenu--;
		if (indexMenu < 0)	indexMenu = TOTAL_OPTIONS;
		

		lastTimeDebounceBack = millis();
	}

}

void DrumInterface::encoderRotate(boolean direction, long position){

	if(savingData)
		return;

	timeWithoutChanges = millis();

	switch (indexMenu) {
	    case MENU_NAME:

			indexPadName = direction ? indexPadName+1 : indexPadName-1;
			if(indexPadName >= Drum.size()) indexPadName = -1;
			else if(indexPadName < -1)	indexPadName = Drum.size()-1;

			break;
	    case MENU_PROPERTY:
	    
			indexPadProperty = direction ? indexPadProperty+1 : indexPadProperty-1;
			if(indexPadProperty >= TOTAL_PROPERTYS) indexPadProperty = 0;
			else if(indexPadProperty < 0)	indexPadProperty = TOTAL_PROPERTYS-1;    	

			break;
	    case MENU_VALUE:

			indexPadValue = direction ? indexPadValue+1 : indexPadValue-1;

			// unsigned long send;

			if(indexPadProperty == NOTE){

				if(indexPadValue > NOTE_MAX) indexPadValue = 0;
				else if(indexPadValue < 0)	indexPadValue = NOTE_MAX;

				// send = ((unsigned long)pad->getID()) | ((unsigned long)NOTE << 4) | ((unsigned long)indexPadValue << 8);

		    }else if(indexPadProperty == THRESHMIN){

		    	if(indexPadValue > ADC_MAX) indexPadValue = 0;
				else if(indexPadValue < 0)	indexPadValue = ADC_MAX;

				// send = ((unsigned long)pad->getID()) | ((unsigned long)THRESHMIN << 4) | ((unsigned long)indexPadValue << 8);
		    
		    }else if(indexPadProperty == THRESHMAX){

		    	if(indexPadValue > ADC_MAX) indexPadValue = 0;
				else if(indexPadValue < 0)	indexPadValue = ADC_MAX;

				// send = ((unsigned long)pad->getID()) | ((unsigned long)THRESHMAX << 4) | ((unsigned long)indexPadValue << 8);
		    
		    }else if(indexPadProperty == SCANTIME){

		    	if(indexPadValue > SCANTIME_MAX) indexPadValue = 0;
				else if(indexPadValue < 0)	indexPadValue = SCANTIME_MAX;

				// send = ((unsigned long)pad->getID()) | ((unsigned long)SCANTIME << 4) | ((unsigned long)indexPadValue << 8);
		    
		    }else if(indexPadProperty == MASKTIME){

		    	if(indexPadValue > MASKTIME_MAX) indexPadValue = 0;
				else if(indexPadValue < 0)	indexPadValue = MASKTIME_MAX; 

				// send = ((unsigned long)pad->getID()) | ((unsigned long)MASKTIME << 4) | ((unsigned long)indexPadValue << 8);
			
			}else if(indexPadProperty == GAIN){

		    	if(indexPadValue > GAIN_MAX) indexPadValue = 0;
				else if(indexPadValue < 0)	indexPadValue = GAIN_MAX;

				// send = ((unsigned long)pad->getID()) | ((unsigned long)GAIN << 4) | ((unsigned long)indexPadValue << 8);
			
			}

			// interface->println(send);

			break;	      
	    default:;
	      // do something
	}
}

void DrumInterface::print(){

	strcat(s_padName, spaces[14 - strlen(s_padName)]);
	strcat(s_padProperty, spaces[8 - strlen(s_padProperty)]);
	strcat(s_padValue, spaces[4 - strlen(s_padValue)]);

	display->setCursor(1, 0);
	display->print(s_padName);
	display->setCursor(1, 1);
	display->print(s_padProperty);
	display->setCursor(11, 1);
	display->print(s_padValue);
	
	switch (indexMenu) {
	    case MENU_NAME:
	    	display->setCursor(0, 0);display->print("<");
	    	display->setCursor(15, 0);display->print(">");
	    	display->setCursor(0, 1);display->print(" ");
	    	display->setCursor(10, 1);display->print(" ");	    	
	    	display->setCursor(15, 1);display->print(" ");	    	
	      break;
	    case MENU_PROPERTY:
	    	display->setCursor(0, 0);display->print(" ");
	    	display->setCursor(15, 0);display->print(" ");
	    	display->setCursor(0, 1);display->print("<");
	    	display->setCursor(10, 1);display->print(" ");	    	
	    	display->setCursor(15, 1);display->print(">");	
	      break;
	    case MENU_VALUE:
	    	display->setCursor(0, 0);display->print(" ");
	    	display->setCursor(15, 0);display->print(" ");
	    	display->setCursor(0, 1);display->print(" ");
	    	display->setCursor(10, 1);display->print("<");	    	
	    	display->setCursor(15, 1);display->print(">");
	      break;
	}
}

/*void DrumInterface::loadData(){

	String name;

	while(true){
		while(interface->available() == 0);

		name = interface->readStringUntil('\n');
		name.trim();

		if(name.startsWith("#"))
			break;

		int id = interface->readStringUntil('\n').toInt();
		int note = interface->readStringUntil('\n').toInt();
		int threshMin = interface->readStringUntil('\n').toInt();
		int threshMax = interface->readStringUntil('\n').toInt();
		int scanTime = interface->readStringUntil('\n').toInt();
		int maskTime = interface->readStringUntil('\n').toInt();
		int gain = interface->readStringUntil('\n').toInt();

		Pad* pad = new Pad(name.c_str(), note, id);
		pad->setID(id);
		pad->setThresholdMin(threshMin);
		pad->setThresholdMax(threshMax);
		pad->setScanTime(scanTime);
		pad->setMaskTime(maskTime);
		pad->setGain(gain);

		Drum.addPad(pad);
	}
}*/

// === Preinstantiate Object === //
DrumInterface Interface = DrumInterface();
