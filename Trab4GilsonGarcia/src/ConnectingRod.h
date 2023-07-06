#ifndef CONNECTINGROD_H_INCLUDED
#define CONNECTINGROD_H_INCLUDED

#include "Polygon.h"
#include <string>

/*
##### ConnectingRod #####
Implementa a biela
########################
*/

#define BASE_WIDTH 80
#define BASE_HEIGHT 80

#define CONNECTION_INITIAL_WIDTH 40
#define CONNECTION_FINAL_WIDTH 15

class ConnectingRod : public Polygon {
    float len;
    Vector3 pistonPin;
    Vector3 crankPin;
    Vector3 initialPistonPin;

    float angle;

    void initiateCoordinates() {
        vertices[0] =
            Vector3(pistonPin.x - CONNECTION_FINAL_WIDTH / 2, pistonPin.y, 1);
        vertices[1] =
            Vector3(pistonPin.x + CONNECTION_FINAL_WIDTH / 2, pistonPin.y, 1);
        vertices[2] = Vector3(pistonPin.x + CONNECTION_INITIAL_WIDTH / 2,
                              pistonPin.y - len + BASE_HEIGHT / 2, 1);
        vertices[3] = Vector3(pistonPin.x + BASE_WIDTH / 2,
                              pistonPin.y - len + BASE_HEIGHT / 2, 1);
        vertices[4] = Vector3(pistonPin.x + BASE_WIDTH / 2,
                              pistonPin.y - len - BASE_HEIGHT / 2, 1);
        vertices[5] = Vector3(pistonPin.x - BASE_WIDTH / 2,
                              pistonPin.y - len - BASE_HEIGHT / 2, 1);
        vertices[6] = Vector3(pistonPin.x - BASE_WIDTH / 2,
                              pistonPin.y - len + BASE_HEIGHT / 2, 1);
        vertices[7] = Vector3(pistonPin.x - CONNECTION_INITIAL_WIDTH / 2,
                              pistonPin.y - len + BASE_HEIGHT / 2, 1);
    }

  public:
    ConnectingRod(float len, Vector3 crankPin) : Polygon(8) {
        this->len = len;
        this->crankPin = crankPin;

        this->pistonPin = Vector3(crankPin.x, crankPin.y + len, crankPin.z);
        this->initialPistonPin = pistonPin - Vector3(0, 100, 0);
        initiateCoordinates();
    }

    void render() {
        CV::translate(0, 0);
        CV::color(0);

        CV::polygon(getXVertices(), getYVertices(), nPoints);
    }

    void update(Vector3 newCrankPin, Vector3 crankPosition) {
        Vector3 A = crankPosition;
        Vector3 B = newCrankPin;
        Vector3 AB = B - A;
        Vector3 BC = newCrankPin - pistonPin;

        float crankR = AB.length();
        // calcula a distância entre o centro da manivela e o pino do pistão
        // controla a movimentação do pistão no eixo y
        float angle = angleDEG(AB, BC);
        float lastPistonPinY = pistonPin.y;

        float AC_Length = calculateTriangleSegmentB(crankR, len, angle);
        pistonPin.y = A.y + AC_Length;

        float deltaY = pistonPin.y - lastPistonPinY;
        translateBy(0, deltaY, 0);

        Vector2 pistonPinToCrankPin =
            (newCrankPin - pistonPin).ignoreZCoordinate();
        Vector2 pistonPinToCrankPosition =
            (crankPosition - pistonPin).ignoreZCoordinate();

        float newAngle =
            -angleDEG(pistonPinToCrankPin, pistonPinToCrankPosition);
        rotate(this->angle - newAngle, pistonPin.x, pistonPin.y);

        this->angle = newAngle;
        this->crankPin = newCrankPin;
    }

    void setLen(float len) { this->len = len; }

    float getLen() { return len; }

    void setPistonPin(Vector3 pistonPin) { this->pistonPin = pistonPin; }

    void rotate(float angle, float cx, float cy) {
        rotatePoints(vertices.data(), nPoints, cx, cy, angle);
    }

    Vector3 getPistonPin() { return pistonPin; }
};

#endif // CONNECTINGROD_H_INCLUDED