#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include "headers/camera.h"
#include "headers/obj_import.h"
#include "headers/cam_movement.h"
#include "headers/draw_objects.h"
#include "headers/stb_image.h"

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

float *cam_pos;
float *cam_center;
float *cam_nv;

void *cam = NULL;

void display();

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Museu de Imagens do Inconsciente");

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthRange(0.0f, 1.0f);

    cam = (Camera *)init_camera();
    init_obj_vecs();
    init_textures_vec();


    load_obj_display("./models/geladeira.obj", 6);
    load_obj_display("./models/lixinho.obj", 11);
    load_obj_display("./models/portaFechada.obj", 13);
    load_obj_display("./models/janelaFechada.obj", 14);
    load_obj_display("./models/casa/chao.obj", 17);
    load_obj_display("./models/casa/teto.obj", 18);
    load_obj_display("./models/casa/paredecomporta.obj", 19);
    load_obj_display("./models/casa/paredecomum.obj", 20);
    load_obj_display("./models/casa/paredecomjanela.obj", 21);
    load_obj_display("./models/janela/base.obj", 22);
    load_obj_display("./models/janela/janela.obj", 23);
    load_obj_display("./models/janela/janela2.obj", 24);

    load_texture("textures/quadro_museu2.jpeg", 0);
    load_texture("textures/chao.jpeg", 2);
    load_texture("textures/parede-3.jpg", 3);
    load_texture("textures/quadro_museu3.jpeg", 6);
    load_texture("textures/quadro_museu.jpg", 7);

    glutDisplayFunc(display);
    glutKeyboardFunc(moveCam);
    glutSpecialFunc(moveCamSpec);
    glutMotionFunc(mouse_func);
    glutPassiveMotionFunc(pass_mouse_func);
    glutMainLoop();

    return 0;
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int i;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, 1.0f * WINDOW_WIDTH / WINDOW_HEIGHT,
                   0.001f, 1000.0f);

    cam_pos = getCamPos(cam);
    cam_center = getCamCenter(cam);
    cam_nv = getCamNV(cam);

    gluLookAt(cam_pos[IX], cam_pos[IY], cam_pos[IZ], cam_center[IX], cam_center[IY],
              cam_center[IZ], cam_nv[IX], cam_nv[IY], cam_nv[IZ]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //casa
    draw_house();

    //geladeira
    draw_fridge();

    //janela
    draw_window();

    //lixeira
    glPushMatrix();
    glEnable( GL_TEXTURE_2D ); 

    glTranslatef(40, 1.5, -66);
    glScalef(3.0, 3.0, 3.0);
    aply_texture(3);
    draw_objects(11, 0.5,  0.5, 0.5, 1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //porta
    glPushMatrix();
    draw_door();
    glPopMatrix();

    //quadro 1
    glPushMatrix();
    glTranslatef ( 1.75 ,30.5 , -71 ) ;
    glScalef(5, 5, 5);
    draw_objects(3, 0.1, 0.5, 0.8, 0);
    glPopMatrix();

    glPushMatrix();
    glEnable( GL_TEXTURE_2D ); 
    glTranslatef ( 1.75 ,30.5 , -71 ) ;
    aply_texture(0);
    glScalef(20, 20, 20);
    draw_cube();
    glDisable( GL_TEXTURE_2D ); 
    glPopMatrix();

    //quadro 2
    glPushMatrix();
    glTranslatef ( 73 ,32.5 , -30 ) ;
    glScalef(5, 5, 5);
    draw_objects(3, 0.1, 0.5, 0.8, 0);
    glPopMatrix();

    glPushMatrix();
    glEnable( GL_TEXTURE_2D ); 
    glTranslatef ( 73 ,32.5 , -30 ) ;
    glRotatef(-90,0,1,0);
    aply_texture(6);
    glScalef(20, 20, 20);
    draw_cube();
    glDisable( GL_TEXTURE_2D ); 
    glPopMatrix();

    //quadro 3
    glPushMatrix();
    glTranslatef ( 73 ,32.5 , 10) ;
    glScalef(5, 5, 5);
    draw_objects(3, 0.1, 0.5, 0.8, 0);
    glPopMatrix();

    glPushMatrix();
    glEnable( GL_TEXTURE_2D ); 
    glTranslatef ( 73 ,32.5 , 10) ;
    glRotatef(-90,0,1,0);
    aply_texture(7);
    glScalef(20, 20, 20);
    draw_cube();
    glDisable( GL_TEXTURE_2D ); 
    glPopMatrix();


    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}