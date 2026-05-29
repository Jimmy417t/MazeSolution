#pragma once

#include <iostream>
#include <string>
using namespace std;

class Terrain
{
protected:
    int time_cost;
    string symbol;
public:
    Terrain(int cost, string sym);
    Terrain();
    Terrain(const Terrain& other);
    virtual ~Terrain();
    void display() const;
    int getCost() const;
    virtual Terrain* clone() = 0;
    virtual string getType() const = 0;
};

class Wall : public Terrain
{
public:
    Wall();
    ~Wall();
    Wall(const Wall& other);
    Terrain* clone() override;
    string getType() const override;
};

class Road : public Terrain
{
public:
    Road();
    ~Road();
    Road(const Road& other);
    Terrain* clone() override;
    string getType() const override;
};

class Grass : public Terrain
{
public:
    Grass();
    ~Grass();
    Grass(const Grass& other);
    Terrain* clone() override;
    string getType() const override;
};

class Pond : public Terrain
{
public:
    Pond();
    ~Pond();
    Pond(const Pond& other);
    Terrain* clone() override;
    string getType() const override;
};

class Start : public Terrain
{
public:
    Start();
    ~Start();
    Start(const Start& other);
    Terrain* clone() override;
    string getType() const override;
};

class Goal : public Terrain
{
public:
    Goal();
    ~Goal();
    Goal(const Goal& other);
    Terrain* clone() override;
    string getType() const override;
};

class DFS_solution : public Terrain
{
public:
    DFS_solution();
    ~DFS_solution();
    DFS_solution(const DFS_solution& other);
    Terrain* clone() override;
    string getType() const override;
};

class BFS_solution : public Terrain
{
public:
    BFS_solution();
    ~BFS_solution();
    BFS_solution(const BFS_solution& other);
    Terrain* clone() override;
    string getType() const override;
};

class Dijkstra_solution : public Terrain
{
public:
    Dijkstra_solution();
    ~Dijkstra_solution();
    Dijkstra_solution(const Dijkstra_solution& other);
    Terrain* clone() override;
    string getType() const override;
};

