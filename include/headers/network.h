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
    std::vector<Link*>   connections;

    void setRandomWeights();

    void backwardPropagation( double target, SDL_Renderer* renderer );

    

public:

    void forwardPropagation( std::vector<double> input, SDL_Renderer* renderer );

    Network();
    ~Network();

    void init( std::vector<double> built, SDL_Renderer *renderer );

    bool learn( std::vector<double> input, double output, SDL_Renderer* renderer );

    void draw_network( SDL_Renderer* renderer );

    void displayNetwork();

};