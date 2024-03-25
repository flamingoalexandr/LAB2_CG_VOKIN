#include <windows.h>
#include <gl/gl.h>
#include "button.h"
#include <iostream>
#include "stb-master/stb_easy_font.h"
#include "stb-master/stb_image.h"
//#define STB_IMAGE_IMPLEMENTATION
#include "textur.h"
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

float windowWidth;
float windowHeight;


Button* Show;
Button* None;
Button* Exit;
Button* Back;
int windowNumber = 1;
GLuint bg;

float vertex[]={-0, -300, 300, -300, 300, 300};
BOOL EventHandler(float x, float y, Button* btn){
    return (x > (btn->Center->x-btn->width/2)) && (x < (btn->Center->x+btn->width/2) ) &&
            (y > ((btn->Center->y)-(btn->height)/2) ) && (y < (btn->Center->y+btn->height/2));
}



int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          512,
                          512,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    Load_Textur("sprite.png", &bg, GL_CLAMP, GL_CLAMP, GL_NEAREST);
    /* program main loop */
    RECT rct; //ñîçäàíèå ïåðåìåííîé ñ êîîðäèíàòàìè ïðÿìîóãîëíèêà
    GetClientRect(hwnd, &rct); //ïîëó÷åíèå òåêóùèõ êîîðäèíàò îêíà
    glOrtho(0, rct.right, rct.bottom, 0, 1, -1); //âûñòàâëÿåì èõ êàê êîîðäèíàòû îêíà


    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {

            /* OpenGL animation code goes here */
            if (windowNumber == 1){
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();

            Show = new Button("Show", 150, 50, new Point(windowWidth/2, windowHeight/2 - 60)); Show->Show();
            None = new Button("None", 150, 50, new Point(windowWidth/2, windowHeight/2)); None->Show();
            Exit = new Button("Exit", 150, 50, new Point(windowWidth/2, windowHeight/2 + 60)); Exit->Show();
            glPopMatrix();

            SwapBuffers(hDC);

            theta += 1.0f;
            Sleep (1);
            }
            else{
                    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();
            glEnableClientState(GL_VERTEX_ARRAY);

            glVertexPointer(2, GL_FLOAT, 0, vertex);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            glDisableClientState(GL_VERTEX_ARRAY);

            glColor3f(1,1,1)
            ShowBackground(bg);
                    Back = new Button("Back", 150, 50, new Point(windowWidth/2, windowHeight/2 + 120)); Back->Show();
                    // IMAGE


            glPopMatrix();

            SwapBuffers(hDC);

            theta += 1.0f;
            Sleep (1);
                }


        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    float k = 1;
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;
        case WM_LBUTTONDOWN:
            if(windowNumber == 1){

                if (EventHandler(LOWORD(lParam), HIWORD(lParam), Show))
                {
                    std::cout << 123;
                    windowNumber = 0;
                }
                if (EventHandler(LOWORD(lParam), HIWORD(lParam), None))
                {
                    std::cout << None->name;
                }
                if (EventHandler(LOWORD(lParam), HIWORD(lParam), Exit))
                {
                    PostQuitMessage(0);
                    std::cout << "123213sdfds";
                }
            }
            else{
                if (EventHandler(LOWORD(lParam), HIWORD(lParam), Back))
                {
                    windowNumber = 1;
                }
            }

            break;
        case WM_SIZE:
            windowWidth = (float)LOWORD(lParam);
            windowHeight = (float)HIWORD(lParam);
            glViewport(0,0, windowWidth, windowHeight);
            glLoadIdentity();
            glOrtho(0, windowWidth, windowHeight, 0, 1, -1); //âûñòàâëÿåì èõ êàê êîîðäèíàòû îêíà
            break;
        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

