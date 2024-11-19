#include "pacman.h"
#include "main.h"
void play_pacman (int ROWS, int COLS) {
	uart_print("\x1b[H"); // Brings cursor to original position
	uart_print("\e[2J");  // Clears the entire screen
	draw_snake_map(ROWS, COLS);

	int curr_input = -1, prev_input = -1, game_select = 1;
	int xdir = 1;
	int ydir = 0;
	int x[1000], y[1000];
	int head = 0, tail = 0;
	x[head] = COLS / 2;
	y[head] = ROWS / 2;
	char map_pacman[ROWS][COLS];

	draw_pacman_map(ROWS, COLS, map_pacman);
	while (game_select == 1) {
		for (int i = 0; i < 5; i += 1) {
			get_input(&curr_input, &prev_input, &game_select);
			// Update movement direction based on input
			if (curr_input == 0) {  // W key for up
				xdir = 0;
				ydir = -1;
			} else if (curr_input == 1) {  // A key for left
				xdir = -1;
				ydir = 0;
			} else if (curr_input == 2) {  // S key for down
				xdir = 0;
				ydir = 1;
			} else if (curr_input == 3) {  // D key for right
				xdir = 1;
				ydir = 0;
			}
			HAL_Delay(50);
		}
//		HAL_Delay(250);  // Game speed control

		// Move Pac-Man based on direction and check for walls
		move_pacman(ROWS, COLS, x, y, &head, &tail, &xdir, &ydir, map_pacman);
	}
}

void move_pacman (int ROWS, int COLS, char x[], char y[], int *head, int *tail, int *xdir, int *ydir, char map_pacman[ROWS][COLS]) {
	int next_x = (x[*head] + *xdir + COLS) % COLS;
	int next_y = (y[*head] + *ydir + ROWS) % ROWS;
	if (map_pacman[next_y][next_x] != '#') {
		// Clear previous position
		char buffer[50];
		sprintf(buffer, "\e[%dB\e[%dC ", y[*tail] + 1, x[*tail] + 1);
		uart_print(buffer);
		sprintf(buffer, "\e[%dF", y[*tail] + 1);
		uart_print(buffer);

		*tail = (*tail + 1) % 1000;  // Move tail forward

		// Update head position to the new location
		int newhead = (*head + 1) % 1000;
		x[newhead] = next_x;
		y[newhead] = next_y;
		*head = newhead;

		// Draw Pac-Man's new head position
		sprintf(buffer, "\e[%dB\e[%dCo", y[*head] + 1, x[*head] + 1);
		uart_print(buffer);
		sprintf(buffer, "\e[%dF", y[*head] + 1);
		uart_print(buffer);
	}
}
void draw_pacman_map(int ROWS, int COLS, char map[ROWS][COLS]) {
	uart_print("\e[?25l");
//	uart_print("\e[2J"); // erase display
	for (int i = 0; i < COLS + 2; i++) {
		  		  uart_print("▓");
		  	  }

		  	  uart_print("\r\n");
		  	  // Inside content
		  	  for (int j = 0; j < ROWS; j++) {

		  	    // Left Border
		  	    uart_print("▓");


		  	    for (int i = 0; i < COLS; i++)
		  	      // drawing dots and walls

		  	      if (j == 0 && i == 8) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 1 && (i == 1 || i == 2 || i == 4 || i == 5 || i == 6 || i == 8 || i == 10 || i == 11 || i == 12 || i == 14 || i == 15)) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 3 && (i == 1 || i == 2 || i == 4 || i == 6 || i == 7 || i == 8 ||i == 9 || i == 10 || i == 12 || i == 14 || i == 15)) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 4 && (i == 4 || i == 8 || i == 12 )) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 5 && (i == 0 || i == 1 || i == 2  || i == 4 || i == 5 || i == 6 || i == 8 || i == 10 || i == 11 || i == 12 || i == 14 || i == 15 || i == 16)) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 6 && (i == 0 || i == 1 || i == 2  || i == 4 || i == 12 || i == 14 || i == 15 || i == 16)) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 7 && (i == 0 || i == 1 || i == 2  || i == 4 || i == 6 || i == 7 || i == 9 ||i == 10 || i == 12 || i == 14 || i == 15 || i == 16)) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 8 && (i == 6 || i == 10 )) { // center
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 9 && (i == 0 || i == 1 || i == 2  || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 ||i == 10 || i == 12 || i == 14 || i == 15 || i == 16)) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 10 && (i == 0 || i == 1 || i == 2  || i == 4 || i == 12 || i == 14 || i == 15 || i == 16)) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 11 && (i == 0 || i == 1 || i == 2  || i == 4 || i == 6 || i ==7 || i == 8 || i == 9 || i == 10 || i == 12 || i == 14 || i == 15 || i == 16)) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 12 && i == 8) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 13 && (i == 1 || i == 2 || i == 4 || i == 5 || i == 6 || i == 8 || i == 10 || i == 11 || i == 12 || i == 14 || i == 15)) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 14 && (i == 2 || i == 14)) {
		  	    	 uart_print("▓");
		  	    	 map[j][i] = '#';
		  	      }

		  	      else if (j == 15 && (i == 0 || i == 2 || i == 4 || i == 6 || i == 7 || i == 8 || i == 10  || i == 12 || i == 14 || i == 16)) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 16 && (i == 4 || i == 12)) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else if (j == 17 && (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 8 || i == 10 || i == 11 || i == 12 || i == 13 || i == 14 || i == 15)) {
		  	        uart_print("▓");
		  	        map[j][i] = '#';
		  	      }

		  	      else {
		  	        uart_print(".");
		  	        map[j][i] = '.';
		  	      }
		  	        // Right border
		  	        uart_print("▓\r\n");
		  	      }

		  	      // Bottom border
		  	  for (int i = 0; i < COLS + 2; i++) {
		  		uart_print("▓");
		  	  }
		  	  uart_print("\n");

		  	  // Move cursor back to top
		  //	  uart_print("\e[%iA", ROWS + 2);
	//	  	  HAL_Delay(2000);
		  	  uart_print("\e[H"); // move cursor to original position
}

