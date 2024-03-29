#ifndef CRANK_H_INCLUDED
#define CRANK_H_INCLUDED

#include "Polygon.h"
#include "math_utils.h"

#define CRANK_THICKNESS 250

/*
##### Manivela #####
Implementa a manivela do motor
######################
*/

class Crank : public Polygon {
    Vector3 position;      // eixo de rotação da manivela
    Vector3 connectionPin; // ponto de fixação da biela

    float r;

    void initiateCoordinates() {
        float x = position.x;
        float y = position.y;
        float z = position.z;
        float center_radius = r;
        
        this->vertices[0] = Vector3(x - center_radius / 3.0, y - center_radius, z - CRANK_THICKNESS/2.0);
        this->vertices[1] = Vector3(x + center_radius * 1.5, y - 20, z - CRANK_THICKNESS/2.0);
        this->vertices[2] = Vector3(x + center_radius * 1.5, y + 20, z - CRANK_THICKNESS/2.0);
        this->vertices[3] = Vector3(x - center_radius / 3.0, y + center_radius, z - CRANK_THICKNESS/2.0);

        for (int i = 0; i < 4; i++) {
            this->vertices[i + 4] = Vector3(this->vertices[i].x, this->vertices[i].y, z + CRANK_THICKNESS/2.0);
        }
    }

  public:
    // é inicizalida em -90 graus e depois rotacionada
    Crank(float center_radius, float x, float y, float z) : Polygon(8) {
        this->position = Vector3(x, y, z);
        this->r = center_radius;

        initiateCoordinates();

        rotatePoints(vertices.data(), nPoints, position.x, position.y, 90);
        this->connectionPin = Vector3(x, y + center_radius, z);
    }

    void render3D(float d) {
        if (!visible) return;
        
        CV::translate(0, 0);
        if (colorScale == RGBA)
            CV::color(r, g, b);
        else if (colorScale == INDEX14)
            CV::color(indexColor);

        Vector2* projection = calculateProjection(d, position);
        drawProjection(projection); 
    }

    void render2D() {
        if (!visible) return;

        CV::translate(0, 0);
        if (colorScale == RGBA)
            CV::color(r, g, b);
        else if (colorScale == INDEX14)
            CV::color(indexColor);

        Vector2* projection = calculateOrthoProjection(position);
        drawProjection(projection); 

    }

    void update(float angle) {
        rotatePoints(vertices.data(), nPoints, position.x, position.y, angle);
        rotatePoints(&connectionPin, 1, position.x, position.y, angle);
    }

    Vector3 getConnectionPoint() { return connectionPin; }

    // retorna o ponto do eixo da manivela
    Vector3 getCenter() { return position; }
    
    // calcula o ponto médio da manivela
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