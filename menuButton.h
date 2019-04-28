#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

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


public:
	//change to true when clicked
	bool pressed = false;

	SDL_Rect mRect;

	menuButton();

	menuButton(int x, int y);

	void handleEvent(SDL_Event* e);

	void setPosition(int x, int y);

	bool checkMouse(int x, int y);

};

/*
class newStageButton : public menuButton
{
public:
	newStageButton();
	std::string getFileName();
};
*/
#endif