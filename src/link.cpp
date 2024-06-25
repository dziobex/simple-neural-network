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

double Link::getValue() {
    if ( neuronIn == nullptr )
        return -1;
    return this->weight * neuronIn->getValue();
}

double Link::getBValue() {
    if ( neuronOut == nullptr )
        return -1;
    return this->weight * neuronOut->getValue();
}

bool Link::isOutNeuron( Neuron* neuron ) {
    return this->neuronOut == neuron;
}

bool Link::isInNeuron( Neuron* neuron ) {
    return this->neuronIn == neuron;
}

double Link::getWeight() {
    return this->weight;
}

double Link::getInValue() {
    return this->neuronIn->getValue();
}

double Link::getOutValue() {
    return this->neuronOut->getValue();
}

Neuron* Link::getInNeuron() {
    return this->neuronIn;
}
Neuron* Link::getOutNeuron() {
    return this->neuronOut;
}