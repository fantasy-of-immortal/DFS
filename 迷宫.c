#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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
int pathCount = 0;


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

int main() 
{
    int choice =0;
    while(1)
    {
        menu();
        scanf("%d",&choice);
        if(choice == 1)
        {    
            srand(time(NULL));

            init(); // 初始化迷宫
            generateMaze(0,maze[0][0]);
            exitandentry();
            // 打印迷宫
            printMaze();
            printf("\n");
        }
        else if(choice == 2)
        {
                // 用户输入迷宫的行数和列数
            printf("请给出所解迷宫的行数和列数 (不大于 %d): ", MAX_ROWS);
            scanf("%d %d", &rows, &cols);
            pathCount = 0; 
            // 用户输入迷宫的元素
            printf("请输入求解迷宫 (0代表可走路径，1代表迷宫墙体，2代表终点):\n");
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    scanf("%d", &maze[i][j]);
                }
            }       

            // 用户输入起点的坐标
            printf("请给出起始点 (坐标): ");
            scanf("%d %d", &startRow, &startCol);

            //数据数组初始化
            for(int i=0;i<rows;++i)
            {
                for(int j=0;j<cols;++j)
                {
                    ori[i][j] = maze[i][j];
                }
            }
            // 从指定起点开始尝试DFS
            dfs(startRow, startCol);

            if (pathCount == 0) 
            {
                printf("该迷宫无解！\n");
            } 
            else {
                printf("共找到 %d 条迷宫解。\n", pathCount);
            }
            printf("\n");
        }
        else if(choice == 3)
        {
            srand(time(NULL));
            cols = 10;
            pathCount = 0;
            rows = 10;
            init(); // 初始化迷宫
            generateMaze(0,maze[0][0]);
            exitandentry();
            printf("迷宫生成完成：\n");
            printMaze();
            printf("\n");
            printf("开始求解......\n");
            for(int i=0;i<rows;++i)
            {
                for(int j=0;j<cols;++j)
                {
                    ori[i][j] = maze[i][j];
                }
            }
            printf("起点(%d,%d)\n",startRow,startCol);
            dfs(startRow,startCol);
            if (pathCount == 0) 
            {
                printf("该迷宫无解！\n");
            } 
            else {
                printf("共找到 %d 条迷宫解。\n", pathCount);
            }
        }
        else if (choice == 4)
            break;
    }
    return 0;
}
