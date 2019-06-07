#pragma once

#include <Arduino.h>


class Encoder{

private:

	static volatile long position;

	static int channelA, channelB;

	static void interrupt();

	static boolean toLimit;
	static int limitMin, limitMax;

	static boolean loopMode;

	static void (*_whenRotate)(boolean, long);

public:

	static const boolean NOLOOP;
	static const boolean LOOP;

	Encoder(int _channelA, int _channelB);

	void begin(WiringPinMode inputMode = INPUT, ExtIntTriggerMode edgeMode = FALLING);

	void setLimits(int min, int max, boolean _loopMode = false);

	void clear();

	long getPosition();

	void whenClick(int pin, voidFuncPtr callback);

	void whenRotate( void (*callback)(boolean, long) );
};
