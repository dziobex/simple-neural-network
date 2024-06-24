#pragma once

#include <math.h>
#include <vector>

#include "network.h"
#include "resourcer.h"
#include "neuron.h"
#include "color.h"
#include "link.h"
#include "constants.h"

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