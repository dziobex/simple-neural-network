#pragma once

#include <vector>
#include "neuron.h"
#include "link.h"

/*
    each layer consists of the set of neurons
    there are 3 types of layer: input, hidden, output
    layer manages the neurons actions
*/

typedef std::vector<Neuron*> Neurons;
typedef std::vector<Link*>   Links;

class Layer {

private:

    Neuron_T type;

public:

    Neurons neurons;
    
    std::vector<Links> links;

    Layer* nextLayer;

    Layer();
    
    ~Layer();

    Layer( int count, Neuron_T type, SDL_Renderer *renderer, int nth, int layersTotal );

    void setNextLayer( Layer *nextLayer );

    void draw_layer( SDL_Renderer *renderer );

    size_t getNeuronsCount();

    Neuron* getNeuron( size_t nth );

    std::vector<Links> getLinks();

    

};