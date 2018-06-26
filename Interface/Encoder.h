#pragma once

// Encoder
// Asafe dos Santos silva
// 30/11/16
// 11h03

#include <Arduino.h>


class Encoder{

private:

	static volatile long position;

	static int channelA, channelB;

	static uint8_t  bitRegister;
	static uint8_t  portRegister;

	static void interrupt();

	static boolean toLimit;
	static int limitMin, limitMax;

	static boolean loopMode;

	static void (*_whenRotate)(boolean, long);

public:

	static const boolean NOLOOP;
	static const boolean LOOP;

	Encoder(int _channelA, int _channelB);

	void begin();

	void setLimits(int min, int max, boolean _loopMode = false);

	void clear();

	long getPosition();

	void whenClick(int pin, void (*callback)(void));

	void whenRotate( void (*callback)(boolean, long) );
};
