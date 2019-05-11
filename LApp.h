#pragma once
//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include <vector>
#include "LButton.h"
#include <fstream>
#include "stageList.h"
#include "MainMenu.h"
#include "ToolPanel.h"



#ifndef __LAPP_H__
#define __LAPP_H__
//-----------------------------------------------------------//
class App {
private:
	static App Instance;

	bool Running = true;
	bool inMenu = true;
	bool loadflag = false;
	bool nStageflag = false;
	bool showcontrols = true;

	SDL_Window* Window = NULL;
	SDL_Renderer* Renderer = NULL;
	SDL_Surface* PrimarySurface = NULL;

	
	const int BUTTON_SPRITE_TOTAL = 5;
	int TOTAL_BUTTONS = 1;

	//SDL_Texture* xTexture = NULL;

	static const int WindowWidth = 1840;
	static const int WindowHeight = 800;

	//Mouse button sprites
	SDL_Rect bSpriteClips[5];
	LTexture gButtonSpriteSheetTexture;

	//text texture
	SDL_Texture* textTexture = nullptr;

	//vector of buttons
	std::vector<LButton> vbuttons;
	std::ofstream outfile;

	stageList stageList;

	TTF_Font *Font = NULL;

	//main menu object pointer
	MainMenu* menu = nullptr;

	menuButton* controlBox = nullptr;

	ToolPanel* rectpanel = nullptr;

private:
	App();

	// Capture SDL Events
	void OnEvent(SDL_Event* Event);

	// Initialize our SDL game / app
	bool Init();

	// Logic loop
	void Loop();

	// Render loop (draw)
	void Render();

	void saveToFile();

	// Free up resources
	void Cleanup();

	// Load stage from button press
	void loadRects();


public:
	int Execute(int argc, char* argv[]);

	//bool LoadMedia();

public:
	static App* GetInstance();

	static int GetWindowWidth();
	static int GetWindowHeight();




};

#endif