#include "Astar.h"

void AStar::FindPath(Position start, Position end)
{
    std::list<std::shared_ptr<Node>> frontier;
    std::shared_ptr<Node> path = nullptr;
    bool pathFound = false;

    std::shared_ptr<Node> source = grid->GetNode(start);
    std::shared_ptr<Node> destination = grid->GetNode(end);

    frontier.push_back(source);

    while (!frontier.empty())
    {
        frontier.sort([](std::shared_ptr<Node> const &first, std::shared_ptr<Node> const &second)->bool
        { return ((first->GetPathCost() + first->GetHeristic()) < (second->GetPathCost() + second->GetHeristic())); }
        );

        std::shared_ptr<Node> currentNode = frontier.front();

        if (currentNode == destination)
            break;

        currentNode->SetVisited(true);
        frontier.pop_front();

        FloodFill(currentNode, destination, frontier, pathFound);

        if (pathFound)
        {
            path = currentNode;
            break;
        }
    }

    if (pathFound)
    {
        while (path != source)
        {
            path = path->GetParentNode();
        }
    }

    grid->ResetNodes();
    
}

void AStar::FloodFill(std::shared_ptr<Node> startNode,std::shared_ptr<Node> endNode , std::list<std::shared_ptr<Node>> &frontier, bool &pathFound )
{
    for (auto i = startNode->Neighbour().begin(); i != startNode->Neighbour().end(); i++)
    {
        std::shared_ptr<Node> currentNode = *i;
        if (currentNode == endNode)
        {
            pathFound = true;
            return;
        }

        if (currentNode->GetPathType() != PATH::WALL && currentNode->IsVisited() == false)
        {
            uint32_t pathcost = startNode->GetPathCost() + Distance(currentNode->GetPosition(), startNode->GetPosition());
            uint32_t heuristic = ManhattanDistance(currentNode->GetPosition(), endNode->GetPosition());
            auto node = std::find(frontier.begin(), frontier.end(), (*i));
            if (node != frontier.end() && pathcost > currentNode->GetPathCost())
            {
                continue;
            }
            else
            {
                currentNode->SetHeristic(heuristic);
                currentNode->SetPathCost(pathcost);
                currentNode->SetParentNode(startNode);

                frontier.push_back(currentNode);
            }
        }
    }
}

uint32_t AStar::ManhattanDistance(Position startPosition, Position endPosition)
{
    return ((abs(endPosition.X() - startPosition.X()) + abs(endPosition.Y() - startPosition.Y())) * 10);
}

uint32_t AStar::Distance(Position startPosition, Position endPosition)
{
    return (int)((sqrt(abs(endPosition.X() - startPosition.X()) + abs(endPosition.Y() - startPosition.Y()))) * 10);
}

std::string AStar::GetName()
{
    return "A Star";
}