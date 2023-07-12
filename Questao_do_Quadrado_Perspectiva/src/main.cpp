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
float d = 40;
float ang = 0;
// -------------------------------------------------------- //

void DesenhaCubo()
{
    Quad = new Mat(8,3);
    *Quad->At(0,0) = 0;
    *Quad->At(0,1) = 0;
    *Quad->At(0,2) = 0;

    *Quad->At(1,0) = 10;
    *Quad->At(1,1) = 0;
    *Quad->At(1,2) = 0;

    *Quad->At(2,0) = 10;
    *Quad->At(2,1) = 0;
    *Quad->At(2,2) = 10;

    *Quad->At(3,0) = 0;
    *Quad->At(3,1) = 0;
    *Quad->At(3,2) = 10;

    *Quad->At(4,0) = 0;
    *Quad->At(4,1) = 10;
    *Quad->At(4,2) = 0;

    *Quad->At(5,0) = 10;
    *Quad->At(5,1) = 10;
    *Quad->At(5,2) = 0;

    *Quad->At(6,0) = 10;
    *Quad->At(6,1) = 10;
    *Quad->At(6,2) = 10;

    *Quad->At(7,0) = 0;
    *Quad->At(7,1) = 10;
    *Quad->At(7,2) = 10;

    Mat *QuadPers = new Mat(8,2);
    float pxl;
    float pyl;
    int i;
    CV::color(5);
    for(i = 0; i < 8; i++)
    {
     float px = *Quad->At(i,0);
     float py = *Quad->At(i,1);
     float pz = *Quad->At(i,2);
     pz += 5;           //Translada
     py += 3;           //Translada
     px += 2;           //Translada
     pxl = px*d/pz;
     pyl = py*d/pz;

     float npxl = px*d/pz;
     float npyl = py*d/pz;
     *QuadPers->At(i,0) = initial_x + px*d/pz;
     *QuadPers->At(i,1) = initial_y + py*d/pz;
     CV::circle(initial_x + px*d/pz, initial_y + py*d/pz, 5, 15);
    }
    /*CV::line(*QuadPers->At(0,0), *QuadPers->At(0,1), *QuadPers->At(1,0), *QuadPers->At(1,1));
    CV::line(*QuadPers->At(1,0), *QuadPers->At(1,1), *QuadPers->At(2,0), *QuadPers->At(2,1));
    CV::line(*QuadPers->At(2,0), *QuadPers->At(2,1), *QuadPers->At(3,0), *QuadPers->At(3,1));
    CV::line(*QuadPers->At(3,0), *QuadPers->At(3,1), *QuadPers->At(4,0), *QuadPers->At(4,1));
    CV::line(*QuadPers->At(4,0), *QuadPers->At(4,1), *QuadPers->At(0,0), *QuadPers->At(0,1));

    CV::line(*QuadPers->At(4,0), *QuadPers->At(4,1), *QuadPers->At(5,0), *QuadPers->At(5,1));
    CV::line(*QuadPers->At(5,0), *QuadPers->At(5,1), *QuadPers->At(6,0), *QuadPers->At(6,1));
    CV::line(*QuadPers->At(6,0), *QuadPers->At(6,1), *QuadPers->At(7,0), *QuadPers->At(7,1));
    CV::line(*QuadPers->At(7,0), *QuadPers->At(7,1), *QuadPers->At(0,0), *QuadPers->At(0,1));*/
}

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

    DesenhaCubo();
    //Quad->Draw(initial_x,initial_y, 30, 2);
    //Quad->DrawPerspective(initial_x,initial_y, 10, 2);
}

void keyboard(int key)
{
    Vec3 camAt = CameraManager::shared_instance().GetCameraAt();
    printf("\nTecla: %d" , key);
    switch(key)
    {
        case 119: //W
            d += 5;
            camAt.x += 1;
            CameraManager::shared_instance().SetCameraAt(camAt);
            break;
        case 97:  //A
            camAt.z -= 1;
            CameraManager::shared_instance().SetCameraAt(camAt);
            break;
        case 115: //S
            d -= 5;
            camAt.x -= 1;
            CameraManager::shared_instance().SetCameraAt(camAt);
            break;
        case 100: //D
            camAt.z += 1;
            CameraManager::shared_instance().SetCameraAt(camAt);
            break;
        case 32: //BARRA
            camAt.y += 1;
            CameraManager::shared_instance().SetCameraAt(camAt);
            break;
        case 120: //X
            camAt.y -= 1;
            CameraManager::shared_instance().SetCameraAt(camAt);
            break;
    }
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
    *Quad->At(0,0) = 10;
    *Quad->At(0,1) = 0;
    *Quad->At(0,2) = 10;

    *Quad->At(1,0) = 10;
    *Quad->At(1,1) = 0;
    *Quad->At(1,2) = 20;

    *Quad->At(2,0) = 20;
    *Quad->At(2,1) = 0;
    *Quad->At(2,2) = 20;

    *Quad->At(3,0) = 20;
    *Quad->At(3,1) = 0;
    *Quad->At(3,2) = 10;

    *Quad->At(4,0) = 10;
    *Quad->At(4,1) = 10;
    *Quad->At(4,2) = 10;

    *Quad->At(5,0) = 10;
    *Quad->At(5,1) = 10;
    *Quad->At(5,2) = 20;

    *Quad->At(6,0) = 20;
    *Quad->At(6,1) = 10;
    *Quad->At(6,2) = 20;

    *Quad->At(7,0) = 20;
    *Quad->At(7,1) = 10;
    *Quad->At(7,2) = 10;

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
