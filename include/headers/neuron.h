#pragma once

#include <iomanip>
#include <sstream>

#include "resourcer.h"
#include "neuron_type.h"
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

    SDL_Texture* valueTexture;
    int tWidth, tHeight, tX, tY;

    Neuron_T type;

public:

    Neuron();
    ~Neuron();

    Neuron( int x, int y, double radius, Color color, SDL_Renderer* renderer );

    void draw_neuron( SDL_Renderer *renderer );

    void setValue( double value, SDL_Renderer *renderer );

    void setType( Neuron_T type );

    position_t getPosition();

    double getValue();

};