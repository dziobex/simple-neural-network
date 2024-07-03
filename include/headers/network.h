#pragma once

#include <random>
#include <ctime>

#include "neuron.h"
#include "link.h"
#include "constants.h"

/*
    central management
*/

class Network {

private:

    std::vector<Neuron*> neurons;
    std::vector<int>     biases;        // for each layer, except of the input one
    std::vector<Link*>   connections;

    void setRandomWeights();
    
    void forwardPropagation( std::vector<double> input );
    void backwardPropagation( double target );

    double lr;

public:

    Network();
    ~Network();

    void init( std::vector<double> built, SDL_Renderer *renderer );

    void draw_network( SDL_Renderer* renderer );

    void displayNetwork( std::vector<std::vector<double>>& input );

    double train( std::vector<std::vector<double>>& input, std::vector<double>& output );

};