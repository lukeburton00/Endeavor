#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

class Input
{
public:
 	static void processInput();
 	static bool isKeyPressed(const char * key);
	static bool isKeyReleased(const char * key);
	static bool isKeyDown(const char * key);
	static bool quit;
	
private:
	static std::vector<SDL_Keycode> pressedKeys;	
	static std::vector<SDL_Keycode> releasedKeys;
	static std::vector<SDL_Keycode> downKeys;
 };