#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "ConnectingRod.h"
#include "Crank.h"
#include "Polygon.h"
#include "math_utils.h"


#define CONNECTING_ROD_LEN 200

/*
##### Motor #####
Implementa o motor
##################
*/

class Engine {
    float speed;
    Crank *crank;
    ConnectingRod *connectingRod;

  public:
    Engine(float speed, float x, float y, float z) {
        this->speed = speed;
        this->crank = new Crank(100, x, y, z);

        Vector3 connectionPin = crank->getConnectionPoint();
        this->connectingRod = new ConnectingRod(
            CONNECTING_ROD_LEN, connectionPin);
    }

    void render() {
        crank->render();
        connectingRod->render();
    }

    void update() {
        crank->rotate(speed);
        connectingRod->update(crank->getConnectionPoint(), crank->getCenter());
    }
};

#endif // ENGINE_H_INCLUDED