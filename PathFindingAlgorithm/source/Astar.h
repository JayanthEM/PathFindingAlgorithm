#pragma once
#include "IPathFindingAlgorithm.h"

class AStar : public IPathFindingAlgorithm
{
public:
    AStar() {}
    virtual ~AStar() {}
    bool FindPath(Position start, Position end, std::list<std::shared_ptr<Node>> &path) override;
    std::string GetName();

    typedef uint32_t(IPathFindingAlgorithm::*Manhattan)(Position, Position);
};