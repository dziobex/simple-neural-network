#include "handler.h"

Handler::Handler() { }

/*
    clean up before quitting
*/
Handler::~Handler() {
    printf("HANDLER is being destroyed\n");

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/*
    checking if sdl engine can be settled
*/
bool Handler::init() {
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 )        // init displayer
        return false;
    
    if( TTF_Init() == -1 )                      // init font
        return false;
    
    this->window = SDL_CreateWindow("MLP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 );

    if ( this-> window == nullptr )
        return false;

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if ( this->renderer == nullptr )
        return false;

    return true;
}

/*
    main ""game"" loop
*/
void Handler::start() {
    SDL_Event event;
    bool running = true;

    Network* network = new Network();

    network->init( {2, 3, 1}, renderer );

    /*
        teaching the network --- xor set
    */

   //int x = 0;
   int cn = 0;
    while ( cn < 100 ) {
        network->learn( { 1, 0 }, 1, renderer );
        network->learn( { 0, 1 }, 1, renderer );
        network->learn( { 0, 0 }, 0, renderer );
        network->learn( { 1, 1 }, 0, renderer );
        ++cn;
    }

    printf("%d\n", cn);

    network->forwardPropagation( {0, 0}, renderer);

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // draw background
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // draw!
        network->draw_network( renderer );

        // update the scene
        SDL_RenderPresent(renderer);

    }

    delete network;
}