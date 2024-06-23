#include "link.h"

Link::Link() {
    neuronIn  = nullptr;
    neuronOut = nullptr;
}

Link::~Link() {
    
}

Link::Link( Neuron *in, Neuron *out ) {
    neuronIn  = in;
    neuronOut = out;

    weight = 0;

    this->color = Color( 0, 0, 0, 255 );
}

void Link::draw_link(SDL_Renderer *renderer) {
    if ( neuronIn == nullptr || neuronOut == nullptr )
        return;

    SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
    SDL_RenderDrawLine( renderer,
                        neuronIn->getPosition().first,
                        neuronIn->getPosition().second,
                        neuronOut->getPosition().first,
                        neuronOut->getPosition().second, 5 );
}

void Link::assignWeight ( double weight ) {
    this->weight = weight;
}

double Link::getValue() {
    if ( neuronIn == nullptr )
        return -1;
    return this->weight * neuronIn->getValue();
}