// keyboard.h
#ifndef UART_Driver_H
#define UART_Driver_H

#include "main.h"    // Include main.h for the UART handle definition

extern UART_HandleTypeDef huart2;  // Declare huart2 as an external variable

void uart_print(char *str);

#endif /* KEYBOARD_H */
