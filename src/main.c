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
}