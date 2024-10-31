// snake.h
#ifndef SNAKE_H
#define SNAKE_H

void draw_snake_map(int rows, int cols);  // Declaration for snake map function

void draw_apple(int ROWS, int COLS, char x[], char y[], int head, int tail, int *apple_x, int *apple_y);

void move_snake(int ROWS, int COLS, char x[], char y[], int *head, int *tail, int *apple_x, int *apple_y, int *xdir, int *ydir);
#endif /* SNAKE_H */
