#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__

#include "Vector2.h"
#include <cmath>
#include <stdio.h>


class Vector3 {
  public:
    float x, y, z;

    Vector3() { x = y = z = 0; }

    Vector3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void set(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void normalize() {
        float norm = (float)sqrt(x * x + y * y + z * z);

        if (norm == 0.0) {
            printf("\n\nNormalize::Divisao por zero");
            x = 1;
            y = 1;
            z = 1;
            return;
        }
        x /= norm;
        y /= norm;
        z /= norm;
    }

    float dot(Vector3 v) { return x * v.x + y * v.y + z * v.z; }

    float length() { return (float)sqrt(x * x + y * y + z * z); }

    Vector3 operator-(const Vector3 &v) const {
        Vector3 aux(x - v.x, y - v.y, z - v.z);
        return aux;
    }

    Vector3 operator+(const Vector3 &v) const {
        Vector3 aux(x + v.x, y + v.y, z + v.z);
        return aux;
    }

    Vector2 ignoreZCoordinate() { return Vector2(x, y); }

    // Adicionem os demais overloads de operadores aqui.
};

#endif
