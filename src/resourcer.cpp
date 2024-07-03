#include "resourcer.h"

/*
    first instance
*/
Resourcer::Resourcer() {
    std::cout << "Resourcer is being created.\n";

    // load font
    font = TTF_OpenFont( "res/Anonymous.ttf", 28 );

    if ( font == NULL )
        std::cerr << "Couldn't load the font! " << TTF_GetError() << "\n";
}

/*
    🎶i want to be break free🎶
*/
Resourcer::~Resourcer() {
    std::cout << "Resourcer is being destroyed.\n";
    TTF_CloseFont( font );
}

/*
    one instance of the object should be fine
*/
Resourcer& Resourcer::getInstance() {
    static Resourcer res;
    return res;
}

TTF_Font* Resourcer::getFont() {
    return this->font;
}

void Resourcer::setFontSize(int size) {
    TTF_SetFontSize( this->font, size );
}