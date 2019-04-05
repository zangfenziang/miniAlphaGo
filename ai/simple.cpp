#include <cstdio>
#include <cstdlib>
#include "util.h"
#include "rollout.h"
int main(int argv, char *args[]){
    int map[MAPSIZE][MAPSIZE];
    if (!input(map, argv, args)){
        printf("-1\n-1\n");
        return 0;
    }
    //print(map);
    Point p = rollout(map, 1);
    printf("%d\n%d\n", p.x, p.y);
    return 0;
}