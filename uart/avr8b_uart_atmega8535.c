/*
 * avr8buart.c
 *
 *  Created on: Jul 23, 2019
 *      Author: radek
 */

#ifdef __AVR_ATmega8535__

#include "avr8b_uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/atomic.h>

void avr8b_uart_setup_speed_and_frame(void);
void avr8b_uart_init(uint8_t rx_int_on_off, uint8_t tx_int_on_off)
{
	//make sure no interrupts will affect the setup
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		avr8b_uart_setup_speed_and_frame();

		//enable receive/transmit complete interrupts
		avr8b_uart_rx_int_set(rx_int_on_off);
		avr8b_uart_tx_int_set(tx_int_on_off);

		//enable receiver and transmitter
		avr8b_uart_receiver_set(1);
		avr8b_uart_transmitter_set(1);
	}
}


//interrupt handlers:
ISR(USART_RX_vect, ISR_BLOCK)
{
	uint8_t error = 0;
	error = UCSRA & (_BV(FE) | _BV(DOR) | _BV(PE));
	int8_t tmp = UDR;

	avr8b_uart_receive_complete_isr(tmp, error);
}

ISR(USART_TX_vect, ISR_BLOCK)
{
	avr8b_uart_transmit_complete_isr();
}

void avr8b_uart_deinit(void)
{
	loop_until_bit_is_set(UCSRA, UDRE);
	loop_until_bit_is_set(UCSRA, TXC);
	//make sure no interrupts will affect deactivation
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		//disable receive/transmit complete interrupts
		avr8b_uart_rx_int_set(0);
		avr8b_uart_tx_int_set(0);

		//disable receiver and transmitter
		avr8b_uart_receiver_set(0);
		avr8b_uart_transmitter_set(0);
	}
}


void avr8b_uart_rx_int_set(uint8_t on_off)
{
	if (on_off)
		UCSRB |= _BV(RXCIE);
	else
		UCSRB &= ~(_BV(RXCIE));
}

void avr8b_uart_tx_int_set(uint8_t on_off)
{
	if (on_off)
		UCSRB |= _BV(TXCIE);
	else
		UCSRB &= ~(_BV(TXCIE));
}

void avr8b_uart_receiver_set(uint8_t on_off)
{
	if (on_off)
		UCSRB |= _BV(RXEN);
	else
		UCSRB &= ~(_BV(RXEN));
}

void avr8b_uart_transmitter_set(uint8_t on_off)
{
	if (on_off)
		UCSRB |= _BV(TXEN);
	else
		UCSRB &= ~(_BV(TXEN));
}

void avr8b_uart_setup_speed_and_frame(void)
{
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	//always set frame, overrun and parity errors bits to 0 in UCSRA
#if USE_2X
	UCSRA = (UCSRA | _BV(U2X)) & ~((_BV(FE) | _BV(DOR) | _BV(PE)));
#else
	UCSRA &= ~(_BV(U2X) | (_BV(FE) | _BV(DOR) | _BV(PE)));
#endif
	//8b character
	UCSRB &= ~(_BV(UCSZ2));

			//access UCSRC 		//8b character 			 	//odd parity
	UCSRC = (_BV(URSEL) | 		_BV(UCSZ0) | _BV(UCSZ1)  | 	_BV(UPM1) | _BV(UPM0))

			//asynchronous    //1 stop bit
			& (~(_BV(UMSEL) | _BV(USBS)));
}

void avr8b_uart_write(int8_t b)
{
	loop_until_bit_is_set(UCSRA, UDRE);
	UDR = b;
}

uint8_t avr8b_uart_read(uint8_t *b)
{
	uint8_t error = 0;
	loop_until_bit_is_set(UCSRA, RXC);
	error = UCSRA & (_BV(FE) | _BV(DOR) | _BV(PE));

	*b = UDR;
	return error;
}

#endif // __AVR_ATmega8535__
