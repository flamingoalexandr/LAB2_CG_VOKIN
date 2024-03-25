#include <string>
#include <iostream>
#include <gl/gl.h>
#include "point.h"
#include "stb-master/stb_easy_font.h"
#include "button.h"


Button::Button(char* name, float width, float height, Point* Center){
        this->name = name;
        this->width = width;
        this->height = height;
        this->Center = Center;
        LeftTop = new Point(0, 0);
        RightTop = new Point(width, 0);
        RightBottom = new Point(width, height);
        LeftBottom = new Point(0, height);
    }
void Button::Show(){
        glPushMatrix();
        //glTranslatef(Center->x-width/2, Center->y-width/2, 0);
        glTranslatef(Center->x - width/2, Center->y-height/2, 0);
        glBegin(GL_TRIANGLES);
            glColor3f(1, 1, 1); glVertex2f(LeftTop->x, LeftTop->y);
           glColor3f(1, 1, 1); glVertex2f(RightTop->x, RightTop->y);
            glColor3f(1, 1, 1); glVertex2f(RightBottom->x, RightBottom->y);

            glColor3f(1, 1, 1); glVertex2f(RightBottom->x, RightBottom->y);
            glColor3f(1, 1, 1); glVertex2f(LeftBottom->x, LeftBottom->y);
            glColor3f(1, 1, 1); glVertex2f(LeftTop->x, LeftTop->y);
        glEnd();
        print_string(0,0, name, 1, 0, 0);
        glPopMatrix();
}
void Button::print_string(float x, float y, char *text, float r, float g, float b)
{
    glPushMatrix();
    glScalef(3, 3, 1);
    static char buffer[99999]; // ~500 chars
    int num_quads;
//    b->num_quads = stb_easy_font_print(0, 0, name, 0, b->buffer, sizeof(b->buffer)); // запись
//    //координат вершин элементов имени
//    b->textPosX = x +(width-stb_easy_font_width(name)*textS)/2.0;
//    b->textPosY = y +(height-stb_easy_font_height(name)*textS)/2.0;
//    b->textPosY+= textS*2;
//    b->textS = textS;
  num_quads = stb_easy_font_print(0, 0, text, NULL, buffer, sizeof(buffer));

  glColor3f(r,g,b);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 16, buffer);
  glDrawArrays(GL_QUADS, 0, num_quads*4);
  glDisableClientState(GL_VERTEX_ARRAY);

  glPopMatrix();
}
