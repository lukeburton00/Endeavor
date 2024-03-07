#pragma once

#include "window.hpp"

#include <string>

namespace Endeavor
{
	class Game
	{
	public:
		Game();
		virtual ~Game() = default;

		static Game& GetInstance() { return *s_Instance; }
		Window& GetWindow() { return m_Window; }

		void Run();

	protected:
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

	protected:
		bool m_Running = true;
		Window m_Window;

	private:
		static Game* s_Instance;

	};

	Game* CreateGame();

}// namespace Endeavor