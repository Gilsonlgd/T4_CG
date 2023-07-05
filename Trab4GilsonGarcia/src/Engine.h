#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "ConnectingRod.h"
#include "Crank.h"
#include "Polygon.h"
#include "Piston.h"
#include "math_utils.h"


#define CONNECTING_ROD_LEN 235
#define SPEED_UP 0.25

/*
##### Motor #####
Implementa o motor
##################
*/

class Engine {
    float speed;
    Crank *crank;
    ConnectingRod *connectingRod;
    Piston* piston;

  public:
    Engine(float speed, float x, float y, float z) {
        this->speed = speed;
        this->crank = new Crank(100, x, y, z);

        Vector3 connectionPin = crank->getConnectionPoint();
        this->connectingRod = new ConnectingRod(
            CONNECTING_ROD_LEN, connectionPin);

        this->piston = new Piston(connectingRod->getPistonPin());
    }

    void render() {
        crank->render();
        connectingRod->render();
        piston->render();
    }

    void update() {
        crank->rotate(speed);
        connectingRod->update(crank->getConnectionPoint(), crank->getCenter());
        piston->update(connectingRod->getPistonPin());
    }

    void speedUP() {
        speed += SPEED_UP;
    }

    void speedDOWN() {
        speed -= SPEED_UP;
    }
};

#endif // ENGINE_H_INCLUDED