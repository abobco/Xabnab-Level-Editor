#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "menuButton.h"
#include "LTexture.h"
#include "Rectangle.h"

#ifndef __STAGELIST_H__
#define __STAGELIST_H__

using namespace std;
class stageList
{
private:
	int stagePages;

	ifstream listIF;
	ofstream listOF;
	SDL_Renderer* Renderer = NULL;
	Rectangle appWindow;
	Rectangle innerWindow;
	Rectangle borderWindow;
public:
	vector<string> vStages;
	vector<menuButton*> stageButtons;
	LTexture textTexture;
private:

public:
	stageList();
	stageList(SDL_Renderer* oRenderer);

	void loadFile();
	void newStage(string filename);
	void removeItem(int index);

	void render();
	void handleEvent(SDL_Event* e);
};

#endif
