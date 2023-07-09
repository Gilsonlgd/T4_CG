#ifndef PISTON_RING_H_INCLUDED
#define PISTON_RING_H_INCLUDED

#include "Vector2.h"
#include "Vector3.h"
#include "constants.h"
#include "gl_canvas2d.h"
#include "math_utils.h"


#include <vector>

using namespace std;

#define PRECISION 0.01
#define HEIGHT_INCREASE 10
#define Y_OFFSET -50
#define HEIGHT 175

/*
##### PistonRing #####
Implementa a capa do pistão
##################
*/

class PistonRing {
    Vector3 position;
    Vector3 crankPosition;

    float radius;
    float height;

    int nPoints;
    float v_angle;

    float angle;
    float angleY;
    float angleX;

    bool visible;

    vector<Vector3> points;

    virtual void translateBy(float xIncrease, float yIncrease, float zIncrease) {
        for (int i = 0; i < nPoints; i++) {
            points[i] = translate3DPoint(points[i], xIncrease, yIncrease, zIncrease);
        }
    }

    void initiateCoordinates() {
        // (y, x, z)
        for (float y = 0; y < height; y += HEIGHT_INCREASE) {
            for (float ang = 0; ang < 2 * PI; ang += PRECISION) {
                float z = radius * cos(ang);
                float x = radius * sin(ang);

                points.push_back(Vector3(position.x + x, position.y + y, position.z + z));
            }
        }
    }

    Vector2 *calculateProjection(float d, Vector3 pivot) {
        Vector2 *projection = new Vector2[nPoints];

        translateBy(-pivot.x, -pivot.y, -pivot.z);

        for (int i = 0; i < nPoints; i++) {
            Vector3 point = points[i];
            point = rotatePointAroundXAxis(point, angleX);
            point = rotatePointAroundYAxis(point, angleY);
            point = translate3DPoint(point, 0, 0, d);
            projection[i] = point.to2D(d);
        }

        translateBy(pivot.x, pivot.y, pivot.z);
        translateProjection(projection, nPoints, pivot.x, pivot.y);

        return projection;
    }

    void drawProjection(Vector2 *p) {     

        for (int i = 0; i < nPoints; i++) {
            CV::point(p[i].x, p[i].y);
        }
    }

  public:
    PistonRing(Vector3 position, Vector3 crankPosition, float piston_width, float piston_depth, float v_angle) {
        this->position = position + Vector3(0, Y_OFFSET, 0);
        this->crankPosition = crankPosition;
        this->v_angle = v_angle;

        this->radius = calculateMinRadiusToFitCube(piston_width, piston_depth);
        this->height = HEIGHT;

        initiateCoordinates();
        this->nPoints = points.size();
        rotate(v_angle, position.x, position.y);

        this->angleY = 0;
        this->angleX = 0;
        this->visible = true;
    }

    void render(float d) {
        if (!visible) return;

        CV::translate(0, 0);
        CV::color(11);

        Vector2 *projection = calculateProjection(d, crankPosition);
        drawProjection(projection);
    }

    void rotate(float angle, float cx, float cy) {
        rotatePoints(points.data(), nPoints, cx, cy, angle);
    }

    void rotateY(float angle) {
        angleY += angle;
    }

    void rotateX(float angle) {
        angleX += angle;
    }

    void setVisible(bool visible) {
        this->visible = visible;
    }

    void toggleVisible() {
        this->visible = !this->visible;
    }
};

#endif // PISTON_RING_H_INCLUDED