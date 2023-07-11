/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instru��es:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <set>
#include <iterator>
#include <cstdlib>
#include <iostream>

#include "gl_canvas2d.h"
#include "Utils/Vec2.h"
#include "Utils/Curves.h"
#include "Utils/Mat.h"
#include "CameraManager.h"


// QUESTÃO DO QUADRADO (OPERAÇÕES EM VETORES, MATRIZES ETC) //
Mat *M, *Quad;
int initial_x, initial_y;
float linex, liney;
// -------------------------------------------------------- //

//Desenha o Quadrado
void render()
{
    CV::clear(0,0,0);

    CV::color(1,1,1);
    // Desenha Eixos X e Y
    CV::line(initial_x,initial_y,initial_x+1600,initial_y);
    CV::line(initial_x,initial_y,initial_x,initial_y+1600);

    // Desenha linha formada por (x1, y0) e (x0, y1);
    CV::color(7);

    Quad->Draw(initial_x, initial_y, 30, 2);
}

void keyboard(int key)
{
    printf("\nTecla: %d" , key);
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
    printf("\nTecla (Liberada): %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    return;
}

void ToOringin(float x, float y, float z)
{
    /* Define a matriz com os vetores que formam os pontos do quadrado. */
    Mat ToOrigin = Mat(4,4);
    *ToOrigin.At(0,0) = 1;
    *ToOrigin.At(1,1) = 1;
    *ToOrigin.At(2,2) = 1;
    *ToOrigin.At(3,3) = 1;
    *ToOrigin.At(0,3) = -x;
    *ToOrigin.At(1,3) = -y;
    *ToOrigin.At(2,3) = -z;
    /* ------------------- */

}

int main(void)
{
    //Delcarando Quadrado (Pontos).
    Quad = new Mat(8,4);
    *Quad->At(0,0) = 0;
    *Quad->At(0,1) = 0;
    *Quad->At(0,2) = 0;

    *Quad->At(1,0) = 1;
    *Quad->At(1,1) = 0;
    *Quad->At(1,2) = 0;

    *Quad->At(2,0) = 1;
    *Quad->At(2,1) = 1;
    *Quad->At(2,2) = 0;

    *Quad->At(3,0) = 0;
    *Quad->At(3,1) = 1;
    *Quad->At(3,2) = 0;

    *Quad->At(4,0) = 0;
    *Quad->At(4,1) = 0;
    *Quad->At(4,2) = 1;

    *Quad->At(5,0) = 1;
    *Quad->At(5,1) = 0;
    *Quad->At(5,2) = 1;

    *Quad->At(6,0) = 1;
    *Quad->At(6,1) = 1;
    *Quad->At(6,2) = 1;

    *Quad->At(7,0) = 0;
    *Quad->At(7,1) = 1;
    *Quad->At(7,2) = 1;

    *Quad->At(0,3) = 1; //Cordenada Homogênea
    *Quad->At(1,3) = 1; //Cordenada Homogênea
    *Quad->At(2,3) = 1; //Cordenada Homogênea
    *Quad->At(3,3) = 1; //Cordenada Homogênea
    *Quad->At(4,3) = 1; //Cordenada Homogênea
    *Quad->At(5,3) = 1; //Cordenada Homogênea
    *Quad->At(6,3) = 1; //Cordenada Homogênea
    *Quad->At(7,3) = 1; //Cordenada Homogênea

    CV::init("Questão do Quadrado.");

    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    //Definindo ponto origem no centro da tela.
    initial_x = screenWidth/2;
    initial_y = screenHeight/2;

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    CV::run();
}
