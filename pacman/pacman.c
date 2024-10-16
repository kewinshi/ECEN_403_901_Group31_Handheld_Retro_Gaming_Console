#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#define COLS 17
#define ROWS 19

int main() {
  // ANSI escape code to hide cursor
  // printf("\e[?25l");

  // Switch to canonical mode, disable echo
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);


  // map state
  char map[ROWS][COLS];

  int x[1000], y[1000];
  int quit = 0;
  while (!quit) {
    // Render table

    // Top border 
    for (int i = 0; i < COLS + 2; i++)
      printf("▓");
    printf("\n");

    // Inside content
    for (int j = 0; j < ROWS; j++) {

      // Left Border
      printf("▓");


      for (int i = 0; i < COLS; i++)
        // drawing dots and walls

        if (j == 0 && i == 8) {
          printf("▓");
          map[j][i] = '#';
        } 
        
        else if (j == 1 && (i == 1 || i == 2 || i == 4 || i == 5 || i == 6 || i == 8 || i == 10 || i == 11 || i == 12 || i == 14 || i == 15)) {
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 3 && (i == 1 || i == 2 || i == 4 || i == 6 || i == 7 || i == 8 ||i == 9 || i == 10 || i == 12 || i == 14 || i == 15)) {
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 4 && (i == 4 || i == 8 || i == 12 )) {
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 5 && (i == 0 || i == 1 || i == 2  || i == 4 || i == 5 || i == 6 || i == 8 || i == 10 || i == 11 || i == 12 || i == 14 || i == 15 || i == 16)) {
          printf("▓");
          map[j][i] = '#';
        }
        
        else if (j == 6 && (i == 0 || i == 1 || i == 2  || i == 4 || i == 12 || i == 14 || i == 15 || i == 16)) {
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 7 && (i == 0 || i == 1 || i == 2  || i == 4 || i == 6 || i == 7 || i == 9 ||i == 10 || i == 12 || i == 14 || i == 15 || i == 16)) {
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 8 && (i == 6 || i == 10 )) { // center
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 9 && (i == 0 || i == 1 || i == 2  || i == 4 || i == 6 || i == 7 || i == 8 || i == 9 ||i == 10 || i == 12 || i == 14 || i == 15 || i == 16)) {
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 10 && (i == 0 || i == 1 || i == 2  || i == 4 || i == 12 || i == 14 || i == 15 || i == 16)) {
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 11 && (i == 0 || i == 1 || i == 2  || i == 4 || i == 6 || i ==7 || i == 8 || i == 9 || i == 10 || i == 12 || i == 14 || i == 15 || i == 16)) {
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 12 && i == 8) {
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 13 && (i == 1 || i == 2 || i == 4 || i == 5 || i == 6 || i == 8 || i == 10 || i == 11 || i == 12 || i == 14 || i == 15)) {
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 14 && (i == 2 || i == 14)) {
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 15 && (i == 0 || i == 2 || i == 4 || i == 6 || i == 7 || i == 8 || i == 10  || i == 12 || i == 14 || i == 16)) {
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 16 && (i == 4 || i == 12)) {
          printf("▓");
          map[j][i] = '#';
        }

        else if (j == 17 && (i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 8 || i == 10 || i == 11 || i == 12 || i == 13 || i == 14 || i == 15)) {
          printf("▓");
          map[j][i] = '#';
        }

        else {
          printf(".");
          map[j][i] = '.';
        }

        
        // if ((i % 5) == 0 || (j % 5) == 0) {
        //     printf(".");
        //     map[j][i] = '.';
        // } else {
        //     printf("▓");
        //     map[j][i] = '#';
        // }


      // Right border
      printf("▓\n");
    }

    // Bottom border
    for (int i = 0; i < COLS + 2; i++)
      printf("▓");
    printf("\n");

    // Move cursor back to top
    printf("\e[%iA", ROWS + 2);

    int head = 0, tail = 0;
    int x = 8;
    int y = 8;
    int gameover = 0;
    int xdir = 1, ydir = 0;
    int stop = 0;

    while (!quit && !gameover) {
      int next_x = (x + xdir + COLS) % COLS;
      int next_y = (y + ydir + ROWS) % ROWS;

      if (map[next_y][next_x] != '#') {
        // Clear previous
        printf("\e[%iB\e[%iC ", y + 1, x + 1);
        printf("\e[%iF", y + 1);

        tail = (tail + 1) % 1000;

        int newhead = (head + 1) % 1000;
        x = (x + xdir + COLS) % COLS;
        y = (y + ydir + ROWS) % ROWS;
        head = newhead;

        // Draw head
        printf("\e[%iB\e[%iCo", y + 1, x + 1);
        printf("\e[%iF", y + 1);
        fflush(stdout);
      } else {
        // to-do:
      }


      usleep(15 * 1000000 / 60); // can modify game speed

      // Read keyboard
      struct timeval tv;
      fd_set fds;
      tv.tv_sec = 0;
      tv.tv_usec = 0;

      FD_ZERO(&fds);
      FD_SET(STDIN_FILENO, &fds);
      select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
      if (FD_ISSET(STDIN_FILENO, &fds)) {
        int ch = getchar();
        if (ch == 27 || ch == 'q') {
          quit = 1;
        } else if (ch == 'a') {
          xdir = -1;
          ydir = 0;
        } else if (ch == 'd') {
          xdir = 1;
          ydir = 0;
        } else if (ch == 's') {
          xdir = 0;
          ydir = 1;
        } else if (ch == 'w') {
          xdir = 0;
          ydir = -1;
        }
      }
    }

    if (!quit) {
      // Show game over
      printf("\e[%iB\e[%iC Game Over! ", ROWS / 2, COLS / 2 - 5);
      printf("\e[%iF", ROWS / 2);
      fflush(stdout);
      getchar();
    }
  }

  // Show cursor
  printf("\e[?25h");

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return 0;
}