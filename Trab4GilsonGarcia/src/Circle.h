#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "Polygon.h"
#include "Vector2.h"
#include "constants.h"
#include <cmath>

#define LEFT_SIDE 0
#define RIGHT_SIDE 1
#define TOP_SIDE 2
#define BOTTOM_SIDE 3
#define MIN_RADIUS 7

using namespace std;

/*
##### Círculo #####
Implementa um circulo simples
######################
*/

class Circle : public Polygon {
    float radius;

  protected:
  public:
    Circle(float radius, float x, float y) : Polygon(1) {
        this->radius = radius;
        vertices[0] = Vector3(x, y, 0);
    }

    void render() {
        CV::translate(0, 0);
        if (colorScale == RGBA)
            CV::color(r, g, b);
        else if (colorScale == INDEX14)
            CV::color(indexColor);

        CV::circleFill(vertices[0].x, vertices[0].y, radius, NUM_SEGMENTS);
        CV::translate(0, 0);
    }

    float getCenterX() { return vertices[0].x; }
    float getCenterY() { return vertices[0].y; }

    float getRadius() { return radius; }

    void setPosition(float x, float y) { vertices[0] = Vector3(x, y, 0); }
};

#endif // CIRCLE_H_INCLUDED
