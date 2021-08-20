#pragma once
#include <SDL.h>
#include "SDL_ttf.h"
#include "InputHandler.h"
#include "PathFinder.h"

#define WIDTH 800
#define HEIGHT 600

//Not a Generic GameEngine, tightly bounded to pathfinding algorithm
class GameEngine
{
public:
    
    GameEngine();
    ~GameEngine();

    void ConstructEngine();
    void GameLoop();
    
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

private:
    
    bool m_quit;
    
    InputHandler *inputHandler;
    PathFinder *pathFinder;
};