#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "LTexture.h"
#include "macros.h"
#include "Rectangle.h"

#ifndef __MENUBUTTON_H__
#define __MENUBUTTON_H__

class menuButton
{
protected:
	//position and dimensions on the screen
	SDL_Point mPosition;
	
	SDL_Color DefaultColor;
	SDL_Color HoldColor;
	SDL_Color HoverColor;

	Rectangle hoverBox;

	//Button constants
	int BUTTON_WIDTH = 300;
	int BUTTON_HEIGHT = 100;
	std::string buttonText;

	LTexture textTexture;

	SDL_Texture* ttfTexture = NULL;

	TTF_Font *Font = NULL;

protected:
	//void loadTexture(SDL_Renderer* Renderer);
public:
	int textWidth, textHeight;
	//change to true when clicked
	bool pressed = false;
	bool hovering = false;
	bool held = false;
	Rectangle displayRect;

	SDL_Rect mRect;
	SDL_Rect textRect;

public:



	menuButton();

	menuButton(int x, int y, std::string text);

	menuButton(Rectangle oRect, std::string text, SDL_Renderer* Renderer);

	void handleEvent(SDL_Event* e);

	void setPosition(int x, int y);

	bool checkMouse(int x, int y);

	bool loadText(SDL_Renderer* Renderer);

	bool loadText(SDL_Renderer* Renderer, SDL_Color stagecolor);

	bool render(SDL_Renderer* Renderer);

	bool render(SDL_Renderer* Renderer, SDL_Color buttonColor);

	std::string getText() { return buttonText; }

	void changeText(std::string text) { buttonText = text; }

	void setDimensions(int w, int h);
	void setDimensions(int w, int h, SDL_Renderer* Renderer);
};


class newStageButton : public menuButton
{
public:
	newStageButton();
	std::string getFileName();
};

#endif
