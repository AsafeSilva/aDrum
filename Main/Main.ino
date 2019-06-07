#include "aDrum.h"

Pad snare("SNARE", SNARE, PA0);
Pad hiTom("HI-TOM", TOM1, PA1);
Pad lowTom("LOW-TOM", TOM4, PA2);
Pad kick("KICK", KICK, PA3);
Pad crash1("CRASH 1", CYMBAL1, PA4);
Pad crash2("CRASH 2", CYMBAL2, PA5);
Pad ride("RIDE", RIDE_TIPE, PA6);
Pad hihat("HIHAT", HIHAT_SHAFT, PA7);
Pad hhc("HH-CONTROL", HH_CONTROLLER, PB0, HH_C);


void setup() {

	DrumKit.addPad(&snare);
	DrumKit.addPad(&hiTom);
	DrumKit.addPad(&lowTom);
	DrumKit.addPad(&kick);
	DrumKit.addPad(&crash1);
	DrumKit.addPad(&crash2);
	DrumKit.addPad(&ride);
	DrumKit.addPad(&hihat);
	DrumKit.addPad(&hhc);

	DrumKit.begin();

	while(true){
		DrumKit.play();		
	}
}

void loop() {
}