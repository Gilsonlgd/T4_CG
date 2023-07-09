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
#define CENTER_DISTANCE 80
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

    ConnectingRod *rightConnectingRod_2;
    Piston *rightPiston_2;
    PistonRing *rightPistonRing_2;

    ConnectingRod *leftConnectingRod_2;
    Piston *leftPiston_2;
    PistonRing *leftPistonRing_2;

    list<Vector3> list;

    float v_angle;

  public:
    Engine(float speed, float x, float y, float z) {
        this->speed = speed;
        this->crank = new Crank(100, x, y, z);
        this->v_angle = V_ANGLE;

        Vector3 connectionPin = crank->getConnectionPoint();

        // inicia o pistão direito
        this->rightConnectingRod =
            new ConnectingRod(crank->getCenter(), crank->getRadius(), -V_ANGLE, -CONNECTIONS_DISTANCE / 2.0 - CENTER_DISTANCE);

        this->rightPiston = new Piston(rightConnectingRod->getPistonPin(), crank->getCenter(), -V_ANGLE);

        // incia o pistão esquerdo
        this->leftConnectingRod =
            new ConnectingRod(crank->getCenter(), crank->getRadius(), V_ANGLE, CONNECTIONS_DISTANCE / 2.0 - CENTER_DISTANCE);

        this->leftPiston = new Piston(leftConnectingRod->getPistonPin(),
                                      crank->getCenter(), V_ANGLE);
        
        // outros dois
        this->rightConnectingRod_2 =
            new ConnectingRod(crank->getCenter(), crank->getRadius(), -V_ANGLE, -CONNECTIONS_DISTANCE / 2.0 + CENTER_DISTANCE);

        this->rightPiston_2 = new Piston(rightConnectingRod_2->getPistonPin(), crank->getCenter(), -V_ANGLE);

        // inicia o pistão esquerdo
        this->leftConnectingRod_2 =
            new ConnectingRod(crank->getCenter(), crank->getRadius(), V_ANGLE, CONNECTIONS_DISTANCE / 2.0 + CENTER_DISTANCE);

        this->leftPiston_2 = new Piston(leftConnectingRod_2->getPistonPin(),
                                      crank->getCenter(), V_ANGLE);

        this->update();
        this->rightPistonRing = new PistonRing(rightPiston->getConnectionPin(), crank->getCenter(), rightPiston->getWidth(),
                                               rightPiston->getThickness(), -V_ANGLE);
        this->leftPistonRing = new PistonRing(leftPiston->getConnectionPin(), crank->getCenter(), leftPiston->getWidth(),
                                               leftPiston->getThickness(), V_ANGLE);  

        // outros dois
        this->rightPistonRing_2 = new PistonRing(rightPiston_2->getConnectionPin(), crank->getCenter(), rightPiston_2->getWidth(),
                                               rightPiston_2->getThickness(), -V_ANGLE);
        this->leftPistonRing_2 = new PistonRing(leftPiston_2->getConnectionPin(), crank->getCenter(), leftPiston_2->getWidth(),
                                               leftPiston_2->getThickness(), V_ANGLE);                                                         
    }

    void render() {
        crank->render(CAM_DISTANCE);

        rightConnectingRod->render(CAM_DISTANCE);
        rightPiston->render(CAM_DISTANCE);
        rightPistonRing->render(CAM_DISTANCE);

        leftConnectingRod->render(CAM_DISTANCE);
        leftPiston->render(CAM_DISTANCE);
        leftPistonRing->render(CAM_DISTANCE);

        rightConnectingRod_2->render(CAM_DISTANCE);
        rightPiston_2->render(CAM_DISTANCE);
        rightPistonRing_2->render(CAM_DISTANCE);

        leftConnectingRod_2->render(CAM_DISTANCE);
        leftPiston_2->render(CAM_DISTANCE);
        leftPistonRing_2->render(CAM_DISTANCE);
    }

    void update() {
        crank->update(speed);

        rightConnectingRod->update(crank->getConnectionPoint(),
                                   crank->getCenter());
        rightPiston->update(rightConnectingRod->getPistonPin());

        leftConnectingRod->update(crank->getConnectionPoint(),
                                  crank->getCenter());
        leftPiston->update(leftConnectingRod->getPistonPin());

        rightConnectingRod_2->update(crank->getConnectionPoint(),
                                   crank->getCenter());
        rightPiston_2->update(rightConnectingRod_2->getPistonPin());

        leftConnectingRod_2->update(crank->getConnectionPoint(),
                                  crank->getCenter());
        leftPiston_2->update(leftConnectingRod_2->getPistonPin());
    }

    void rotateY(float angle) {
        crank->rotateY(angle);

        rightConnectingRod->rotateY(angle);
        rightPiston->rotateY(angle);
        rightPistonRing->rotateY(angle);

        leftConnectingRod->rotateY(angle);
        leftPiston->rotateY(angle);
        leftPistonRing->rotateY(angle);

        rightConnectingRod_2->rotateY(angle);
        rightPiston_2->rotateY(angle);
        rightPistonRing_2->rotateY(angle);

        leftConnectingRod_2->rotateY(angle);
        leftPiston_2->rotateY(angle);
        leftPistonRing_2->rotateY(angle);
    }

    void rotateX(float angle) {
        crank->rotateX(angle);

        rightConnectingRod->rotateX(angle);
        rightPiston->rotateX(angle);
        rightPistonRing->rotateX(angle);

        leftConnectingRod->rotateX(angle);
        leftPiston->rotateX(angle);
        leftPistonRing->rotateX(angle);

        rightConnectingRod_2->rotateX(angle);
        rightPiston_2->rotateX(angle);
        rightPistonRing_2->rotateX(angle);

        leftConnectingRod_2->rotateX(angle);
        leftPiston_2->rotateX(angle);
        leftPistonRing_2->rotateX(angle);
    }

    void toggleCrankVisibility() { crank->toggleVisible(); }

    void toggleConnectingRodVisibility() {
        rightConnectingRod->toggleVisible();
        leftConnectingRod->toggleVisible();

        /*rightConnectingRod_2->toggleVisible();
        leftConnectingRod_2->toggleVisible();*/
    }

    void togglePistonVisibility() {
        rightPiston->toggleVisible();
        leftPiston->toggleVisible();

        /*rightPiston_2->toggleVisible();
        leftPiston_2->toggleVisible();*/
    }

    void togglePistonRingVisibility() {
        rightPistonRing->toggleVisible();
        leftPistonRing->toggleVisible();

        /*rightPistonRing_2->toggleVisible();
        leftPistonRing_2->toggleVisible();*/
    }

    void speedUP() { speed -= SPEED_UP; }

    void speedDOWN() { speed += SPEED_UP; }

    void increaseV_angle() {
        if (v_angle > 55) return;
        v_angle += 1;

        rightConnectingRod->setV_angle(-v_angle);
        rightPiston->setV_angle(-v_angle);
        rightPistonRing->setV_angle(-v_angle);

        leftConnectingRod->setV_angle(v_angle);
        leftPiston->setV_angle(v_angle);
        leftPistonRing->setV_angle(v_angle);

        rightConnectingRod_2->setV_angle(-v_angle);
        rightPiston_2->setV_angle(-v_angle);
        rightPistonRing_2->setV_angle(-v_angle);

        leftConnectingRod_2->setV_angle(v_angle);
        leftPiston_2->setV_angle(v_angle);
        leftPistonRing_2->setV_angle(v_angle);
    }

    void decreaseV_angle() {
        if (v_angle < 30) return;
        v_angle -= 1;

        rightConnectingRod->setV_angle(-v_angle);
        rightPiston->setV_angle(-v_angle);
        rightPistonRing->setV_angle(-v_angle);

        leftConnectingRod->setV_angle(v_angle);
        leftPiston->setV_angle(v_angle);
        leftPistonRing->setV_angle(v_angle);

        rightConnectingRod_2->setV_angle(-v_angle);
        rightPiston_2->setV_angle(-v_angle);
        rightPistonRing_2->setV_angle(-v_angle);

        leftConnectingRod_2->setV_angle(v_angle);
        leftPiston_2->setV_angle(v_angle);
        leftPistonRing_2->setV_angle(v_angle);
    }
};

#endif // ENGINE_H_INCLUDED