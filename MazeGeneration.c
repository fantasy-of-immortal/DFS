#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <MazeGeneration.h>


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int maze[H][L];

void init() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < L; j++) {
            maze[i][j] = WALL; // 初始化迷宫为墙
        }
    }
}

void printMaze() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < L; j++) {
            if (maze[i][j] == WALL) {
                printf("1 "); // 墙
            } else if (maze[i][j] == PATH) {
                printf("0 "); // 路径
            } else if (maze[i][j] == 0) {
                printf("0 "); // 入口
            } else if (maze[i][j] == 2) {
                printf("2 "); // 出口
            }
        }
        printf("\n");
    }
}

int Safe(int x, int y) {
    return (x >= 0 && x < H && y >= 0 && y < L && maze[x][y] == WALL);
}

void generateMaze(int x, int y) {
    maze[x][y] = PATH; // 将当前位置标记为路径

    // 定义上下左右四个方向
    int dx[] = {1, -1, 0, 0};// 1为向右，-1为向左
    int dy[] = {0, 0, 1, -1};//-1为向上，1为向下

    // 打乱方向
    for (int i = 0; i < 4; i++) {
        int random_index = rand() % 4;
        int temp = dx[i];//随机交换值，数组0-1里的数表示该次移动的方向
        dx[i] = dx[random_index];
        dx[random_index] = temp;//完成值传递，使得左右随机探索

        temp = dy[i];//完成Y值传递，使随机上下移动
        dy[i] = dy[random_index];
        dy[random_index] = temp;
    }

    // 按随机顺序探索四个方向
    for (int i = 0; i < 4; i++) {
        int X1 = x + dx[i] *2;//向左或右探索2个试探边界
        int Y1= y + dy[i]*2 ;//向上或下探索2个试探边界

        if (Safe(X1, Y1)) {
            maze[X1][Y1] = PATH;
            maze[x + dx[i]][y + dy[i]] = PATH;//打破墙命为路
            generateMaze(X1, Y1);
        }
    }
}

void exitandentry(){
    int entrance = rand()%(L-2)+1;
    int exit = rand()%(L-2)+1;
    maze[0][entrance] = 0;
    maze[H-1][exit] = 2;
    startRow =0;
    startCol =entrance;
}

