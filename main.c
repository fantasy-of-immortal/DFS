#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <MazeGeneration.h>
#include <MazeSolving.h>


int pathCount =0;

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
