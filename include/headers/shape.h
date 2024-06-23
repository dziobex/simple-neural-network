#pragma once

#include "SDL.h"
#include <math.h>

/*
    simple modules, which allow to draw complex shapes
    such as circle, thick line etc
*/

int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius);

int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

int SDL_RenderDrawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int thickness);