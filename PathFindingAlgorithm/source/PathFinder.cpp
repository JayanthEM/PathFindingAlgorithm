#include "PathFinder.h"
#include "PathFinderFactory.h"
#include "Grid.h"
#include <iostream>
#include <array>

PathFinder::~PathFinder()
{
    SDL_DestroyTexture(m_StartPositionTexture);
    SDL_DestroyTexture(m_EndPositionTexture);
    SDL_DestroyTexture(m_FootPrintTexture);
    SDL_DestroyTexture(m_WallTexture);

    delete pathFinder;
}

void PathFinder::Create(const int32_t width, const int32_t height, SDL_Renderer *renderer)
{
    Grid::GetInstance()->CreateGrid(height, width);
 
    pathFinder = PathFinderFactory::CreatePathFinder(PATHFINDING_ALGORITHM::AStar_Algorithm);
    
    m_StartPosition = Position(1, 2);
    m_EndPosition = Position(1, 5);

    m_StartPositionTexture = LoadTexture("F:/C++/PathFinding/PathFindingAlgorithm/Assets/Image/wavingstartflag.png", renderer);
    m_EndPositionTexture = LoadTexture("F:/C++/PathFinding/PathFindingAlgorithm/Assets/Image/house.png", renderer); 
    m_FootPrintTexture = LoadTexture("F:/C++/PathFinding/PathFindingAlgorithm/Assets/Image/footprint.png", renderer);    
    m_WallTexture = LoadTexture("F:/C++/PathFinding/PathFindingAlgorithm/Assets/Image/wall.png", renderer);

    m_font = TTF_OpenFont("F:/C++/PathFinding/PathFindingAlgorithm/Assets/Font/calibri.ttf", 26);
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
    if (event.key.keysym.sym == SDLK_a)
        pathFinder = PathFinderFactory::CreatePathFinder(PATHFINDING_ALGORITHM::AStar_Algorithm);
    else if(event.key.keysym.sym == SDLK_d)
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
    m_frontier.clear();
    pathFinder->FindPath(m_StartPosition, m_EndPosition, m_path, m_frontier);

}

void PathFinder::UpdateWall(const  Position& position)
{
    auto it = std::find(m_Wall.begin(), m_Wall.end(), position);
    std::shared_ptr<Node> node = Grid::GetInstance()->GetNode(position);
    std::array<Position,4> neighbours = { Position(1,0), Position(0,1), Position(-1,0), Position(0,-1) }; 
    
    int32_t width = Grid::GetInstance()->GetWidth();
    int32_t height = Grid::GetInstance()->GetHeight();
    
    if (it == m_Wall.end())
    {   
        if (m_StartPosition != position && m_EndPosition != position)
        {
            node->SetPathType(PATH::WALL);

            for (auto neighbour : neighbours)
            {
                Position pos(node->GetPosition().Y() + neighbour.Y(), node->GetPosition().X() + neighbour.X());
                if (Grid::GetInstance()->IsLocationValid(pos, width, height))
                {
                    std::shared_ptr<Node> neighbourNode = Grid::GetInstance()->GetNode(pos);
                    if(neighbourNode->GetPathType() == PATH::WAKABLE)
                        neighbourNode->SetPathType(PATH::NEAR_WALL);
                }
            }
            m_Wall.push_back(position);
        }
    }
    else
    {
        UpdateNearbyNeighbour(node, neighbours);
        m_Wall.remove(position);
        
        //Update nearby walkable into walk depends on its neighbor
        for (auto neighbour : neighbours)
        {
            Position pos(node->GetPosition().Y() + neighbour.Y(), node->GetPosition().X() + neighbour.X());
            
            std::shared_ptr<Node> neighbourNode = Grid::GetInstance()->GetNode(pos);

            if(neighbourNode && neighbourNode->GetPathType() == PATH::NEAR_WALL)
                UpdateNearbyNeighbour(neighbourNode, neighbours);
        }
    }
}

void PathFinder::UpdateNearbyNeighbour(std::shared_ptr<Node> neighbourNode, const std::array<Position,4>& neighbours)
{    
    int totalNeigbourdiff = neighbourNode->Neighbour().size() - neighbours.size();
    int totalNeighbour;

    if (totalNeigbourdiff > 0)
        totalNeighbour = neighbourNode->Neighbour().size() - totalNeigbourdiff;

    for (auto currentnodeNeighbour : neighbours)
    {
        Position pos(neighbourNode->GetPosition().Y() + currentnodeNeighbour.Y(), neighbourNode->GetPosition().X() + currentnodeNeighbour.X());
        std::shared_ptr<Node> currentNeighborNode = Grid::GetInstance()->GetNode(pos);
        if (currentNeighborNode)
        {
            if (currentNeighborNode->GetPathType() == PATH::WALL)
                break;
            else
                --totalNeighbour;
        }
    }
    
    if (totalNeighbour == 0)
        neighbourNode->SetPathType(PATH::WAKABLE);
    else
        neighbourNode->SetPathType(PATH::NEAR_WALL);
}

void PathFinder::Renderer(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Visited 
    for (auto i = m_frontier.begin(); i != m_frontier.end(); ++i)
    {
        auto isFound = std::find(m_path.begin(), m_path.end(), (*i));
        if (isFound == m_path.end())
        {
            SDL_Rect rect = { (*i)->GetPosition().Y() * 40, (*i)->GetPosition().X() * 40, 40, 40 };
            SDL_SetRenderDrawColor(renderer, 230, 230, 230, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

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
            SDL_Rect rect = { currentPosition.Y() * 41, currentPosition.X() * 41, 20, 20 };

            if (m_FootPrintTexture)
            {
                double angle = 0;

                int x = previousPosition.X() - currentPosition.X();
                int y = previousPosition.Y() - currentPosition.Y();
                
                if (x != 0 && y != 0)
                {
                    if (x == 1)
                        angle = (y == 1) ? 315 : 45;
                    else
                        angle = (y == 1) ? 225 : 115;
                }
                else if (y != 0)
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

    // Print algorithm name
    {
        SDL_Surface* surface = TTF_RenderText_Solid(m_font, pathFinder->GetName().c_str(), { 0,0,0,0 });
        if (surface)
        {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture)
            {
                SDL_Rect rect = { 5, 5, surface->w, surface->h };
                SDL_RenderCopy(renderer, texture, nullptr, &rect);
            }
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
    }

    SDL_RenderPresent(renderer);
}