#pragma once
#include "IPathFindingAlgorithm.h""
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
    static IPathFindingAlgorithm* CreatePathFinder(PATHFINDING_ALGORITHM type);

private:
    static AStar *astar;
    static Dijkstra *dijkstra;
};