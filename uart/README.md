# About the uart subproject

Please read the [header](avr8b_uart.h) file and follow the instructions. Basically you have to define two functions in your program to handle interrupts (leave them empty if you will). Frequency definition and mcu type should be already set up in Makefile. You should also set the baud rate. There is also the [test application](test/avr8b_uart_test.c) just to check if everythong works ok.

# Supported MCUs

The number of supported devices will grow in time. For now these are on the table (it might work for you if mcu is similar):

  * ATMega8535
  * ...


