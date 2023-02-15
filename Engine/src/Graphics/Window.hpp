#pragma once
#ifdef _WIN32
#include <glew.h>
#else
#include <GL/glew.h>
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Observer.hpp"
#include <stdio.h>
#include <iostream>

class Window
{
public:
    void create(const int &windowWidth, const int &windowHeight, const char * title, const GLuint &flags);
    void refresh();
    void swapBuffers();
    void destroy();
    SDL_Window * getWindow(){ return mWindow; };
    void onWindowResized(float width, float height);

private:
    int mWindowWidth;
    int mWindowHeight;
    GLuint mWindowFlags;
    SDL_Window * mWindow;
    SDL_GLContext mContext;
};