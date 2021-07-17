#pragma once
#include <list>
#include <functional>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "IPathFindingAlgorithm.h"
#include "Node.h"

class PathFinder
{
public:
    PathFinder() {}
    ~PathFinder() {}

    void Create(const int32_t width,const int32_t height, SDL_Renderer *renderer);

    void Update();
    void Renderer(SDL_Renderer* renderer);
    void HandleUserInput(std::function<void(Position&)> callBack);
    void ChangePathFindingAlgorithm(const SDL_Event& event);
    
private:

    bool validMouseInput;

    Position mouseInputPosition;

    IPathFindingAlgorithm* pathFinder;

    Position m_StartPosition;
    Position m_EndPosition;
    std::list<std::shared_ptr<Node>> m_path;

    SDL_Texture* m_StartPositionTexture;
    SDL_Texture* m_EndPositionTexture;
    SDL_Texture* m_FootPrintTexture;
    SDL_Texture* m_WallTexture;

    bool m_IsStartPosition;
    bool m_IsEndPosition;
    std::list<Position> m_Wall;

    void UpdateWall(const  Position& position);
    SDL_Texture* LoadTexture(std::string path, SDL_Renderer* renderer);
};