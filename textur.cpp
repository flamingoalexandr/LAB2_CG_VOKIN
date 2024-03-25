#include <gl/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"
#include "textur.h"

void ShowBackground(GLuint texture)
{
    glPushMatrix();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    static float svertix[]= {0,0, 1280,0, 1280,240, 0,240}; //вектор текстурируемого многоугольника
    static float TexCord[]= {1,0, 0,0, 0,1, 1,1}; // текстурные координаты изображени€
    glEnable(GL_TEXTURE_2D); //разрешение использовани€ текстуры

    glBindTexture(GL_TEXTURE_2D, texture);

    glEnableClientState(GL_VERTEX_ARRAY); //использование вектора координат
    glEnableClientState(GL_TEXTURE_COORD_ARRAY); //использование вектора
    // текстурных координат
    glVertexPointer(2, GL_FLOAT, 0, svertix); //используем вектор координат
    glTexCoordPointer(2, GL_FLOAT, 0, TexCord); //используем вектор текстурных координат

    glDrawArrays(GL_TRIANGLE_FAN,0,4); //отрисовка текстурированного объекта

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();
}

void Load_Textur(char *filename, GLuint *textureID, int swarp, int twarp, int filter)
{
    int twidth, thight, tcnt; //переменные ширины, высоты,
    unsigned char *data=stbi_load(filename,&twidth,&thight,&tcnt,0); // в поле filename,
    //прописываетс€ им€ файла Уimage.pngФ, а файл хранитс€ в директории проекта
    glGenTextures(1, textureID); //генераци€ текстуры
    glBindTexture(GL_TEXTURE_2D, *textureID);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,swarp); //настройки
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,twarp);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,filter);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,filter);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, thight,
    0, tcnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0); //задание текстуры
    stbi_image_free(data); //освобождение буффера
}
