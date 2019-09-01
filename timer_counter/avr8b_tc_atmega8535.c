/*
 * avr8b_tc_atmega8535.c
 *
 *  Created on: Aug 19, 2019
 *      Author: radek
 */


#ifdef __AVR_ATmega8535__

#include "avr8b_tc.h"
#include <avr/io.h>
#include <util/atomic.h>

#define TCNT(n) (TCNT##n)
#define OCPREG(n, ab) (OCR##n##ab)
#define TCONTROLREG(n, ab) (TCCR##n##ab)

void avr8b_tc_clk_set(uint8_t tc_num, AVR8B_TC_CLK_DIV clk_opt)
{
	switch (tc_num)
	{
		case 0:
		{
			//stop
			TCONTROLREG(0,) &= ~( _BV(CS02) | _BV(CS01) |  _BV(CS00) );

			switch (clk_opt)
			{
				case DIV_BY_1:
					TCONTROLREG(0,) |= ( _BV(CS00) );
					TCONTROLREG(0,) &= ~( _BV(CS02) | _BV(CS01) );
					break;
				case DIV_BY_8:
					TCONTROLREG(0,) |= ( _BV(CS01));
					TCONTROLREG(0,) &= ~( _BV(CS02) | _BV(CS00) );
					break;
				case DIV_BY_64:
					TCONTROLREG(0,) |= ( _BV(CS01) | _BV(CS00) );
					TCONTROLREG(0,) &= ~( _BV(CS02) );
					break;
				case DIV_BY_256:
					TCONTROLREG(0,) |= ( _BV(CS02) );
					TCONTROLREG(0,) &= ~( _BV(CS01) | _BV(CS00) );
					break;
				case DIV_BY_1024:
					TCONTROLREG(0,) |= ( _BV(CS02) | _BV(CS00) );
					TCONTROLREG(0,) &= ~( _BV(CS01) );
					break;
				case DIV_BY_INF: //clk is off
				default:
					TCONTROLREG(0,) &= ~( _BV(CS02) | _BV(CS01) |  _BV(CS00) );
					break;
			}
			break;
		}

		case 1:
		{
			//stop
			TCONTROLREG(1, B) &= ~( _BV(CS12) | _BV(CS11) | _BV(CS10) );
			switch (clk_opt)
			{
				case DIV_BY_1:
					TCONTROLREG(1, B) |= ( _BV(CS10));
					TCONTROLREG(1, B) &= ~(_BV(CS12) | _BV(CS11));
					break;
				case DIV_BY_8:
					TCONTROLREG(1, B) |= (_BV(CS11));
					TCONTROLREG(1, B) &= ~(_BV(CS12) | _BV(CS10));
					break;
				case DIV_BY_64:
					TCONTROLREG(1, B) |= (_BV(CS11) | _BV(CS10));
					TCONTROLREG(1, B) &= ~(_BV(CS12));
					break;
				case DIV_BY_256:
					TCONTROLREG(1, B) |= (_BV(CS12));
					TCONTROLREG(1, B) &= ~( _BV(CS11) | _BV(CS10));
					break;
				case DIV_BY_1024:
					TCONTROLREG(1, B) |= (_BV(CS12) | _BV(CS10));
					TCONTROLREG(1, B) &= ~(_BV(CS11));
					break;
				case DIV_BY_INF: //clk is off
				default:
					TCONTROLREG(1, B) &= ~( _BV(CS12) | _BV(CS11) | _BV(CS10) );
					break;
			}
			break;
		}

		case 2:
		{
			//stop
			TCONTROLREG(2,) &= ~( _BV(CS22) | _BV(CS21) |  _BV(CS20) );

			switch (clk_opt)
			{
				case DIV_BY_1:
					TCONTROLREG(2,) |= ( _BV(CS20) );
					TCONTROLREG(2,) &= ~( _BV(CS22) | _BV(CS21) );
					break;
				case DIV_BY_8:
					TCONTROLREG(2,) |= ( _BV(CS21));
					TCONTROLREG(2,) &= ~( _BV(CS22) | _BV(CS20) );
					break;
				case DIV_BY_32:
					TCONTROLREG(2,) |= ( _BV(CS21) | _BV(CS20) );
					TCONTROLREG(2,) &= ~( _BV(CS22) );
					break;
				case DIV_BY_64:
					TCONTROLREG(2,) |= ( _BV(CS22) );
					TCONTROLREG(2,) &= ~( _BV(CS21) | _BV(CS20) );
					break;
				case DIV_BY_128:
					TCONTROLREG(2,) |= ( _BV(CS22) | _BV(CS20));
					TCONTROLREG(2,) &= ~( _BV(CS21) );
					break;
				case DIV_BY_256:
					TCONTROLREG(2,) |= ( _BV(CS22) | _BV(CS21) );
					TCONTROLREG(2,) &= ~( _BV(CS20) );
					break;
				case DIV_BY_1024:
					TCONTROLREG(2,) |= ( _BV(CS22) | _BV(CS21) | _BV(CS20) );
					break;
				case DIV_BY_INF: //clk is off
				default:
					TCONTROLREG(2,) &= ~( _BV(CS22) | _BV(CS21) |  _BV(CS20) );
					break;
			}
			break;
		}

		default:
			break;
	}

}

