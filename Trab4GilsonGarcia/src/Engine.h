#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "ConnectingRod.h"
#include "Crank.h"
#include "Piston.h"
#include "PistonRing.h"

#include "Polygon.h"
#include "math_utils.h"

#include <list>

#define SPEED_UP 0.25
#define V_ANGLE 45
#define CONNECTIONS_DISTANCE 28
#define CAM_DISTANCE 1200

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
    PistonRing *rightPistonRing;

    ConnectingRod *leftConnectingRod;
    Piston *leftPiston;
    PistonRing *leftPistonRing;

    list<Vector3> list;

  public:
    Engine(float speed, float x, float y, float z) {
        this->speed = speed;
        this->crank = new Crank(100, x, y, z);

        Vector3 connectionPin = crank->getConnectionPoint();

        // incia o pistão direito
        this->rightConnectingRod =
            new ConnectingRod(crank->getCenter(), crank->getRadius(), -V_ANGLE, -CONNECTIONS_DISTANCE / 2.0);

        this->rightPiston = new Piston(rightConnectingRod->getPistonPin(), crank->getCenter(), -V_ANGLE);

        // incia o pistão esquerdo
        this->leftConnectingRod =
            new ConnectingRod(crank->getCenter(), crank->getRadius(), V_ANGLE, CONNECTIONS_DISTANCE / 2.0);

        this->leftPiston = new Piston(leftConnectingRod->getPistonPin(),
                                      crank->getCenter(), V_ANGLE);

        this->update();
        this->rightPistonRing = new PistonRing(rightPiston->getConnectionPin(), crank->getCenter(), rightPiston->getWidth(),
                                               rightPiston->getThickness(), -V_ANGLE);
        this->leftPistonRing = new PistonRing(leftPiston->getConnectionPin(), crank->getCenter(), leftPiston->getWidth(),
                                               leftPiston->getThickness(), V_ANGLE);                          
    }

    void render() {
        crank->render(CAM_DISTANCE);

        rightConnectingRod->render(CAM_DISTANCE);
        rightPiston->render(CAM_DISTANCE);
        rightPistonRing->render(CAM_DISTANCE);

        leftConnectingRod->render(CAM_DISTANCE);
        leftPiston->render(CAM_DISTANCE);
        leftPistonRing->render(CAM_DISTANCE);
    }

    void update() {
        crank->update(speed);

        rightConnectingRod->update(crank->getConnectionPoint(),
                                   crank->getCenter());
        rightPiston->update(rightConnectingRod->getPistonPin());

        leftConnectingRod->update(crank->getConnectionPoint(),
                                  crank->getCenter());
        leftPiston->update(leftConnectingRod->getPistonPin());
    }

    void rotateY(float angle) {
        crank->rotateY(angle);

        rightConnectingRod->rotateY(angle);
        rightPiston->rotateY(angle);
        rightPistonRing->rotateY(angle);

        leftConnectingRod->rotateY(angle);
        leftPiston->rotateY(angle);
        leftPistonRing->rotateY(angle);
    }

    void rotateX(float angle) {
        crank->rotateX(angle);

        rightConnectingRod->rotateX(angle);
        rightPiston->rotateX(angle);
        rightPistonRing->rotateX(angle);

        leftConnectingRod->rotateX(angle);
        leftPiston->rotateX(angle);
        leftPistonRing->rotateX(angle);
    }

    void toggleCrankVisibility() { crank->toggleVisible(); }

    void toggleConnectingRodVisibility() {
        rightConnectingRod->toggleVisible();
        leftConnectingRod->toggleVisible();
    }

    void togglePistonVisibility() {
        rightPiston->toggleVisible();
        leftPiston->toggleVisible();
    }

    void togglePistonRingVisibility() {
        rightPistonRing->toggleVisible();
        leftPistonRing->toggleVisible();
    }

    void speedUP() { speed -= SPEED_UP; }

    void speedDOWN() { speed += SPEED_UP; }
};

#endif // ENGINE_H_INCLUDED