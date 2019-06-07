#include "Encoder.h"
#include "Arduino.h"


int Encoder::channelA;
int Encoder::channelB;
volatile long Encoder::position;

boolean Encoder::toLimit;
int Encoder::limitMin;
int Encoder::limitMax;

boolean Encoder::loopMode;
const boolean Encoder::NOLOOP = false;
const boolean Encoder::LOOP = true;

void (*Encoder::_whenRotate)(boolean, long);


Encoder::Encoder(int _channelA, int _channelB){

	channelA = _channelA;
	channelB = _channelB;

	toLimit = false;
}

void Encoder::begin(WiringPinMode inputMode, ExtIntTriggerMode edgeMode){

	pinMode(channelA, inputMode);
	pinMode(channelB, inputMode);

	attachInterrupt(digitalPinToInterrupt(channelA), Encoder::interrupt, edgeMode);

	position = 0;
}

void Encoder::setLimits(int min, int max, boolean _loopMode){
	toLimit = true;

	limitMin = min;
	limitMax = max;

	loopMode = _loopMode;
}

void Encoder::clear(){
	position = toLimit ? limitMin : 0;
}

void Encoder::interrupt(){

	uint32 direction = gpio_read_bit(PIN_MAP[channelB].gpio_device, PIN_MAP[channelB].gpio_bit);

	position = direction ? position+1 : position-1;

	if(toLimit){
		if(loopMode == NOLOOP)
			position = constrain(position, limitMin, limitMax);
		else{
			if(position > limitMax) position = limitMin;
			else if(position < limitMin) position = limitMax;
		}
	}

	if(_whenRotate != NULL) _whenRotate(direction == 1, position);
}

long Encoder::getPosition(){
	return position;
}

void Encoder::whenClick(int pin, voidFuncPtr callback){
	pinMode(pin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(pin), callback, FALLING);
}

void Encoder::whenRotate( void (*callback)(boolean, long) ){
	_whenRotate = callback;
}