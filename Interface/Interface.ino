#include "_config.h"

#include "DrumInterface.h"


void setup(){

	Serial.begin(9600);
	
	Interface.begin();
}

void loop(){
	Interface.runInterface();
}