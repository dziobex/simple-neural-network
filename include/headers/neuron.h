#pragma once

#include <iomanip>
#include <sstream>
#include <cmath>

#include "resourcer.h"
#include "color.h"
#include "shape.h"

/*
    displays single neuron
    hold its physical attributes, like: position, color etc
    and its artificial ones: type, as one of the input, hidden or output layer
    also, responsible for contacts between the other neurons
*/

typedef std::pair<int, int> position_t;

class Neuron {

private:

    position_t position;    // position on the screen

    double radius;          // radius of the circle

    Color color;            // color inside the circle

    double value;           // value the neuron holds

    double gradient;        // error

    SDL_Texture* valueTexture;

    int tWidth, tHeight, tX, tY;

    int layer;

public:

    Neuron();
    ~Neuron();

    Neuron( int x, int y, double radius, Color color, SDL_Renderer* renderer );
    
    position_t getPosition();

    void draw_neuron( SDL_Renderer *renderer );
    void updateVisuals( SDL_Renderer* renderer );

    void setValue( double value );
    double getValue();
    
    double activationFunction();
    double activationFunctionDerivative();

    void setLayer( int layer );
    int getLayer( );

    void setGradient (double gradient );
    double getGradient();

};