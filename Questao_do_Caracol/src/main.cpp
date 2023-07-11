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

//Inicio dos Eixos
float initial_x;
float initial_y;
//

// QUESTÃO DO QUADRADO (OPERAÇÕES EM VETORES, MATRIZES ETC) //
float angle;
float radius;
float angle_variation;
float radius_variation;
// -------------------------------------------------------- //

//Desenha o Caracol
/*
    Esta questão utiliza conhecimento de coordenadas polares, para isto os pontos são mapeados utilizando raio e angulo ao invés de x e y.
    o x e o y são calculados na hora de desenhar com base nas coordenadas originais.
*/
void render()
{
    CV::clear(0,0,0);
    CV::color(1,1,1);
    //CV::circleFill(800,800,50,10);
    int row = 400;
    int col = 400;
    int i, j;
    float r, g, b;
    for(i = 0; i < row; i++)
    {
        r = ((float) ((i*3 + j) % 256)) / 255;
        g = ((float) ((i + j*3) % 256)) / 255;
        b = ((float) ((i + j) % 256)) / 255;
        CV::color(r,g,b);
        for(j = 0; j < col; j++)
        {
            CV::point(i,j);
        }
    }
    // Desenha Eixos X e Y
    /*CV::line(initial_x,initial_y,initial_x+1600,initial_y);
    CV::line(initial_x,initial_y,initial_x,0);

    //Questão
    CV::color(7);

    angle = 0.0;
    radius = 1.1;
    angle_variation = -0.1;
    radius_variation = 1.0;

    float x, y, x_temp, y_temp;
    int i;
    for (i = 0; i < 1000; i++)
    {
        //Cria o vetor do raio paralelo ao eixo X
        x = radius;
        y = 0;

        //Aplica a rotação neste vetor no angulo alfa
        x_temp = x*cos(angle) + y*(-sin(angle));
        y_temp = x*sin(angle) + y*(cos(angle));

        //  Note que, coomo o y é igual a zero, a aplicação da matrix de rotação poderia ser simplificada para:

        //  x_temp = x*cos(angle) + y*(-sin(angle));    =>   x_temp = x*cos(angle));   =>  x_temp = radius*cos(angle));
        //  y_temp = x*sin(angle) + y*(cos(angle));     =>   y_temp = x*sin(angle));   =>  y_temp = radius*sin(angle));

        CV::circle(x_temp+initial_x, initial_y-y_temp, 2, 10);
        radius += radius_variation;
        angle += angle_variation;
    }*/

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
    //Variáveis para visualização
    initial_x = 500;
    initial_y = 670;
    //


    CV::init("Questão do Caracol.");


    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    //Definindo ponto origem no centro da tela.
    initial_x = screenWidth/2;
    initial_y = screenHeight/2;

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    CV::run();
}
