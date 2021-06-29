#pragma once
#include "Position.h"
#include <string>
#include "Grid.h"
#include <list>

class IPathFinder
{
public:
    
    virtual ~IPathFinder() {}
    virtual bool FindPath(Position start, Position end, std::list<std::shared_ptr<Node>> &path) = 0;
    virtual std::string GetName() = 0;

protected:

    void FloodFill(std::shared_ptr<Node> startNode, std::shared_ptr<Node> endNode,
        std::list<std::shared_ptr<Node>> &frontier, bool &pathFound , uint32_t(IPathFinder::*heuristicFunction)(Position, Position));

    uint32_t ManhattanDistance(Position startPosition, Position endPosition);
    uint32_t Distance(Position startPosition, Position endPosition);
};