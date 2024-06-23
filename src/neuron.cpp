#include "neuron.h"

#include <stdio.h>

/*
    default construct
*/
Neuron::Neuron() {

}

Neuron::~Neuron() {
    SDL_DestroyTexture( valueTexture );
}

Neuron::Neuron( int x, int y, double radius, Color color, SDL_Renderer* renderer ) {
    this->position = std::make_pair( x, y );
    this->radius = radius;
    this->color  = color;

    setValue( 0.0, renderer );
}

/*
    displays the neuron's body (BALL)
    with the value it holds
*/
void Neuron::draw_neuron( SDL_Renderer *renderer ) {
    
    SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );

    SDL_RenderDrawCircle( renderer, position.first, position.second, radius );
    SDL_RenderFillCircle( renderer, position.first, position.second, radius );

    // draw text
    SDL_Rect renderQuad = { tX, tY, tWidth, tHeight };
    SDL_RenderCopy(renderer, valueTexture, nullptr, &renderQuad);
    
}

/*
    updates the value in the neuron
    and makes it displayable on the screen
*/
void Neuron::setValue( double value, SDL_Renderer *renderer ) {
    this->value = value;

    /* value gets texted B) */
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << value;
    std::string valueText = ss.str();

    /* prepare the text texure */

    SDL_Color textColor = { 255, 0, 0, 255 };     // 红色
    SDL_Surface* textSurface = TTF_RenderText_Solid( Resourcer::getInstance().getFont(), valueText.c_str(), textColor );

    /* value gets RECTed */
    tWidth = textSurface->w;
    tHeight = textSurface->h;
    tX = position.first - tWidth / 2;
    tY = position.second - tHeight / 2;

    /* init valueTexture */
    valueTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
    SDL_FreeSurface(textSurface);
}

void Neuron::setType( Neuron_T type ) {

    switch ( type ) {
        default:
        case input:
            this->color = Color(0, 255, 0, 255);
            break;
        case hidden:
            this->color = Color(128, 128, 128, 255);
            break;
        case output:
            this->color = Color(0, 0, 255, 255);
            break;
    }

    this->type = type;
}

/*
    returns center of the circle
*/
position_t Neuron::getPosition() {
    return this->position;
}

double Neuron::getValue() {
    return this->value;
}