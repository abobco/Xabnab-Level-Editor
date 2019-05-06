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

	SDL_Color textColor;
public:
	std::string inputText = "input text";

	menuButton textDisplay;

	bool done = false;
	bool firstinput = true;

public:
	KeyboardHandler(SDL_Renderer* Renderer, int size);
	
	bool handleInput(SDL_Event* e);
};

#endif