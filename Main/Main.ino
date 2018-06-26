#include "ArduinoDrum.h"

Pad snare("SNARE", SNARE, A0);
Pad hiTom("HI-TOM", TOM1, A1);
Pad lowTom("LOW-TOM", TOM4, A2);
Pad kick("KICK", KICK, A3);
Pad crash1("CRASH 1", CYMBAL1, A4);
Pad crash2("CRASH 2", CYMBAL2, A5);
Pad ride("RIDE", RIDE_TIPE, A6);

Pad hihat("HIHAT", HIHAT_SHAFT, MUX0);
Pad hhc("HH-CONTROL", HH_CONTROLLER, MUX1, HH_C);
Pad snareEdge("SNARE-EDGE", SNARE_SIDESTICK, MUX2);
Pad midTom("MID-TOM", TOM2, MUX3);
Pad crash1Choke("CRASH1-CHOKE", CYMBAL1_CHOKE, MUX4);
Pad crash2Choke("CRASH2-CHOKE", CYMBAL2_CHOKE, MUX5);
Pad rideBell("RIDE-BELL", RIDE_BELL, MUX6);

void setup() {

	Drum.addPad(&snare);
	Drum.addPad(&hiTom);
	Drum.addPad(&lowTom);
	Drum.addPad(&kick);
	Drum.addPad(&crash1);
	Drum.addPad(&crash2);
	Drum.addPad(&ride);

	Drum.addPad(&hihat);
	Drum.addPad(&hhc);
	Drum.addPad(&snareEdge);
	Drum.addPad(&midTom);
	Drum.addPad(&crash1Choke);
	Drum.addPad(&crash2Choke);
	Drum.addPad(&rideBell);

	Drum.begin(115200, FAST_ADC);	// abaixo dos 'addPad()'
}

void loop() {
	Drum.play();
}