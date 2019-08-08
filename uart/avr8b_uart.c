/*
 * avr8buart.c
 *
 *  Created on: Jul 23, 2019
 *      Author: radek
 */

#include "avr8b_uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void avr8b_uart_setup_speed_and_frame(void);
void avr8b_uart_init(uint8_t rx_int_on_off, uint8_t tx_int_on_off)
{
	//disable interrupts for the time of the setup
	cli();

	avr8b_uart_setup_speed_and_frame();

	//enable receive/transmit complete interrupts
	avr8b_uart_rx_int_set(rx_int_on_off);
	avr8b_uart_tx_int_set(tx_int_on_off);

	//enable receiver and transmitter
	avr8b_uart_receiver_set(1);
	avr8b_uart_transmitter_set(1);

	//enable interrupts
	sei();
}


//interrupt handlers:
#ifdef __AVR_ATmega8535__
ISR(USART_RX_vect, ISR_BLOCK)
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please declare RX ISR"
#endif
{
#ifdef __AVR_ATmega8535__
	uint8_t error = 0;
	error = UCSRA & (_BV(FE) | _BV(DOR) | _BV(PE));
	int8_t tmp = UDR;
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please provide data receive procedure."
#endif
	avr8b_uart_receive_complete_isr(tmp, error);
}

#ifdef __AVR_ATmega8535__
ISR(USART_TX_vect, ISR_BLOCK)
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please declare TX ISR"
#endif
{
	avr8b_uart_transmit_complete_isr();
}

void avr8b_uart_deinit(void)
{
	//disable interrupts for the time of the deactivation
	cli();

	//disable receive/transmit complete interrupts
	avr8b_uart_rx_int_set(0);
	avr8b_uart_tx_int_set(0);

	//disable receiver and transmitter
	avr8b_uart_receiver_set(0);
	avr8b_uart_transmitter_set(0);

	//enable interrupts
	sei();
}


void avr8b_uart_rx_int_set(uint8_t on_off)
{
	if (on_off)
#ifdef __AVR_ATmega8535__
		UCSRB |= _BV(RXCIE);
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please provide receiver interrupt enable bit and register."
#endif
	else
#ifdef __AVR_ATmega8535__
		UCSRB &= ~(_BV(RXCIE));
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please provide receiver interrupt disable bit and register."
#endif
}

void avr8b_uart_tx_int_set(uint8_t on_off)
{
	if (on_off)
#ifdef __AVR_ATmega8535__
		UCSRB |= _BV(TXCIE);
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please provide transmitter interrupt enable bit and register."
#endif
	else
#ifdef __AVR_ATmega8535__
		UCSRB &= ~(_BV(TXCIE));
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please provide transmitter interrupt disable bit and register."
#endif
}

void avr8b_uart_receiver_set(uint8_t on_off)
{
	if (on_off)
	{
#ifdef __AVR_ATmega8535__
		UCSRB |= _BV(RXEN);
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please provide receiver enable bit and register."
#endif
	}
	else
#ifdef __AVR_ATmega8535__
		UCSRB &= ~(_BV(RXEN));
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please provide receiver disable bit and register."
#endif
}

void avr8b_uart_transmitter_set(uint8_t on_off)
{
	if (on_off)
#ifdef __AVR_ATmega8535__
		UCSRB |= _BV(TXEN);
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please provide transmitter enable bit and register."
#endif
	else
#ifdef __AVR_ATmega8535__
		UCSRB &= ~(_BV(TXEN));
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please provide transmitter disable bit and register."
#endif
}

void avr8b_uart_setup_speed_and_frame(void)
{
#ifdef __AVR_ATmega8535__
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
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please provide UART speed and frame setup routine."
#endif
}

void avr8b_uart_write(int8_t b)
{
#ifdef __AVR_ATmega8535__
	loop_until_bit_is_set(UCSRA, UDRE);
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please provide UART transmitter ready flag."
#endif
	UDR = b;
}

uint8_t avr8b_uart_read(uint8_t *b)
{
	uint8_t error = 0;
#ifdef __AVR_ATmega8535__
	loop_until_bit_is_set(UCSRA, RXC);
	error = UCSRA & (_BV(FE) | _BV(DOR) | _BV(PE));
#else
	#error "AVR8b UART - Your MCU is not supported yet. Please provide UART receiver data ready flag."
#endif
	*b = UDR;
	return error;
}
