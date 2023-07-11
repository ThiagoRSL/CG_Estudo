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
#include <stdlib.h>
#include <ctype.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <set>
#include <iterator>
#include <cstdlib>
#include <iostream>


/*
#include "gl_canvas2d.h"
#include "Utils/Vec2.h"
#include "Utils/Curves.h"
#include "Mat.h"
#include "CameraManager.h"
*/
int* screenHeight;
int* screenWidth;
float cam_pos_x = 0, cam_pos_y = 10, cam_pos_z = 0;
float cam_ori_x = 0, cam_ori_y = 0, cam_ori_z = 0;

void Render();
void Reshape(int w, int h);
void KeyPress(unsigned char key, int, int);
void KeyUp(unsigned char key, int, int);
void MouseEvent(int button, int state, int wheel, int direction, int x, int y);
void MouseClick(int button, int state, int x, int y);
void MouseMove(int x, int y);
void MouseWheel(int wheel, int direction, int x, int y);
void Inicializar(const char *title);
void Display (void);


//funcao chamada sempre que a tela for redimensionada.
void Reshape (int w, int h)
{
   *screenHeight = h; //atualiza as variaveis da main() com a nova dimensao da tela.
   *screenWidth = w;

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   //cria uma projecao ortografica com z entre (-1, 1).
   //parametros: left, right, bottom, top
   //gluOrtho2D (0.0, w, h, 0.0); //o eixo y cresce para baixo

   //glMatrixMode(GL_MODELVIEW);
   //glLoadIdentity ();
}

//Renderiza a tela
void Display (void)
{

    float abertura = 45.0;
    float znear  = 1;
    float zfar   = 30;
    float aspect = 1;

    glMatrixMode(GL_PROJECTION);                    //Define a Pila de matrix que pode ser GL_Projection, GL_ModelView ou GL_Texture.
    glLoadIdentity( );                              //Carrega matriz identidade (Base da Pilha)
    gluPerspective(abertura, aspect, znear, zfar);
    //glMatrixMode(GL_MODELVIEW);
    //glShadeModel(GL_SMOOTH);

    glClear(GL_COLOR_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    gluLookAt(cam_pos_x, cam_pos_y, cam_pos_z,  //from. Posicao onde a camera esta posicionada
              cam_ori_x, cam_ori_y, cam_ori_z,  //to. Posicao absoluta onde a camera esta vendo
              0, 0, 1); //up. Vetor Up.


    Render();

    glFlush();
    glutSwapBuffers();
}

//Desenha o Quadrado
void Render()
{
    /* Controle de Frames aqui dentro. */
    glClearColor(0,0,0,1);
    glColor3f(1,0,0);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);

        glVertex3f(1,0,0);
        glVertex3f(1,1,0);

        glVertex3f(1,1,0);
        glVertex3f(0,1,0);

        glVertex3f(0,1,0);
        glVertex3f(0,0,0);
    glEnd();
    glColor3f(0,1,0);
    glBegin(GL_LINES);
        glVertex3f(0,0,1);
        glVertex3f(1,0,1);

        glVertex3f(1,0,1);
        glVertex3f(1,1,1);

        glVertex3f(1,1,1);
        glVertex3f(0,1,1);

        glVertex3f(0,1,1);
        glVertex3f(0,0,1);
    glEnd();
    glColor3f(0,0,1);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,0,1);

        glVertex3f(1,0,0);
        glVertex3f(1,0,1);

        glVertex3f(1,1,0);
        glVertex3f(1,1,1);

        glVertex3f(0,1,0);
        glVertex3f(0,1,1);
    glEnd();
}

int main(void)
{
    //Define alguns valores para preparar para inicializar.
    Inicializar("Cubo em 3D");

    //Inicia execução
    glutMainLoop();
}

void KeyPress(unsigned char key, int, int)
{
    printf("\nTecla: %d" , key);


    switch(key)
    {
        case 119: //W
            cam_pos_x++;
            break;
        case 97:  //A
            cam_pos_z--;
            break;
        case 115: //S
            cam_pos_x--;
            break;
        case 100: //D
            cam_pos_z++;
            break;
        case 32: //BARRA
            cam_pos_y++;
            break;
        case 120: //X
            cam_pos_y--;
            break;
    }
}

//funcao chamada toda vez que uma tecla for liberada
void KeyUp(unsigned char key, int, int)
{
    printf("\nTecla (Liberada): %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void MouseClick(int button, int state, int x, int y){ MouseEvent(button, state, -2, -2, x, y);}
void MouseMove(int x, int y){ MouseEvent(-2, -2, -2, -2, x, y);}
void MouseWheel(int wheel, int direction, int x, int y){ MouseEvent(-2, -2, wheel, direction, x, y);}
void MouseEvent(int button, int state, int wheel, int direction, int x, int y)
{
    return;
}


//Define valores do glut e do OPengl
void Inicializar(const char *title)
{
    //Inicia execução do Glut e captura o tamanho do monitor.
    int argc = 0;
    glutInit(&argc, NULL);

    int height = glutGet(GLUT_SCREEN_WIDTH);
    int width = glutGet(GLUT_SCREEN_HEIGHT);

    screenHeight = &height;
    screenWidth = &width;

    //habilita MSAA
    //glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);// GLUT_MULTISAMPLE
    //glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

    //Define o tamanho da janela principal, sua posição na tela, o título da janela e define como tela cheia.
    glutInitWindowSize (height, width);
    glutInitWindowPosition (0, 0);
    glutCreateWindow (title);
    glutFullScreen();

    //Limpa a tela.
    glClearColor(1,1,1,1);

    //Especifica como
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    glutKeyboardFunc(KeyPress);
    glutKeyboardUpFunc(KeyUp);

    //Se não tiver nenhum evento, chama a render.
    glutIdleFunc(Display);
    glutMouseFunc(MouseClick);
    glutMotionFunc(MouseMove);
    glutPassiveMotionFunc(MouseMove);
    //glutMouseWheelFunc(MouseWheel);

    printf("GL Version: %s", glGetString(GL_VERSION));
}
