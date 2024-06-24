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

    void backwardPropagation();

public:

    void forwardPropagation( std::vector<int> input, SDL_Renderer* renderer );

    Network();
    ~Network();

    void init( std::vector<int> built, SDL_Renderer *renderer );

    bool learn( std::vector<int> input, int output, SDL_Renderer* renderer );

    void draw_network( SDL_Renderer* renderer );

};