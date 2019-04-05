#pragma once
#include "util.h"
const int rollout_evaluate[MAPSIZE][MAPSIZE] = {
    {18, -6, 2, 2, 2, 2, -6, 18},
    {-6, -8, 1, 1, 1, 1, -8, -6},
    {2, 1, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 1, 2},
    {2, 1, 0, 0, 0, 0, 1, 2},
    {-6, -8, 1, 1, 1, 1, -8, -6},
    {18, -6, 2, 2, 2, 2, -6, 18}
};
Point rollout(int map[MAPSIZE][MAPSIZE], int color);
double _rollout_evaluate(int map[MAPSIZE][MAPSIZE], int result[MAPSIZE][MAPSIZE], int color);
int remainder(int map[MAPSIZE][MAPSIZE], int color);