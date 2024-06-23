#include "shape.h"

/*
    CREDITS for "circling" modules:
    Gumichan01
    https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c
    thanks!
*/

int
SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}


int
SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int
SDL_RenderDrawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, int thickness) {
    // invalid thickness
    if (thickness <= 0) {
        return -1;
    }

    // line's angle and length
    float angle = atan2(y2 - y1, x2 - x1);
    float dx = sin(angle) * thickness / 2.0f;
    float dy = cos(angle) * thickness / 2.0f;

    // points of the thick line's quad
    SDL_Point points[4];
    points[0].x = x1 + dx;
    points[0].y = y1 - dy;
    points[1].x = x2 + dx;
    points[1].y = y2 - dy;
    points[2].x = x2 - dx;
    points[2].y = y2 + dy;
    points[3].x = x1 - dx;
    points[3].y = y1 + dy;

    // filled quadrilateral
    SDL_RenderDrawLine(renderer, points[0].x, points[0].y, points[1].x, points[1].y);
    SDL_RenderDrawLine(renderer, points[1].x, points[1].y, points[2].x, points[2].y);
    SDL_RenderDrawLine(renderer, points[2].x, points[2].y, points[3].x, points[3].y);
    SDL_RenderDrawLine(renderer, points[3].x, points[3].y, points[0].x, points[0].y);

    // Scanline Fill Algorithm
    int min_x = fmin(fmin(points[0].x, points[1].x), fmin(points[2].x, points[3].x));
    int max_x = fmax(fmax(points[0].x, points[1].x), fmax(points[2].x, points[3].x));
    int min_y = fmin(fmin(points[0].y, points[1].y), fmin(points[2].y, points[3].y));
    int max_y = fmax(fmax(points[0].y, points[1].y), fmax(points[2].y, points[3].y));

    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            int i, j;
            int intersections = 0;
            for (i = 0, j = 3; i < 4; j = i++) {
                if (((points[i].y > y) != (points[j].y > y)) &&
                    (x < (points[j].x - points[i].x) * (y - points[i].y) / (points[j].y - points[i].y) + points[i].x)) {
                    intersections++;
                }
            }
            if (intersections % 2 != 0) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }

    return 0;
}