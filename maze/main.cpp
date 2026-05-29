#include "Maze.h"

int main() {
    srand(time(nullptr));
    
    int size = 0;
    
    cout << "請輸入迷宮大小 (奇數，51~151): ";
    cin >> size;
    
    if (size < 51) size = 51;
    if (size % 2 == 0) size++;
    if (size > 151) size = 151;
    
    Maze maze(size, size);
    
    maze.generate();
    cout << endl;
    maze.showStats();
    
    cout << "\n按 Enter 顯示迷宮...";
    cin.ignore();
    cin.get();
    
    maze.display();
    
    cout << "\n按 Enter 開始 DFS 求解...";
    cin.get();
    
    cout << "\n========== DFS 求解 ==========" << endl << endl;
    auto start = high_resolution_clock::now();
    if (maze.dfsSolve()) {
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        maze.display();
        cout << "\nDFS 執行時間: " << duration.count() << " 毫秒" << endl;
    }
    else {
        cout << "DFS 找不到路徑！" << endl;
    }
    
    cout << "\n按 Enter 開始 BFS 求解...";
    cin.get();
    
    cout << "\n========== BFS 求解 ==========" << endl << endl;
    start = high_resolution_clock::now();
    if (maze.bfsSolve()) {
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        maze.display();
        cout << "\nBFS 執行時間: " << duration.count() << " 毫秒" << endl;
    }
    else {
        cout << "BFS 找不到路徑！" << endl;
    }

    cout << "\n按 Enter 開始 Dijkstra 求解...";
    cin.get();
    
    cout << "\n========== Dijkstra 求解 ==========" << endl << endl;
    start = high_resolution_clock::now();
    if (maze.dijkstraSolve()) {
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        maze.display();
        cout << "\nDijkstra 執行時間: " << duration.count() << " 毫秒" << endl;
    } else {
        cout << "Dijkstra 找不到路徑！" << endl;
    }
    
    return 0;
}