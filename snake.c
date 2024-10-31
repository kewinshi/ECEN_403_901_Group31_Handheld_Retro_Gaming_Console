#include "snake.h"
#include "main.h"
#include <stdio.h>
#include <time.h>

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

void draw_apple(int ROWS, int COLS, char x[], char y[], int head, int tail, int *apple_x, int *apple_y) {
//	for (int i = tail; i != head; i = (i + 1) % 1000) {
//		if (x[i] == *apple_x && y[i] == *apple_y) {
//			*apple_x = rand() % COLS;
//			*apple_y = rand() % ROWS;
//		}
//	}
//	*apple_x = rand() % COLS;
//	*apple_y = rand() % ROWS;

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
