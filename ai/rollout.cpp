#include "rollout.h"
#include <cstdio>
#include <cmath>
Point rollout(int map[MAPSIZE][MAPSIZE], int color){
    Point p;
    double max = -inf;
    p.x = p.y = -1;
    for (int i = 0; i < MAPSIZE; ++i){
        for (int j = 0; j < MAPSIZE; ++j){
            if (map[i][j] == 0){
                int result[MAPSIZE][MAPSIZE];
                Point t;
                t.x = i;
                t.y = j;
                nextStep(map, result, t, color);
                int di = diff(map, result);
                if (di != 1){
                    double value = _rollout_evaluate(map, result, color) + di;
                    //printf("%d %d %f\n", i, j, value);
                    if (value > max){
                        max = value;
                        p = t;
                    }
                }
            }
        }
    }
    return p;
}
double _rollout_evaluate(int map[MAPSIZE][MAPSIZE], int result[MAPSIZE][MAPSIZE], int color){
    double sum = 0;
    sum += -3 * (sqrt(remainder(result, 3 - color)));
    for (int i = 0; i < MAPSIZE; ++i){
        for (int j = 0; j < MAPSIZE; ++j){
            if (result[i][j] != 0){
                if (result[i][j] == color){
                    sum += rollout_evaluate[i][j];
                }
                else{
                    sum -= rollout_evaluate[i][j];
                }
            }
        }
    }
    return sum;
}
int remainder(int map[MAPSIZE][MAPSIZE], int color){
    int count = 0;
    for (int i = 0; i < MAPSIZE; ++i){
        for (int j = 0; j < MAPSIZE; ++j){
            if (map[i][j] == 0){
                int result[MAPSIZE][MAPSIZE];
                Point p;
                p.x = i;
                p.y = j;
                nextStep(map, result, p, color);
                if (diff(map, result) > 1){
                    if ((i == 0 || i == 7) && (j == 0 || j == 7)){
                        count += 18;
                    }
                    else{
                        count++;
                    }
                }
            }
        }
    }
    return count;
}