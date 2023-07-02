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
#include "math_utils.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Circle.h"

using namespace std;

#define X_AXIS_LEN 400
#define Y_AXIS_LEN 400 

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

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
float angle = 0.0;

float r = 100;
Circle *virabrequim = new Circle(10, r *cos(0.0) + 500, r *sin(0.0) + 200);

void render() {
    for (float ang = 0.0; ang < 2 * PI; ang += 0.001) {
        float x = r * cos(ang) + 500;
        float y = r * sin(ang) + 200;
        CV::color(0, 0, 0);
        CV::point(x, y);
    }

    angle += 0.01;
    if (angle > 360)
        angle = 0;

    virabrequim->render();
}
/*void render()
{
   Vector3 p;
   Vector2 saida[8];

   for (int i = 0; i < 8; i++) {
      p = entrada[i];
      p = rotatePointAroundZAxis(p, angle);
      p = rotatePointAroundYAxis(p, angle);
      p = translate3DPoint(p, 0, 0, d + 100);
      saida[i] = project3DPoint(p, d);
   }

   CV::translate(300, 200);
   CV::color(0);
   angle += 0.3;
   drawCube(saida);
}*/

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
