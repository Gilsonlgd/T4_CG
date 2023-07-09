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

#define CONNECTION_INITIAL_WIDTH 45
#define CONNECTION_FINAL_WIDTH 18

#define CONNECTING_ROD_LEN 235
#define CONNECTING_ROD_THICKNESS 20.0

/*
##### Biela #####
Implementa a biela
##################
*/

class ConnectingRod : public Polygon {
    Vector3 pistonPin;
    Vector3 crankPin;
    Vector3 crankPosition;
    Vector3 initialPistonPin;

    float angle;
    float len;
    float v_angle;

    void initiateCoordinates() {
        float z = pistonPin.z;

        vertices[0] =
            Vector3(pistonPin.x - CONNECTION_FINAL_WIDTH / 2, pistonPin.y + 15, z - CONNECTING_ROD_THICKNESS / 2.0);
        vertices[1] =
            Vector3(pistonPin.x + CONNECTION_FINAL_WIDTH / 2, pistonPin.y + 15, z - CONNECTING_ROD_THICKNESS / 2.0);
        vertices[2] = Vector3(pistonPin.x + CONNECTION_INITIAL_WIDTH / 2,
                              pistonPin.y - len + BASE_HEIGHT / 2, z - CONNECTING_ROD_THICKNESS / 2.0);
        vertices[3] = Vector3(pistonPin.x + BASE_WIDTH / 2,
                              pistonPin.y - len + BASE_HEIGHT / 2, z - CONNECTING_ROD_THICKNESS / 2.0);
        vertices[4] = Vector3(pistonPin.x + BASE_WIDTH / 2,
                              pistonPin.y - len - BASE_HEIGHT / 2, z - CONNECTING_ROD_THICKNESS / 2.0);
        vertices[5] = Vector3(pistonPin.x - BASE_WIDTH / 2,
                              pistonPin.y - len - BASE_HEIGHT / 2, z - CONNECTING_ROD_THICKNESS / 2.0);
        vertices[6] = Vector3(pistonPin.x - BASE_WIDTH / 2,
                              pistonPin.y - len + BASE_HEIGHT / 2, z - CONNECTING_ROD_THICKNESS / 2.0);
        vertices[7] = Vector3(pistonPin.x - CONNECTION_INITIAL_WIDTH / 2,
                              pistonPin.y - len + BASE_HEIGHT / 2, z - CONNECTING_ROD_THICKNESS / 2.0);
        
        for (int i = 0; i < 8; i++) {
            this->vertices[i + 8] = Vector3(this->vertices[i].x, this->vertices[i].y, z + CONNECTING_ROD_THICKNESS / 2.0);
        }
    }

  public:
    ConnectingRod(Vector3 crankPosition, float crankR, float v_angle)
        : Polygon(16) {
        this->len = CONNECTING_ROD_LEN;
        this->v_angle = v_angle;
        this->angle = 0;
        
        this->crankPin = crankPosition + Vector3(0, crankR, 0);
        this->crankPosition = crankPosition;

        this->pistonPin = Vector3(crankPin.x, crankPin.y + len, crankPin.z);
        this->initialPistonPin = pistonPin;

        initiateCoordinates();

        rotate(v_angle, crankPin.x, crankPin.y);

        rotatePoint(pistonPin.x, pistonPin.y, crankPin.x, crankPin.y, v_angle);

        rotatePoint(initialPistonPin.x, initialPistonPin.y, crankPin.x,
                    crankPin.y, v_angle);
    }

    ConnectingRod(Vector3 crankPosition, float crankR, float v_angle, float z_connection)
        : Polygon(16) {
        this->len = CONNECTING_ROD_LEN;
        this->v_angle = v_angle;
        this->angle = 0;
        
        this->crankPin = crankPosition + Vector3(0, crankR, z_connection);
        this->crankPosition = crankPosition;

        this->pistonPin = Vector3(crankPin.x, crankPin.y + len, crankPin.z);
        this->initialPistonPin = pistonPin;

        initiateCoordinates();

        rotate(v_angle, crankPin.x, crankPin.y);

        rotatePoint(pistonPin.x, pistonPin.y, crankPin.x, crankPin.y, v_angle);

        rotatePoint(initialPistonPin.x, initialPistonPin.y, crankPin.x,
                    crankPin.y, v_angle);
    }

    void render(float d) {
        if (!visible) return;
        
        CV::translate(0, 0);
        CV::color(0);

        Vector2* projection = calculateProjection(d, crankPosition);
        drawProjection(projection);
    }

    void update(Vector3 newCrankPin, Vector3 crankPosition) {
        Vector3 A = crankPosition;
        Vector3 B = newCrankPin;
        Vector3 AB = B - A;
        Vector3 BC = newCrankPin - pistonPin;

        float crankR = AB.length();
        float ang = angleDEG(AB, BC);
        float lastPistonPinX = pistonPin.x;
        float lastPistonPinY = pistonPin.y;

        // Inclinação dos pistões
        float inclineAngle = -v_angle * PI / 180.0;

        // Calcula a nova posição do pistão
        float AC_Length = calculateTriangleSegmentB(crankR, len, ang);
        pistonPin.x = A.x + AC_Length * sin(inclineAngle);
        pistonPin.y = A.y + AC_Length * cos(inclineAngle);

        float deltaX = pistonPin.x - lastPistonPinX;
        float deltaY = pistonPin.y - lastPistonPinY;

        translateBy(deltaX, deltaY, 0);

        // Atualiza a rotação da biela para acompanhar o movimento da manivela
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

    Vector3 getPosition() {
        float x = 0;
        float y = 0;
        for (int i = 3; i <= 6; i++) {
            x += vertices[i].x;
            y += vertices[i].y;
        }

        return Vector3(x / 4, y / 4, 0);
    }

    Vector3 getPistonPin() { return pistonPin; }
};

#endif // CONNECTINGROD_H_INCLUDED