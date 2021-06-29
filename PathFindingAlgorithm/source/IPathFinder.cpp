#include "IPathFinder.h"

void IPathFinder::FloodFill(std::shared_ptr<Node> startNode, std::shared_ptr<Node> endNode,
    std::list<std::shared_ptr<Node>> &frontier, bool &pathFound ,uint32_t(IPathFinder::*heuristicFunction)(Position, Position))
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
            uint32_t heuristic = 0;

            if(heuristicFunction)
                heuristic = (this->*heuristicFunction)(currentNode->GetPosition(), endNode->GetPosition());

            auto node = std::find(frontier.begin(), frontier.end(), (*i));
            if (node == frontier.end() || pathcost < currentNode->GetPathCost())
            {
                currentNode->SetHeristic(heuristic);
                currentNode->SetPathCost(pathcost);
                currentNode->SetParentNode(startNode);

                frontier.push_back(currentNode);
            }
        }
    }
}

uint32_t IPathFinder::ManhattanDistance(Position startPosition, Position endPosition)
{
    return ((abs(endPosition.X() - startPosition.X()) + abs(endPosition.Y() - startPosition.Y())) * 10);
}

uint32_t IPathFinder::Distance(Position startPosition, Position endPosition)
{
    return (int)((sqrt(abs(endPosition.X() - startPosition.X()) + abs(endPosition.Y() - startPosition.Y()))) * 10);
}
