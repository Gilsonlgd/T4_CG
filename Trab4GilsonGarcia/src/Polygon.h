#ifndef FIGURA_H_INCLUDED
#define FIGURA_H_INCLUDED

#include "Vector3.h"
#include "constants.h"
#include "gl_canvas2d.h"
#include "math_utils.h"
#include <cfloat>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

/*
##### Polygon #####
Implementa um polígono
de n lados.
######################
*/

class Polygon {
  protected:
    int nPoints;
    vector<Vector3> vertices;
    float angle;

    float offsetX, offsetY;

    float r, g, b;
    int indexColor;
    int colorScale;

    // translada de acordo com um valor
    virtual void translateBy(float xIncrease, float yIncrease,
                             float zIncrease) {
        for (int i = 0; i < nPoints; i++) {
            vertices[i] =
                translate3DPoint(vertices[i], xIncrease, yIncrease, zIncrease);
        }
    }

    Vector2 *getProjection(float d) {
        Vector2 *pl_project = new Vector2[nPoints];
        for (int i = 0; i < nPoints; i++) {
            pl_project[i] = project3DPoint(vertices[i], d);
        }
        return pl_project;
    }

  public:
    Polygon(int nPoints) {
        r = 1;
        g = 0;
        b = 0;
        indexColor = 2;
        angle = 0;
        colorScale = INDEX14;

        this->nPoints = nPoints;
        for (int i = 0; i < nPoints; i++) {
            vertices.push_back(Vector3(0, 0, 0));
        }
    }

    virtual ~Polygon() {}

    virtual void render(float d) {
        CV::translate(0, 0);
        if (colorScale == RGBA)
            CV::color(r, g, b);
        else if (colorScale == INDEX14)
            CV::color(indexColor);

        Vector2 *pl_project = getProjection(d);
        for (int i = 0; i < nPoints - 1; i++) {
            CV::line(pl_project[i].x, pl_project[i].y, pl_project[i + 1].x,
                     pl_project[i + 1].y);
        }
        // Conecta o último vértice ao primeiro vértice para fechar o polígono
        CV::line(pl_project[nPoints - 1].x, pl_project[nPoints - 1].y,
                 pl_project[0].x, pl_project[0].y);
    }

    void setColor(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
        colorScale = RGBA;
    }

    void setColor(int index) {
        indexColor = index;
        colorScale = INDEX14;
    }

    float getColorR() { return r; }

    float getColorG() { return g; }

    float getColorB() { return b; }

    int getIndexColor() { return indexColor; }

    int getColorScale() { return colorScale; }

    float getAngle() { return angle; }
};

#endif // FIGURA_H_INCLUDED
