#include "Node.h"

Node::Node(Position position) 
    : mPosition(position),mVisited(false), mParentNode(nullptr),mPathType(PATH::WAKABLE),
    mHeuristic(0), mPathCost(0)
{

}

bool Node::operator<(const Node& node) const
{
    return (mPathCost+mHeuristic < node.GetPathCost()+node.GetHeristic());
}

Position Node::GetPosition()
{
    return mPosition;
}

void Node::SetParentNode(std::shared_ptr<Node> node)
{ 
    mParentNode = node;
}

std::shared_ptr<Node> Node::GetParentNode() const
{ 
    return mParentNode;
}

void Node::SetPathCost(const uint32_t &pathcost)
{ 
    mPathCost = pathcost;
}

uint32_t Node::GetPathCost() const
{ 
    return mPathCost;
}

void Node::SetHeristic(const uint32_t &_heuristic)
{ 
    mHeuristic = _heuristic;
}

uint32_t Node::GetHeristic() const
{ 
    return mHeuristic;
}

PATH Node::GetPathType() const 
{ 
    return mPathType;
}

void Node::SetPathType(PATH pathtype)
{ 
    mPathType = pathtype;
}

bool Node::IsVisited() 
{ 
    return mVisited;
}

void Node::SetVisited(bool status) 
{ 
    mVisited = status;
}

std::vector<std::shared_ptr<Node>>& Node::Neighbour()
{
    return mNeighbhourNode;
}

void Node::Reset()
{
    mVisited = false;
    mParentNode = nullptr;
    mHeuristic = 0;
    mPathCost = 0;
}