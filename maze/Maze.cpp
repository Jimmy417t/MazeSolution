#include "Maze.h"

Maze::Maze(int w, int h) : width(w), height(h) {
    if (width % 2 == 0) width++;
    if (height % 2 == 0) height++;
    
    map.resize(height, vector<Terrain*>(width, nullptr));
    originalMap.resize(height, vector<Terrain*>(width, nullptr));
    start = make_pair(1, 1);
    goal = make_pair(width - 2, height - 2);
}

Maze::~Maze() {
    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
        {
            delete map[y][x];
            delete originalMap[y][x];
        }
}

bool Maze::isValid(int x, int y) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool Maze::isInBounds(int x, int y) {
    return x > 0 && x < width-1 && y > 0 && y < height-1;
}

void Maze::resetMap() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if(originalMap[y][x] != nullptr){
                delete map[y][x];
                map[y][x] = originalMap[y][x]->clone();
            }
        }
    }
}

vector<int> Maze::shuffleDirections() {
    vector<int> dirs = {0, 1, 2, 3};
    static random_device random_seed;
    static mt19937 gen(random_seed());
    shuffle(dirs.begin(), dirs.end(), gen);
    return dirs;
}

void Maze::generate() {
    // 先全部初始化為牆
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            map[y][x] = new Wall();
        }
    }
    
    stack<pair<int, int>> st;
    vector<vector<bool>> visited(height, vector<bool>(width, false));
    
    // 從起點開始
    st.push(start);
    visited[start.second][start.first] = true;
    delete map[start.second][start.first];
    map[start.second][start.first] = new Start();
    
    while (!st.empty()) {
        pair<int, int> current = st.top();
        int x = current.first;
        int y = current.second;
        
        // 找出所有未訪問的鄰居（距離2格）
        vector<pair<int, pair<int, int>>> neighbors;
        vector<int> dirs = shuffleDirections();
        for (int i : dirs) {
            int nx = x + dx[i] * 2;
            int ny = y + dy[i] * 2;
            if (isInBounds(nx, ny) && !visited[ny][nx] && map[ny][nx]->getType() == "Wall") {
                neighbors.push_back(make_pair(i, make_pair(nx, ny)));
            }
        }
        
        if (!neighbors.empty()) {
            // 隨機選擇一個鄰居
            int idx = rand() % neighbors.size();
            int dir = neighbors[idx].first;
            int nx = neighbors[idx].second.first;
            int ny = neighbors[idx].second.second;
            int wx = x + dx[dir];
            int wy = y + dy[dir];
            
            // 打通牆壁和目標格
            delete map[wy][wx];
            delete map[ny][nx];
            if(rand() % 100 < 4) 
            {
                map[ny][nx] = new Pond();
                map[wy][wx] = new Pond();
            }
            if(rand() % 100 < 10)
            {
                map[wy][wx] = new Grass();
                map[ny][nx] = new Grass();
            }
            else 
            {
                map[ny][nx] = new Road();
                map[wy][wx] = new Road();
            }
            visited[ny][nx] = true;
            st.push(make_pair(nx, ny));
            
            // 增加分岔 有機率也打通其他方向的牆
            if (neighbors.size() > 1 && rand() % 100 < 25) 
            {
                int idx2 = rand() % neighbors.size();
                if (idx2 != idx) {
                    int dir2 = neighbors[idx2].first;
                    int nx2 = neighbors[idx2].second.first;
                    int ny2 = neighbors[idx2].second.second;
                    int wx2 = x + dx[dir2];
                    int wy2 = y + dy[dir2];
                    delete map[wy2][wx2];
                    delete map[ny2][nx2];
                    map[wy2][wx2] = new Road();
                    map[ny2][nx2] = new Road();
                    visited[ny2][nx2] = true;
                    st.push(make_pair(nx2, ny2));
                }
            }
        } else {
            st.pop();
        }
    }
    
    // 第二階段：隨機打通一些牆壁，創造更多迴路
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            if (map[y][x]->getType() == "Wall") {
                // 檢查上下或左右是否都是路
                int pathCount = 0;
                if (map[y-1][x]->getType() == "Road") pathCount++;
                if (map[y+1][x]->getType() == "Road") pathCount++;
                if (map[y][x-1]->getType() == "Road") pathCount++;
                if (map[y][x+1]->getType() == "Road") pathCount++;
    
                // 如果兩邊都有路，有機率打通（創造捷徑）
                if(pathCount >= 2 && rand() % 100 < 3) 
                {
                    delete map[y][x];
                    map[y][x] = new Pond();
                }
                if(pathCount >= 2 && rand() % 100 < 7) 
                {
                    delete map[y][x];
                    map[y][x] = new Grass();
                }
                if(pathCount >= 2 && rand() % 100 < 8) 
                {
                    delete map[y][x];
                    map[y][x] = new Road();
                }
            }
        }
    }
    
    delete map[goal.second][goal.first];
    map[goal.second][goal.first] = new Goal();
    
    // 保存原始地圖
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            originalMap[y][x] = map[y][x]->clone();
        }
    }
}

