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
#define SCANTIME_MAX	200
#define MASKTIME_MAX	200
#define GAIN_MAX		127
#define ADC_MAX			4095

// --- Propertys IDs
#define TOTAL_PROPERTYS 5
#define	NOTE 		0
#define	THRESHMIN 	1
#define	SCANTIME 	2
#define	MASKTIME 	3
#define	GAIN 		4

// --------------------------------------------------------------------

// Serial Communication
#define BAUD_RATE	115200

// --- Encoder Pins
#define ENC_A		PB11		// ENC_A must be external interrupt pin
#define ENC_B		PB10

// --- Buttons Pins (must be external interrupt pins)
#define BTN_BACK	PB15
#define BTN_ENTER	PB14
#define BTN_STORE	PB13
#define BTN_STANDBY	PB12

// --- Leds Pins
#define LED_STATUS 			PA11
#define LED_SENDING_DATA	PA12

// --- Master Volume
#define USING_MASTER_VOLUME
#define MASTER_VOLUME	PB1

#define NEGATIVE_VOLTAGE PB9

// --- Pins LCD
// #define LCD_RW	-->	GND
#define	LCD_RS		PB8
#define	LCD_EN		PB7
#define	LCD_D4		PB6
#define	LCD_D5		PB5
#define	LCD_D6		PB4
#define	LCD_D7		PB3
#define LCD_LED		PA15

// --- Uncomment if you don't use interface
#define USING_INTERFACE

// --- EEPROM
// #define USING_EEPROM

// --- MACROS
#define TurnOn(pin) 	digitalWrite(pin, HIGH)
#define TurnOff(pin) 	digitalWrite(pin, LOW)
// #define Toggle(pin) 	digitalWrite(pin, !digitalRead(pin))
