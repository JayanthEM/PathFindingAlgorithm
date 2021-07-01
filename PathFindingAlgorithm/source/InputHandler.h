#pragma once
#include <SDL.h>
#include <queue>
#include "Position.h"

class InputHandler
{
public:
    void HandleInput(bool &quit);
    void ReceivedMouseInput(int x, int y);
    std::queue<Position> inputQueue;
};
