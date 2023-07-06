#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "ConnectingRod.h"
#include "Crank.h"
#include "Piston.h"
#include "Polygon.h"
#include "math_utils.h"


#include <list>

#define SPEED_UP 0.25
#define V_ANGLE 45

/*
##### Motor #####
Implementa o motor
##################
*/

class Engine {
    float speed;
    Crank *crank;

    ConnectingRod *rightConnectingRod;
    Piston *rightPiston;

    ConnectingRod *leftConnectingRod;
    Piston *leftPiston;

    list<Vector3> list;

  public:
    Engine(float speed, float x, float y, float z) {
        this->speed = speed;
        this->crank = new Crank(100, x, y, z);

        Vector3 connectionPin = crank->getConnectionPoint();

        // incia o pistão direito
        this->rightConnectingRod =
            new ConnectingRod(crank->getCenter(), crank->getRadius(), -V_ANGLE);

        this->rightPiston = new Piston(rightConnectingRod->getPistonPin(), -V_ANGLE);

        // inicia o pistão esquerdo
        this->leftConnectingRod =
            new ConnectingRod(crank->getCenter(), crank->getRadius(), V_ANGLE);

        this->leftPiston = new Piston(leftConnectingRod->getPistonPin(), V_ANGLE);
    }

    void render() {
        crank->render();

        rightConnectingRod->render();
        rightPiston->render();

        leftConnectingRod->render();
        leftPiston->render();
    }

    void update() {
        crank->rotate(speed);

        rightConnectingRod->update(crank->getConnectionPoint(),
        crank->getCenter()); 
        rightPiston->update(rightConnectingRod->getPistonPin());

        leftConnectingRod->update(crank->getConnectionPoint(),
        crank->getCenter());
        leftPiston->update(leftConnectingRod->getPistonPin());
    }

    void speedUP() { speed -= SPEED_UP; }

    void speedDOWN() { speed += SPEED_UP; }
};

#endif // ENGINE_H_INCLUDED