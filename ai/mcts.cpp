#include "mcts.h"
#include <cstring>
#include <ctime>
#include <cstdio>
Point MCTS::predict(int map[MAPSIZE][MAPSIZE], int color){
    clear();
    root = createNode();
    memcpy(root->map, map, sizeof(int) * MAPSIZE * MAPSIZE);
    root->color = color;
    root->parent = NULL;
    int startTime = time(NULL);
    int endTime = startTime;
    while(endTime - startTime < MAXTIME){
        dfs(root);
        endTime = time(NULL);
    }
    Point p;
    p.x = p.y = -1;
    double max = -inf;
    for (int i = 0; i < root->children.size(); ++i){
        MCTSNode *child = root->children[i];
        double value = child->score(root->time, false);
        if (value > max){
            max = value;
            p = child->p;
        }
    }
    return p;
}
void MCTS::clear(){
    for (auto it = nodes.begin(); it != nodes.end(); ++it){
        if (*it != NULL){
            delete *it;
            *it = NULL;
        }
    }
    root = NULL;
    nodes.clear();
}
MCTS::~MCTS(){
    clear();
}
void MCTS::dfs(MCTSNode *p){
    if (p->time == 0){
        int color = p->color;
        int map[MAPSIZE][MAPSIZE];
        bool flag = false;
        memcpy(map, p->map, sizeof(int) * MAPSIZE * MAPSIZE);
        while(true){
            Point p = rollout(map, color);
            if (p.x != -1 && p.y != -1){
                int newMap[MAPSIZE][MAPSIZE];
                nextStep(map, newMap, p, color);
                memcpy(map, newMap, sizeof(int) * MAPSIZE * MAPSIZE);
                flag = false;
            }
            else{
                if (flag){
                    break;
                }
                flag = true;
            }
            color = 3 - color;
        }
        update(p, getWinColor(map));
    }
    else{
        if (p->time == 1 && p->children.size() == 0){
            for (int i = 0; i < MAPSIZE; ++i){
                for (int j = 0; j < MAPSIZE; ++j){
                    if (p->map[i][j] == 0){
                        Point t;
                        t.x = i, t.y = j;
                        int map[MAPSIZE][MAPSIZE];
                        nextStep(p->map, map, t, p->color);
                        if (diff(p->map, map) > 1){
                            MCTSNode *node = createNode();
                            memcpy(node->map, map, sizeof(int) * MAPSIZE * MAPSIZE);
                            node->parent = p;
                            node->color = calculate(node->map, 3 - p->color);
                            node->p = t;
                            p->children.push_back(node);
                        }
                    }
                }
            }
        }
        if (p->children.size() == 0){
            update(p, getWinColor(p->map));
        }
        else{
            MCTSNode *ptr = NULL;
            double max = -inf;
            for (int i = 0; i < p->children.size(); ++i){
                MCTSNode *child = p->children[i];
                double value = child->score(p->time, true);
                if (value > max){
                    max = value;
                    ptr = child;
                }
            }
            dfs(ptr);
        }
    }
}
MCTSNode *MCTS::createNode(){
    MCTSNode *node = new MCTSNode();
    nodes.push_back(node);
    node->value = 0;
    node->time = 0;
    node->parent = NULL;
    return node;
}
void MCTS::update(MCTSNode *p, int winColor){
    while(p != NULL){
        p->time++;
        if (p->color != winColor){
            p->value++;
        }
        p = p->parent;
    }
}
double MCTSNode::score(int all, bool isDFS){
    if (time == 0){
        return inf;
    }
    double score = value / time;
    if (isDFS){
        score += C * sqrt(log(all) / time);
    }
    return score;
}