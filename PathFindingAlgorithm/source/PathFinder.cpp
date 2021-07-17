#include "PathFinder.h"
#include "PathFinderFactory.h"
#include "Grid.h"


void PathFinder::Create(const int32_t width, const int32_t height, SDL_Renderer *renderer)
{
    Grid::GetInstance()->CreateGrid(height, width);
 
    pathFinder = PathFinderFactory::CreatePathFinder(PATHFINDING_ALGORITHM::AStar_Algorithm);
    
    m_StartPosition = Position(1, 2);
    m_EndPosition = Position(1, 5);

    m_StartPositionTexture = LoadTexture("F:/C++/PathFinding/PathFindingAlgorithm/External Libraries/Image/wavingstartflag.png", renderer);
    m_EndPositionTexture = LoadTexture("F:/C++/PathFinding/PathFindingAlgorithm/External Libraries/Image/house.png", renderer); 
    m_FootPrintTexture = LoadTexture("F:/C++/PathFinding/PathFindingAlgorithm/External Libraries/Image/FootTexture.png", renderer);    
    m_WallTexture = LoadTexture("F:/C++/PathFinding/PathFindingAlgorithm/External Libraries/Image/wall.png", renderer);
}

SDL_Texture* PathFinder::LoadTexture(std::string path, SDL_Renderer* renderer)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface)
    {
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        return texture;
    }    
    return nullptr;
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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Grid
    int32_t width = Grid::GetInstance()->GetWidth();
    int32_t height = Grid::GetInstance()->GetHeight();

    for (int i = 0; i < width; ++i)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);       
        SDL_RenderDrawLine(renderer, i * 40, 0, i * 40, height*40);
    }
    for (int i = 0; i < height; ++i)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, 0, i * 40, width * 40, i * 40);
    }

    // wall

    for (auto i = m_Wall.begin(); i != m_Wall.end(); ++i)
    {
        SDL_Rect rect = { i->Y() * 40, i->X() * 40, 40, 40 };
        if (m_WallTexture)
        {
            SDL_RenderCopyEx(renderer, m_WallTexture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rect);
        }            
    }

    
    {
        //Start position,
        SDL_Rect rect = { m_StartPosition.Y() * 40,  m_StartPosition.X() * 40, 40, 40 };
        if (m_StartPositionTexture)
        {
            SDL_RenderCopyEx(renderer, m_StartPositionTexture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rect);
        }
            
        //End position
        rect = { m_EndPosition.Y() * 40, m_EndPosition.X() * 40, 40, 40 };
        if (m_EndPositionTexture)
        {
            SDL_RenderCopyEx(renderer, m_EndPositionTexture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rect);
        }
            
    }

    //Path
    {
        Position previousPosition = m_StartPosition;
        for (auto i = m_path.begin(); i != m_path.end(); ++i)
        {
            Position currentPosition((*i)->GetPosition().Y(), (*i)->GetPosition().X());
            SDL_Rect rect = { currentPosition.Y() * 40,currentPosition.X() * 40, 40, 40 };

            if (m_FootPrintTexture)
            {
                double angle = 0;

                int x = previousPosition.X() - currentPosition.X();
                int y = previousPosition.Y() - currentPosition.Y();

                if (y != 0)
                {
                    angle = (y == 1) ? 270 : 90;
                }
                else
                {
                    angle = (x == 1) ? 0 : 180;
                }

                SDL_RenderCopyEx(renderer, m_FootPrintTexture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &rect);
            }
            previousPosition = currentPosition;
        }
    }
    SDL_RenderPresent(renderer);
}