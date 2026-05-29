#include "Color.h"

void setColor(Color color) 
{
    cout << "\033[" << color << "m";
}

void setColor(string type)
{
    int color = 0;
    if(type == "Wall") color = 90;
    if(type == "Road") color = 97;
    if(type == "Grass") color = 92;
    if(type == "Pond") color = 94;
    if(type == "DFS_solution") color = 95;
    if(type == "BFS_solution") color = 93;
    if(type == "Dijkstra_solution") color = 91;
    cout << "\033[" << color << "m";
}