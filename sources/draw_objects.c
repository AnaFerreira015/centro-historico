#include "../headers/draw_objects.h"
#include "../headers/obj_import.h"
#include "../headers/stb_image.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

//sentido de rotação dos objetos, clockwise, anticlockwise
#define CW -1
#define ACW 1

struct TextureInfo
{
    unsigned int textureID;
};

int WIN_ROT = 0;
int WIN_ROT_DIR = CW;

int HEX_ANGLE = 0;

int DOOR_ROT = 0;
int DOOR_ROT_DIR = CW;

TextureInfo **textures = NULL;

void draw_axis()
{
    float width = 1.5f;
    glLineWidth(width);
    glColor3f(1.0f, 0.0f, 0.0f);
    draw_line(0.0f, 0.0f, 0.0f, 100, 0.0f, 0.0f);
    draw_line(0.0f, 0.0f, 0.0f, 100, 0.0f, 0.0f);
    draw_line(0.0f, 0.0f, 0.0f, 100, 0.0f, 0.0f);
    draw_line(0.0f, 0.0f, 0.0f, 100, 0.0f, 0.0f);
    draw_line(0.0f, 0.0f, 0.0f, 100, 0.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    draw_line(0.0f, 0.0f, 0.0f, -100, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    draw_line(0.0f, 0.0f, 0.0f, 0.0f, 100, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    draw_line(0.0f, 0.0f, 0.0f, 0.0f, -100, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    draw_line(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100);
    glColor3f(0.0f, 0.0f, 1.0f);
    draw_line(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -100);
}

void draw_line(float x0, float y0, float z0, float x1, float y1, float z1)
{
    glBegin(GL_LINES);
    glVertex3f(x0, y0, z0);
    glVertex3f(x1, y1, z1);
    glEnd();
}

void draw_axis_ticks()
{

    int colors[3][3] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}};

    float i;
    glColor3f(0.0f, 0.0f, 1.0f);
    for (i = -99; i < 100; i++)
    {
        glBegin(GL_LINES);
        glVertex3f(i, 0.0f, 100.0f);
        glVertex3f(i, 0.0f, -100.0f);
        glEnd();
    }
    glColor3f(0.0f, 1.0f, 0.0f);
    for (i = -99; i < 100; i++)
    {
        glBegin(GL_LINES);
        glVertex3f(-100.0f, i, 0.0f);
        glVertex3f(100.0f, i, 0.0f);
        glEnd();
    }
    glColor3f(0.0f, 0.0f, 1.0f);
    for (i = -99; i < 100; i++)
    {
        glBegin(GL_LINES);
        glVertex3f(-100.0f, 0.0f, i);
        glVertex3f(100.0f, 0.0f, i);
        glEnd();
    }
}

void draw_window()
{

    //base
    glPushMatrix();
    glTranslatef(28, 30, 63);
    glScalef(0.5, 0.7, 0.5);
    draw_objects(22, 0.84, 0.82, 1.27, 1);
    glPopMatrix();

    //janela2
    glPushMatrix();
    glTranslatef(63, 30, 73);
    glScalef(0.5, 0.7, 0.5);
    glRotatef(-WIN_ROT, 0, 1, 0); //Objeto espelhados com janela, daí gira no sentido inverso
    draw_objects(24, 0.84, 0.82, 1.27, 0);
    glPopMatrix();

    //janela
    glPushMatrix();
    glTranslatef(30, 30, 73);
    glScalef(0.5, 0.7, 0.5);
    glRotatef(WIN_ROT, 0, 1, 0);
    draw_objects(23, 0.84, 0.82, 1.27, 0);
    glPopMatrix();
}

void draw_cube() {
    
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1);

        glTexCoord2f(0, 0);
        glNormal3f(0, 0, 1);
		glVertex3f(0, 0, 0);
        
        glTexCoord2f(1, 0);
        glNormal3f(0, 0, 1);
		glVertex3f(1.5, 0, 0);
        
        glTexCoord2f(1, 1);
        glNormal3f(0, 0, 1);
        glVertex3f(1.5, 1, 0);

        glTexCoord2f(0, 1);
        glNormal3f(0, 0, 1);
        glVertex3f(0, 1, 0);
    
    glEnd();
    
}

/*----------Ventilador--------------*/
void draw_helix() { 
    //glScalef(5.0,5.0,5.0);
    draw_objects(5, 0.2, 0.8, 0.8, 1);
    glTranslatef(0, 0.5, 0);
    glScalef(1.5, 1.5, 1.2);
    glRotatef(180, 1, 0, 0);//rotaciona o ventilador pro plano xy

    //controla a velocidade do ventilador
    HEX_ANGLE += 3;//gira um grau a cada redisplay
    HEX_ANGLE %= 360;//mantém o angulo entre 0 e 360
    glRotatef(HEX_ANGLE, 0, 1, 0);//Gira no Y pq  ventilador original ta no plano XZ e não no XY

    draw_objects(4, 1, 1, 1, 1);  
    
}

void draw_door()
{
    glTranslatef(-55, 1, -72);
    glRotated(10, 0, 1, 0);
    glRotatef(DOOR_ROT, 0, 1, 0); //gira a porta conforme foi aberta/fechada
    glScalef(11.0, 8.5, 5.0);
    draw_objects(13, 0.5, 0.5, 0.5, 1);
}

void draw_house()
{
    /*----------chão--------------*/
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTranslatef(0, 0.5, 0);
    aply_texture(12);
    draw_objects(17, 1, 1, 1, 1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    /*---------------------------*/

    /*----------teto--------------*/
    glPushMatrix();
    glTranslatef(0, 71, 0);
    draw_objects(18, 1, 1, 1, 1);
    glPopMatrix();
    /*------------------------------*/

    /*Parede que tem a porta*/
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    aply_texture(3);
    glTranslatef(0, 0, 1.5);
    draw_objects(19, 1, 1, 1, 1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    /*------------------------------*/

    /*--Paredes comuns----*/
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    aply_texture(3);
    draw_objects(20, 1, 1, 1, 9);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    aply_texture(3);
    glRotatef(180, 0, 1, 0);
    draw_objects(20, 1, 1, 1, 1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    /*--------------------*/

    /*Parede que tem a janela*/
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    aply_texture(3);
    glTranslatef(0, 0, -0.5);
    draw_objects(21, 1, 1, 1, 1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void draw_fridge()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glTranslatef(30, 1, -30);
    aply_texture(11);
    glRotatef(90,0,1,0);
    glScalef(9.0, 20.0, 14.0);
    draw_objects(6, 255, 255, 255, 1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void change_door_state()
{
    //controla quanto a porta fecha/abre
    if (DOOR_ROT == 90 || DOOR_ROT == 0)
    { //aberta ou fechada
        DOOR_ROT_DIR = -DOOR_ROT_DIR;
    }
    DOOR_ROT += DOOR_ROT_DIR;
    DOOR_ROT %= 360;
}

void change_window_state()
{
    //controla quanto a janela fecha/abre
    if (WIN_ROT == 90 || WIN_ROT == 0)
    { //aberta ou fechada
        WIN_ROT_DIR = -WIN_ROT_DIR;
    }
    WIN_ROT += WIN_ROT_DIR;
}

void draw_objects(int index, float r, float g, float b, int ap_texture)
{
    if (0 <= index < MODEL_QUANT)
    {
        int i;
        float OFF_SET_COL = 0.1;

        VERTICES = vecs[index]->VERTICES;
        NORMALS = vecs[index]->NORMALS;
        TEX_COORDS = vecs[index]->TEX_COORDS;
        VERTEX_COUNT = vecs[index]->VERTEX_COUNT;

        if (ap_texture)
        {
            OFF_SET_COL = 0;
        }
        else
        {
            OFF_SET_COL = 0.1;
        }

        glBegin(GL_TRIANGLES);
        for (i = 0; i < VERTEX_COUNT; i++)
        {
            glColor3f(r + OFF_SET_COL, g + OFF_SET_COL, b + OFF_SET_COL);
            glTexCoord2f(TEX_COORDS[i].x, TEX_COORDS[i].y);
            glNormal3f(NORMALS[i].x, NORMALS[i].y, NORMALS[i].z);
            glVertex3f(VERTICES[i].x, VERTICES[i].y, VERTICES[i].z);
            OFF_SET_COL = -OFF_SET_COL;
        }
        glEnd();
    }
    else
    {
        printf("Indice fora do range permitido: [0, %d)", MODEL_QUANT);
        exit(1);
    }
}

void load_texture(const char *path, int index)
{

    if (0 <= index <= MODEL_QUANT)
    {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data)
        {
            textures[index] = (TextureInfo *)malloc(sizeof(TextureInfo));

            unsigned int textureID;
            glGenTextures(1, &textureID);

            textures[index]->textureID = textureID;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            printf("Falha ao carregar a textura.");
            stbi_image_free(data);
            exit(1);
        }
        stbi_image_free(data);
    }
    else
    {
        printf("Indice de textura inválido.");
        exit(1);
    }
}

void init_textures_vec()
{
    textures = (TextureInfo **)malloc(MODEL_QUANT * sizeof(TextureInfo *));

    int i;
    for (i = 0; i < MODEL_QUANT; i++)
    {
        textures[i] = NULL;
    }
}

void aply_texture(int index)
{
    if (0 <= index <= MODEL_QUANT)
    {
        if (textures[index])
        {
            unsigned int textureID = textures[index]->textureID;
            glBindTexture(GL_TEXTURE_2D, textureID);
        }
    }
    else
    {
        printf("Indice de textura inválido.");
        exit(1);
    }
}
