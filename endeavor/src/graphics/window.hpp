#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <stdio.h>
#include <iostream>

namespace Endeavor
{
    class Window
    {
    public:
        void create(const int &windowWidth, const int &windowHeight, const char * title);
        void clear();
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
} // namespace Endeavor