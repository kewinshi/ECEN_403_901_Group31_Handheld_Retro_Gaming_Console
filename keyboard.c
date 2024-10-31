// keyboard.c
#include "keyboard.h"
#include <string.h>   // For strlen

char read_keyboard() {
//    char key;
//    HAL_UART_Receive(&huart2, (uint8_t*)&key, 1, HAL_MAX_DELAY);  // TO-Do make unblocking
//    return key;
}

void uart_print(char *str) {
    HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), 10);  // UART transmit
}
