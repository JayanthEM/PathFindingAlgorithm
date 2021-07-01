#pragma once
#include "Position.h"
#include <vector>
#include <memory>

enum PATH
{
    WAKABLE,
    WALL,
};

class Node
{
public:

    Node(Position position);

    Position GetPosition();

    void SetParentNode(std::shared_ptr<Node> node);
    std::shared_ptr<Node> GetParentNode() const;

    void SetPathCost(const uint32_t &pathcost);
    uint32_t GetPathCost() const;

    void SetHeristic(const uint32_t &_heuristic);
    uint32_t GetHeristic() const;

    PATH GetPathType() const;
    void SetPathTYPe(PATH path);

    bool IsVisited();
    void SetVisited(bool status);

    std::vector<std::shared_ptr<Node>> Neighbour();

    void Reset();

    bool operator<(const Node& node) const;
    bool operator=(const Node& node) const;
    void operator()(const Node& node1, const Node& node2) const {}

private:
    
    Position mPosition;
    uint32_t mPathCost;
    uint32_t mHeuristic;
    bool mVisited;

    PATH mPathType;
    std::shared_ptr<Node> mParentNode;

    std::vector< std::shared_ptr<Node>> mNeighbhourNode;
};