#pragma once

#include "menuButton.h"
#include "stageList.h"
#include <vector>
#include <SDL.h>
#include "KeyboardHandler.h"

#ifndef __MAINMENU_H__
#define __MAINMENU_H__

class MainMenu
{
private:
	bool loadStage = false;
	bool newStage = false;

public:
	stageList stages;
	vector<menuButton> buttons;
	newStageButton NSbutton;
	KeyboardHandler* KBhandler = nullptr;
	SDL_Renderer* mRenderer = NULL;

public:
	MainMenu(SDL_Renderer* Renderer);

	void handleEvent(SDL_Event* e);

	std::string getFileName() { return filename; }

	bool render(SDL_Renderer* Renderer);

	bool exit = false;

	std::string filename;


};

#endif