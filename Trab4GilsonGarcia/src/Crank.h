#ifndef CRANK_H_INCLUDED
#define CRANK_H_INCLUDED

#include "Polygon.h"
#include "math_utils.h"

#define CRANK_THICKNESS 40

/*
##### Manivela #####
Implementa a manivela do motor
######################
*/

class Crank : public Polygon {
    Vector3 position;      // pivot de rotação da manivela
    Vector3 connectionPin; // ponta da biela

    float r;
    float angleY;

    void translateProjection(Vector2 *p, int n, float dx, float dy) {
        for (int i = 0; i < n; i++) {
            p[i].x += dx;
            p[i].y += dy;
        }
    }

    Vector2* calculateProjection(float d) {
        Vector2* projection = new Vector2[nPoints];
        
        translateBy(-position.x, -position.y, -position.z);
        Vector3 center = getRealCenter();

        for (int i = 0; i < nPoints; i++) {
            Vector3 point = vertices[i];
            point = rotatePointAroundYAxis(point, angleY);
            point = translate3DPoint(point, 0, 0, d);
            projection[i] = point.to2D(d);
        }

        translateBy(position.x, position.y, position.z);
        translateProjection(projection, nPoints, position.x, position.y);

        return projection;
    }

    void drawProjection(Vector2 *p) {
        int secCount = 5;
        for (int i = 1; i < 4; i++) {
            //frente
            CV::line(p[i - 1].x, p[i - 1].y, p[i].x, p[i].y);
            // fundo
            CV::line(p[secCount - 1].x, p[secCount - 1].y, p[secCount].x,
                     p[secCount].y);
            secCount++;
        }
        CV::line(p[3].x, p[3].y, p[0].x, p[0].y);
        CV::line(p[7].x, p[7].y, p[4].x, p[4].y);

        // arestas faltantes
        for (int i = 0; i < 4; i++) {
            CV::line(p[i].x, p[i].y, p[i + 4].x, p[i + 4].y);
        }
    }


  public:
    Crank(float center_radius, float x, float y, float z) : Polygon(8) {
        this->position = Vector3(x, y, z);
        this->r = center_radius;
        this->angleY = 0;

        this->vertices[0] = Vector3(x - center_radius / 3.0, y - center_radius, z - CRANK_THICKNESS/2.0);
        this->vertices[1] = Vector3(x + center_radius * 1.5, y - 20, z - CRANK_THICKNESS/2.0);
        this->vertices[2] = Vector3(x + center_radius * 1.5, y + 20, z - CRANK_THICKNESS/2.0);
        this->vertices[3] = Vector3(x - center_radius / 3.0, y + center_radius, z - CRANK_THICKNESS/2.0);

        this->vertices[4] = Vector3(x - center_radius / 3.0, y - center_radius, z + CRANK_THICKNESS/2.0);
        this->vertices[5] = Vector3(x + center_radius * 1.5, y - 20, z + CRANK_THICKNESS/2.0);
        this->vertices[6] = Vector3(x + center_radius * 1.5, y + 20, z + CRANK_THICKNESS/2.0);
        this->vertices[7] = Vector3(x - center_radius / 3.0, y + center_radius, z + CRANK_THICKNESS/2.0);

        rotatePoints(vertices.data(), nPoints, position.x, position.y, 90);
        this->connectionPin = Vector3(x, y + center_radius, 0);
    }

    void render(float d) {
        CV::translate(0, 0);
        if (colorScale == RGBA)
            CV::color(r, g, b);
        else if (colorScale == INDEX14)
            CV::color(indexColor);

        Vector2* projection = calculateProjection(d);
        drawProjection(projection); 
    }

    void update(float angle) {
        rotatePoints(vertices.data(), nPoints, position.x, position.y, angle);
        rotatePoints(&connectionPin, 1, position.x, position.y, angle);
    }

    void rotateY(float angle) {
        angleY += angle;
    }

    Vector3 getConnectionPoint() { return connectionPin; }

    Vector3 getCenter() { return position; }

    Vector3 getRealCenter() {
        float x = 0;
        float y = 0;
        float z = 0;

        int n = nPoints;
        for (int i = 0; i < n; i++) {
            x += vertices[i].x;
            y += vertices[i].y;
            z += vertices[i].z;
        }

        return Vector3(x / n, y / n, z / n);
    }

    float getRadius() { return r; }
};

#endif // CRANK_H_INCLUDED