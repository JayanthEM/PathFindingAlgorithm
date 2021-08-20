#include "Dijkstra.h"
#include <algorithm>

void Dijkstra::FindPath(Position start, Position end, std::list<std::shared_ptr<Node>> &path, std::vector<std::shared_ptr<Node>> &floodFillNodes)
{
    std::list<std::shared_ptr<Node>> frontier;
    bool pathFound = false;

    std::shared_ptr<Node> source = Grid::GetInstance()->GetNode(start);
    std::shared_ptr<Node> destination = Grid::GetInstance()->GetNode(end);

    frontier.push_back(source);
    {
        while (!frontier.empty())
        {
            frontier.sort([](std::shared_ptr<Node> const &first, std::shared_ptr<Node> const &second)->bool
            { return ((first->GetPathCost()) < (second->GetPathCost())); }
            );
            
            std::shared_ptr<Node> currentNode = frontier.front();

            if (currentNode == destination)
                break;

            currentNode->SetVisited(true);
            frontier.pop_front();

            FloodFill(currentNode, destination, frontier, floodFillNodes, pathFound, nullptr);

            if (pathFound)
            {
                if(currentNode != source)
                    path.push_back(currentNode);
                break;
            }
        }
    }
    
    if (pathFound && path.size())
    {
        std::shared_ptr<Node> node = path.back()->GetParentNode();
        while (node != source)
        {
            path.push_front(node);
            node = node->GetParentNode();
        }
    }

    Grid::GetInstance()->ResetNodes();
}

std::string Dijkstra::GetName()
{
    return "Dijkstra";
}