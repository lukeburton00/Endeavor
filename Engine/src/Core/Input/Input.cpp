#include "Core/Input/Input.hpp"

#include <stdio.h>
#include <iostream>

std::vector<SDL_Keycode> Endeavor::Input::pressedKeys;	
std::vector<SDL_Keycode> Endeavor::Input::releasedKeys;
std::vector<SDL_Keycode> Endeavor::Input::downKeys;

bool Endeavor::Input::quit = false;

bool Endeavor::Input::leftMouseButtonDown = false;
bool Endeavor::Input::rightMouseButtonDown = false;

bool Endeavor::Input::leftMouseButtonPressed = false;
bool Endeavor::Input::rightMouseButtonPressed = false;

int Endeavor::Input::mousePositionX, Endeavor::Input::mousePositionY;

void Endeavor::Input::processInput()
{	
	SDL_Keycode keyCodeDown;
	SDL_Keycode keyCodeUp;
	SDL_Event event;
	quit = false;
 	releasedKeys.clear();
	downKeys.clear();
	leftMouseButtonPressed = false;
	rightMouseButtonPressed = false;

 	while (SDL_PollEvent(&event) != 0)
 	{
		SDL_GetMouseState(&mousePositionX, &mousePositionY);
 		switch(event.type)
 		{
 			case SDL_KEYDOWN:
 			{
 				keyCodeDown = event.key.keysym.sym;
				if (!count(pressedKeys.begin(), pressedKeys.end(), keyCodeDown))
				{
 					pressedKeys.push_back(keyCodeDown);
				}

				if (!count(downKeys.begin(), downKeys.end(), keyCodeDown))
				{
 					downKeys.push_back(keyCodeDown);
				}
 				break;
 			}

 			case SDL_KEYUP:
 			{
 				keyCodeUp = event.key.keysym.sym;
				if (count(pressedKeys.begin(), pressedKeys.end(), keyCodeUp))
				{
 					pressedKeys.erase(remove(pressedKeys.begin(), pressedKeys.end(), keyCodeUp));
 					releasedKeys.push_back(keyCodeUp);
				}

 				break;
 			}

			case SDL_MOUSEBUTTONDOWN:
			{
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						leftMouseButtonPressed = true;
						leftMouseButtonDown = true;
						break;
					}
					case SDL_BUTTON_RIGHT:
					{
						rightMouseButtonPressed = true;
						rightMouseButtonDown = true;
						break;
					}

					default: break;
				}
				break;
			}

			case SDL_MOUSEBUTTONUP:
			{
				switch (event.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						leftMouseButtonDown = false;
						break;
					}
					case SDL_BUTTON_RIGHT:
					{
						rightMouseButtonDown = false;
						break;
					}

					default: break;
				}
				break;
			}

 			case SDL_QUIT:
 			{
 				quit = true;
 				break;
 			}

			case SDL_WINDOWEVENT:
			{
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{

				}
				break;
			}

 			default:
 			{
 				break;
 			}
 		}
 	}
 }

bool Endeavor::Input::isKeyDown(const char * keyName)
{
    bool keyWasPressed = count(pressedKeys.begin(), pressedKeys.end(), SDL_GetKeyFromName(keyName));

 	return keyWasPressed;
}

bool Endeavor::Input::isKeyReleased(const char * keyName)
{
	bool keyWasReleased = count(releasedKeys.begin(), releasedKeys.end(), SDL_GetKeyFromName(keyName));

 	return keyWasReleased;
}

bool Endeavor::Input::isKeyPressed(const char * keyName)
{
	bool keyDown = count(downKeys.begin(), downKeys.end(), SDL_GetKeyFromName(keyName));

 	return keyDown;
}

bool Endeavor::Input::isLeftMouseButtonPressed()
{
	return leftMouseButtonPressed;
}

bool Endeavor::Input::isRightMouseButtonPressed()
{
	return rightMouseButtonPressed;
}

bool Endeavor::Input::isLeftMouseButtonDown()
{
	return leftMouseButtonDown;
}

bool Endeavor::Input::isRightMouseButtonDown()
{
	return rightMouseButtonDown;
}
