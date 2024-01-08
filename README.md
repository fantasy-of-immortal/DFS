# 使用方法
  本程序共有三种功能：10X10迷宫的自动生成，10X10规格内迷宫的自动求解，以及自动生成和求解
  可以根据命令行菜单选择
# 编译指令
  gcc -c -I. MazeGeneration.c
  gcc -c -I. MazeSolving.c
  gcc -c -I. main.c
  gcc -o MazeProgram -I. main.o MazeGeneration.o  MazeSolving.o
