#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <random>
#include <climits>
#include <tuple>
#include "Terrain.h"
#include "Color.h"

using namespace std;
using namespace chrono;

class Maze {
private:
    int width, height;
    vector<vector<Terrain*>> map;
    vector<vector<Terrain*>> originalMap;
    pair<int, int> start, goal;
    
    const int dx[4] = {0, 0, -1, 1};// 上 下 左 右 
    const int dy[4] = {-1, 1, 0, 0};// 上 下 左 右  
    
    bool isValid(int x, int y);
    bool isInBounds(int x, int y);
    void resetMap();
    vector<int> shuffleDirections();
    
public:
    Maze(int w, int h);
    ~Maze();
    
    void generate();
    int getBranchCount();
    bool dfsSolve();
    bool bfsSolve();
    bool dijkstraSolve();
    void display();
    void showStats();
};

