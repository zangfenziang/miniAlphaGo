#pragma once
#include "util.h"
#include "rollout.h"
#include <vector>
#include <cmath>
const int MAXTIME = 30;
const double C = sqrt(2);
struct MCTSNode{
    int value;
    int time;
    int map[MAPSIZE][MAPSIZE];
    int color;
    Point p;
    MCTSNode *parent;
    std::vector<MCTSNode *> children;
    double score(int all, bool isDFS);
};
class MCTS{
    public:
    Point predict(int map[MAPSIZE][MAPSIZE], int color);
    ~MCTS();
    private:
    std::vector<MCTSNode *> nodes;
    MCTSNode *root;
    void clear();
    void dfs(MCTSNode *p);
    void update(MCTSNode *p, int winColor);
    MCTSNode *createNode();
};