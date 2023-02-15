#include "Input.hpp"

std::vector<SDL_Keycode> Input::pressedKeys;	
std::vector<SDL_Keycode> Input::releasedKeys;
bool Input::quit = false;

void Input::processInput()
{	
	SDL_Keycode keyCodeDown;
	SDL_Keycode keyCodeUp;
	SDL_Event event;
	quit = false;
 	releasedKeys.clear();
 	while (SDL_PollEvent(&event) != 0)
 	{
 		switch(event.type)
 		{
 			case SDL_KEYDOWN:
 			{
 				keyCodeDown = event.key.keysym.sym;
				if (!count(pressedKeys.begin(), pressedKeys.end(), keyCodeDown))
				{
 					pressedKeys.push_back(keyCodeDown);
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

bool Input::isKeyPressed(const char * keyName)
{
    bool keyWasPressed = count(pressedKeys.begin(), pressedKeys.end(), SDL_GetKeyFromName(keyName));

 	return keyWasPressed;
}

bool Input::isKeyReleased(const char * keyName)
{
	bool keyWasReleased = count(releasedKeys.begin(), releasedKeys.end(), SDL_GetKeyFromName(keyName));

 	return keyWasReleased;
}