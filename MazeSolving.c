#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <MazeSolving.h>
#include <MazeGeneration.h>



// 定义方向数组，用于探索上、下、左、右四个方向
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void res_init()  //将结果数组用数据数组覆盖，回归空白迷宫状态
{
    for(int i=0;i<rows;++i)
    {
        for(int j=0;j<cols;++j)
        {
            res[i][j] = ori[i][j];
        }
    }
}

// 检查坐标是否在迷宫范围内
int isValid(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}


// 深度优先搜索函数
void dfs(int x, int y) 
{
    // 如果坐标越界或者当前位置是墙或者已经访问过，返回
    if (!isValid(x, y) || maze[x][y] == 1 || maze[x][y] == -1) {
        return;
    }

    // 如果当前位置是终点，输出一条解的路径
    if (maze[x][y] == 2) {
        res_init();//初始化结果数组
        // 存储当前路径
        for (int i = 0; i < pathCount; ++i) {
            res[path[i][0]][path[i][1]]= 3;
        }
        res[x][y]= 3;
         for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (res[i][j] == 3) {
                    printf("P "); // 输出路径
                } else if (res[i][j] == 1) {
                    printf("1 "); // 输出墙
                } else {
                    printf("0 "); // 输出其他位置
                }
            }
            printf("\n");
        }
        printf("\n");
        pathCount++;
        return;
    }

    // 标记当前位置已经访问过
    maze[x][y] = -1;
    
    // 存储当前位置到路径数组
    path[pathCount][0] = x;
    path[pathCount][1] = y;
    pathCount++;

    // 尝试在四个方向上进行DFS
    for (int i = 0; i < 4; ++i) {
        int nextX = x + directions[i][0];
        int nextY = y + directions[i][1];

        // 递归调用DFS
        dfs(nextX, nextY);
    }

    // 回溯，取消标记当前位置为已访问过
    maze[x][y] = 0;
    pathCount--;
}



void menu()
{
    printf("选择所需的功能：\n");
    printf("迷宫生成：          1\n");
    printf("迷宫求解：          2\n");
    printf("迷宫生成与自动求解: 3\n");
    printf("退出：              4\n");
}