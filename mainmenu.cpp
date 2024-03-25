#include "button.h"
#include "mainmenu.h"
#include <gl/gl.h>
MainMenu::MainMenu(float windowWidth, float windowHeight){
        glPushMatrix();

            Show = new Button("None", 150, 50, new Point(windowWidth/2, windowHeight/2)); Show->Show();
            None = new Button("Show", 150, 50, new Point(windowWidth/2, windowHeight/2 - 60)); None->Show();
            Exit = new Button("Exit", 150, 50, new Point(windowWidth/2, windowHeight/2 + 60)); Exit->Show();
            //print_string(oglToWindowCoordinateX(0.5, windowWidth), oglToWindowCoordinateY(0, windowHeight), "123",1,0,0);
            //print_string(0,0, "123",1,0,0);
        glPopMatrix();
        }
