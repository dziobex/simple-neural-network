#include "layer.h"

Layer::Layer() {
    nextLayer = nullptr;
}

/*
    clean up the layer
*/
Layer::~Layer() {

    for ( auto* neuron : neurons )
        delete neuron;
    
    for ( auto linkList : links )
            for ( auto* link : linkList )
                delete link;
    
}

/*
    adding numbers of neurons of given type
*/
Layer::Layer( int count, Neuron_T type, SDL_Renderer *renderer, int nth = 0, int layersTotal = 1 ) {

    // 800 x 600
    for ( int i = 0; i < count; ++i ) {

        int nx = ( nth + 0.5f ) * 800 / layersTotal;
        int ny = ( i + 0.5f ) * 600 / count;

        Color neuron_color = Color( 128, 128, 128, 255 );
        Neuron* neuron = new Neuron( nx, ny, 50, neuron_color, renderer );

        neuron->setValue( i * 10 + i / 100.f, renderer );

        neuron->setType( type );

        neurons.push_back( neuron );

    }
}

void Layer::setNextLayer( Layer *nextLayer ) {
    this->nextLayer = nextLayer;

    // settle connections
    // we can assume nextLayer already has got some neurons inside

    for ( size_t i = 0; i < neurons.size(); ++i ) {
        Links newLinks;

        for ( size_t j = 0; j < nextLayer->getNeuronsCount(); ++j ) {
            Link* link = new Link( neurons[i], nextLayer->getNeuron(j) );
            newLinks.push_back( link );
        }

        links.push_back( newLinks );
    }

}

void Layer::draw_layer( SDL_Renderer *renderer ) {
    
    // draw links ( with the next layer, if not nullptr )
    if ( nextLayer != nullptr ) {
        for ( auto linkList : links )
            for ( auto* link : linkList )
                link->draw_link(renderer);
    }

    // draw neurons
    for ( auto* neuron : neurons )
        neuron->draw_neuron(renderer);

}

size_t Layer::getNeuronsCount() {
    return this->neurons.size();
}

Neuron* Layer::getNeuron( size_t nth ) {
    if ( nth >= neurons.size() )
        return nullptr;
    return neurons[ nth ];
}

std::vector<Links> Layer::getLinks() {
    return this->links;
}