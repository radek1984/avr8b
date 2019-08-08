/*
 * avr8b_uart.h
 *
 *  Created on: Jul 23, 2019
 *      Author: radek
 *
 *  Simple UART code. This code uses interrupts. To be used with Eclipse AVR plugin.
 *  Synchronous mode is not supported yet. Define your configuration here.
 */

#ifndef UART_AVR8B_UART_H_
#define UART_AVR8B_UART_H_

#include <stdint.h>

/* Please define your configuration in the following section: */

/*-------------------------- CONFIGURATION ------------------------------*/

// This one should come from eclipse plugin
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

#ifndef BAUD
	#define BAUD 57600
#endif


// These are the currently supported AVRs:
#ifndef __AVR_ATmega8535__
	#error "AVR8b UART - Your MCU is not supported yet"
#endif

#include <util/setbaud.h>

// Define these somewhere in your code. These will be called from ISR context. error > 0 indicates receive problem.
extern void avr8b_uart_receive_complete_isr(int8_t b, uint8_t error);
extern void avr8b_uart_transmit_complete_isr(void);

/*---------------------- CONFIGURATION END ------------------------------*/


/*----------------------------- API -------------------------------------*/


/**************** Convenience configuration functions ****************/

// This one turns on the global interrupts flag. Turns on Receiver and Transmitter.
// Gives you the option to turn on or off rx/tx interrupts
void avr8b_uart_init(uint8_t rx_int_on_off, uint8_t tx_int_on_off);
// Shuts down receiver and transmitter as well as tx/rx interrupts
void avr8b_uart_deinit(void);

/******************* Fine configuration functions: *******************/

// 1 - turns the interrupt on, 0 - turns it off
void avr8b_uart_rx_int_set(uint8_t on_off);
void avr8b_uart_tx_int_set(uint8_t on_off);

// 1 - turns the module on, 0 - turns it off
void avr8b_uart_receiver_set(uint8_t on_off);
void avr8b_uart_transmitter_set(uint8_t on_off);

/******************************** R/W ********************************/

// Reads a single byte from UDR. Waits for available data in the receiver. Returns positive number if there was an error.
uint8_t avr8b_uart_read(uint8_t *b);
//Writes a single byte to UDR. Waits for the transmitter buffer to be ready before sending.
void avr8b_uart_write(int8_t b);


/*----------------------------- API END ---------------------------------*/

#endif /* UART_AVR8B_UART_H_ */
