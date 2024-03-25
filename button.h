#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include "Point.h"
class Button{
public:
    Point* LeftTop;
    Point* RightTop;
    Point* RightBottom;
    Point* LeftBottom;
    void print_string(float x, float y, char *text, float r, float g, float b);
    float width;
    float height;
    Point* Center;
    char* name;
    Button(char* name, float width, float height, Point* Center);
    void Show();

};

#endif // BUTTON_H_INCLUDED
