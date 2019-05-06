#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "LTexture.h"
#include "macros.h"

#ifndef __MENUBUTTON_H__
#define __MENUBUTTON_H__

class menuButton
{
protected:
	//position and dimensions on the screen
	SDL_Point mPosition;


	//Button constants
	int BUTTON_WIDTH = 300;
	int BUTTON_HEIGHT = 100;
	std::string buttonText;

	LTexture textTexture;

	SDL_Texture* ttfTexture = NULL;

	TTF_Font *Font = NULL;

protected:
	void loadTexture(SDL_Renderer* Renderer);
public:
	int textWidth, textHeight;

public:
	//change to true when clicked
	bool pressed = false;

	SDL_Rect mRect;
	SDL_Rect textRect;

	menuButton();

	menuButton(int x, int y, std::string text);

	void handleEvent(SDL_Event* e);

	void setPosition(int x, int y);

	bool checkMouse(int x, int y);

	bool loadText(SDL_Renderer* Renderer);

	bool render(SDL_Renderer* Renderer);

	std::string getText() { return buttonText; }

	void changeText(std::string text) { buttonText = text; }
};


class newStageButton : public menuButton
{
public:
	newStageButton();
	std::string getFileName();
};

#endif