void avr8b_tc_oca_int_set(uint8_t tc_num, uint8_t on_off)
{
	switch (tc_num)
	{
		case 0:
		{
			if (on_off)
				TIMSK |= _BV(OCIE0);
			else
				TIMSK &= ~(_BV(OCIE0));
			break;
		}
		case 1:
		{
			if (on_off)
				TIMSK |= _BV(OCIE1A);
			else
				TIMSK &= ~(_BV(OCIE1A));
			break;
		}
		case 2:
		{
			if (on_off)
				TIMSK |= _BV(OCIE2);
			else
				TIMSK &= ~(_BV(OCIE2));
			break;
		}
		default:
			break;
	}
}

void avr8b_tc_ocb_int_set(uint8_t tc_num, uint8_t on_off)
{
	if (tc_num != 1)
		return;

	if (on_off)
		TIMSK |= _BV(OCIE1B);
	else
		TIMSK &= ~(_BV(OCIE1B));
}

void avr8b_tc_tov_int_set(uint8_t tc_num, uint8_t on_off)
{
	switch (tc_num)
	{
		case 0:
		{
			if (on_off)
				TIMSK |= _BV(TOIE0);
			else
				TIMSK &= ~(_BV(TOIE0));
			break;
		}
		case 1:
		{
			if (on_off)
				TIMSK |= _BV(TOIE1);
			else
				TIMSK &= ~(_BV(TOIE1));
			break;
		}
		case 2:
		{
			if (on_off)
				TIMSK |= _BV(TOIE2);
			else
				TIMSK &= ~(_BV(TOIE2));
			break;
		}
		default:
			break;
	}
}

void _avr8b_tc_oca_mode(uint8_t tc_num, AVR8B_TC_OC_MODE oca_mode)
{
	switch (tc_num)
	{
		case 0:
		{
			if (oca_mode == OC_MODE_OFF)
			{
				TCONTROLREG(0, ) &= (~( _BV(COM01) | _BV(COM00) ));
			}
			else
			{
				if (oca_mode == OC_MODE_TOGGLE_ON_COMPARE)
				{
					TCONTROLREG(0, ) |= ( _BV(COM00) );
					TCONTROLREG(0, ) &= (~( _BV(COM01) ));
				}

				if (oca_mode == OC_MODE_SET_LOW_ON_COMPARE)
				{
					TCONTROLREG(0, ) |= ( _BV(COM01) );
					TCONTROLREG(0, ) &= (~( _BV(COM00) ));
				}

				if (oca_mode == OC_MODE_SET_HIGH_ON_COMPARE)
				{
					TCONTROLREG(0, ) |= ( _BV(COM01) | _BV(COM00) );
				}
				// ocp pin enable as output
				DDRB |= _BV(PIN3);
			}
			break;
		}
		case 1:
		{
			if (oca_mode == OC_MODE_OFF)
			{
				TCONTROLREG(1, A) &= (~( _BV(COM1A1) | _BV(COM1A0) ));
			}
			else
			{
				if (oca_mode == OC_MODE_TOGGLE_ON_COMPARE)
				{
					TCONTROLREG(1, A) &= (~( _BV(COM1A1) ));
					TCONTROLREG(1, A) |= _BV(COM1A0);
				}

				if (oca_mode == OC_MODE_SET_LOW_ON_COMPARE)
				{
					TCONTROLREG(1, A) |= _BV(COM1A1);
					TCONTROLREG(1, A) &= (~( _BV(COM1A0) ));
				}

				if (oca_mode == OC_MODE_SET_HIGH_ON_COMPARE)
				{
					TCONTROLREG(1, A) |= (_BV(COM1A1) | _BV(COM1A0));
				}
				// ocp pin enable as output
				DDRD |= _BV(PIN5);
			}
			break;
		}
		case 2:
		{
			if (oca_mode == OC_MODE_OFF)
			{
				TCONTROLREG(2, ) &= (~( _BV(COM21) | _BV(COM20) ));
			}
			else
			{
				if (oca_mode == OC_MODE_TOGGLE_ON_COMPARE)
				{
					TCONTROLREG(2, ) |= ( _BV(COM20) );
					TCONTROLREG(2, ) &= (~( _BV(COM21) ));
				}

				if (oca_mode == OC_MODE_SET_LOW_ON_COMPARE)
				{
					TCONTROLREG(2, ) |= ( _BV(COM21) );
					TCONTROLREG(2, ) &= (~( _BV(COM20) ));
				}

				if (oca_mode == OC_MODE_SET_HIGH_ON_COMPARE)
				{
					TCONTROLREG(2, ) |= ( _BV(COM21) | _BV(COM20) );
				}
				// ocp pin enable as output
				DDRD |= _BV(PIN7);
			}
			break;
		}
		default:
			break;
	}
}

