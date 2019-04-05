#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "util.h"
bool input(int map[MAPSIZE][MAPSIZE], int size, char *args[]){
    if (size - 1 != MAPSIZE * MAPSIZE){
        return false;
    }
    for (int i = 0; i < MAPSIZE; ++i){
        for (int j = 0; j < MAPSIZE; ++j){
            if (sscanf(args[i * MAPSIZE + j + 1], "%d", &map[i][j]) != 1){
                return false;
            }
        }
    }
    return true;
}
void nextStep(int map[MAPSIZE][MAPSIZE], int result[MAPSIZE][MAPSIZE], Point p, int color){
    memcpy(result, map, sizeof(int) * MAPSIZE * MAPSIZE);
    Point t;
    for (t.x = -1; t.x <= 1; ++t.x){
        for (t.y = -1; t.y <= 1; ++t.y){
            if (t.x != 0 || t.y != 0){
                _nextOneStep(result, p, color, t);
            }
        }
    }
    result[p.x][p.y] = color;
}
void _nextOneStep(int map[MAPSIZE][MAPSIZE], Point p, int color, Point addition){
    int x = p.x + addition.x;
    int y = p.y + addition.y;
    while(inMap(x, y)){
        if (map[x][y] == 0){
            break;
        }
        else if (map[x][y] == color){
            while (x != p.x || y != p.y){
                map[x][y] = color;
                x -= addition.x;
                y -= addition.y;
            }
            break;
        }
        x += addition.x;
        y += addition.y;
    }
}
bool inMap(int x, int y){
    return (x >= 0) && (x < MAPSIZE) && (y >= 0) && (y < MAPSIZE);
}
int diff(int a[MAPSIZE][MAPSIZE], int b[MAPSIZE][MAPSIZE]){
    int count = 0;
    for (int i = 0; i < MAPSIZE; ++i){
        for (int j = 0; j < MAPSIZE; ++j){
            if (a[i][j] != b[i][j]){
                count++;
            }
        }
    }
    return count;
}
void print(int map[MAPSIZE][MAPSIZE]){
    for (int i = 0; i < MAPSIZE; ++i){
        for (int j = 0; j < MAPSIZE; ++j){
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}
int calculate(int map[MAPSIZE][MAPSIZE], int color){
    for (int i = 0; i < MAPSIZE; ++i){
        for (int j = 0; j < MAPSIZE; ++j){
            int result[MAPSIZE][MAPSIZE];
            Point p;
            p.x = i, p.y = j;
            nextStep(map, result, p, color);
            if (diff(map, result) > 1){
                return color;
            }
        }
    }
    return 3 - color;
}
int getWinColor(int map[MAPSIZE][MAPSIZE]){
    int white = 0, black = 0;
    for (int i = 0; i < MAPSIZE; ++i){
        for (int j = 0; j < MAPSIZE; ++j){
            if (map[i][j] == 1){
                white++;
            }
            else if (map[i][j] == 2){
                black++;
            }
        }
    }
    return white > black ? 1 : 2;
}