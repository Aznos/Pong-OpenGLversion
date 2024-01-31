#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc;
    HWND hwnd;
    HDC hdc;
    HGLRC hrc;
    MSG msg;
    BOOL bQuit = FALSE;

    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProcedure;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass(&wc);

    hwnd = CreateWindow(
        "GLSample", "Pong",
        WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
        0, 0, 1280, 720,
        NULL, NULL, hInstance, NULL
    );

    EnableOpenGL(hwnd, &hdc, &hrc);

    while(!bQuit) {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if(msg.message == WM_QUIT) {
                bQuit = TRUE;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

            glBegin(GL_QUADS);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex2f(-0.92f, 0.2f);
                glVertex2f(-0.88f, 0.2f);
                glVertex2f(-0.88f, -0.2f);
                glVertex2f(-0.92f, -0.2f);
            glEnd();

            glBegin(GL_QUADS);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex2f(0.88f, 0.2f);
                glVertex2f(0.92f, 0.2f);
                glVertex2f(0.92f, -0.2f);
                glVertex2f(0.88f, -0.2f);
            glEnd();

            SwapBuffers(hdc);
        }
    }

    DisableOpenGL(hwnd, hdc, hrc);
    DestroyWindow(hwnd);
    return msg.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam) {
    switch(message) {
        case WM_CLOSE:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lparam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hdc, HGLRC* hrc) {
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    *hdc = GetDC(hwnd);

    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat(*hdc, &pfd);
    SetPixelFormat(*hdc, iFormat, &pfd);

    *hrc = wglCreateContext(*hdc);
    wglMakeCurrent(*hdc, *hrc);
}

void DisableOpenGL(HWND hwnd, HDC hdc, HGLRC hrc) {
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hrc);
    ReleaseDC(hwnd, hdc);
}