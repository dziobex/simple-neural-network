#pragma once

#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"

/*
    Resource handler
    gets font, images etc - stuff from the outside
*/

class Resourcer {

private:

    Resourcer();
    ~Resourcer();
    
    static Resourcer res;

    /*
        those are loaded!
    */

    TTF_Font* font = NULL;

public:

    static Resourcer& getInstance();

    TTF_Font* getFont();
    void setFontSize(int size);

};