void _avr8b_tc_ocb_mode(uint8_t tc_num, AVR8B_TC_OC_MODE ocb_mode)
{
	if (tc_num == 1)
	{
		if (ocb_mode == OC_MODE_OFF)
		{
			TCONTROLREG(1, A) &= (~( _BV(COM1B1) | _BV(COM1B0) ));
		}
		else
		{
			if (ocb_mode == OC_MODE_TOGGLE_ON_COMPARE)
			{
				TCONTROLREG(1, A) &= (~( _BV(COM1B1) ));
				TCONTROLREG(1, A) |= _BV(COM1B0);
			}

			if (ocb_mode == OC_MODE_SET_LOW_ON_COMPARE)
			{
				TCONTROLREG(1, A) |= _BV(COM1B1);
				TCONTROLREG(1, A) &= (~( _BV(COM1B0) ));
			}

			if (ocb_mode == OC_MODE_SET_HIGH_ON_COMPARE)
			{
				TCONTROLREG(1, A) |= (_BV(COM1B1) | _BV(COM1B0));
			}

			// ocp pin enable as output
			DDRD |= _BV(PIN4);
		}
	}
}

void avr8b_tc_init(AVR8B_TC_CONFIG *cfg)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		avr8b_tc_deinit(cfg->tc_num);

		if (cfg->tc_num == 0)
		{
			// set force output compare to 0
			// stop the clock for now, no source
			TCONTROLREG(0, ) &= (~( _BV(FOC0) | _BV(CS02) | _BV(CS01) | _BV(CS00) ));

			if (cfg->tc_mode == MODE_FAST_PWM)
			{
				TCONTROLREG(0, ) |= ( _BV(WGM01) | _BV(WGM00) );
			}

			if (cfg->tc_mode == MODE_NORMAL)
			{
				TCONTROLREG(0, ) &= (~( _BV(WGM01) | _BV(WGM00) ));
			}
		}

		if (cfg->tc_num == 1)
		{
			// set force output compare to 0
			// stop the clock for now, no source
			TCONTROLREG(1, A) &= (~( _BV(FOC1A) | _BV(FOC1B) ));
			TCONTROLREG(1, B) &= (~( _BV(ICNC1) | _BV(ICES1) | _BV(CS12) | _BV(CS11) | _BV(CS10) ));

			if (cfg->tc_mode == MODE_FAST_PWM)
			{
				TCONTROLREG(1, A) |= ( _BV(WGM11) | _BV(WGM10) );
				TCONTROLREG(1, B) |= ( _BV(WGM13) | _BV(WGM12) );
			}

			if (cfg->tc_mode == MODE_NORMAL)
			{
				TCONTROLREG(1, A) &= (~( _BV(WGM11) | _BV(WGM10) ));
				TCONTROLREG(1, B) &= (~( _BV(WGM13) | _BV(WGM12) ));
			}
		}

		if (cfg->tc_num == 2)
		{
			// set force output compare to 0
			// stop the clock for now, no source
			TCONTROLREG(2, ) &= (~( _BV(FOC2) | _BV(CS22) | _BV(CS21) | _BV(CS20) ));

			if (cfg->tc_mode == MODE_FAST_PWM)
			{
				TCONTROLREG(2, ) |= ( _BV(WGM21) | _BV(WGM20) );
			}

			if (cfg->tc_mode == MODE_NORMAL)
			{
				TCONTROLREG(2, ) &= (~( _BV(WGM21) | _BV(WGM20) ));
			}
		}

		avr8b_tc_ocra_set(cfg->tc_num, cfg->ocra_val);
		avr8b_tc_ocrb_set(cfg->tc_num, cfg->ocrb_val);
		avr8b_tc_oca_int_set(cfg->tc_num, cfg->oca_int_on_off);
		avr8b_tc_ocb_int_set(cfg->tc_num, cfg->ocb_int_on_off);
		avr8b_tc_tov_int_set(cfg->tc_num, cfg->overflow_int_on_off);
		_avr8b_tc_oca_mode(cfg->tc_num, cfg->oca_mode);
		_avr8b_tc_ocb_mode(cfg->tc_num, cfg->ocb_mode);
	}
}

