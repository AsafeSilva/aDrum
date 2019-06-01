#pragma once

#include <Arduino.h>

#define PROJECT_NAME	"aDrum Module"
#define PROJECT_VERSION	"v2.0"

// --- Notes (Addictive Drums)
#define HH_CONTROLLER	4
#define SNARE 			38
#define SNARE_SIDESTICK 42
#define KICK 			36
#define TOM1 			71
#define TOM2 			69
#define TOM3 			67
#define TOM4 			65
#define HIHAT_SHAFT		7
#define HIHAT_TIP		8
#define CYMBAL1 		77
#define CYMBAL1_CHOKE 	78
#define CYMBAL2 		79
#define CYMBAL2_CHOKE 	80
#define CYMBAL3 		81
#define CYMBAL3_CHOKE 	82
#define RIDE_TIPE 		60
#define RIDE_BELL 		61

// --- Types
#define PIEZO 	144
#define HH_C 	176
#define OFF 	128

// --- Define number of midi channel
#define MIDI_CHANNEL 0

// --- Define maximum value of property
#define NOTE_MAX		127
#define VELOCITY_MAX	127
#define SCANTIME_MAX	50
#define MASKTIME_MAX	500
#define GAIN_MAX		127

// --- Propertys IDs
#define TOTAL_PROPERTYS 5
#define	NOTE 		0
#define	THRESHMIN 	1
#define	SCANTIME 	2
#define	MASKTIME 	3
#define	GAIN 		4

// --- Encoder Pins
// #define ENC_A		3		// ENC_A must be external interrupt pin
// #define ENC_B		2

// --- Buttons Pins (must be external interrupt pins)
// #define BTN_BACK	18
// #define BTN_ENTER	19
// #define BTN_STORE	20
// #define BTN_STANDBY	21

// --- Leds Pins
// #define LED_STATUS	14
// #define LED_SENDING_DATA	15

// #define MASTER_VOLUME	A15

// --- Pins LCD
// #define LCD_RW	-->	GND
// #define	LCD_RS		4
// #define	LCD_EN		5
// #define	LCD_D4		6
// #define	LCD_D5		7
// #define	LCD_D6		8
// #define	LCD_D7		9
// #define LCD_LED		16

// --- Uncomment if you don't use interface
// #define USING_INTERFACE

// --- EEPROM
// #define USING_EEPROM

// --- MACROS
// #define TurnOn(pin)	digitalWrite(pin, 1)
// #define TurnOff(pin)	digitalWrite(pin, 0)
// #define Toggle(pin)	digitalWrite(pin, !digitalRead(pin))
