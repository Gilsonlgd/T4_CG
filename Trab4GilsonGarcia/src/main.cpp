/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario
conhecimentos de OpenGL para usar.
//  Autor: Gilson Garcia
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.


#include <cmath>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Engine.h"
#include "Vector2.h"
#include "Vector3.h"
#include "gl_canvas2d.h"
#include "math_utils.h"

using namespace std;

#define ROTATION_SPEED 2.5

// variavel global para selecao do que sera exibido na canvas.
int opcao = 50;
int screenWidth = 1200,
    screenHeight = 700; // largura e altura inicial da tela . Alteram com o
                        // redimensionamento de tela.
int mouseX,
    mouseY; // variaveis globais do mouse para poder exibir dentro da render().

bool is_3D = true;


Engine* engine;

// funcao chamada continuamente. Deve-se controlar o que desenhar por meio de
// variaveis globais Todos os comandos para desenho na canvas devem ser chamados
// dentro da render(). Deve-se manter essa funcao com poucas linhas de codigo.
void render() {
    is_3D ? engine->render3D() : engine->render2D();
    engine->update();
}

// funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key) {
    if (key < 200) {
        opcao = key;
    }

    switch (key) {
        case SHIFT:
            is_3D = !is_3D;
        break;
        case UP:
            engine->rotateX(ROTATION_SPEED);
        break;
        case DOWN:
            engine->rotateX(-ROTATION_SPEED);
        break;
        case LEFT:
            engine->rotateY(ROTATION_SPEED);
        break;
        case RIGHT:
            engine->rotateY(-ROTATION_SPEED);
        break;
        case KEY_2:
            engine->toggleConnectingRodVisibility();
        break;
        case KEY_4:
            engine->togglePistonRingVisibility();
        break;
        case KEY_3:
            engine->togglePistonVisibility();
        break;
        case KEY_1:
            engine->toggleCrankVisibility();
        break;
        case W_KEY:
            engine->speedUP();
            printf("");
        break;
        case S_KEY:
            engine->speedDOWN();
            printf("");
        break;
        case J_KEY:
            engine->increaseV_angle();
        break;
        case U_KEY:
            engine->decreaseV_angle();
        break;  
    }
    
}

// funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key) {
    switch (key) {}
}

// funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y) {
    mouseX = x; // guarda as coordenadas do mouse para exibir dentro da render()
    mouseY = y;

    if (state == 1) {
    };

    if (state == 0) // clicou
    {
    }
}

int main(void) {
    engine = new Engine(1.5, 600, 200, 100);


    CV::init(&screenWidth, &screenHeight, "");
    CV::run();
}
