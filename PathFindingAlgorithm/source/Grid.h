#pragma once
#include <memory>
#include<map>
#include "Position.h"
#include "Node.h"

class Grid
{
public:
    std::shared_ptr<Grid> CreateGrid(const int32_t height, const int32_t width);
    std::shared_ptr<Node> GetNode(Position position);
    
    void ResetNodes();

private:
    std::map<Position, std::shared_ptr<Node>> mNodes;
    bool IsLocationValid(Position pos, const int32_t &width, const int32_t &height);
};