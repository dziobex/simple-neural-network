#include "handler.h"

Handler::Handler() {

}

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

    Layer* layer1 = new Layer( 2, input, renderer, 0, 3 );
    Layer* layer2 = new Layer( 2, hidden, renderer, 1, 3 );    
    Layer* layer3 = new Layer( 1, output, renderer, 2, 3 );

    layer1->setNextLayer( layer2 );
    layer2->setNextLayer( layer3 );    

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

        layer1->draw_layer( renderer );
        layer2->draw_layer( renderer );
        layer3->draw_layer( renderer );

        // update the scene
        SDL_RenderPresent(renderer);

    }

    delete layer1;
    delete layer2;
    delete layer3;

}