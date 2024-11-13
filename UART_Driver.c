// keyboard.c
#include <string.h>   // For strlen
#include <UART_Driver.h>

void uart_print(char *str) {
    HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 10);  // UART transmit
}
