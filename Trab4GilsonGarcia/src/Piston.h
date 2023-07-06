#ifndef PISTON_H_INCLUDED
#define PISTON_H_INCLUDED

#include "Polygon.h"
#include "math_utils.h"

#define PISTON_HEIGHT 100
#define PISTON_WIDTH 100

class Piston : public Polygon {
    Vector3 connectionRodPin;

    void initiateCoordinates() {
        vertices[0] = Vector3(connectionRodPin.x - PISTON_WIDTH / 2, connectionRodPin.y - PISTON_HEIGHT*1/3, 1);
        vertices[1] = Vector3(connectionRodPin.x + PISTON_WIDTH / 2, connectionRodPin.y - PISTON_HEIGHT*1/3, 1);
        vertices[2] = Vector3(connectionRodPin.x + PISTON_WIDTH / 2, connectionRodPin.y + PISTON_HEIGHT*2/3, 1);
        vertices[3] = Vector3(connectionRodPin.x - PISTON_WIDTH / 2, connectionRodPin.y + PISTON_HEIGHT*2/3, 1);
    }   
  public:
    Piston(Vector3 connectionRodPin, float v_angle) : Polygon(4) {
        this->connectionRodPin = connectionRodPin;

        initiateCoordinates();
        rotate(v_angle, connectionRodPin.x, connectionRodPin.y);
    }

    void render() {
        CV::translate(0, 0);
        CV::color(0);

        CV::polygon(getXVertices(), getYVertices(), nPoints);
        CV::circle(connectionRodPin.x, connectionRodPin.y, 6, 25);
    }

    void update(Vector3 newConnectionPin) {
        float deltaX = newConnectionPin.x - connectionRodPin.x;
        float deltaY = newConnectionPin.y - connectionRodPin.y;
        translateBy(deltaX, deltaY, 0);
        this->connectionRodPin = newConnectionPin;
    }

    void rotate(float angle, float cx, float cy) {
        rotatePoints(vertices.data(), nPoints, cx, cy, angle);
    }
};

#endif