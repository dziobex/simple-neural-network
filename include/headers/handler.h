#pragma once

#include <vector>

#include "network.h"

class Handler {

private:

    SDL_Renderer *renderer = nullptr;
    SDL_Window   *window   = nullptr;

public:

    Handler();
    ~Handler();

    bool init();
    void start();

};