void avr8b_tc_start(uint8_t tc_num, AVR8B_TC_CLK_DIV clk_opt)
{
	avr8b_tc_clk_set(tc_num, clk_opt);
}

void avr8b_tc_stop(uint8_t tc_num)
{
	avr8b_tc_clk_set(tc_num, DIV_BY_INF);
}

void avr8b_tc_ocra_set(uint8_t tc_num, uint16_t ocra_val)
{
	switch (tc_num)
	{
		case 0:
			OCPREG(0, ) = (uint8_t)ocra_val;
			break;
		case 1:
			OCPREG(1, A) = ocra_val;
			break;
		case 2:
			OCPREG(2, ) = (uint8_t)ocra_val;
			break;
		default:
			break;
	}
}

void avr8b_tc_ocrb_set(uint8_t tc_num, uint16_t ocrb_val)
{
	if (tc_num != 1)
		return;
	OCPREG(1, B) = ocrb_val;
}

void avr8b_tc_deinit(uint8_t tc_num)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		avr8b_tc_stop(tc_num);
		avr8b_tc_oca_int_set(tc_num, 0);
		avr8b_tc_ocb_int_set(tc_num, 0);
		avr8b_tc_tov_int_set(tc_num, 0);

		if (tc_num == 0)
		{
			TCONTROLREG(0, ) = 0;
			//clear all pending counter interrupts
			TIFR &= (~( _BV(OCF0) | _BV(TOV0) ));
			TCNT(0) = 0;
			OCPREG(0, ) = 0;
		}

		if (tc_num == 1)
		{
			TCONTROLREG(1, A) = 0;
			TCONTROLREG(1, B) = 0;
			//clear all pending counter interrupts
			TIFR &= (~( _BV(OCF1A) | _BV(OCF1B) | _BV(TOV1) ));
			TCNT(1) = 0;
			OCPREG(1, A) = 0;
			OCPREG(1, B) = 0;
		}

		if (tc_num == 2)
		{
			TCONTROLREG(2, ) = 0;
			//clear all pending counter interrupts
			TIFR &= (~( _BV(OCF2) | _BV(TOV2) ));
			TCNT(2) = 0;
			OCPREG(2, ) = 0;
		}
	}
}

//interrupt handlers:

//t0
ISR(TIMER0_COMP_vect, ISR_BLOCK)
{
	avr8b_tc_oca_isr(0);
}

ISR(TIMER0_OVF_vect, ISR_BLOCK)
{
	avr8b_tc_tov_isr(0);
}

//t1
ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
	avr8b_tc_oca_isr(1);
}

ISR(TIMER1_COMPB_vect, ISR_BLOCK)
{
	avr8b_tc_ocb_isr(1);
}

ISR(TIMER1_OVF_vect, ISR_BLOCK)
{
	avr8b_tc_tov_isr(1);
}

//t2
ISR(TIMER2_COMP_vect, ISR_BLOCK)
{
	avr8b_tc_oca_isr(2);
}

ISR(TIMER2_OVF_vect, ISR_BLOCK)
{
	avr8b_tc_tov_isr(2);
}

#endif
