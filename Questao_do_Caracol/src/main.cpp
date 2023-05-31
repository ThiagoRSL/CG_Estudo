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
#include "Mat.h"
#include "CameraManager.h"


// QUESTÃO DO QUADRADO (OPERAÇÕES EM VETORES, MATRIZES ETC) //
Mat *M, *M2, *M3, *M4, *M5;
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
    CV::line(initial_x,initial_y,initial_x,0);

    // Desenha linha formada por (x1, y0) e (x0, y1);
    CV::color(7);
    CV::line(initial_x,initial_y-liney,initial_x+linex,initial_y);

    M->Draw(initial_x, initial_y, 2);
    M2->Draw(initial_x, initial_y, 3);
    M3->Draw(initial_x, initial_y, 4);
    M4->Draw(initial_x, initial_y, 5);
    M5->Draw(initial_x, initial_y, 6);
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

int main(void)
{
    initial_x = 500;
    initial_y = 670;

    float x1, y1, L;
    float x2 = 400, y2 = 400;
    linex = x2;
    liney = y2;

    L = 100;
    x1 = -L;
    y1 = 1;

    /* Define a matriz com os vetores que formam os pontos do quadrado. */
    M = new Mat(3,4);
    *M->At(0,0) = x1;
    *M->At(1,0) = y1;
    *M->At(2,0) = 1;
    *M->At(0,1) = x1 + L;
    *M->At(1,1) = y1;
    *M->At(2,1) = 1;
    *M->At(0,2) = x1 + L;
    *M->At(1,2) = y1 - L;
    *M->At(2,2) = 1;
    *M->At(0,3) = x1;
    *M->At(1,3) = y1 - L;
    *M->At(2,3) = 1;
    /* ------------------- */

    /* Define a matriz de translação que tras o quadrado à Origem. */
    Mat T1 = Mat(3,3);
    *T1.At(0,0) = 1;
    *T1.At(0,2) = L;
    *T1.At(1,1) = 1;
    *T1.At(1,2) = L;
    *T1.At(2,2) = 1;
    /* ------------------- */

    /* Define a matriz de para adequar a escala, alterando o tamanho dos lados para 1/3 do tamanho original. */
    Mat E = Mat(3,3);
    *E.At(0,0) = 1/3.0;
    *E.At(1,1) = 1/3.0;
    *E.At(2,2) = 1;
    /* ------------------- */

    //
    //O Vetor formado por (-x1, y1) é paralelo ao vetor formado por (x1, 0) e (0, y1)
    //Define o v1 como o vetor formado pelos pontos x1 e y1 da questão.
    //
    Vec2 v1 = Vec2(-x2, y2);
    //Normaliza o vetor para cortar a divisão do produto interno futuramente
    v1.Normalize();
    //Define um vetor já normalizado paralelo ao eixo Y.
    Vec2 v2 = Vec2(0, 1);
    //Encontra o angulo atraves do produto interno dos dois vetores.
    float alfa = acos(v1.DotProduct(&v2));

    /* Define a matriz de rotação. */
    Mat R = Mat(3,3);
    *R.At(0,0) = cos(alfa);
    *R.At(0,1) = -sin(alfa);
    *R.At(1,0) = sin(alfa);
    *R.At(1,1) = cos(alfa);
    *R.At(2,2) = 1;
    /* ------------------- */

    /* Define a matriz de translação para deslocar o quadrado para o ponto alvo. */
    Mat T2 = Mat(3,3);
    *T2.At(0,0) = 1;
    *T2.At(0,2) = x2;
    *T2.At(1,1) = 1;
    *T2.At(1,2) = 0;
    *T2.At(2,2) = 1;
    /* ------------------- */

    /* Salva as operações */
    M2 = Mat::Mult(&T1, M);     // Aplica a primeira translação para trazer o quadrado para origem.
    M3 = Mat::Mult(&E, M2);     // Aplica a escala definida, 1/3 do tamanho original.
    M4 = Mat::Mult(&R, M3);     // Aplica a rotação.
    M5 = Mat::Mult(&T2, M4);    // Aplica a translação para deslocar ao ponto desejado.
    /* ------------------- */

    /* PRINTS DAS MATRIZES */
    printf("\nMatrix M");
    M->ShowMatrix();
    printf("\nMatrix T1");
    T1.ShowMatrix();
    printf("\nMatrix E");
    E.ShowMatrix();
    printf("\nMatrix R");
    R.ShowMatrix();
    printf("\nMatrix T2");
    T2.ShowMatrix();
    printf("\nMatrix M2");
    M2->ShowMatrix();
    printf("\nMatrix M3");
    M3->ShowMatrix();
    printf("\nMatrix M4");
    M4->ShowMatrix();
    printf("\nMatrix M5");
    M5->ShowMatrix();
    /* ------------------- */

    CV::init("Questão do Quadrado.");

    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    CV::run();
}
