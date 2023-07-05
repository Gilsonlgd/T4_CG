#ifndef CONNECTINGROD_H_INCLUDED
#define CONNECTINGROD_H_INCLUDED

#include "Polygon.h"
#include <string>

/*
##### ConnectingRod #####
Implementa a biela
########################
*/

#define BASE_WIDTH 40
#define BASE_HEIGHT 40

#define CONNECTION_INITIAL_WIDTH 20
#define CONNECTION_FINAL_WIDTH 10

class ConnectingRod : public Polygon {
    float len;
    Vector3 pistonPin;
    Vector3 crankPin;

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
        initiateCoordinates();
    }

    void render() {
        CV::translate(0, 0);
        CV::color(0);

        CV::polygon(getXVertices(), getYVertices(), nPoints);
    }

    void update(Vector3 newCrankPin, Vector3 cranckPosition) {
        this->crankPin = newCrankPin;

        float crankPinToCrankPositionLength =
            (newCrankPin - cranckPosition).length();
        Vector3 crankPinToPistonPin = newCrankPin - pistonPin;

        // calcula a distância entre o centro da manivel e o pino do pistão
        // controla a movimentação do pistão no eixo y
        float angle =
            angleDEG(crankPinToPistonPin, newCrankPin - cranckPosition);
        float lastPistonPinY = pistonPin.y;
        pistonPin.y = cranckPosition.y +
                      calculateTriangleSegmentB(crankPinToCrankPositionLength,
                                                len, angle);

        float deltaY = pistonPin.y - lastPistonPinY;
        translateBy(0, deltaY, 0);

        Vector2 pistonPinToCrankPin =
            (newCrankPin - pistonPin).ignoreZCoordinate();
        Vector2 pistonPinToCrankPosition =
            (cranckPosition - pistonPin).ignoreZCoordinate();

        float newAngle =
            -angleDEG(pistonPinToCrankPin, pistonPinToCrankPosition);
        rotate(this->angle - newAngle, pistonPin.x, pistonPin.y);
        this->angle = newAngle;        
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