#pragma once

#include "menuButton.h"
#include "stageList.h"
#include <vector>
#include <SDL2/SDL.h>
#include "KeyboardHandler.h"

#ifndef __MAINMENU_H__
#define __MAINMENU_H__

class MainMenu
{
private:
	bool loadStage = false;
	bool newStage = false;;
	bool showStageList = false;

public:
	stageList stages;
	
	//menuButton controls;
	//vector<menuButton> buttons;
	menuButton NSbutton;
	menuButton stageListButton;
	menuButton* instructions = nullptr;

	KeyboardHandler* KBhandler = nullptr;
	SDL_Renderer* mRenderer = NULL;

public:
	MainMenu(SDL_Renderer* Renderer);

	void handleEvent(SDL_Event* e);

	std::string getFileName() { return filename; }

	bool render(SDL_Renderer* Renderer);

	void setStageList() { showStageList = true; }

	bool exit = false;

	std::string filename;


};

#endif
