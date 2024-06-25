#include "network.h"
#include <random>
#include <cmath>
#include <cstdio>

Network::Network() {}

Network::~Network() {

    for (auto* neuron : neurons)
        delete neuron;
    for (auto* con : connections)
        delete con;

}

void Network::init(std::vector<double> built, SDL_Renderer* renderer) {
    if (built.size() < 2)   // please, give me more!
        return;

    // innit neurons ( order, visuals etc )
    for (size_t b = 0; b < built.size(); ++b) {
        for (int count = 0; count < built[b]; ++count) {
            int _x = (b + 0.5f) * SCREEN_WIDTH / built.size();
            int _y = (count + 0.5f) * SCREEN_HEIGHT / built[b];
            
            Neuron* neu = new Neuron(_x, _y, NEURON_RADIUS, Color(128, 128, 128, 255), renderer);
            neu->setValue(0, renderer);
            neu->setLayer(b == 0 ? 0 : (b == built.size() - 1) ? 2 : 1);

            neurons.push_back(neu);
        }
    }

    // innit connections (n-1 layer to n layer)
    for (size_t i = 0; i < neurons.size(); ++i) {
        for (size_t j = 0; j < neurons.size(); ++j) {
            if (neurons[i]->getLayer() + 1 == neurons[j]->getLayer()) {
                Link* con = new Link(neurons[i], neurons[j]);
                connections.push_back(con);
            } else if (neurons[i]->getLayer() + 1 < neurons[j]->getLayer()) {
                break; // more than 2 layers - hey! connections are sorted by the layer number
            }
        }
    }

    setRandomWeights();
}

void Network::draw_network(SDL_Renderer* renderer) {

    // draw connections
    for (auto con : connections)
        con->draw_link(renderer);

    // draw neurons
    for (auto* neuron : neurons)
        neuron->draw_neuron(renderer);

}

/*
    each connection gets number from a range (-0.5; 0.5)
*/
void Network::setRandomWeights() {
    std::mt19937 gen(time(nullptr));
    std::uniform_real_distribution<> range(-0.5, 0.5);

    for (auto* con : connections) {
        double w = range(gen);
        con->assignWeight(w);
    }
}

/*
    the easier one B) B(
*/
void Network::forwardPropagation(std::vector<double> input, SDL_Renderer* renderer ) {
    /*
        inputs X, Y from the user
    */
    for (size_t i = 0; i < input.size(); ++i)
        neurons[i]->setValue(input[i], renderer);

    for (size_t i = input.size() ; i < neurons.size(); ++i) {
        if ( neurons[i]->getLayer() == 0 )
            continue;

        double newValue = 0;

        for (auto* con : connections) {
            if ( con->isOutNeuron( neurons[i]) )
                newValue += con->getValue();
        }

        neurons[i]->setValue(newValue, renderer);
        neurons[i]->activationFunction( renderer );
    }
}

void Network::backwardPropagation(double target, SDL_Renderer* renderer) {

    Neuron* outputNeuron = neurons.back();
    double output = outputNeuron->getValue();
    double outputError = output - target;
    outputNeuron->setGradient(outputError * output * (1 - output));

    for (int i = neurons.size() - 2; i >= 0; --i) {
        Neuron* neuron = neurons[i];

        double gradientSum = 0.0;
        for (auto* con : connections) {
            if (con->isInNeuron(neuron)) {
                gradientSum += con->getWeight() * con->getOutNeuron()->getGradient();
            }
        }
        neuron->setGradient(gradientSum * neuron->getValue() * (1 - neuron->getValue()));
    }

    // adjust connections' weights
    for (auto* con : connections) {
        double deltaWeight = LEARNING_RATE * con->getInNeuron()->getValue() * con->getOutNeuron()->getGradient();
        con->assignWeight(con->getWeight() + deltaWeight);
    }
}

bool Network::learn(std::vector<double> input, double output, SDL_Renderer* renderer) {

    forwardPropagation(input, renderer);

    backwardPropagation( output, renderer );

    double o = output;
    double error = o - neurons[neurons.size() - 1]->getValue();

    if ( abs(error) < LEARNING_PRECISION ) { // error close enough to 0 is fine
        //printf("%d xor %d = %d\n", input[0], input[1], output);

        // displayNetwork();

        return true;
    }

    return false;
}

void Network::displayNetwork() {
    for (size_t i = 0; i < neurons.size(); ++i) {
        if (neurons[i]->isBiased()) {}

        printf("Neuron %d, layer %d, value %f:\n", i, neurons[i]->getLayer(), neurons[i]->getValue());

        for (auto* con : connections) {
            if (con->isInNeuron(neurons[i]))
                printf("\t%f\n", con->getWeight());
        }
        printf("\n");
    }
}
