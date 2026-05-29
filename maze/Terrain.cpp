#include "Terrain.h"

// Terrain
Terrain::Terrain(int cost, string sym) : time_cost(cost), symbol(sym){}
Terrain::Terrain(){}
Terrain::Terrain(const Terrain& other) : time_cost(other.time_cost), symbol(other.symbol){}
Terrain::~Terrain(){}
void Terrain::display() const {cout << symbol;}
int Terrain::getCost() const { return this->time_cost;}

// Wall
Wall::Wall() : Terrain(-1, "█"){}
Wall::~Wall(){}
Wall::Wall(const Wall& other) : Terrain(other){}
Terrain* Wall::clone(){ return new Wall(*this); }
string Wall::getType() const{ return "Wall"; }

// Road
Road::Road() : Terrain(1, " "){}
Road::~Road(){}
Road::Road(const Road& other) : Terrain(other){}
Terrain* Road::clone(){ return new Road(*this); }
string Road::getType() const{ return "Road"; }

// Grass
Grass::Grass() : Terrain(3, "█"){}
Grass::~Grass(){}
Grass::Grass(const Grass& other):Terrain(other){}
Terrain* Grass::clone(){ return new Grass(*this); }
string Grass::getType() const{ return "Grass"; }

// Pond
Pond::Pond() : Terrain(5, "█"){}
Pond::~Pond(){}
Pond::Pond(const Pond& other):Terrain(other){}
Terrain* Pond::clone(){ return new Pond(*this); }
string Pond::getType() const{ return "Pond"; }

// Start
Start::Start(): Terrain(1, "S"){}
Start::~Start(){}
Start::Start(const Start& other):Terrain(other){}
Terrain* Start::clone(){ return new Start(*this); }
string Start::getType() const{ return "Start"; }

// Goal
Goal::Goal() : Terrain(1, "G"){}
Goal::~Goal(){}
Goal::Goal(const Goal& other):Terrain(other){}
Terrain* Goal::clone(){ return new Goal(*this); }
string Goal::getType() const{ return "Goal"; }

// DFS_solution
DFS_solution::DFS_solution():Terrain(0, "D"){}
DFS_solution::~DFS_solution(){}
DFS_solution::DFS_solution(const DFS_solution& other):Terrain(other){}
Terrain* DFS_solution::clone(){ return new DFS_solution(*this); }
string DFS_solution::getType() const{ return "DFS_solution"; }

// BFS_solution
BFS_solution::BFS_solution():Terrain(0, "B"){}
BFS_solution::~BFS_solution(){}
BFS_solution::BFS_solution(const BFS_solution& other):Terrain(other){}
Terrain* BFS_solution::clone(){ return new BFS_solution(*this); }
string BFS_solution::getType() const{ return "BFS_solution"; }

// Dijkstra_solution
Dijkstra_solution::Dijkstra_solution():Terrain(0, "J"){}
Dijkstra_solution::~Dijkstra_solution(){}
Dijkstra_solution::Dijkstra_solution(const Dijkstra_solution& other):Terrain(other){}
Terrain* Dijkstra_solution::clone(){ return new Dijkstra_solution(*this); }
string Dijkstra_solution::getType() const{ return "Dijkstra_solution"; }