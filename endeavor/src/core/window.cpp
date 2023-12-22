#include "window.hpp"

namespace Endeavor 
{
    Window::Window(WindowProperties properties)
        : m_Properties(properties) {}

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::Init()
    {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #if defined(__APPLE__) || defined(__MACH__)
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif 

        m_Window = glfwCreateWindow(m_Properties.width, m_Properties.height, m_Properties.title.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(m_Window);

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        glfwSetWindowUserPointer(m_Window, this);

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
            {
                Window* gameWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
                gameWindow->quit = true;
            });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
            {
                Window* gameWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
                gameWindow->OnResize(width, height);
            });

        glViewport(0, 0, m_Properties.width, m_Properties.height);
    }

    void Window::Update()
    {
        glfwPollEvents();
    }

    void Window::Clear(float red, float blue, float green)
    {
        glClearColor(red, blue, green, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }

    GLFWwindow* Window::GetNativeWindow()
    {
        return m_Window;
    }

    void Window::OnResize(uint32_t width, uint32_t height)
    {
        m_Properties.width = width;
        m_Properties.height = height;
        glViewport(0, 0, width, height);
    }
}