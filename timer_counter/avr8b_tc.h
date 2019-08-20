/*
 * avr8b_tc.h
 *
 *  Created on: Aug 19, 2019
 *      Author: radek
 */

#ifndef TIMER_COUNTER_AVR8B_TC_H_
#define TIMER_COUNTER_AVR8B_TC_H_

#include <stdint.h>

/* Please define your configuration in the following section: */

/*-------------------------- CONFIGURATION ------------------------------*/


// These are the currently supported AVRs:
#ifndef __AVR_ATmega8535__
	#error "AVR8b timer - Your MCU is not supported yet"
#endif


#ifdef __AVR_ATmega8535__
extern void avr8b_tc_oca_isr(uint8_t tc_num);
extern void avr8b_tc_ocb_isr(uint8_t tc_num);
extern void avr8b_tc_tov1_isr(uint8_t tc_num);
#endif

/*---------------------- CONFIGURATION END ------------------------------*/

/*----------------------------- API -------------------------------------*/

typedef enum {
	DIV_BY_1,
	DIV_BY_8,
	DIV_BY_64,
	DIV_BY_256,
	DIV_BY_1024,
	DIV_BY_INF //clk is off
} AVR8B_TC_CLK_DIV;

typedef enum {
	MODE_NORMAL,
	MODE_FAST_PWM
} AVR8B_TC_MODE;

typedef enum {
	OC_MODE_OFF,
	OC_MODE_TOGGLE_ON_COMPARE,
	OC_MODE_SET_LOW_ON_COMPARE,
	OC_MODE_SET_HIGH_ON_COMPARE
} AVR8B_TC_OC_MODE;

typedef struct {
	uint8_t tc_num;
	uint16_t ocra_val;
	uint16_t ocrb_val;
	uint8_t oca_int_on_off;
	uint8_t ocb_int_on_off;
	uint8_t overflow_int_on_off;
	AVR8B_TC_MODE tc_mode;
	AVR8B_TC_OC_MODE oca_mode;
	AVR8B_TC_OC_MODE ocb_mode;
} AVR8B_TC_CONFIG;


// This function initiates the selected timer to a specified configuration. It stops the selected
// timer had it been running prior to initialization.
// It will not turn on the global interrupt flag and it will not start the timer.
// Timer has to be started with avr8b_tc_start().
void avr8b_tc_init(AVR8B_TC_CONFIG *cfg);
// This one deinitializes and stops the selected timer and clears all interrupts indicators.
void avr8b_tc_deinit(uint8_t tc_num);

// Fine grained api:

// These functions start/stop the selected timer (tc_num) with selected clock option.
// Init should be called prior to calling these.
void avr8b_tc_start(uint8_t tc_num, AVR8B_TC_CLK_DIV clk_opt);
void avr8b_tc_stop(uint8_t tc_num);

// These functions set A and B output compare registers for selected timer (tc_num).
// Buffered only in PWM modes.
void avr8b_tc_ocra_set(uint8_t tc_num, uint16_t ocra_val);
void avr8b_tc_ocrb_set(uint8_t tc_num, uint16_t ocrb_val);

// These functions turn on/off output compare interrupts A and and also
// timer counter overflow on selected timer (tc_num)
void avr8b_tc_oca_int_set(uint8_t tc_num, uint8_t on_off);
void avr8b_tc_ocb_int_set(uint8_t tc_num, uint8_t on_off);
void avr8b_tc_tov_int_set(uint8_t tc_num, uint8_t on_off);


/*----------------------------- API END ---------------------------------*/

#endif /* TIMER_COUNTER_AVR8B_TC_H_ */
