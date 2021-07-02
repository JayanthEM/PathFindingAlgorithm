#pragma once
#include <memory>
#include <map>
#include "Position.h"
#include "Node.h"

class Grid
{
public:
    static std::shared_ptr<Grid> instance;
    static std::shared_ptr<Grid> GetInstance();

    void CreateGrid(const int32_t height, const int32_t width);
    std::shared_ptr<Node> GetNode(Position position);
    
    void ResetNodes();

    int32_t GetHeight() { return m_height; }
    int32_t GetWidth() { return m_width; }

private:
    int32_t m_height;
    int32_t m_width;
    std::map<Position, std::shared_ptr<Node>> mNodes;
    bool IsLocationValid(Position pos, const int32_t &width, const int32_t &height);
};