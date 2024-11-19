// keyboard.c
#include <string.h>   // For strlen
#include <UART_Driver.h>
#include <stdio.h>

void uart_print(char *str) {
    HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 10);  // UART transmit
}

void uart_int_print(int num) {
	char buffer[20];
	int len = sprintf(buffer, "%d", num);
	HAL_UART_Transmit(&huart2, (uint8_t*)buffer, len, 10);
}
