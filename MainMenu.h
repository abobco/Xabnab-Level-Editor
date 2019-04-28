#pragma once

#include "menuButton.h"
#include "stageList.h"
#include <vector>

#ifndef __MAINMENU_H__
#define __MAINMENU_H__

class MainMenu
{
private:
	bool loadStage = false;
	bool newStage = false;

public:
	stageList stages;
	//vector<menuButton> buttons;

public:
	MainMenu();

	void handleEvent(SDL_Event* e);

	std::string getFileName() { return filename; }

	bool exit = false;

	std::string filename;


};

#endif