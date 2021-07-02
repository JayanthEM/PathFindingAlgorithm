#pragma once
#include "PathFinderFactory.h"
#include "Node.h"
#include <list>
#include "SDL.h"

class PathFinder
{
public:
    PathFinder() {}
    ~PathFinder() {}

    void Create(const int32_t width,const int32_t height);

    void Update();
    void Renderer(SDL_Renderer* renderer);

private:
    IPathFinder* pathFinder;

    Position m_StartPosition;
    Position m_EndPosition;
    std::list<std::shared_ptr<Node>> m_path;

    bool m_IsStartPosition;
    bool m_IsEndPosition;
    std::list<Position> m_Wall;

    void UpdateWall(const  Position& position);
};