int Maze::getBranchCount() {
    int branches = 0;
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            if (map[y][x]->getType() == "Road" || map[y][x]->getType() == "Grass" || map[y][x]->getType() == "Pond"){
                int exits = 0;
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];
                    if (map[ny][nx]->getType() == "Road" || map[ny][nx]->getType() == "Start"||
                        map[ny][nx]->getType() == "Goal") {
                        exits++;
                    }
                }
                if (exits >= 3) branches++;
            }
        }
    }
    return branches;
}

bool Maze::dfsSolve() {
    resetMap();
    stack<pair<int, int>> st;
    vector<vector<bool>> visited(height, vector<bool>(width, false));
    vector<vector<pair<int, int>>> parent(height, vector<pair<int, int>>(width, make_pair(-1, -1)));
    
    st.push(start);
    visited[start.second][start.first] = true;
    
    while (!st.empty()) {
        pair<int, int> current = st.top();
        st.pop();
        int x = current.first;
        int y = current.second;
        
        if (x == goal.first && y == goal.second) {
            pair<int, int> cur = goal;
            int steps = 0;
            int total_cost = 0;
            while (cur != start) {
                pair<int, int> p = parent[cur.second][cur.first];
                int px = p.first;
                int py = p.second;
                if (map[py][px]->getType() != "Start" && map[py][px]->getType() != "Goal") 
                {
                    total_cost += map[py][px]->getCost();
                    delete map[py][px];
                    map[py][px] = new DFS_solution();
                }
                cur = make_pair(px, py);
                steps++;
            }
            cout << "DFS 路徑長度: " << steps << " 步 || " << "時間: " << total_cost << " 單位" << endl;
            return true;
        }
        
        // 隨機打亂方向，增加不確定性
        vector<int> dirs = shuffleDirections();
        for (int i : dirs) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isValid(nx, ny) && !visited[ny][nx] && ((map[ny][nx]->getType() == "Road" || map[ny][nx]->getType() == "Grass" ||
                map[ny][nx]->getType() == "Pond" || map[ny][nx]->getType() == "Goal"))) 
            {
                visited[ny][nx] = true;
                parent[ny][nx] = make_pair(x, y);
                st.push(make_pair(nx, ny));
            }
        }
    }
    return false;
}

bool Maze::bfsSolve() {
    resetMap();
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(height, vector<bool>(width, false));
    vector<vector<pair<int, int>>> parent(height, vector<pair<int, int>>(width, make_pair(-1, -1)));
    
    q.push(start);
    visited[start.second][start.first] = true;
    
    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();
        int x = current.first;
        int y = current.second;
        
        if (x == goal.first && y == goal.second) {
            pair<int, int> cur = goal;
            int steps = 0;
            int total_cost = 0;
            while (cur != start) {
                pair<int, int> p = parent[cur.second][cur.first];
                int px = p.first;
                int py = p.second;
                if (map[py][px]->getType() != "Start" && map[py][px]->getType() != "Goal") 
                {
                    total_cost += map[py][px]->getCost();
                    delete map[py][px];
                    map[py][px] = new BFS_solution();
                }
                cur = make_pair(px, py);
                steps++;
            }
            cout << "BFS 路徑長度: " << steps << " 步 || " << "時間: " << total_cost << " 單位" << endl;
            return true;
        }
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isValid(nx, ny) && !visited[ny][nx] && ((map[ny][nx]->getType() == "Road" || map[ny][nx]->getType() == "Grass" ||
                map[ny][nx]->getType() == "Pond" || map[ny][nx]->getType() == "Goal"))) 
            {
                visited[ny][nx] = true;
                parent[ny][nx] = make_pair(x, y);
                q.push(make_pair(nx, ny));
            }
        }
    }
    return false;
}

