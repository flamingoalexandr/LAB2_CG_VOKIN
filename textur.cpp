#include <gl/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"
#include "textur.h"

void ShowBackground(GLuint texture)
{
    glPushMatrix();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    static float svertix[]= {0,0, 1280,0, 1280,240, 0,240}; //������ ��������������� ��������������
    static float TexCord[]= {1,0, 0,0, 0,1, 1,1}; // ���������� ���������� �����������
    glEnable(GL_TEXTURE_2D); //���������� ������������� ��������

    glBindTexture(GL_TEXTURE_2D, texture);

    glEnableClientState(GL_VERTEX_ARRAY); //������������� ������� ���������
    glEnableClientState(GL_TEXTURE_COORD_ARRAY); //������������� �������
    // ���������� ���������
    glVertexPointer(2, GL_FLOAT, 0, svertix); //���������� ������ ���������
    glTexCoordPointer(2, GL_FLOAT, 0, TexCord); //���������� ������ ���������� ���������

    glDrawArrays(GL_TRIANGLE_FAN,0,4); //��������� ����������������� �������

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();
}

void Load_Textur(char *filename, GLuint *textureID, int swarp, int twarp, int filter)
{
    int twidth, thight, tcnt; //���������� ������, ������,
    unsigned char *data=stbi_load(filename,&twidth,&thight,&tcnt,0); // � ���� filename,
    //������������� ��� ����� �image.png�, � ���� �������� � ���������� �������
    glGenTextures(1, textureID); //��������� ��������
    glBindTexture(GL_TEXTURE_2D, *textureID);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,swarp); //���������
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,twarp);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,filter);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,filter);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, thight,
    0, tcnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0); //������� ��������
    stbi_image_free(data); //������������ �������
}
