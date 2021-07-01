#include "PathFinder.h"
#include "Grid.h"

void PathFinder::Create(const int32_t width, const int32_t height)
{
    Grid::GetInstance()->CreateGrid(height, width);
 
    pathFinder = PathFinderFactory::CreatePathFinder(PATHFINDING_ALGORITHM::AStar_Algorithm);
    
    m_StartPosition = Position(5, 5);
    m_EndPosition = Position(10, 10);
}

void PathFinder::Update()
{
    //Check for the input
    //Check the input position
    //startposition and endposition
    
    pathFinder->FindPath(m_StartPosition, m_EndPosition, m_path);
   
}



void PathFinder::Renderer()
{

}