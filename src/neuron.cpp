#include "neuron.h"

Neuron::Neuron() {
    value               = 0;
    layer               = 0;
    gradient            = 0.0;
    valueTexture        = nullptr;
}

Neuron::~Neuron() {
    SDL_DestroyTexture(valueTexture);
}

Neuron::Neuron(int x, int y, double radius, Color color, SDL_Renderer* renderer) {
    this->value         = value;
    this->position      = std::make_pair( x, y );
    this->radius        = radius;
    this->color         = color;
    this->valueTexture  = nullptr;
}

void Neuron::draw_neuron(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_RenderDrawCircle(renderer, position.first, position.second, radius);
    SDL_RenderFillCircle(renderer, position.first, position.second, radius);

    // draw txt
    SDL_Rect renderQuad = { tX, tY, tWidth, tHeight };
    SDL_RenderCopy(renderer, valueTexture, nullptr, &renderQuad);
}

void Neuron::setValue( double value ) {
    this->value = value;
}

void Neuron::setLayer( int layer ) {
    switch (layer) {
        default:
        case 0:
            this->color = Color(0, 255, 0, 255);        // 绿色
            break;
        case 1:
            this->color = Color(128, 128, 128, 255);    // 灰色
            break;
        case 2:
            this->color = Color(0, 0, 255, 255);        // 蓝色
            break;
    }

    this->layer = layer;
}

position_t Neuron::getPosition() {
    return this->position;
}

double Neuron::getValue() {
    return this->value;
}

int Neuron::getLayer() {
    return this->layer;
}

void Neuron::setGradient(double gradient) {
    this->gradient = gradient;
}

double Neuron::getGradient() {
    return this->gradient;
}

void Neuron::updateVisuals( SDL_Renderer* renderer ) {

    // text texture
    std::stringstream ss;

    // double val = ( value != 1 && value != 0 ) ? log ( abs ( value / (1 - value) ) ) / log(std::exp(1)): value ;
    ss << std::fixed << std::setprecision(1) << value;
    std::string valueText = ss.str() ;

    SDL_Color textColor = { 255, 0, 0, 255 };           // 红色
    SDL_Surface* textSurface = TTF_RenderText_Solid(Resourcer::getInstance().getFont(), valueText.c_str(), textColor);

    tWidth = textSurface->w;
    tHeight = textSurface->h;
    tX = position.first - tWidth / 2;
    tY = position.second - tHeight / 2;

    // init valueTexture
    valueTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
}

/*
    removed sigmoid 1/(1+e^(-x)) because of corvengence to 0.5
*/
double Neuron::activationFunction() {
    return tanh( this->value );
}

double Neuron::activationFunctionDerivative() {
    return 1.0 - this->value * this->value;
}