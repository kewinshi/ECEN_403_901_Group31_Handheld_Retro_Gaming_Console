#include "Input.h"
#include "stm32f1xx_hal.h"  // Includes the HAL library
#include "main.h"           // Includes project-specific definitions (like LD2_GPIO_Port)

// implement can't go backwards logic here
void get_input(int *curr_input, int *prev_input, int *game_select) {
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) == GPIO_PIN_SET) // w
	{
		//		uart_print("pin 7 is HIGH");
		*prev_input = *curr_input;
		*curr_input = 0;
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1); // test with LED
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET) //a
	{
		//		uart_print("pin 8 is HIGH");
		*prev_input = *curr_input;
		*curr_input = 1;
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_SET) //s
	{
		//		uart_print("pin 9 is HIGH");
		*prev_input = *curr_input;
		*curr_input = 2;
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_SET) //d
	{
		//		uart_print("pin 10 is HIGH");
		*prev_input = *curr_input;
		*curr_input = 3;
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6) == GPIO_PIN_SET) // quit
	{
//				uart_print("pin 6 is HIGH");
		*game_select = -1;
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
	}
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == GPIO_PIN_SET) // select
	{
//				uart_print("pin 4 is HIGH");
		*game_select = 1;
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
	}
	else {
		*curr_input = -1;
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);
		//		uart_print("no pin is HIGH");
	}
}
