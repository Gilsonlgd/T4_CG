#ifndef PISTON_H_INCLUDED
#define PISTON_H_INCLUDED

#include "Polygon.h"
#include "math_utils.h"

#define PISTON_HEIGHT 100
#define PISTON_WIDTH 100

#define PISTON_THICKNESS 100

/*
##### Pistão #####
Implementa o pistão
##################
*/

class Piston : public Polygon {
    Vector3 connectionRodPin;
    Vector3 crankPosition;

    void initiateCoordinates() {
        float z = connectionRodPin.z;

        vertices[0] = Vector3(connectionRodPin.x - PISTON_WIDTH / 2, connectionRodPin.y - PISTON_HEIGHT*1/3, z - PISTON_THICKNESS/2.0);
        vertices[1] = Vector3(connectionRodPin.x + PISTON_WIDTH / 2, connectionRodPin.y - PISTON_HEIGHT*1/3, z - PISTON_THICKNESS/2.0);
        vertices[2] = Vector3(connectionRodPin.x + PISTON_WIDTH / 2, connectionRodPin.y + PISTON_HEIGHT*2/3, z - PISTON_THICKNESS/2.0);
        vertices[3] = Vector3(connectionRodPin.x - PISTON_WIDTH / 2, connectionRodPin.y + PISTON_HEIGHT*2/3, z - PISTON_THICKNESS/2.0);

        for (int i = 0; i < 4; i++) {
            this->vertices[i + 4] = Vector3(this->vertices[i].x, this->vertices[i].y, z + PISTON_THICKNESS/2.0);
        }


    }   
  public:
    Piston(Vector3 connectionRodPin, Vector3 crankPosition, float v_angle) : Polygon(8) {
        this->connectionRodPin = connectionRodPin;
        this->crankPosition = crankPosition;

        initiateCoordinates();
        rotate(v_angle, connectionRodPin.x, connectionRodPin.y);
    }

    void render(float d) {
        CV::translate(0, 0);
        CV::color(4);

        Vector2* projection = calculateProjection(d, crankPosition);
        drawProjection(projection);
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

    float getHeight() {
        return PISTON_HEIGHT;
    }

    float getWidth() {
        return PISTON_WIDTH;
    }

    float getThickness() {
        return PISTON_THICKNESS;
    }

    Vector3 getConnectionPin() {
        return connectionRodPin;
    }
};

#endif