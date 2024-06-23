#include "network.h"

Network::Network() {

}

Network::~Network() {
    delete inputLayer;
    delete outputLayer;
}

void Network::init( int in, int hid, int out ) {
    // 
}

void Network::draw_network( SDL_Renderer* renderer ) {

}


/*
    assign random weights to the connections <-0.5; 0.5>
*/
void Network::setRandomWeights() {
    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<> range(-0.5, 0.5);

    /*
    // input
    for ( size_t i = 0; i < inputLayer.links.size(); ++i ) {
        for ( size_t j = 0; j < inputLayer.links[i].size(); ++j ) {

            double weight = range(gen);
            printf("%f, ", weight );

            inputLayer.links[i][j]->assignWeight( weight );
        }
    }

    // hidden
    for ( size_t a = 0; a < hiddenLayers.size(); ++a ) {
        for ( size_t i = 0; i < hiddenLayers[a].links.size(); ++i ) {
            for ( size_t j = 0; j < hiddenLayers[a].links[i].size(); ++j ) {

                double weight = range(gen);
                printf("%f, ", weight );

                hiddenLayers[a].links[i][j]->assignWeight( weight );
            }
        }
    }
    */
}

void Network::backwardPropagation() {
    // determine the error
}

void launchTest() {

}