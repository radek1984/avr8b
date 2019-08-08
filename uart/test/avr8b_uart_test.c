/*
 * avr8b_uart_test.c
 *
 *  Created on: Jul 23, 2019
 *      Author: radek
 */

#include "../avr8b_uart.h"
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

int16_t error_count = 0;
void avr8b_uart_receive_complete_isr(int8_t b, uint8_t error)
{
	avr8b_uart_write(b);
	if(error)
		error_count++;
}

uint8_t tx_arr[]= {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
int tx_ix = 1;
void avr8b_uart_transmit_complete_isr(void)
{
	if (tx_ix < sizeof(tx_arr))
	{
		avr8b_uart_write(tx_arr[tx_ix]);
		tx_ix++;
	}
}

int main()
{
	uint8_t recv;
	//disable interrupts for now
	avr8b_uart_init(0, 0);

	const char *test1 = "Echo test. Send 10 characters from PC to AVR\r\n";
	for(int i = 0; i < strlen(test1); i++)
		avr8b_uart_write(*(test1 + i));

	for (int i = 0; i < 10; i++)
	{
		if(avr8b_uart_read(&recv) != 0) error_count++;
		avr8b_uart_write(recv);
	}
	const char *test1b = "\r\nError count: ";
	for(int i = 0; i < strlen(test1b); i++)
		avr8b_uart_write(*(test1b + i));

	char err_str[10];
	itoa(error_count, err_str, 10);
	for(int i = 0; i < strlen(err_str); i++)
		avr8b_uart_write(*(err_str + i));

	avr8b_uart_deinit();
	avr8b_uart_init(0, 0);

	const char *test2 = "\r\nSending 15 chars to PC using TX interrupt\r\n";
	for(int i = 0; i < strlen(test2); i++)
		avr8b_uart_write(*(test2 + i));
	avr8b_uart_tx_int_set(1);
	avr8b_uart_write(tx_arr[0]);
	_delay_ms(1000.0);

	const char *test3 = "\r\nMaking echo on interrupts available for 10 seconds\r\n";
	error_count = 0;
	for(int i = 0; i < strlen(test3); i++)
		avr8b_uart_write(*(test3 + i));

	//clear rx buffer by turning it of and on again
	avr8b_uart_receiver_set(0);
	avr8b_uart_receiver_set(1);
	avr8b_uart_rx_int_set(1);
	_delay_ms (10000.0);
	avr8b_uart_rx_int_set(0);
	//show error count
	for(int i = 0; i < strlen(test1b); i++)
		avr8b_uart_write(*(test1b + i));
	itoa(error_count, err_str, 10);
	for(int i = 0; i < strlen(err_str); i++)
		avr8b_uart_write(*(err_str + i));

	const char *test4 = "\r\nDisabling library for 5 seconds to check if it will initialize properly again. Try to sending something now. \r\n";
	for(int i = 0; i < strlen(test4); i++)
		avr8b_uart_write(*(test4 + i));

	avr8b_uart_deinit();
	_delay_ms (5000.0);

	avr8b_uart_init(1, 0);
	const char *test4b = "On again\r\n";
	for(int i = 0; i < strlen(test4b); i++)
		avr8b_uart_write(*(test4b + i));

	while(1)
	{
	}
	return 0;
}
