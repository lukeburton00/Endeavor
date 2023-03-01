#pragma once

#ifdef _WIN32
#include <SDL.h>
#undef main
#endif

/* ----- Core ----- */
#include "Application/Application.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "Random.hpp"
#include "Game.hpp"
#include "Scene/Scene.hpp"
#include "Behavior.hpp"

/* ----- ECS ----- */
#include "Transform.hpp"
#include "RigidBody.hpp"
#include "Sprite.hpp"
#include "Script.hpp"

/* ----- Events -----*/
#include "Observer.hpp"
#include "Subject.hpp"

/* ----- Graphics ----- */
#include "AssetManager.hpp"