#include "aDrum.h"

Pad snare("SNARE", SNARE, A0);
Pad hiTom("HI-TOM", TOM1, A1);
Pad lowTom("LOW-TOM", TOM4, A2);
Pad kick("KICK", KICK, A3);
Pad crash1("CRASH 1", CYMBAL1, A4);
Pad crash2("CRASH 2", CYMBAL2, A5);
Pad ride("RIDE", RIDE_TIPE, A6);

Pad hihat("HIHAT", HIHAT_SHAFT, A7);
Pad hhc("HH-CONTROL", HH_CONTROLLER, A8, HH_C);

Pad snareEdge("SNARE-EDGE", SNARE_SIDESTICK, A9);
Pad midTom("MID-TOM", TOM2, A10);
Pad crash1Choke("CRASH1-CHOKE", CYMBAL1_CHOKE, A11);
Pad crash2Choke("CRASH2-CHOKE", CYMBAL2_CHOKE, A12);
Pad rideBell("RIDE-BELL", RIDE_BELL, A13);

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
	
	DrumKit.addPad(&snareEdge);
	DrumKit.addPad(&midTom);
	DrumKit.addPad(&crash1Choke);
	DrumKit.addPad(&crash2Choke);
	DrumKit.addPad(&rideBell);

	DrumKit.begin(115200, FAST_ADC);	// abaixo dos 'addPad()'
}

void loop() {
	DrumKit.play();
}