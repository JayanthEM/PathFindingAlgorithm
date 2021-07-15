#include "PathFinder.h"
#include "PathFinderFactory.h"
#include "Grid.h"

void PathFinder::Create(const int32_t width, const int32_t height)
{
    Grid::GetInstance()->CreateGrid(height, width);
 
    pathFinder = PathFinderFactory::CreatePathFinder(PATHFINDING_ALGORITHM::Dijkstra_Algorithm);
    
    m_StartPosition = Position(1, 2);
    m_EndPosition = Position(1, 5);
}

void PathFinder::HandleUserInput(std::function<void(Position&)> callBack)
{
    validMouseInput = true;
    callBack(mouseInputPosition);
}

void PathFinder::ChangePathFindingAlgorithm(const SDL_Event& event)
{
    if (event.type == SDL_SCANCODE_1)
        pathFinder = PathFinderFactory::CreatePathFinder(PATHFINDING_ALGORITHM::AStar_Algorithm);
    else
        pathFinder = PathFinderFactory::CreatePathFinder(PATHFINDING_ALGORITHM::Dijkstra_Algorithm);
}

void PathFinder::Update()
{
    if (validMouseInput)
    {
        validMouseInput = false;

        int x = (mouseInputPosition.X() - (mouseInputPosition.X() % 40))/ 40;
        int y = (mouseInputPosition.Y() - (mouseInputPosition.Y() % 40)) /40;

        Position position(y, x);

        if (!m_IsStartPosition && m_StartPosition == position)
        {
            m_IsStartPosition = true;
            return;
        }
        else if (!m_IsEndPosition && m_EndPosition == position)

        {
            m_IsEndPosition = true;
            return;
        }

        if (m_IsStartPosition)
        {
            m_IsStartPosition = false;
            m_StartPosition = position;
        }
        else if (m_IsEndPosition)
        {
            m_IsEndPosition = false;
            m_EndPosition = position;
        }   
        UpdateWall(position);
    }
    m_path.clear();
    pathFinder->FindPath(m_StartPosition, m_EndPosition, m_path);
}

void PathFinder::UpdateWall(const  Position& position)
{
    auto it = std::find(m_Wall.begin(), m_Wall.end(), position);
    std::shared_ptr<Node> node = Grid::GetInstance()->GetNode(position);

    if (it == m_Wall.end())
    {   
        if (m_StartPosition != position && m_EndPosition != position)
        {
            node->SetPathType(PATH::WALL);
            m_Wall.push_back(position);
        }
    }
    else
    {
        node->SetPathType(PATH::WAKABLE);
        m_Wall.remove(position);
    }
}

void PathFinder::Renderer(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Grid
    int32_t width = Grid::GetInstance()->GetWidth();
    int32_t height = Grid::GetInstance()->GetHeight();

    for (int i = 0; i < width; ++i)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);       
        SDL_RenderDrawLine(renderer, i * 40, 0, i * 40, height*40);
    }
    for (int i = 0; i < height; ++i)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, 0, i * 40, width * 40, i * 40);
    }

    // wall
    for (auto i = m_Wall.begin(); i != m_Wall.end(); ++i)
    {
        SDL_Rect rect = {  i->Y()*40, i->X() * 40, 40, 40 };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);
    }

    
    {
        //Start position,
        SDL_Rect rect = {m_StartPosition.Y()*40,  m_StartPosition.X() * 40, 40, 40 };
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);

        //end position
        rect = { m_EndPosition.Y() * 40, m_EndPosition.X() * 40, 40, 40 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Path
    {
        for (auto i = m_path.begin(); i != m_path.end(); ++i)
        {
            SDL_Rect rect = { (*i)->GetPosition().Y() * 40,(*i)->GetPosition().X() * 40, 40, 40 };
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
}