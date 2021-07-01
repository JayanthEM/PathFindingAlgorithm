#include "InputHandler.h"


void InputHandler::HandleInput(bool &quit)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;

        case SDL_MOUSEBUTTONDOWN:
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            ReceivedMouseInput(x, y);
        }
            break;
        default:
            break;
        }
    }
}

void InputHandler::ReceivedMouseInput(int x, int y)
{
    inputQueue.push(Position(x, y));
}