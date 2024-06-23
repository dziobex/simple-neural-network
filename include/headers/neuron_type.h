#pragma once

/*
    neuron can belong to one of the 3 general layers:
    input, hidden, output
*/

typedef enum NeuronType {
    input,
    hidden,
    output
} Neuron_T;