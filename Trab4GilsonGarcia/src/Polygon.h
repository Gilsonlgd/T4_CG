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
de n vertices.
######################
*/

class Polygon {
  protected:
    int nPoints;
    vector<Vector3> vertices;
    float angle;
    float angleY;
    float angleX;

    float offsetX, offsetY;

    float r, g, b;
    int indexColor;
    int colorScale;

    bool visible;

    // translada de acordo com um valor
    virtual void translateBy(float xIncrease, float yIncrease,
                             float zIncrease) {
        for (int i = 0; i < nPoints; i++) {
            vertices[i] =
                translate3DPoint(vertices[i], xIncrease, yIncrease, zIncrease);
        }
    }

    // translada para uma posição
    virtual void translateTo(float x, float y, float z) {
        float xIncrease = x - vertices[0].x;
        float yIncrease = y - vertices[0].y;
        float zIncrease = z - vertices[0].z;
        translateBy(xIncrease, yIncrease, zIncrease);
    }

    Vector2 *getProjection(float d) {
        Vector2 *pl_project = new Vector2[nPoints];
        for (int i = 0; i < nPoints; i++) {
            pl_project[i] = project3DPoint(vertices[i], d);
        }
        return pl_project;
    }

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

    Vector2* calculateProjection(float d, Vector3 pivot) {
        Vector2* projection = new Vector2[nPoints];
        
        translateBy(-pivot.x, -pivot.y, -pivot.z);

        for (int i = 0; i < nPoints; i++) {
            Vector3 point = vertices[i];
            point = rotatePointAroundYAxis(point, angleY);
            point = rotatePointAroundXAxis(point, angleX);
            point = translate3DPoint(point, 0, 0, d);
            projection[i] = point.to2D(d);
        }

        translateBy(pivot.x, pivot.y, pivot.z);
        translateProjection(projection, nPoints, pivot.x, pivot.y);
        
        return projection;
    }

    void drawProjection(Vector2 *p) {
        int secCount = (nPoints / 2) + 1;
        int n = nPoints / 2;
        
        for (int i = 1; i < n; i++) {
            //frente
            CV::line(p[i - 1].x, p[i - 1].y, p[i].x, p[i].y);
            // fundo
            CV::line(p[secCount - 1].x, p[secCount - 1].y, p[secCount].x,
                     p[secCount].y);
            secCount++;
        }
        CV::line(p[n-1].x, p[n-1].y, p[0].x, p[0].y);
        CV::line(p[nPoints-1].x, p[nPoints-1].y, p[n].x, p[n].y);

        // arestas faltantes
        for (int i = 0; i < n; i++) {
            CV::line(p[i].x, p[i].y, p[i + n].x, p[i + n].y);
        }
    }

  public:
    Polygon(int nPoints) {
        r = 1;
        g = 0;
        b = 0;
        indexColor = 2;
        angle = 0;
        angleY = 0;
        angleX = 0;

        colorScale = INDEX14;

        this->nPoints = nPoints;
        for (int i = 0; i < nPoints; i++) {
            vertices.push_back(Vector3(0, 0, 0));
        }

        visible = true;
    }

    virtual void render(float d) {
        if (!visible) return;

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
        visible = !visible;
    }

    float getColorR() { return r; }

    float getColorG() { return g; }

    float getColorB() { return b; }

    int getIndexColor() { return indexColor; }

    int getColorScale() { return colorScale; }

    float getAngle() { return angle; }
};

#endif // FIGURA_H_INCLUDED
