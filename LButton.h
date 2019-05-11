#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Rectangle.h"

#ifndef __LBUTTON_H__
#define __LBUTTON_H__

//The mouse button
class LButton
{
public:
	enum ResizeState
	{
		NO_RESIZE = 0,
		TOP_RESIZE = 1,
		BOT_RESIZE = 2,
		LEFT_RESIZE = 3,
		RIGHT_RESIZE = 4,
		TLC_RESIZE = 5,
		TRC_RESIZE = 6,
		BLC_RESIZE = 7,
		BRC_RESIZE = 8
	};
	enum LButtonSprite
	{
		BUTTON_SPRITE_MOUSE_OUT = 0,
		BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
		BUTTON_SPRITE_MOUSE_DOWN = 2,
		BUTTON_SPRITE_MOUSE_UP = 3,
		BUTTON_SPRITE_DRAG = 4,
		BUTTON_SPRITE_TOTAL = 5
	};
	//Initializes internal variables
	LButton();

	LButton(int x, int y);

	LButton(SDL_Rect* rect);

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	SDL_Point* getPos();

	void setEdges();

	int checkResize(int x, int y);
	
	void HandleResize(SDL_Event* e, int ResizeState);
	//void move();


public:



	//Currently used global sprite
	LButtonSprite mCurrentSprite;

	SDL_Rect mRect;

	SDL_Rect edgeBoxes[4];

	SDL_Rect cornerBoxes[4];

	//Button constants
	int BUTTON_WIDTH = 300;
	int BUTTON_HEIGHT = 200;
	const int TOTAL_BUTTONS = 4;

	bool toolHover = false;
	bool mouseHover = false;

	Rectangle glowRect;

private:
	//Top left position
	SDL_Point mPosition;

	bool mouseDrag = false;
	bool resizeDrag = false;
	bool resizing = false;
	long int relX=0, relY=0;
	long int relDragX, relDragY = 0;

	long int stableEdgeX = 0;
	long int stableEdgeY = 0;

	int ResizeState = 0;
	
	

};

#endif