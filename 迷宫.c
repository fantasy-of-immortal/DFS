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

int rows, cols; // �Թ�������������
int startRow, startCol; // ��������
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
            maze[i][j] = WALL; // ��ʼ���Թ�Ϊǽ
        }
    }
}

void printMaze() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < L; j++) {
            if (maze[i][j] == WALL) {
                printf("1 "); // ǽ
            } else if (maze[i][j] == PATH) {
                printf("0 "); // ·��
            } else if (maze[i][j] == 0) {
                printf("0 "); // ���
            } else if (maze[i][j] == 2) {
                printf("2 "); // ����
            }
        }
        printf("\n");
    }
}

int Safe(int x, int y) {
    return (x >= 0 && x < H && y >= 0 && y < L && maze[x][y] == WALL);
}

void generateMaze(int x, int y) {
    maze[x][y] = PATH; // ����ǰλ�ñ��Ϊ·��

    // �������������ĸ�����
    int dx[] = {1, -1, 0, 0};// 1Ϊ���ң�-1Ϊ����
    int dy[] = {0, 0, 1, -1};//-1Ϊ���ϣ�1Ϊ����

    // ���ҷ���
    for (int i = 0; i < 4; i++) {
        int random_index = rand() % 4;
        int temp = dx[i];//�������ֵ������0-1�������ʾ�ô��ƶ��ķ���
        dx[i] = dx[random_index];
        dx[random_index] = temp;//���ֵ���ݣ�ʹ���������̽��

        temp = dy[i];//���Yֵ���ݣ�ʹ��������ƶ�
        dy[i] = dy[random_index];
        dy[random_index] = temp;
    }

    // �����˳��̽���ĸ�����
    for (int i = 0; i < 4; i++) {
        int X1 = x + dx[i] *2;//�������̽��2����̽�߽�
        int Y1= y + dy[i]*2 ;//���ϻ���̽��2����̽�߽�

        if (Safe(X1, Y1)) {
            maze[X1][Y1] = PATH;
            maze[x + dx[i]][y + dy[i]] = PATH;//����ǽ��Ϊ·
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






// ���巽�����飬����̽���ϡ��¡������ĸ�����
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void res_init()  //������������������鸲�ǣ��ع�հ��Թ�״̬
{
    for(int i=0;i<rows;++i)
    {
        for(int j=0;j<cols;++j)
        {
            res[i][j] = ori[i][j];
        }
    }
}

// ��������Ƿ����Թ���Χ��
int isValid(int x, int y) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}


// ���������������
void dfs(int x, int y) 
{
    // �������Խ����ߵ�ǰλ����ǽ�����Ѿ����ʹ�������
    if (!isValid(x, y) || maze[x][y] == 1 || maze[x][y] == -1) {
        return;
    }

    // �����ǰλ�����յ㣬���һ�����·��
    if (maze[x][y] == 2) {
        res_init();//��ʼ���������
        // �洢��ǰ·��
        for (int i = 0; i < pathCount; ++i) {
            res[path[i][0]][path[i][1]]= 3;
        }
        res[x][y]= 3;
         for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (res[i][j] == 3) {
                    printf("P "); // ���·��
                } else if (res[i][j] == 1) {
                    printf("1 "); // ���ǽ
                } else {
                    printf("0 "); // �������λ��
                }
            }
            printf("\n");
        }
        printf("\n");
        pathCount++;
        return;
    }

    // ��ǵ�ǰλ���Ѿ����ʹ�
    maze[x][y] = -1;
    
    // �洢��ǰλ�õ�·������
    path[pathCount][0] = x;
    path[pathCount][1] = y;
    pathCount++;

    // �������ĸ������Ͻ���DFS
    for (int i = 0; i < 4; ++i) {
        int nextX = x + directions[i][0];
        int nextY = y + directions[i][1];

        // �ݹ����DFS
        dfs(nextX, nextY);
    }

    // ���ݣ�ȡ����ǵ�ǰλ��Ϊ�ѷ��ʹ�
    maze[x][y] = 0;
    pathCount--;
}

void menu()
{
    printf("ѡ������Ĺ��ܣ�\n");
    printf("�Թ����ɣ�          1\n");
    printf("�Թ���⣺          2\n");
    printf("�Թ��������Զ����: 3\n");
    printf("�˳���              4\n");
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
