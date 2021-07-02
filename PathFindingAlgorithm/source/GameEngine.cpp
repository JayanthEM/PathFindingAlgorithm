#include "GameEngine.h"


GameEngine::GameEngine() : m_quit(false), m_window(nullptr), m_renderer(nullptr)
{
    inputHandler = new InputHandler();
    pathFinder = new PathFinder();
}

GameEngine::~GameEngine()
{    
    delete inputHandler;
    delete pathFinder;
}

void GameEngine::ConstructEngine()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return;

    m_window = SDL_CreateWindow("Path Finding", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (!m_window)
        return;

    m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
}


void GameEngine::GameLoop()
{
    while (!m_quit)
    {
        inputHandler->HandleInput(m_quit);
        pathFinder->Update();
        pathFinder->Renderer(m_renderer);
    }
    
}