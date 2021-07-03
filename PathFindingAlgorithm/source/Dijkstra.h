#pragma once
#include "IPathFindingAlgorithm.h"

class Dijkstra : public IPathFindingAlgorithm
{
public:
    bool FindPath(Position start, Position end, std::list < std::shared_ptr<Node>> &path) override;
    virtual std::string GetName();

};