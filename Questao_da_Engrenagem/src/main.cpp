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

float initial_x, initial_y;
float rot = 0;

//Desenha o Quadrado
void render()
{
    // Pinta o fundo e Desenha Eixos X e Y //
    CV::clear(0,0,0);
    CV::color(1,1,1);
    CV::line(initial_x,initial_y,initial_x+1600,initial_y);
    CV::line(initial_x,initial_y,initial_x,0);
    // ----------------------------------- //

    bool  outer = false, outer2 = false;
    float teeth = 10.0;
    float lines = teeth*2;

    float radius = 200.0, radius2 = 220.0;
    float radius_min = 50;
    float radius_max = 60;

    float angle, angle2;
    float angle_variation = PI/lines;    // - é horário e + anti-horário

    CV::color(3);
    int i;
    for (angle = 0.0; angle <= 2*PI; angle+=angle_variation)
    {
        angle2 = angle + angle_variation;

        if(!outer && !outer2)
            outer2 = true;
        else if (!outer && outer2)
            outer = true;
        else if (outer && outer2)
            outer2 = false;
        else if (outer && !outer2)
            outer = false;

        if(outer)
            radius = radius_max;
        else
            radius = radius_min;
        if(outer2)
            radius2 = radius_max;
        else
            radius2 = radius_min;

        float x = radius * cos(angle);
        float y = radius * sin(angle);

        float x2 = radius2 * cos(angle2);
        float y2 = radius2 * sin(angle2);

        CV::line(initial_x + x, initial_y - y, initial_x + x2, initial_y - y2);
    }

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
    rot = 0;
    CV::init("Questão da Engrenagem.");

    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    //Definindo ponto origem no centro da tela.
    initial_x = screenWidth/2;
    initial_y = screenHeight/2;

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    CV::run();
}
