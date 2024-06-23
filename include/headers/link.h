#pragma once

#include "neuron.h"
#include "shape.h"

/*
    holds the connections between two specific neurons
    and displays it in a fun color
    contains the value
*/

class Link {

    private:

        Neuron *neuronIn;
        Neuron *neuronOut;

        Color color;

        double weight;

    public:

        Link();
        ~Link();

        Link( Neuron *in, Neuron *out );

        void draw_link(SDL_Renderer *renderer);

        void assignWeight ( double weight );

        double getValue();

};