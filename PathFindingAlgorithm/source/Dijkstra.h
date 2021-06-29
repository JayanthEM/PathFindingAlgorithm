#pragma once
#include "IPathFinder.h"

class Dijkstra : public IPathFinder
{
public:
    bool FindPath(Position start, Position end, std::list < std::shared_ptr<Node>> &path) override;
    virtual std::string GetName();

};