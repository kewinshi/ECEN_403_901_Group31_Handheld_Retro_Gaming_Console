#include "pacman.h"
#include "main.h"

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
