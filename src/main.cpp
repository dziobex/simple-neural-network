#define SDL_MAIN_HANDLED

#include "handler.h"

int main( int argc, char** args ) {

    Handler *handler = new Handler();

    if ( handler->init() )
        handler->start();

    delete handler;

    return 0;
}
