#include "Input.hpp"

std::vector<SDL_Keycode> Input::pressedKeys;	
std::vector<SDL_Keycode> Input::releasedKeys;
std::vector<SDL_Keycode> Input::downKeys;
bool Input::quit = false;

bool Input::leftMouseButtonDown = false;
bool Input::rightMouseButtonDown = false;

bool Input::leftMouseButtonPressed = false;
bool Input::rightMouseButtonPressed = false;

int Input::mousePositionX, Input::mousePositionY;

void Input::processInput()
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

bool Input::isKeyDown(const char * keyName)
{
    bool keyWasPressed = count(pressedKeys.begin(), pressedKeys.end(), SDL_GetKeyFromName(keyName));

 	return keyWasPressed;
}

bool Input::isKeyReleased(const char * keyName)
{
	bool keyWasReleased = count(releasedKeys.begin(), releasedKeys.end(), SDL_GetKeyFromName(keyName));

 	return keyWasReleased;
}

bool Input::isKeyPressed(const char * keyName)
{
	bool keyDown = count(downKeys.begin(), downKeys.end(), SDL_GetKeyFromName(keyName));

 	return keyDown;
}

bool Input::isLeftMouseButtonPressed()
{
	return leftMouseButtonPressed;
}

bool Input::isRightMouseButtonPressed()
{
	return rightMouseButtonPressed;
}

bool Input::isLeftMouseButtonDown()
{
	return leftMouseButtonDown;
}

bool Input::isRightMouseButtonDown()
{
	return rightMouseButtonDown;
}
