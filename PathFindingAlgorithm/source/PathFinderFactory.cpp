#include "PathFinderFactory.h"
#include "Astar.h"

AStar *PathFinderFactory::astar = nullptr;
Dijkstra *PathFinderFactory::dijkstra = nullptr;


IPathFinder* PathFinderFactory::CreatePathFinder(PATHFINDING_ALGORITHM type)
{
    switch (type)
    {

    case AStar_Algorithm:
        if (!astar)
            astar = new AStar();
        return astar;

    case Dijkstra_Algorithm:
        if (!dijkstra)
            dijkstra = new Dijkstra();
        return dijkstra;

    default:
        break;
    }
}

