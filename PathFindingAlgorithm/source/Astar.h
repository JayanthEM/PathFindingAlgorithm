#pragma once
#include "IPathFinder.h"
#include "Grid.h"
#include <list>

class AStar : public IPathFinder
{
public:
     void FindPath(Position start, Position end) override;
     std::string GetName();

private:
    std::shared_ptr<Grid> grid;
    void FloodFill(std::shared_ptr<Node> startNode, std::shared_ptr<Node> endNode, 
                    std::list<std::shared_ptr<Node>> &frontier, bool &pathFound);


    uint32_t ManhattanDistance(Position startPosition, Position endPosition);
    uint32_t Distance(Position startPosition, Position endPosition);
};