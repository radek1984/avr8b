/*
 * avr8b_tc_test.c
 *
 *  Created on: Aug 20, 2019
 *      Author: radek
 */


#include "../avr8b_tc.h"
#include <avr/interrupt.h>

void avr8b_tc_oca_isr(uint8_t tc_num)
{

}

void avr8b_tc_ocb_isr(uint8_t tc_num)
{

}

void avr8b_tc_tov1_isr(uint8_t tc_num)
{

}

int main(void)
{
	AVR8B_TC_CONFIG cfg;
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
	avr8b_tc_start(1, DIV_BY_1024);

	while (1);
	return 0;
}
