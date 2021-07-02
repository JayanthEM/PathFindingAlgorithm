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
    int x = 10, y = 10;
    Position position(x, y);
   
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
    // Grid
    int32_t width = Grid::GetInstance()->GetWidth();
    int32_t height = Grid::GetInstance()->GetHeight();

    for (int i = 0; i < height; ++i)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, 0, i * 40, height, i * 40);        
    }
    for (int i = 0; i < width; ++i)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, i*40, 0, i*40,width);
    }

    // wall
    for (auto i = m_Wall.begin(); i != m_Wall.end(); ++i)
    {
        int x = i->X();
        int y = i->Y();
        SDL_Rect rect = { x - (x % 40), y - (y % 40), 40, 40 };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);
    }

    
    {
        //Start position,
        int x = m_StartPosition.X();
        int y = m_StartPosition.Y();
        SDL_Rect rect = { x - (x % 40), y - (y % 40), 40, 40 };
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);

        //end position
        x = m_StartPosition.X();
        y = m_StartPosition.Y();
        rect = { x - (x % 40), y - (y % 40), 40, 40 };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);
    }

    //Path
    {
        for (auto i = m_path.begin(); i != m_path.end(); ++i)
        {
            int x = (*i)->GetPosition().X();
            int y = (*i)->GetPosition().Y();
            int x1 = x % 40;
            int y1 = y % 40;
            SDL_Rect rect = { x - x1, y - y1, 40, 40 };
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
}