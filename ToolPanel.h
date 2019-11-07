#pragma once

#include <SDL2/SDL.h>
#include "Rectangle.h"
#include "menuButton.h"
#include <vector>
#include "LButton.h"

using namespace std;
#ifndef __TOOLPANEL_H__
#define __TOOLPANEL_H__

class ToolPanel
{
private:
	Rectangle toolBox;
	Rectangle border;
	vector<menuButton> rectButtons;

	vector<LButton*> Lbuttons;
	SDL_Renderer* Renderer = nullptr;
	SDL_Rect fullwindow = { 0,0,WINDOW_WIDTH + 400, WINDOW_HEIGHT };

private:
	bool checkMouse(int x, int y);

public:
	ToolPanel();
	ToolPanel(SDL_Renderer* oRenderer, vector<LButton>& vbuttons);

	void render();

	void handleEvent(SDL_Event *e);

	void addButton(LButton *butt);

	void removeButton();
};
#endif