bool Maze::dijkstraSolve() {
    resetMap();
    
    // 成本記錄陣列，初始化為無限大
    vector<vector<int>> minCost(height, vector<int>(width, INT_MAX));
    // 父節點記錄
    vector<vector<pair<int, int>>> parent(height, vector<pair<int, int>>(width, make_pair(-1, -1)));
    
    // 優先隊列：儲存 (成本, x, y)，使用最小堆積
    auto cmp = [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        return get<0>(a) > get<0>(b);  // 成本小的優先
    };
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(cmp)> pq(cmp);
    // 資料型態/容器/比較方式

    // 起點初始化
    minCost[start.second][start.first] = 0;
    pq.push(make_tuple(0, start.first, start.second));
    
    while (!pq.empty()) {
        auto [currentCost, x, y] = pq.top();
        pq.pop();
        
        // 如果這個節點的記錄已經不是最新的，跳過（優化）
        if (currentCost > minCost[y][x]) {
            continue;
        }
        
        // 到達終點（從佇列取出時才保證是最小成本）
        if (x == goal.first && y == goal.second) {
            // 回溯標記路徑並輸出結果
            pair<int, int> cur = goal;
            int steps = 0;
            int total_cost = currentCost;  // 直接使用當前成本
            
            while (cur != start) {
                pair<int, int> p = parent[cur.second][cur.first];
                int px = p.first;
                int py = p.second;
                if (map[py][px]->getType() != "Start" && map[py][px]->getType() != "Goal") {
                    delete map[py][px];
                    map[py][px] = new Dijkstra_solution();
                }
                cur = make_pair(px, py);
                steps++;
            }
            cout << "Dijkstra 路徑長度: " << steps << " 步 || 最小成本: " << total_cost << " 單位" << endl;
            return true;
        }
        
        // 擴展四個方向
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            // 檢查是否有效且可走（加上起點和終點）
            if (isValid(nx, ny)) {
                string cellType = map[ny][nx]->getType();
                if (cellType == "Road" || cellType == "Grass" || cellType == "Pond" || 
                    cellType == "Goal" || cellType == "Start") {
                    
                    // 計算移動成本（起點和終點成本為0）
                    int newCost = currentCost + map[ny][nx]->getCost();
                    
                    // 如果找到更小的成本
                    if (newCost < minCost[ny][nx]) {
                        minCost[ny][nx] = newCost;
                        parent[ny][nx] = make_pair(x, y);
                        pq.push(make_tuple(newCost, nx, ny));
                    }
                }
            }
        }
    }
    
    cout << "Dijkstra: 找不到路徑！" << endl;
    return false;
}

void Maze::display() {
    cout << endl;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            setColor(map[y][x]->getType());
            map[y][x]->display();
        }
        setColor(WHITE);
        cout << endl;
    }
    setColor(WHITE);
    cout << "\n圖例: █=牆  空格=路  S=起點  G=終點  ";
    setColor(GREEN);
    cout << "█=草地 ";
    setColor(BLUE);
    cout << "█=池塘 ";
    setColor(PURPLE);
    cout << "D=DFS路徑 ";
    setColor(YELLOW);
    cout << "B=BFS最短路徑 ";
    setColor(RED);
    cout << "J=Dijkstra最佳路徑 ";
    setColor(WHITE);
    cout << endl;
}

void Maze::showStats() {
    cout << "\n=== 迷宮資訊 ===" << endl;
    cout << "尺寸: " << width << " x " << height << endl;
    cout << "起點: (1, 1)" << endl;
    cout << "終點: (" << width-2 << ", " << height-2 << ")" << endl;
    cout << "分岔點數量: " << getBranchCount() << endl;
}