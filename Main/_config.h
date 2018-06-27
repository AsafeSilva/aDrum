#pragma once

// === Notes (Addictive Drums) === // 
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

// Uncomment if you don't use interface
#define USING_INTERFACE

// === Types === //
#define PIEZO 	144
#define HH_C 	176
#define OFF 	128

// Define number of midi channel
#define MIDI_CHANNEL 0

// Define maximum value of property
#define NOTE_MAX		127
#define ADC_MAX			1023
#define SCANTIME_MAX	50
#define MASKTIME_MAX	500
#define GAIN_MAX		1000

// Propertys IDs
#define TOTAL_PROPERTYS 6
#define	NOTE 		0
#define	THRESHMIN 	1
#define	THRESHMAX 	2
#define	SCANTIME 	3
#define	MASKTIME 	4
#define	GAIN 		5

// Software Serial pins
#define RX_PIN	8
#define TX_PIN	9

// == Encoder Pins == //
#define ENC_ENTER	2 		// ENC_ENTER must be a pin of External Interrupt
#define ENC_A		3		// ENC_A must be a pin of External Interrupt
#define ENC_B		4

// == Pins LCD == //
// #define LCD_RW		GND
#define	LCD_RS		14
#define	LCD_EN		15
#define	LCD_D4		16
#define	LCD_D5		17
#define	LCD_D6		18
#define	LCD_D7		19

// EEPROM
#define USING_EEPROM
#define SAVE_DATA_PIN	12

// MUX
#define USING_MUX
#define MUX_PIN		A7
#define MUX_DDR		DDRD
#define MUX_PORT	PORTD
#define MUX_BIT		5
#define MUX_MASK	0B11100000
#define MUX0	100	
#define MUX1	101
#define MUX2	102
#define MUX3	103
#define MUX4	104
#define MUX5	105
#define MUX6	106
#define MUX7	107