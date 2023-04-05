#pragma once

#include "Graphics/Window.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Time/Time.hpp"
#include "Core/AssetManager.hpp"
#include "Game/Game.hpp"
#include "ECS/System/PhysicsSystem.hpp"
#include "ECS/System/RenderSystem.hpp"
#include "ECS/System/ScriptSystem.hpp"

#include <string>
#include <vector>

namespace Endeavor 
{
    class Application
    {
    public:
        Application(Game& game);
        void start();
        
    private:
        Game& mActiveGame;

        Window mWindow;
        bool mGameIsRunning;

        std::shared_ptr<PhysicsSystem> mPhysicsSystem;
        std::shared_ptr<RenderSystem> mRenderSystem;
        std::shared_ptr<ScriptSystem> mScriptSystem;

        void loop();

        void processInput();
        void update(float deltaTime);
        void render();

        void quit();
    };
} // namespace Endeavor