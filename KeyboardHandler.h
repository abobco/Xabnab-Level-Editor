#pragma once
#include <SDL.h>
#include <string>
#include "menuButton.h"
#include "macros.h"


#ifndef __KEYBOARDHANDLER_H__
#define __KEYBOARDHANDLER_H__

class KeyboardHandler
{
protected:
	SDL_Renderer* kRenderer = NULL;
public:
	std::string inputText = "input text";

	menuButton textDisplay;

public:
	KeyboardHandler(SDL_Renderer* Renderer);
	
	bool handleInput(SDL_Event* e);
};

#endif