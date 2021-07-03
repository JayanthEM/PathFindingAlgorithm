#include "InputHandler.h"


void InputHandler::HandleInput(bool &quit,PathFinder* pathFinder)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;

        case SDL_SCANCODE_1:
        case SDL_SCANCODE_2:
            pathFinder->ChangePathFindingAlgorithm(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            pathFinder->HandleUserInput([&](Position& position) { position = Position(x, y); });
        }
        break;
        default:
            break;
        }
    }
}