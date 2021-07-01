#pragma once
#include "PathFinderFactory.h"
#include "Node.h"
#include <List>

class PathFinder
{
public:

    ~PathFinder() {}

    void Create(const int32_t width,const int32_t height);

    void Update();
    void Renderer();

private:
    IPathFinder* pathFinder;

    Position m_StartPosition;
    Position m_EndPosition;
    std::list<std::shared_ptr<Node>> m_path;
    
};