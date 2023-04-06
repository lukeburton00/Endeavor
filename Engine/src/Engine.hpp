#pragma once

#ifdef _WIN32
#include <SDL.h>
#undef main
#endif

/* ----- Core ----- */
#include "Application/Application.hpp"
#include "Core/Input/Input.hpp"
#include "Core/Time/Time.hpp"
#include "Core/Math/Random.hpp"
#include "Core/Math/Noise/PerlinNoise.hpp"
#include "Game/Game.hpp"
#include "Scene/Scene.hpp"
#include "Scripting/Behavior.hpp"

/* ----- ECS ----- */
#include "ECS/Component/Camera.hpp"
#include "ECS/Component/RigidBody.hpp"
#include "ECS/Component/Script.hpp"
#include "ECS/Component/Sprite.hpp"
#include "ECS/Component/Transform.hpp"
#include "ECS/Component/Tag.hpp"

#include "ECS/Entity/Entity.hpp"

/* ----- Graphics ----- */
#include "Core/AssetManager.hpp"