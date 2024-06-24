#include "network.h"

Network::Network() {}

Network::~Network() {

    for ( auto* neuron : neurons )
        delete neuron;
    
    for ( auto* con : connections )
        delete con;
        
}

/*
    built has size of the numbers of layer
    each i-element of ne value, represents the number of neurons (ne) in i+1 layer
    built must have 2 or more elements (its total count will be n)
    0th element is input
    (n - 1)th element is output
*/
void Network::init( std::vector<int> built, SDL_Renderer *renderer ) {

    if ( built.size() < 2 )
        return;

    // init neurons
    for ( size_t b = 0; b < built.size(); ++b ) {
        
        bool biased = (b != built.size() - 1);
        
        for ( int count = 0; count < (built[b] + biased); ++count ) {

            int _x = ( b + 0.5f ) * SCREEN_WIDTH / built.size() ;
            int _y = ( count + 0.5f ) * SCREEN_HEIGHT / (built[b]+biased) ;

            Neuron* neu = new Neuron( _x, _y, NEURON_RADIUS, Color( 128, 128, 128, 255 ), renderer );
            neu->setValue( count == built[b] ? 1 : 0, renderer );
            neu->setLayer( b == 0 ? 0 : ( b == built.size() - 1 ) ? 2 : 1 );
            neu->setBiased( count == built[b] );

            neurons.push_back( neu );

        }
    }

    // init connections ( n - 1 layer to n layer )
    for ( size_t i = 0; i < neurons.size(); ++i ) {

        for ( size_t j = 0; j < neurons.size(); ++j ) {
            if ( neurons[i]->getLayer() + 1 == neurons[j]->getLayer() && !neurons[j]->isBiased() ) {
                // establish link

                Link* con = new Link( neurons[i], neurons[j] );
                connections.push_back( con );

            }
            else if ( neurons[i]->getLayer() + 1 < neurons[j]->getLayer() ) {
                break; // more than 2 layers, but connections are sorted by a layer number
            }
        }
    }
    
    // set random weights between neurons
    setRandomWeights();
}

void Network::draw_network( SDL_Renderer* renderer ) {
    
    // draw connections
    for ( auto con : connections )
        con->draw_link( renderer );
    

    // draw neurons
    for ( auto* neuron : neurons )
        neuron->draw_neuron(renderer);
}


/*
    assign random weights to the connections <-0.5; 0.5>
*/
void Network::setRandomWeights() {

    std::mt19937 gen( time(nullptr) );
    std::uniform_real_distribution<> range(-1, 1);

    for ( auto* con : connections ) {
        double w = range( gen );
        con->assignWeight( w );
    }

}

/*
    forward propagation
*/
void Network::forwardPropagation( std::vector<int> input, SDL_Renderer* renderer ) {

    for ( size_t i = 0; i < input.size(); ++i ) {
        neurons[i]->setValue( input[i], renderer );
    }

    for ( size_t i = 0; i < neurons.size(); ++i ) {
        if ( neurons[i]->getLayer() == 0 )
            continue;
        
        if ( neurons[i]->isBiased()) continue;

        double newValue = 0;

        for ( auto* con : connections ) {
            if ( con->isOutNeuron( neurons[i] ) )
                newValue += con->getValue();
        }

        neurons[i]->setValue( newValue, renderer );
        neurons[i]->activationFunction( renderer );

    }
}

void Network::backwardPropagation() {
    // determine the error
}

bool Network::learn( std::vector<int> input, int output, SDL_Renderer* renderer ) {
    
    forwardPropagation( input, renderer );

    /*
        backward propagation
    */

    double error =  output - neurons[ neurons.size() - 1 ]->getValue();
    neurons[ neurons.size() - 1 ]->setValue( output, renderer );

    // CHECK IF FOUNNDD

    //printf("%f ", error * LEARNING_PRECISION);
    if ( output != error && abs(round( error * LEARNING_PRECISION )) == 0 ) {

        printf("%d xor %d = %d\n", input[0], input[1], output);
        forwardPropagation( input, renderer );

        return true;
    }
    

    for ( int i = neurons.size() - 2; i >= 0; --i ) {    // omitting the output layer
    
        double newValue = 0;

        if ( neurons[i]->isBiased() )
            continue;

        for ( auto* con : connections ) {

            if ( con->isInNeuron( neurons[i] ) )
                newValue += con->getBValue();
            
        }

        neurons[i]->setValue( newValue, renderer );
        neurons[i]->activationFunction( renderer );

    }

    // adjust connections' weights
    for ( auto* con : connections ) {
        double w = con->getWeight();

        w += LEARNING_RATE * con->getInValue() * con->getOutValue() * ( 1.f - con->getWeight() );

        con->assignWeight( w );
    }
    
    return false;
}