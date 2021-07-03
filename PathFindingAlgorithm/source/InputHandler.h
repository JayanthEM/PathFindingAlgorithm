#pragma once
#include <SDL.h>
#include <queue>
#include "PathFinder.h"
#include "Position.h"

class InputHandler
{
public:
    void HandleInput(bool &quit, PathFinder* pathFinder);
};
