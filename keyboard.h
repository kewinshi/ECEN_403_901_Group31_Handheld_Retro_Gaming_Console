// keyboard.h
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "main.h"    // Include main.h for the UART handle definition

extern UART_HandleTypeDef huart2;  // Declare huart2 as an external variable

char read_keyboard();
void uart_print(char *str);

#endif /* KEYBOARD_H */
