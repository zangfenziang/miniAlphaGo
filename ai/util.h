#pragma once
const int MAPSIZE = 8;
const int inf = (~0u >> 2);
struct Point{
    int x, y;
};
bool input(int map[MAPSIZE][MAPSIZE], int size, char *args[]);
void nextStep(int map[MAPSIZE][MAPSIZE], int result[MAPSIZE][MAPSIZE], Point p, int color);
void _nextOneStep(int map[MAPSIZE][MAPSIZE], Point p, int color, Point addition);
bool inMap(int x, int y);
int diff(int a[MAPSIZE][MAPSIZE], int b[MAPSIZE][MAPSIZE]);
void print(int map[MAPSIZE][MAPSIZE]);
int calculate(int map[MAPSIZE][MAPSIZE], int color);
int getWinColor(int map[MAPSIZE][MAPSIZE]);