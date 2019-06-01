#include "aDrum.h"

Pad snare("SNARE", SNARE,/* A*/0);
Pad hiTom("HI-TOM", TOM1,/* A*/1);
Pad lowTom("LOW-TOM", TOM4,/* A*/2);
Pad kick("KICK", KICK,/* A*/3);
Pad crash1("CRASH 1", CYMBAL1,/* A*/4);
Pad crash2("CRASH 2", CYMBAL2,/* A*/5);
Pad ride("RIDE", RIDE_TIPE,/* A*/6);

Pad hihat("HIHAT", HIHAT_SHAFT,/* A*/7);
Pad hhc("HH-CONTROL", HH_CONTROLLER,/* A*/8, HH_C);

Pad snareEdge("SNARE-EDGE", SNARE_SIDESTICK,/* A*/9);
Pad midTom("MID-TOM", TOM2,/* A*/10);
Pad crash1Choke("CRASH1-CHOKE", CYMBAL1_CHOKE,/* A*/11);
Pad crash2Choke("CRASH2-CHOKE", CYMBAL2_CHOKE,/* A*/12);
Pad rideBell("RIDE-BELL", RIDE_BELL,/* A*/13);

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