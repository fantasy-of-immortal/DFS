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

            init(); // ��ʼ���Թ�
            generateMaze(0,maze[0][0]);
            exitandentry();
            // ��ӡ�Թ�
            printMaze();
            printf("\n");
        }
        else if(choice == 2)
        {
                // �û������Թ�������������
            printf("����������Թ������������� (������ %d): ", MAX_ROWS);
            scanf("%d %d", &rows, &cols);
            pathCount = 0; 
            // �û������Թ���Ԫ��
            printf("����������Թ� (0�������·����1�����Թ�ǽ�壬2�����յ�):\n");
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    scanf("%d", &maze[i][j]);
                }
            }       

            // �û�������������
            printf("�������ʼ�� (����): ");
            scanf("%d %d", &startRow, &startCol);

            //���������ʼ��
            for(int i=0;i<rows;++i)
            {
                for(int j=0;j<cols;++j)
                {
                    ori[i][j] = maze[i][j];
                }
            }
            // ��ָ����㿪ʼ����DFS
            dfs(startRow, startCol);

            if (pathCount == 0) 
            {
                printf("���Թ��޽⣡\n");
            } 
            else {
                printf("���ҵ� %d ���Թ��⡣\n", pathCount);
            }
            printf("\n");
        }
        else if(choice == 3)
        {
            srand(time(NULL));
            cols = 10;
            pathCount = 0;
            rows = 10;
            init(); // ��ʼ���Թ�
            generateMaze(0,maze[0][0]);
            exitandentry();
            printf("�Թ�������ɣ�\n");
            printMaze();
            printf("\n");
            printf("��ʼ���......\n");
            for(int i=0;i<rows;++i)
            {
                for(int j=0;j<cols;++j)
                {
                    ori[i][j] = maze[i][j];
                }
            }
            printf("���(%d,%d)\n",startRow,startCol);
            dfs(startRow,startCol);
            if (pathCount == 0) 
            {
                printf("���Թ��޽⣡\n");
            } 
            else {
                printf("���ҵ� %d ���Թ��⡣\n", pathCount);
            }
        }
        else if (choice == 4)
            break;
    }
    return 0;
}
