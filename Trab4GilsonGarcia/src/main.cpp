/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Gilson Garcia
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "gl_canvas2d.h"

using namespace std;

#define X_AXIS_LEN 400
#define Y_AXIS_LEN 400 

struct Vector3 {
   float x, y, z;
};

Vector3 entrada[8];


float x = 100;
float y = 100;
float z = 50;
float d = 131;

float width = 100;
float height = 100;
float deth = 100;


//variavel global para selecao do que sera exibido na canvas.
int opcao  = 50;
int screenWidth = 1200, screenHeight = 700; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY;           //variaveis globais do mouse para poder exibir dentro da render().
bool alreadyTransformed = false;

// copia uma array para o outro
void arrcopy(float *origin, float* dest, int tam){
   for (int i = 0; i < tam; i++) {
      dest[i] = origin[i];
   }
}

// translada um quadrado para algum ponto. offset define o pivot
void translateSquare(float *qx, float *qy, float pivotX, float pivotY) {
   for (int i = 0; i < 4; i++) {
      qx[i] += pivotX;
      qy[i] += pivotY;
   }
}

float getCenterX(float * vx, int nPoints) {
   float sum = 0;
   for (int i = 0; i < nPoints; i++) {
      sum += vx[i]; 
   }

   return sum / nPoints;
}

float getCenterY(float * vy, int nPoints) {
   float sum = 0;
   for (int i = 0; i < nPoints; i++) {
      sum += vy[i]; 
   }

   return sum / nPoints;
}

void rotatePoint(float& x1, float& y1, float angle) {
   // Converte o ângulo para radianos
   float rad = (angle) * PI / 180.0;

   // Rotaciona o ponto utilizando a matriz de rotação
   float newX = x1 * cos(rad) + y1 * (-sin(rad));
   float newY = x1 * sin(rad) + y1 * cos(rad);

   x1 = newX;
   y1 = newY;
}


// rotaciona todos os pontos de um rect
void rotateRect(float* qx, float* qy, float angle) {
   for (int i = 0; i < 4; i++) {
      rotatePoint(qx[i], qy[i], angle);
   }
}

Vector2 project(Vector3 v, float d) {
   Vector2 v2;
   v2.x = v.x * d / (v.z + d);
   v2.y = v.y * d / (v.z + d);

   return v2;
}



void drawCube(Vector2 cube[8]) {
   int secCount = 5;
   for (int i = 1; i < 4; i++) {
      //quadrado da frente
      CV::line(cube[i-1].x, cube[i-1].y, cube[i].x, cube[i].y);
      //quadrado do fundo
      CV::line(cube[secCount - 1].x, cube[secCount - 1].y, cube[secCount].x, cube[secCount].y);
      secCount++;
   }
   CV::line(cube[3].x, cube[3].y, cube[0].x, cube[0].y);
   CV::line(cube[7].x, cube[7].y, cube[4].x, cube[4].y);

   // arestas faltantes
   for (int i = 0; i < 4; i++) {
      CV::line(cube[i].x, cube[i].y, cube[i+4].x, cube[i+4].y);
   }
}

Vector3 rotatePointAroundYAxis(Vector3 p, double angle) {
    Vector3 rotatedPoint;
    
    // Conversão do ângulo de graus para radianos
    double theta = angle * PI / 180.0;
    
    // Matriz de rotação em torno do eixo y
    double rotationMatrix[3][3] = {
        {cos(theta), 0, sin(theta)},
        {0, 1, 0},
        {-sin(theta), 0, cos(theta)}
    };
    
    // Realiza a multiplicação da matriz de rotação pelo ponto
    rotatedPoint.x = rotationMatrix[0][0] * p.x + rotationMatrix[0][1] * p.y + rotationMatrix[0][2] * p.z;
    rotatedPoint.y = rotationMatrix[1][0] * p.x + rotationMatrix[1][1] * p.y + rotationMatrix[1][2] * p.z;
    rotatedPoint.z = rotationMatrix[2][0] * p.x + rotationMatrix[2][1] * p.y + rotationMatrix[2][2] * p.z;
    
    return rotatedPoint;
}
//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
float angle = 0.0;
void render()
{
   Vector3 p;
   Vector2 saida[8];

   for (int i = 0; i < 8; i++) {
      p = entrada[i];
      p = rotatePointAroundYAxis(p, angle);
      saida[i] = project(p, d);
   }

   CV::translate(300, 200);
   CV::color(0);
   angle += 0.3;
   drawCube(saida);
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
   if( key < 200 )
   {
      opcao = key;
   }

   switch(key)
   {  
   }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   switch(key)
   {
      
   }
}


//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
   mouseY = y;

   if(state == 1) {

   };

   if( state == 0 ) //clicou
   {
   }
}

int main(void)
{  
   for (int i = 0; i < 8; i++) {
      entrada[i] = *new Vector3();
   }   

   entrada[0].x = -width/2;
   entrada[0].y = -height/2;
   entrada[0].z = -deth/2;

   entrada[1].x = width/2;
   entrada[1].y = -height/2;
   entrada[1].z = -deth/2;

   entrada[2].x = width/2;
   entrada[2].y = height/2;
   entrada[2].z = -deth/2;

   entrada[3].x = -width/2;
   entrada[3].y = height/2;
   entrada[3].z = -deth/2;

   entrada[4].x = -width/2;
   entrada[4].y = -height/2;
   entrada[4].z = deth/2;

   entrada[5].x = width/2;
   entrada[5].y = -height/2;
   entrada[5].z = deth/2;

   entrada[6].x = width/2;
   entrada[6].y = height/2;
   entrada[6].z = deth/2;

   entrada[7].x = -width/2;
   entrada[7].y = height/2;
   entrada[7].z = deth/2;


   CV::init(&screenWidth, &screenHeight, "");
   CV::run();
}
