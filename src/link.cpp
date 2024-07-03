#include "link.h"

Link::Link() {
    neuronIn  = nullptr;
    neuronOut = nullptr;
}

Link::~Link() { }

Link::Link( Neuron *in, Neuron *out ) {
    neuronIn  = in;
    neuronOut = out;
    weight = 0;
    this->color = Color( 0, 0, 0, 255 );
}

void Link::draw_link( SDL_Renderer *renderer ) {
    if ( neuronIn == nullptr || neuronOut == nullptr )
        return;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
    SDL_RenderDrawLine( renderer,
                        neuronIn->getPosition().first,
                        neuronIn->getPosition().second,
                        neuronOut->getPosition().first,
                        neuronOut->getPosition().second, 5 );
}

void Link::assignWeight ( double weight ) {
    this->weight = weight;

    // change color
    color.r = weight < 0.f ? 255 : 0;
    color.g = weight > 0.f ? 255 : 0;
    color.b = 0;
    color.a = (Uint8) ( (double)255 * abs( weight ) );

}

double Link::getWeight() {
    return this->weight;
}

Neuron* Link::getInNeuron() {
    return this->neuronIn;
}

Neuron* Link::getOutNeuron() {
    return this->neuronOut;
}