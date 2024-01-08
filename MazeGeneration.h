#ifndef MAZEGENERATION_H
#define MAZEGENERATION_H


#define MAX_ROWS 10
#define MAX_COLS 10
#define ZXDJ 10
#define XXDJ 14

#define H 10
#define L 10

#define WALL 1
#define PATH 0

int rows, cols; // 迷宫的行数和列数
int startRow, startCol; // 起点的坐标
int maze[MAX_ROWS][MAX_COLS];
int res[MAX_ROWS][MAX_COLS];
int ori[MAX_ROWS][MAX_COLS];
int path[MAX_ROWS * MAX_COLS][2];
extern int pathCount;

void clearInputBuffer();
void init();
void printMaze();
int Safe(int x, int y);
void generateMaze(int x, int y);
void exitandentry();

#endif
