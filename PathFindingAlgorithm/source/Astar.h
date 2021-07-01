#pragma once
#include "IPathFinder.h"
#include "Grid.h"

class AStar : public IPathFinder
{
public:
    AStar() {}
    virtual ~AStar() {}
    bool FindPath(Position start, Position end, std::list<std::shared_ptr<Node>> &path) override;
    std::string GetName();

};