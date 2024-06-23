#pragma once

#include <random>

#include "layer.h"

/*
    central management
*/

class Network {

private:

    Layer* inputLayer;

    std::vector<Layer> hiddenLayers;
    
    Layer* outputLayer;

public:

    Network();
    ~Network();

    void init( int in, int hid, int out );

    void draw_network( SDL_Renderer* renderer );

    void setRandomWeights();

    void backwardPropagation();

    void launchTest();


};