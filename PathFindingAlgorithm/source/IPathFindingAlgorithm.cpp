#include "IPathFindingAlgorithm.h"

void IPathFindingAlgorithm::FloodFill(std::shared_ptr<Node> startNode, std::shared_ptr<Node> endNode,
    std::list<std::shared_ptr<Node>> &frontier,std::vector<std::shared_ptr<Node>> &floodFillNodes, bool &pathFound, uint32_t(IPathFindingAlgorithm::*heuristicFunction)(Position, Position) )
{
    for (auto i = startNode->Neighbour().begin(); i != startNode->Neighbour().end(); i++)
    {
        std::shared_ptr<Node> currentNode = *i;
        if (currentNode == endNode)
        {
            pathFound = true;
            return;
        }

        if (currentNode->GetPathType() != PATH::WALL && currentNode->IsVisited() == false )
        {
            int distance = Distance(currentNode->GetPosition(), startNode->GetPosition());

            if (currentNode->GetPathType() == PATH::NEAR_WALL && distance > 10)
            {
                continue;
            }
            uint32_t pathcost = startNode->GetPathCost() + distance;
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

                if(node == frontier.end())
                    floodFillNodes.push_back(currentNode);
            }
        }
    }
}

uint32_t IPathFindingAlgorithm::ManhattanDistance(Position startPosition, Position endPosition)
{
    return ((abs(endPosition.X() - startPosition.X()) + abs(endPosition.Y() - startPosition.Y())) * 10);
}

uint32_t IPathFindingAlgorithm::Distance(Position startPosition, Position endPosition)
{
    return (int)((sqrt(abs(endPosition.X() - startPosition.X()) + abs(endPosition.Y() - startPosition.Y()))) * 10);
}
