#include "Graphics/Window.hpp"

void Endeavor::Window::create(const int &windowWidth, const int &windowHeight, const char * title, const GLuint &flags)
{
    #ifdef DEBUG
    printf("Creating window...\n");
    #endif

    mWindowWidth = windowWidth;
    mWindowHeight = windowHeight;
    mWindowFlags = flags;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL video could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }

    else
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        mWindow = SDL_CreateWindow( title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWindowWidth, mWindowHeight, mWindowFlags);
        if( mWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }

        else
        {
            mContext = SDL_GL_CreateContext(mWindow);
        }

        SDL_GL_SetSwapInterval(0);
        glewExperimental = GL_TRUE;
        glewInit();
    }

    #ifdef DEBUG
    printf("Window created.\n");
    #endif
}

void Endeavor::Window::clear()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Endeavor::Window::swapBuffers()
{
	SDL_GL_SwapWindow(mWindow);
}

void Endeavor::Window::destroy()
{
    #ifdef DEBUG
    printf("\nDestroying Window...\n");
    #endif
    
    SDL_DestroyWindow(mWindow);
    SDL_GL_DeleteContext(mContext);

    #ifdef DEBUG
    printf("Window destroyed.\n");
    #endif
}

void Endeavor::Window::onWindowResized(float width, float height)
{
    glViewport(0, 0, width, height);
}