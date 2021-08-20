#include "GameEngine.h"


GameEngine::GameEngine() : m_quit(false), m_window(nullptr), m_renderer(nullptr)
{
    inputHandler = new InputHandler();
    pathFinder = new PathFinder();
}

GameEngine::~GameEngine()
{    
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    delete inputHandler;
    delete pathFinder;
}

void GameEngine::ConstructEngine()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0 || TTF_Init() < 0)
        return;
    
    m_window = SDL_CreateWindow("Path Finding", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (!m_window)
        return;

    m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);

    pathFinder->Create(WIDTH / 40, HEIGHT / 40, m_renderer);
}


void GameEngine::GameLoop()
{
    while (!m_quit)
    {
        inputHandler->HandleInput(m_quit, pathFinder);
        pathFinder->Update();
        pathFinder->Renderer(m_renderer);
    }
}