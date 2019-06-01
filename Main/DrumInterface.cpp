/*#include "DrumInterface.h"

volatile int DrumInterface::indexMenu; 
volatile int DrumInterface::indexPadName;
volatile int DrumInterface::indexPadProperty;
volatile int DrumInterface::indexPadValue;

volatile bool DrumInterface::storingData;
volatile bool DrumInterface::storeMenu;

volatile bool DrumInterface::standby;

volatile unsigned long DrumInterface::timeWithoutChanges;

volatile unsigned long DrumInterface::debounceEnterButton;
volatile unsigned long DrumInterface::debounceBackButton;
volatile unsigned long DrumInterface::debounceStoreButton;
volatile unsigned long DrumInterface::debounceStandbyButton;

Pad* DrumInterface::pad;

DrumInterface::DrumInterface(){}

void DrumInterface::begin(){

	display = new LiquidCrystal(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

	// Initialize the LCD
	display->begin(16, 2);
	display->clear();

	pinMode(LED_STATUS, OUTPUT);
	pinMode(LED_SENDING_DATA, OUTPUT);
	pinMode(LCD_LED, OUTPUT);

	splashScreen();

	encoder = new Encoder(ENC_A, ENC_B);

	btnEnter = new ButtonEvent(BTN_ENTER);
	btnBack = new ButtonEvent(BTN_BACK);
	btnStore = new ButtonEvent(BTN_STORE);
	btnStandby = new ButtonEvent(BTN_STANDBY);

	// Initialize the Encoder
	encoder->begin(INPUT, RISING);
	encoder->whenRotate(this->encoderRotateEvent);

	// Initialize buttons
	btnEnter->begin(INPUT_PULLUP, FALLING);
	btnEnter->whenClick(this->buttonEnterEvent);
	btnBack->begin(INPUT_PULLUP, FALLING);
	btnBack->whenClick(this->buttonBackEvent);
	btnStore->begin(INPUT_PULLUP, FALLING);
	btnStore->whenClick(this->buttonStoreEvent);
	btnStandby->begin(INPUT_PULLUP, FALLING);
	btnStandby->whenClick(this->buttonStandbyEvent);


	strcpy(s_padName, "");
	strcpy(s_padProperty, "");
	strcpy(s_padValue, "");

	indexMenu = 0;
	indexPadName = 0;
	indexPadProperty = 0;
	indexPadValue = 0;

	storingData = false;
	storeMenu = false;

	standby = false;

	timeWithoutChanges = millis();
}

void DrumInterface::runInterface(){

	if(standby){
		TurnOff(LCD_LED);
		TurnOff(LED_STATUS);
		display->noDisplay();
		while(standby);
	}

	TurnOn(LCD_LED);
	display->display();


	if(storeMenu){
		strcpy(s_padName, "  SAVE DATA?  ");
		strcpy(s_padProperty, "");
		strcpy(s_padValue, "");

		if(storingData){
			display->setCursor(1, 0);
			display->print(F("  SAVING      "));

		#ifdef USING_EEPROM
			DrumKit.saveAllData();
			for (int i = 9; i <= 12; i++){
				delay(500);
				display->setCursor(i, 0);
				display->print(F("."));
			}
		#endif

	    	storeMenu = false;
	    	storingData = false;
	    	timeWithoutChanges = millis();
	    }

	}else{

		if(indexMenu == MENU_NAME){

		    pad = DrumKit.get(indexPadName);

		    indexPadProperty = NOTE;
		    indexPadValue = pad->getNote();

			strcpy(s_padName, pad->getName());
			strcpy(s_padProperty, propertys[indexPadProperty]);
			sprintf(s_padValue, "%d", pad->getNote());

		} else if(indexMenu == MENU_PROPERTY){

		    strcpy(s_padProperty, propertys[indexPadProperty]);

		    if(indexPadProperty == NOTE){
		    	sprintf(s_padValue, "%d", pad->getNote());
		    	indexPadValue = pad->getNote();
		    }else if(indexPadProperty == THRESHMIN){
		    	sprintf(s_padValue, "%d", pad->getThresholdMin());
		    	indexPadValue = pad->getThresholdMin();
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
			else if(indexPadProperty == SCANTIME)	pad->setScanTime(indexPadValue);
			else if(indexPadProperty == MASKTIME)	pad->setMaskTime(indexPadValue);
			else if(indexPadProperty == GAIN)		pad->setGain(indexPadValue);

		}
	}


	if(millis() - timeWithoutChanges < 500){
		print();
		TurnOff(LED_STATUS);
	}else{
		TurnOn(LED_STATUS);
	}
}


void DrumInterface::buttonEnterEvent(){
	timeWithoutChanges = millis();

	if(millis() - debounceEnterButton >= DEBOUNCE_200){
		debounceEnterButton = millis();

		if(storingData || standby)
			return;

		if(storeMenu){
			storingData = true;
			return;
		}

		indexMenu++;
		if (indexMenu >= TOTAL_OPTIONS)	indexMenu = 0;
	}
}

void DrumInterface::buttonBackEvent(){
	timeWithoutChanges = millis();

	if(millis() - debounceBackButton >= DEBOUNCE_200){
		debounceBackButton = millis();

		if(storingData || standby)
			return;

		if(storeMenu){
			storeMenu = false;
			return;
		}

		indexMenu--;
		if (indexMenu < 0)	indexMenu = TOTAL_OPTIONS-1;
	}
}

void DrumInterface::buttonStoreEvent(){
	timeWithoutChanges = millis();

	if(millis() - debounceStoreButton >= DEBOUNCE_200){
		debounceStoreButton = millis();

		if(storingData || standby)
			return;

		storeMenu = true;
		indexMenu = MENU_NAME;
	}

}

void DrumInterface::buttonStandbyEvent(){
	timeWithoutChanges = millis();

	if(millis() - debounceStandbyButton >= DEBOUNCE_200){
		debounceStandbyButton = millis();

		standby = !standby;
	}

}

void DrumInterface::encoderRotateEvent(boolean direction, long position){
	timeWithoutChanges = millis();

	if(storingData || standby)
		return;


	switch (indexMenu) {
	    case MENU_NAME:

			indexPadName = direction ? indexPadName+1 : indexPadName-1;
			if(indexPadName >= DrumKit.size()) indexPadName = 0;
			else if(indexPadName < 0)	indexPadName = DrumKit.size()-1;

			break;
	    case MENU_PROPERTY:
	    
			indexPadProperty = direction ? indexPadProperty+1 : indexPadProperty-1;
			if(indexPadProperty >= TOTAL_PROPERTYS) indexPadProperty = 0;
			else if(indexPadProperty < 0)	indexPadProperty = TOTAL_PROPERTYS-1;    	

			break;
	    case MENU_VALUE:

			indexPadValue = direction ? indexPadValue+1 : indexPadValue-1;

			if(indexPadProperty == NOTE){

				if(indexPadValue > NOTE_MAX) indexPadValue = 0;
				else if(indexPadValue < 0)	indexPadValue = NOTE_MAX;

		    }else if(indexPadProperty == THRESHMIN){

		    	if(indexPadValue > VELOCITY_MAX) indexPadValue = 0;
				else if(indexPadValue < 0)	indexPadValue = VELOCITY_MAX;

		    }else if(indexPadProperty == SCANTIME){

		    	if(indexPadValue > SCANTIME_MAX) indexPadValue = 0;
				else if(indexPadValue < 0)	indexPadValue = SCANTIME_MAX;

		    }else if(indexPadProperty == MASKTIME){

		    	if(indexPadValue > MASKTIME_MAX) indexPadValue = 0;
				else if(indexPadValue < 0)	indexPadValue = MASKTIME_MAX; 

			}else if(indexPadProperty == GAIN){

		    	if(indexPadValue > GAIN_MAX) indexPadValue = 0;
				else if(indexPadValue < 0)	indexPadValue = GAIN_MAX;

			}

			break;	      
	    default:;
	      // do something
	}
}

void DrumInterface::print(){

	strcat(s_padName, spaces[14 - strlen(s_padName)]);
	strcat(s_padProperty, spaces[9 - strlen(s_padProperty)]);
	strcat(s_padValue, spaces[3 - strlen(s_padValue)]);

	display->setCursor(1, 0);
	display->print(s_padName);
	display->setCursor(1, 1);
	display->print(s_padProperty);
	display->setCursor(12, 1);
	display->print(s_padValue);
	
	switch (indexMenu) {
	    case MENU_NAME:
	    	display->setCursor(0, 0);display->print("<");
	    	display->setCursor(15, 0);display->print(">");
	    	display->setCursor(0, 1);display->print(" ");
	    	display->setCursor(11, 1);display->print(" ");	    	
	    	display->setCursor(15, 1);display->print(" ");	    	
	      break;
	    case MENU_PROPERTY:
	    	display->setCursor(0, 0);display->print(" ");
	    	display->setCursor(15, 0);display->print(" ");
	    	display->setCursor(0, 1);display->print("<");
	    	display->setCursor(11, 1);display->print(" ");	    	
	    	display->setCursor(15, 1);display->print(">");	
	      break;
	    case MENU_VALUE:
	    	display->setCursor(0, 0);display->print(" ");
	    	display->setCursor(15, 0);display->print(" ");
	    	display->setCursor(0, 1);display->print(" ");
	    	display->setCursor(11, 1);display->print("<");	    	
	    	display->setCursor(15, 1);display->print(">");
	      break;
	}
}

void DrumInterface::splashScreen(){
	TurnOn(LCD_LED);
	display->display();

	display->setCursor(2, 0);
	display->print(F(PROJECT_NAME));
	display->setCursor(12, 1);
	display->print(F(PROJECT_VERSION));

	delay(4000);

	display->clear();
}

// === Preinstantiate Object === //
DrumInterface Interface = DrumInterface();
*/