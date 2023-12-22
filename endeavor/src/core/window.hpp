#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>

namespace Endeavor
{
	struct WindowProperties
	{
		WindowProperties(const std::string& title, uint32_t width, uint32_t height) : title(title), width(width), height(height) {}

		uint32_t width, height;
		std::string title;
	};

	class Window
	{
	public:
		Window(WindowProperties properties);
		~Window();

		void Init();
		void Update();
		void Clear(float red, float blue, float green);
		void SwapBuffers();
		void OnResize(uint32_t width, uint32_t height);

		GLFWwindow* GetNativeWindow();

	public:
		bool quit = false;

	private:
		GLFWwindow* m_Window = nullptr;
		WindowProperties m_Properties;
	};
}