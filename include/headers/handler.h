#pragma once

#include <math.h>

#include "resourcer.h"
#include "neuron.h"
#include "color.h"
#include "link.h"
#include "layer.h"

const int SCREEN_HEIGHT    = 600;
const int SCREEN_WIDTH     = 800;

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