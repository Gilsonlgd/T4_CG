#ifndef CONNECTINGROD_H_INCLUDED
#define CONNECTINGROD_H_INCLUDED

#include "Polygon.h"
#include <string>

/*
##### ConnectingRod #####
Implementa a biela
########################
*/

class ConnectingRod {
    float len;
    Vector3 pistonPin;
    Vector3 crankPin;

  public:
    ConnectingRod(float len, Vector3 crankPin) {
        this->len = len;
        this->crankPin = crankPin;

        this->pistonPin = Vector3(crankPin.x, crankPin.y + len, crankPin.z);
    }

    void render() {
        CV::translate(0, 0);
        CV::color(0);
        CV::line(pistonPin.x, pistonPin.y, crankPin.x, crankPin.y);
        char *len = new char[10];

        Vector3 vet = pistonPin - crankPin;
        sprintf(len, "%.2f", vet.length());

        CV::text(pistonPin.x, pistonPin.y, len);
    }

    void update(Vector3 crankPin, Vector3 crankPosition) {
        this->crankPin = crankPin;
        
        float radius = (crankPin - crankPosition).length();
        Vector3 crankPinToPistonPin = crankPin - pistonPin;
        float angle = angleDEG(crankPinToPistonPin, crankPin - crankPosition);

        pistonPin.y = crankPosition.y + calculateTriangleSegmentB(radius, len, angle);
    }

    void setLen(float len) { this->len = len; }

    float getLen() { return len; }

    void setPistonPin(Vector3 pistonPin) { this->pistonPin = pistonPin; }

    Vector3 getPistonPin() { return pistonPin; }
};

#endif // CONNECTINGROD_H_INCLUDED