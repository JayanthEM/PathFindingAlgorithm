#include "Grid.h"

std::shared_ptr<Grid> Grid::instance = nullptr;

std::shared_ptr<Grid> Grid::GetInstance()
{
    if (!instance)
        instance = std::make_shared<Grid>();
    return instance;
}

void Grid::CreateGrid(const int32_t height, const int32_t width)
{
    for (int32_t x = 0; x < height; ++x)
    {
        for (int32_t y = 0; y < width; ++y)
        {
            mNodes.insert(std::make_pair(Position(x, y), new Node(Position(x,y))));
        }
    }

    //Setting up neighbor Node
    Position neighbour[] = { Position(-1,0), Position(1,0), Position(0,-1), Position(0,1),
                            Position(-1,-1), Position(1,1), Position(1,-1), Position(-1,1) };   // Diagonal Nodes
    
    for (int32_t x = 0; x < height; ++x)
    {
        for (int32_t y= 0; y < width; ++y)
        {
            std::shared_ptr<Node> node = mNodes.at(Position(x, y));

            for (auto position : neighbour)
            {
                Position pos(Position(node->GetPosition().X() + position.X(), node->GetPosition().Y() + position.Y()));
                if (IsLocationValid(pos, width, height))
                {
                    node->Neighbour().push_back(mNodes.at(pos));
                }
            }
        }
    } 
}

std::shared_ptr<Node> Grid::GetNode(Position position)
{
    if (mNodes.find(position) != mNodes.end())
        return mNodes.find(position)->second;

    return nullptr;
}

bool Grid::IsLocationValid(Position pos, const int32_t &width, const int32_t &height)
{
    return ((pos.X() >= 0 &&  pos.X() < height) && (pos.Y() >= 0 && pos.Y() < width));
    return true;
}

void Grid::ResetNodes()
{
    for (auto &node : mNodes)
    {
         node.second->Reset();
    }
}