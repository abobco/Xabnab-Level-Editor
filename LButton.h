#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#ifndef __LBUTTON_H__
#define __LBUTTON_H__

//The mouse button
class LButton
{
public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	SDL_Point* getPos();

	//void move();


public:
	enum LButtonSprite
	{
		BUTTON_SPRITE_MOUSE_OUT = 0,
		BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
		BUTTON_SPRITE_MOUSE_DOWN = 2,
		BUTTON_SPRITE_MOUSE_UP = 3,
		BUTTON_SPRITE_DRAG = 4,
		BUTTON_SPRITE_TOTAL = 5
	};

	//Currently used global sprite
	LButtonSprite mCurrentSprite;

	;

	//Button constants
	const int BUTTON_WIDTH = 300;
	const int BUTTON_HEIGHT = 200;
	const int TOTAL_BUTTONS = 4;



private:
	//Top left position
	SDL_Point mPosition;

	bool mouseDrag = false;
	long int relX=0, relY=0;
};

#endif