#include <cstdio>
#include <cstdlib>
#include "util.h"
#include "mcts.h"
int main(int argv, char *args[]){
    int map[MAPSIZE][MAPSIZE];
    if (!input(map, argv, args)){
        printf("-1\n-1\n");
        return 0;
    }
    MCTS mcts;
    Point p = mcts.predict(map, 1);
    printf("%d\n%d\n", p.x, p.y);
    return 0;
}