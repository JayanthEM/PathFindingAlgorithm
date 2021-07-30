#pragma once
#include "IPathFindingAlgorithm.h"

class Dijkstra : public IPathFindingAlgorithm
{
public:
    void FindPath(Position start, Position end, std::list < std::shared_ptr<Node>> &path , std::vector<std::shared_ptr<Node>> &floodFillNodes) override;
    virtual std::string GetName();

};