/*
 * avr8b_tc_test.c
 *
 *  Created on: Aug 20, 2019
 *      Author: radek
 */


#include "../avr8b_tc.h"
#include <avr/interrupt.h>
#include <util/delay.h>

void avr8b_tc_oca_isr(uint8_t tc_num)
{

}

void avr8b_tc_ocb_isr(uint8_t tc_num)
{
	//PORTD |= _BV(PIN5);
	PORTD &= ~_BV(PIN4);
}

void avr8b_tc_tov_isr(uint8_t tc_num)
{
	if (tc_num != 1)
		return;

	PORTD |= _BV(PIN5);
	PORTD |= _BV(PIN4);
}

int main(void)
{
	AVR8B_TC_CONFIG cfg;

	//16b timer:
	cfg.tc_num = 1;
	cfg.ocra_val = 32000;
	cfg.ocrb_val = 32000;
	cfg.oca_int_on_off = 0;
	cfg.ocb_int_on_off = 0;
	cfg.overflow_int_on_off = 0;
	cfg.tc_mode = MODE_NORMAL;
	cfg.oca_mode = OC_MODE_TOGGLE_ON_COMPARE;
	cfg.ocb_mode = OC_MODE_TOGGLE_ON_COMPARE;

	avr8b_tc_init(&cfg);
	avr8b_tc_start(cfg.tc_num, DIV_BY_1024);


	//8b timers:
	cfg.tc_num = 0;
	cfg.ocra_val = 128;

	avr8b_tc_init(&cfg);
	avr8b_tc_start(cfg.tc_num, DIV_BY_1024);

	cfg.tc_num = 2;
	cfg.ocra_val = 128;

	avr8b_tc_init(&cfg);
	avr8b_tc_start(cfg.tc_num, DIV_BY_1024);

	_delay_ms(20000); //wait for 20 seconds

	//tests tov and output compare

	DDRD |= _BV(PIN4) | _BV(PIN5);

	cfg.tc_num = 1;
	cfg.ocra_val = 32000;
	cfg.ocrb_val = 32000;
	cfg.oca_int_on_off = 1;
	cfg.ocb_int_on_off = 1;
	cfg.overflow_int_on_off = 1;
	cfg.tc_mode = MODE_NORMAL;
	cfg.oca_mode = OC_MODE_OFF;
	cfg.ocb_mode = OC_MODE_OFF;
	avr8b_tc_init(&cfg);
	sei();
	avr8b_tc_start(cfg.tc_num, DIV_BY_1024);

	while (1);
	return 0;
}
