#include "network.h"

Network::Network() {}

Network::~Network() {

    for ( auto* neuron : neurons )
        delete neuron;
    
    for ( auto* con : connections )
        delete con;

}

void Network::init( std::vector<double> built, SDL_Renderer* renderer ) {
    if ( built.size() < 2 )   // please, give me more!
        return;

    lr = LEARNING_RATE;         // got to be adjusted as the training number increases

    // innit neurons ( the order, visuals etc )
    for ( size_t b = 0; b < built.size(); ++b ) {

        for ( int count = 0; count < built[b]; ++count ) {
            
            int _x = ( b + 0.5f ) * SCREEN_WIDTH / built.size();
            int _y = ( count + 0.5f ) * SCREEN_HEIGHT / built[b];
            
            Neuron* neu = new Neuron( _x, _y, NEURON_RADIUS, Color( 128, 128, 128, 255 ), renderer );
            neu->setValue( 0 );

            neu->setLayer( b ); // 0, 1, 2, 3
            neurons.push_back( neu );
        }

    }

    // innit connections (n-1 layer to n layer)
    for ( size_t i = 0; i < neurons.size(); ++i ) {

        for ( size_t j = i + 1; j < neurons.size(); ++j ) {

            if ( neurons[i]->getLayer() + 1 == neurons[j]->getLayer() ) {
                Link* con = new Link( neurons[i], neurons[j] );
                connections.push_back( con );
            }
            else if ( neurons[i]->getLayer() + 1 < neurons[j]->getLayer() ) {
                break; // more than 2 layers - hey! connections are sorted by the layer number
            }

        }

    }

    // add biases for each non-input layer
    for ( size_t i = 0; i < built.size() - 1; ++i )
        biases.push_back( 1 );

    setRandomWeights();
}

void Network::draw_network( SDL_Renderer* renderer ) {

    // draw connections (they're behind the neurons because... it looks neat)
    for ( auto con : connections )
        con->draw_link( renderer );

    // draw neurons
    for ( auto* neuron : neurons ) {
        neuron->updateVisuals( renderer );
        neuron->draw_neuron( renderer );
    }

}

/*
    each connection gets a random weight
*/
void Network::setRandomWeights() {
    std::mt19937 gen( time( nullptr ) );
    std::uniform_real_distribution<> range( -0.75f, 0.75f );

    for ( auto* con : connections ) {
        double w = range( gen );
        con->assignWeight( w );
    }
}

/*
    the easier one B) B(
*/
void Network::forwardPropagation( std::vector<double> input ) {
    /*
        inputs X, Y from the user
    */
    for ( size_t i = 0; i < input.size(); ++i ) {
        neurons[i]->setValue( input[i] );
    }

    for ( size_t i = 0; i < neurons.size(); ++i ) {
        if ( neurons[i]->getLayer() == 0 )
            continue;

        double newValue = 0.0;

        for ( auto* con : connections ) {
            if ( con->getOutNeuron() == neurons[i] )
                newValue += con->getInNeuron()->getValue() * con->getWeight();
        }

        neurons[i]->setValue( newValue + biases[ neurons[i]->getLayer() - 1 ] );
        neurons[i]->setValue( neurons[i]->activationFunction() );
    }
}

/*
    what a headache
*/
void Network::backwardPropagation( double target ) {

    double outputError = target - neurons.back()->getValue();

    neurons.back()->setGradient( outputError );

    for ( int i = neurons.size() - 2; i >= 0; --i ) {
        
        double gradientSum = 0.0;

        for ( auto* con : connections )
            if ( con->getInNeuron() == neurons[i] )
                gradientSum += con->getWeight() * con->getOutNeuron()->getGradient();
                
        neurons[i]->setGradient( gradientSum * neurons[i]->activationFunctionDerivative() );
    }

    // adjust weights

    for ( auto* con : connections ) {
        
        double deltaWeight =
            LEARNING_RATE * con->getInNeuron()->getValue() * con->getOutNeuron()->getGradient() ;

        con->assignWeight( con->getWeight() + deltaWeight );

        // change biases
        biases[ con->getOutNeuron()->getLayer() - 1 ] += LEARNING_RATE * con->getOutNeuron()->getGradient();
    }
}

void Network::displayNetwork( std::vector<std::vector<double>>& input ) {

    if ( input.size() < 3 )
        return;

    for ( size_t i = 0; i < input.size(); ++i ) {
        forwardPropagation( input[i] );
        printf( "%.1f xor %.1f = %.1f\n", neurons[0]->getValue(), neurons[1]->getValue(), abs( neurons.back()->getValue() ) );
    }

}

double Network::train( std::vector<std::vector<double>>& input, std::vector<double>& output ) {
    double error = 0.0;

    for ( size_t i = 0; i < input.size(); ++i ) {
        forwardPropagation( input[i] );
        backwardPropagation( output[i] );

        error += pow( neurons.back()->getGradient(), 2 );
    }

    lr *= 0.99f;

    return error / input.size() ;
}
