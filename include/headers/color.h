#pragma once

#include "SDL.h"

/*
    simple structure that holds 4 pieces of color
*/

struct Color {
    Uint8 r, g, b, a;

    Color()
        : r(0), g(0), b(0), a(0) {}

    Color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) 
        : r(red), g(green), b(blue), a(alpha) {}
};