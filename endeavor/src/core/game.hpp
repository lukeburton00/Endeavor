#pragma once

#include "window.hpp"

#include <string>

namespace Endeavor
{
	class Game
	{
	public:
		Game();
		~Game();

		void Run();

	protected:
		virtual void Update() = 0;
		virtual void Render() = 0;

	protected:
		bool m_Running = true;
		Window m_Window;

	};

	Game* CreateGame();
}// namespace Endeavor