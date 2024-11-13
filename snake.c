#include "snake.h"
#include "main.h"
#include <stdio.h>
#include <time.h>
#include <input.h>

void play_snake(int ROWS, int COLS) {
	uart_print("\x1b[H"); // Brings cursor to original position
	uart_print("\e[2J");  // Clears the entire screen
	draw_snake_map(ROWS, COLS);
	srand(time(NULL));


	int curr_input = -1, prev_input = -1, game_select = 1;
	int xdir = 1;
	int ydir = 0;
	int apple_x = -1;
	int apple_y = 1;
	int x[1000], y[1000];
	int head = 0, tail = 0;
	x[head] = COLS / 2;
	y[head] = ROWS / 2;
	apple_x = rand() % COLS;
	apple_y = rand() % ROWS;
	while (game_select == 1)
	{

		/* USER CODE BEGIN 3 */
		get_input(&curr_input, &prev_input, &game_select);
		if (curr_input == 0) { // W
			xdir = 0;
			ydir = -1;
		}
		else if (curr_input == 1) { // A
			xdir = -1;
			ydir = 0;
		}
		else if (curr_input == 2) { // S
			xdir = 0;
			ydir = 1;
		}
		else if (curr_input == 3) { // D
			xdir = 1;
			ydir = 0;
		}
		HAL_Delay(250);

		if (apple_x < 0) {
			apple_x = rand() % COLS;
			apple_y = rand() % ROWS;
		}
		draw_apple(&apple_x, &apple_y);
		move_snake(ROWS, COLS, x, y, &head, &tail, &apple_x, &apple_y, &xdir, &ydir);
	}
}
void draw_snake_map(int ROWS, int COLS) {
//		uart_print("\e[2J"); // erase display
//		uart_print("\e[s"); // save cursor position
//
//	    uart_print("\e[u"); // move cursor to original position
		uart_print("\e[?25l"); // hide cursor
	    // Render table
	    uart_print("┌");
	    for (int i = 0; i < COLS; i++)
	      uart_print("─");
	    uart_print("┐\r\n");

	    for (int j = 0; j < ROWS; j++) {
	      uart_print("│");
	      for (int i = 0; i < COLS; i++)
	        uart_print(" ");
	      uart_print("│\r\n");
	    }

	    uart_print("└");
	    for (int i = 0; i < COLS; i++)
	      uart_print("─");
	    uart_print("┘\r\n");

	    // Move cursor back to top
//	    uart_print("\e[%iA", ROWS + 2);
	    char buffer[20];
	    sprintf(buffer, "\e[%dA", ROWS + 2); // ROWS + 2 for the top and bottom borders
	    uart_print(buffer);
}

void draw_apple(int *apple_x, int *apple_y) {

	char buffer[50];  // Ensure this buffer is large enough for the output
	sprintf(buffer, "\e[%dB\e[%dC@", *apple_y + 1, *apple_x + 1);
	uart_print(buffer);
	sprintf(buffer, "\e[%dF", *apple_y + 1);
	uart_print(buffer);
}

void move_snake (int ROWS, int COLS, char x[], char y[], int *head, int *tail, int *apple_x, int *apple_y, int *xdir, int *ydir) {
	// Clear snake tail
	char buffer[50];
	sprintf(buffer, "\e[%dB\e[%dC ", y[*tail] + 1, x[*tail] + 1);
	uart_print(buffer);
	sprintf(buffer, "\e[%dF", y[*tail] + 1);
	uart_print(buffer);

	if (x[*head] == *apple_x && y[*head] == *apple_y) {
		*apple_x = -1;
	}
	else {
		*tail = (*tail + 1) % 1000;
	}

	int newhead = (*head + 1) % 1000;
	x[newhead] = (x[*head] + *xdir + COLS) % COLS;
	y[newhead] = (y[*head] + *ydir + ROWS) % ROWS;
	*head = newhead;
	sprintf(buffer, "\e[%dB\e[%dCo", y[*head] + 1, x[*head] + 1);
	uart_print(buffer);
	sprintf(buffer, "\e[%dF", y[*head] + 1);
	uart_print(buffer);

}
