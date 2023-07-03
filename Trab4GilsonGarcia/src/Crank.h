#ifndef CRANK_H_INCLUDED
#define CRANK_H_INCLUDED

#include "Polygon.h"
#include "math_utils.h"

/*
##### Manivela #####
Implementa a manivela do motor
######################
*/

class Crank : public Polygon {
    Vector3 position; //pivot de rotação da manivela
    Vector3 connectingRod; //ponta da biela

    float r = 0.0f;
    
    float* getXVertices() {
        float* xVertices = new float[nPoints];
        for (int i = 0; i < nPoints; i++) {
            xVertices[i] = vertices[i].x;
        }
        return xVertices;
    }

    float* getYVertices() {
        float* yVertices = new float[nPoints];
        for (int i = 0; i < nPoints; i++) {
            yVertices[i] = vertices[i].y;
        }
        return yVertices;
    }

  public:
    Crank(float center_radius, float x, float y, float z) : Polygon(4) {
        this->position = Vector3(x, y, z);
        this->r = center_radius;
        this->vertices[0] = Vector3(x - center_radius/3.0, y - center_radius, 1);
        this->vertices[1] = Vector3(x + center_radius*1.5, y - 20, 1);
        this->vertices[2] = Vector3(x + center_radius*1.5, y + 20, 1);
        this->vertices[3] = Vector3(x - center_radius/3.0, y + center_radius, 1);
        rotatePoints(vertices.data(), nPoints, position.x, position.y, 90);

        this->connectingRod = Vector3(x, y + center_radius, 0);
        
    }

    void render() {
        CV::translate(0, 0);
        if (colorScale == RGBA)
            CV::color(r, g, b);
        else if (colorScale == INDEX14)
            CV::color(indexColor);

        CV::polygon(getXVertices(), getYVertices(), nPoints);

        CV::color(0);
        CV::circle(position.x, position.y, r/10, 50);

        CV::color(0, 0, 255);
        CV::circle(connectingRod.x, connectingRod.y, r/10, 50);

    }

    void rotate(float angle, float cx, float cy) {
        rotatePoints(vertices.data(), nPoints, cx, cy, angle);
        rotatePoints(&connectingRod, 1, cx, cy, angle);
    }

    void rotate(float angle) {
        rotatePoints(vertices.data(), nPoints, position.x, position.y, angle);
        rotatePoints(&connectingRod, 1, position.x, position.y, angle);
    }

    Vector3 getConnectionPoint() {
        return connectingRod;
    }

    Vector3 getCenter() {
        return position;
    }

    float getRadius() {
        return r/3.0;
    }

};

#endif // CRANK_H_INCLUDED