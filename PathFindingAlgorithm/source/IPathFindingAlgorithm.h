#pragma once
#include "Position.h"
#include <string>
#pragma  once
#include <list>
#include <vector>
#include <functional>
#include "Grid.h"


class IPathFindingAlgorithm
{
public:
    

    virtual ~IPathFindingAlgorithm() {}
    virtual void FindPath(Position start, Position end, std::list<std::shared_ptr<Node>> &path, std::vector<std::shared_ptr<Node>> &frontier) = 0;
    virtual std::string GetName() = 0;

    void FloodFill(std::shared_ptr<Node> startNode, std::shared_ptr<Node> endNode,std::list<std::shared_ptr<Node>> &frontier, std::vector<std::shared_ptr<Node>> &floodFillNodes, bool &pathFound, uint32_t(IPathFindingAlgorithm::*heuristicFunction)(Position, Position));

    uint32_t ManhattanDistance(Position startPosition, Position endPosition);
protected:
    uint32_t Distance(Position startPosition, Position endPosition);
};