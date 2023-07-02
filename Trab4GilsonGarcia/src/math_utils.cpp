#include "math_utils.h"

using namespace std;

vector<vector<float>> multiplyMatrices(const vector<vector<float>> &matrix1,
                                       const vector<vector<float>> &matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int rows2 = matrix2.size();
    int cols2 = matrix2[0].size();

    vector<vector<float>> result(rows1, vector<float>(cols2, 0.0f));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

float dotProduct(float x1, float y1, float x2, float y2) {
    return x1 * x2 + y1 * y2;
}

void projectPolygon(const vector<float> &vertices, float axisX, float axisY,
                    float &min, float &max) {
    min = dotProduct(vertices[0], vertices[1], axisX, axisY);
    max = min;

    for (size_t i = 2; i < vertices.size(); i += 2) {
        float projection =
            dotProduct(vertices[i], vertices[i + 1], axisX, axisY);
        if (projection < min) {
            min = projection;
        } else if (projection > max) {
            max = projection;
        }
    }
}

float evaluateBSpline(float p1, float p2, float p3, float p4, float t) {
    return (pow((1 - t), 3.0) / 6) * p1 +
           ((3 * pow(t, 3.0) - 6 * pow(t, 2.0) + 4) / 6) * p2 +
           ((-3 * pow(t, 3.0) + 3 * pow(t, 2.0) + 3 * t + 1) / 6) * p3 +
           (pow(t, 3.0) / 6) * p4;
}

float randomFloat(float min, float max) {
    static mt19937 rng(time(nullptr));
    uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

// calcula a distancia entre dois pontos
// pode ser visto também como o módulo de um vetor
float dist(float x1, float y1, float x2, float y2) {
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

// retorna o angulo entre dois vetores (x1, y1) e (x2, y2) em graus
float angleDEG(float x1, float y1, float x2, float y2) {
    return (atan2(y1, x1) - atan2(y2, x2)) * 180.0 / PI;
}

// rotaciona em angle um ponto (x1, y1) com relação a um pivot
// recebe o angle em graus e transforma para RAD
void rotatePoint(float &x1, float &y1, float pivotX, float pivotY,
                 float angle) {
    // Converte o ângulo para radianos
    float rad = (angle)*PI / 180.0;
    float rotMatrix[2][2] = {{cos(rad), -sin(rad)}, {sin(rad), cos(rad)}};

    x1 -= pivotX;
    y1 -= pivotY;

    // Rotaciona o ponto utilizando a matriz de rotação
    float newX = x1 * rotMatrix[0][0] + y1 * rotMatrix[0][1];
    float newY = x1 * rotMatrix[1][0] + y1 * rotMatrix[1][1];

    x1 = newX;
    y1 = newY;

    // Translada o ponto de volta para a sua posição original
    x1 += pivotX;
    y1 += pivotY;
}

// rotaciona em angle os pontos da figura com relação a um pivot
// recebe o angle em graus e transforma para RAD
void rotatePoints(float *vx, float *vy, int nPoints, float pivotX, float pivotY,
                  float angle) {
    // Converte o ângulo para radianos
    float rad = (angle)*PI / 180.0;

    float rotMatrix[2][2] = {{cos(rad), -sin(rad)}, {sin(rad), cos(rad)}};

    for (int i = 0; i < nPoints; i++) {
        // Translada o ponto para o ponto de pivot
        vx[i] -= pivotX;
        vy[i] -= pivotY;

        // Rotaciona o ponto utilizando a matriz de rotação
        float x = vx[i] * rotMatrix[0][0] + vy[i] * rotMatrix[0][1];
        float y = vx[i] * rotMatrix[1][0] + vy[i] * rotMatrix[1][1];

        vx[i] = x;
        vy[i] = y;

        // Translada o ponto de volta para a sua posição original
        vx[i] += pivotX;
        vy[i] += pivotY;
    }
}

float calculateMagnitude(float x, float y) { return sqrt(x * x + y * y); }

// avalia bezier de grau 2
float evaluateBezier2(float p1, float p2, float p3, float t) {
    return p1 * pow((1 - t), 2) + p2 * (2 * t * (1 - t)) + p3 * pow(t, 2);
}

// avalia bezier de grau 3
float evaluateBezier3(float p1, float p2, float p3, float p4, float t) {
    return p1 * pow((1 - t), 3) + p2 * (3 * t * pow((1 - t), 2)) +
           p3 * (3 * pow(t, 2) * (1 - t)) + p4 * pow(t, 3);
}

Vector2 project3DPoint(Vector3 v, float d) {
    Vector2 v2;
    v2.x = v.x * d / (v.z);
    v2.y = v.y * d / (v.z);

    return v2;
}

Vector3 rotatePointAroundYAxis(Vector3 p, double angle) {
    Vector3 rotatedPoint;

    // Conversão do ângulo de graus para radianos
    double theta = angle * PI / 180.0;

    // Matriz de rotação em torno do eixo y
    double rotationMatrix[3][3] = {
        {cos(theta), 0, sin(theta)}, {0, 1, 0}, {-sin(theta), 0, cos(theta)}};

    // Realiza a multiplicação da matriz de rotação pelo ponto
    rotatedPoint.x = rotationMatrix[0][0] * p.x + rotationMatrix[0][1] * p.y +
                     rotationMatrix[0][2] * p.z;
    rotatedPoint.y = rotationMatrix[1][0] * p.x + rotationMatrix[1][1] * p.y +
                     rotationMatrix[1][2] * p.z;
    rotatedPoint.z = rotationMatrix[2][0] * p.x + rotationMatrix[2][1] * p.y +
                     rotationMatrix[2][2] * p.z;

    return rotatedPoint;
}

Vector3 rotatePointAroundXAxis(Vector3 p, double angle) {
    Vector3 rotatedPoint;

    // Conversão do ângulo de graus para radianos
    double theta = angle * PI / 180.0;

    // Matriz de rotação em torno do eixo x
    double rotationMatrix[3][3] = {
        {1, 0, 0}, {0, cos(theta), -sin(theta)}, {0, sin(theta), cos(theta)}};

    // Realiza a multiplicação da matriz de rotação pelo ponto
    rotatedPoint.x = rotationMatrix[0][0] * p.x + rotationMatrix[0][1] * p.y +
                     rotationMatrix[0][2] * p.z;
    rotatedPoint.y = rotationMatrix[1][0] * p.x + rotationMatrix[1][1] * p.y +
                     rotationMatrix[1][2] * p.z;
    rotatedPoint.z = rotationMatrix[2][0] * p.x + rotationMatrix[2][1] * p.y +
                     rotationMatrix[2][2] * p.z;

    return rotatedPoint;
}

Vector3 rotatePointAroundZAxis(Vector3 p, double angle) {
    Vector3 rotatedPoint;

    // Conversão do ângulo de graus para radianos
    double theta = angle * PI / 180.0;

    // Matriz de rotação em torno do eixo z
    double rotationMatrix[3][3] = {
        {cos(theta), -sin(theta), 0}, {sin(theta), cos(theta), 0}, {0, 0, 1}};

    // Realiza a multiplicação da matriz de rotação pelo ponto
    rotatedPoint.x = rotationMatrix[0][0] * p.x + rotationMatrix[0][1] * p.y +
                     rotationMatrix[0][2] * p.z;
    rotatedPoint.y = rotationMatrix[1][0] * p.x + rotationMatrix[1][1] * p.y +
                     rotationMatrix[1][2] * p.z;
    rotatedPoint.z = rotationMatrix[2][0] * p.x + rotationMatrix[2][1] * p.y +
                     rotationMatrix[2][2] * p.z;

    return rotatedPoint;
}

Vector3 translate3DPoint(Vector3 p, float dx, float dy, float dz) {
    // Criando a matriz de translação
    float translationMatrix[4][4] = {{1.0f, 0.0f, 0.0f, dx},
                                     {0.0f, 1.0f, 0.0f, dy},
                                     {0.0f, 0.0f, 1.0f, dz},
                                     {0.0f, 0.0f, 0.0f, 1.0f}};

    // Adicionando as coordenadas do ponto como uma coluna
    float pointMatrix[4][1] = {{p.x}, {p.y}, {p.z}, {1.0f}};

    // Multiplicando a matriz de translação pelo ponto
    float transformedPoint[4][1];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 1; ++j) {
            transformedPoint[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                transformedPoint[i][j] +=
                    translationMatrix[i][k] * pointMatrix[k][j];
            }
        }
    }

    // Criando o vetor Vector3 com as coordenadas transformadas
    Vector3 translatedPoint;
    translatedPoint.x = transformedPoint[0][0];
    translatedPoint.y = transformedPoint[1][0];
    translatedPoint.z = transformedPoint[2][0];

    return translatedPoint;
}
