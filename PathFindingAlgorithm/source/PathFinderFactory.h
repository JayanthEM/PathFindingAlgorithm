#pragma once
#include "IPathFinder.h""
#include "Astar.h"
#include "Dijkstra.h"

enum PATHFINDING_ALGORITHM
{
    AStar_Algorithm,
    Dijkstra_Algorithm,
};

class PathFinderFactory
{
public:
    static IPathFinder* CreatePathFinder(PATHFINDING_ALGORITHM type);

private:
    static AStar *astar;
    static Dijkstra *dijkstra;
};