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

std::set<int> PressedKeys;

float moving;
int rotating;

bool control_rotating_right;
bool control_rotating_left;
bool control_moving;


float angIni;

Mat* m;
Mat* m2;
Mat* m3;
Mat* m4;
Mat* m5;

int initial_x, initial_y;
float linex, liney;


void render()
{
    CV::clear(0,0,0);
    CV::color(1,1,1);
    // Eixo X
    CV::line(initial_x,initial_y,initial_x+1600,initial_y);
    // Eixo y
    CV::line(initial_x,initial_y,initial_x,0);


    CV::color(7);
    CV::line(initial_x,initial_y-liney,initial_x+linex,initial_y);

    m->Draw(initial_x, initial_y, 2);
    m2->Draw(initial_x, initial_y, 3);
    m3->Draw(initial_x, initial_y, 4);
    m4->Draw(initial_x, initial_y, 5);
    m5->Draw(initial_x, initial_y, 6);

}

// DEsenha Caracol (Cordenadas Polares)
/*void render()
{
    CV::color(1);
    float ang = 0;
    float raio = 0;
    for(int i = 0; i < 1000; i++)
    {
         float x = raio * cos(ang + angIni);
         float y = raio * sin(ang + angIni);
         CV::point( x + 100, y + 100);
         raio +=0.1;
         ang -= 0.01;
    }
    angIni -= 0.01;
} */


void keyboard(int key)
{
    //printf("\nTecla: %d" , key);

    if(PressedKeys.find(key) != PressedKeys.end())
    {
        return;
    }
    PressedKeys.insert(key);

    switch(key)
    {
      //seta para a esquerda
      case 99:
        //tecla C
        //player_character->ReceiveDamage(200);
      break;
      case 120:
        //tecla X
        //enemy_character->Shoot();
      break;
      case 122:
        //tecla Z
        //player_character->ActivateSpecial();
      break;
      case 97:
        //player_character->SetRotating(-1);
      break;
      case 100:
        //player_character->SetRotating(1);
      break;
      case 115:
        //player_character->SetMoving(-0.5);
      break;
      case 119:
        //player_character->SetMoving(1);
      break;
    }
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
    //printf("\nLiberou: %d" , key);
    if(PressedKeys.find(key) != PressedKeys.end())
        PressedKeys.erase(PressedKeys.find(key));
    switch(key)
    {
      case 27:
         //exit(0);
      break;
        //InventoryManager::shared_instance().OpenMenu();
      case 107:
        //ClearAllFigures();
        break;
      case 108:
        //LoadSave();
        break;
      case 109:
        //FileManager::shared_instance().SaveData(SavedFilePath, FigureManager::shared_instance().GetFiguresAsString(), FigureManager::shared_instance().CountFigures());
        break;
      //seta para a esquerda
      case 98:
        break;
      case 99:
        break;
      case 105:
        break;
      case 97:
      break;
      case 100:
      break;
      case 115:
      break;
      case 119:

      break;
    }
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{

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

    Mat A = Mat(3,3);
    *A.At(0,0) = 1;
    *A.At(1,1) = 1;
    *A.At(2,2) = 1;
    A.ShowMatrix();

    printf("\nMatrix B");
    Mat B = Mat(3,4);
    *B.At(0,0) = x1;
    *B.At(1,0) = y1;
    *B.At(2,0) = 1;
    *B.At(0,1) = x1 + L;
    *B.At(1,1) = y1;
    *B.At(2,1) = 1;
    *B.At(0,2) = x1 + L;
    *B.At(1,2) = y1 - L;
    *B.At(2,2) = 1;
    *B.At(0,3) = x1;
    *B.At(1,3) = y1 - L;
    *B.At(2,3) = 1;
    B.ShowMatrix();


    printf("\nMatrix T1");
    Mat T1 = Mat(3,3);
    *T1.At(0,0) = 1;
    *T1.At(0,2) = L;
    *T1.At(1,1) = 1;
    *T1.At(1,2) = L;
    *T1.At(2,2) = 1;
    T1.ShowMatrix();

    printf("\nMatrix E");
    Mat E = Mat(3,3);
    *E.At(0,0) = 1/3.0;
    *E.At(1,1) = 1/3.0;
    *E.At(2,2) = 1;
    E.ShowMatrix();


    Vec2 v1 = Vec2(-x2, y2);
    v1.Normalize();
    Vec2 v2 = Vec2(0, 1);

    float alfa = acos(v1.DotProduct(&v2));

    printf("\nMatrix R");
    Mat R = Mat(3,3);
    *R.At(0,0) = cos(alfa);
    *R.At(0,1) = -sin(alfa);
    *R.At(1,0) = sin(alfa);
    *R.At(1,1) = cos(alfa);
    *R.At(2,2) = 1;
    R.ShowMatrix();


    printf("\nMatrix T2");
    Mat T2 = Mat(3,3);
    *T2.At(0,0) = 1;
    *T2.At(0,2) = x2;
    *T2.At(1,1) = 1;
    *T2.At(1,2) = 0;
    *T2.At(2,2) = 1;
    T2.ShowMatrix();

    printf("\nMatrix M");
    m = Mat::Mult(&A, &B);
    m2 = Mat::Mult(&T1, m);
    m3 = Mat::Mult(&E, m2);
    m4 = Mat::Mult(&R, m3);
    m5 = Mat::Mult(&T2, m4);
    m->ShowMatrix();
    m2->ShowMatrix();
    m3->ShowMatrix();
    m4->ShowMatrix();

    angIni = 0;
    control_rotating_right = false;
    control_rotating_left = false;
    control_moving = false;

    float RGB[3] = {0.0,0.75,0.75};
    float RGB2[3] = {0.75,0.0,0.75};
    float RGB3[3] = {0.75, 0.75, 0.0};
    float RGB4[3] = {0.75, 0.35, 0.35};
   //Sleep(1000);



    CV::init("Space Extinction");

    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    CameraManager::shared_instance().SetCameraOffset(Pnt2((float) -screenWidth/2, (float) -screenHeight/2));
    CameraManager::shared_instance().SetCameraAnchor(new Pnt2(-10, 800));

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    CV::run();
}
