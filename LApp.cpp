#include "LApp.h"



App App::Instance;

//==============================================================================
App::App() {
}

//------------------------------------------------------------------------------
void App::OnEvent(SDL_Event* Event) {
}

//------------------------------------------------------------------------------
bool App::Init() {
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		Window = SDL_CreateWindow("XabNab Level Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
		if (Window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);
			//Create renderer for window
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
			if (Renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				if(!gButtonSpriteSheetTexture.loadFromFile("button.png", Renderer))
				{
					printf("Failed to load button sprite texture!\n");
					success = false;
				}
				else
				{
					/*
					//Set buttons
					for (int i = 0; i < TOTAL_BUTTONS; i++)
					{
						//add buttons to vector
						vbuttons.push_back(LButton());
					}
					*/
					//Set sprites
					for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
					{
						//get button dimensions
						int h = 200, w = 300;

						//set sprite clip rects
						bSpriteClips[i].x = 0;
						bSpriteClips[i].y = i * h;
						bSpriteClips[i].w = w;
						bSpriteClips[i].h = h;
					}

				}
				//Initialize renderer color
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Init Font
				if (TTF_Init() < 0) {
					// Error handling code
					printf("SDL_TTF could not initialize! SDL_TTF Error: %s\n", TTF_GetError());
				}

				//stageList.textTexture.loadFromRenderedText(Renderer,stageList.vStages[0], Stagecolor, Font);

				menu = new MainMenu(Renderer);
			}
		}
	}

	return success;
}

void App::Loop() {

}

void App::Render() {

	SDL_SetRenderDrawColor(Renderer, 0xDE, 0xB8, 0xFF, 0xFF);
	SDL_RenderClear(Renderer);

	//check if in menu
	if (menu->exit)
	{
		//draw all stage rects
		for (int i = 0; i < vbuttons.size(); ++i)
		{
			SDL_Rect dstrect;
			dstrect.x = vbuttons[i].getPos()->x;
			dstrect.y = vbuttons[i].getPos()->y;
			dstrect.h = vbuttons[i].BUTTON_HEIGHT;
			dstrect.w = vbuttons[i].BUTTON_WIDTH;

			SDL_RenderCopyEx(Renderer, gButtonSpriteSheetTexture.getTexture(), &bSpriteClips[vbuttons[i].mCurrentSprite], &dstrect, 0, NULL, SDL_FLIP_NONE);

			SDL_SetRenderDrawColor(Renderer, 0x6D, 0x28, 0x28, 0xFF);
			SDL_RenderDrawRects(Renderer, vbuttons[i].edgeBoxes, 4);
			SDL_RenderFillRects(Renderer, vbuttons[i].edgeBoxes, 4);
		}

		menuButton controlBox(640, 0, "Backspace to return to menu, S to save, A, to add rectangles, X to delete rectanges");
		controlBox.loadText(Renderer);
		controlBox.mRect.h = controlBox.textRect.h *= 0.4;
		controlBox.mRect.w = controlBox.textRect.w *= 0.4;
		controlBox.render(Renderer);
	}
	//draw Menu
	else
	{
		menu->render(Renderer);
	}

	SDL_RenderPresent(Renderer);
	
}

void App::Cleanup() {
	if (Renderer) {
		SDL_DestroyRenderer(Renderer);
		Renderer = NULL;
	}

	if (Window) {
		SDL_DestroyWindow(Window);
		Window = NULL;
	}

	SDL_Quit();
}

//------------------------------------------------------------------------------
int App::Execute(int argc, char* argv[]) {
	if (!Init()) return 0;

	SDL_Event Event;

	while (Running) {
		while (SDL_PollEvent(&Event) != 0) {

			//global event loop
			if (Event.type == SDL_QUIT) Running = false;
			if (Event.type == SDL_KEYDOWN && Event.key.keysym.sym == SDLK_ESCAPE)
			{
				Running = false;
			}

			if (!menu->exit)
				menu->handleEvent(&Event);
			else if (menu->exit && !loadflag)
			{
				loadRects();
				loadflag = true;
			}

			else
			{
				if (Event.type == SDL_KEYDOWN)
				{
					switch (Event.key.keysym.sym)
					{
					case SDLK_a:
						int x, y;
						SDL_GetMouseState(&x, &y);
						vbuttons.push_back(LButton(x, y));
						break;
					case SDLK_x:
						vbuttons.pop_back();
						break;
					case SDLK_s:
						saveToFile();
						break;
					case SDLK_ESCAPE:
						Running = false;
						break;
					case SDLK_BACKSPACE:
						menu = new MainMenu(Renderer);
						vbuttons.clear();
						loadflag = false;
						break;
					}
				}
				if (menu->exit)
				{
					for (int i = 0; i < vbuttons.size(); ++i)
					{
					vbuttons[i].handleEvent(&Event);
					}
				}
			}
		}

		Loop();

		Render();

		SDL_Delay(1); // Breath
	}

	Cleanup();

	return 1;
}

//=============================================================================//
void App::saveToFile()
{
	outfile.open(menu->filename);
	outfile << "Size: " << vbuttons.size() << std::endl;
	for (int i = 0; i < vbuttons.size(); i++)
	{
		outfile << vbuttons[i].mRect.x << ",";
		outfile << vbuttons[i].mRect.y << ",";
		outfile << vbuttons[i].mRect.w << ",";
		outfile << vbuttons[i].mRect.h << std::endl;
	}
	outfile.close();
}
//==============================================================================
void App::loadRects()
{
	std::string filename = menu->filename;
	std::ifstream iFile;
	iFile.open(filename);
	std::string line;
	std::string sSize;
	if(getline(iFile, line))
	{
		for (int i = 0; i < line.size(); i++)
		{
			if (isdigit(line[i]))
				sSize += line[i];
		}
		int size = std::stoi(sSize);
		SDL_Rect* nRect;
		for (int i = 0; i < size; i++)
		{
			nRect = new SDL_Rect;
			int coordinates[4];

			getline(iFile, line);
			int count = 0;
			for (int i = 0; i < 4; i++)
			{
				string sNum;
				int num;
				while (line[count] != ',' && count != line.size())
				{
					sNum += line[count];
					count++;
				}
				num = stoi(sNum);
				coordinates[i] = num;
				count++;
			}

			nRect->x = coordinates[0];
			nRect->y = coordinates[1];
			nRect->w = coordinates[2];
			nRect->h = coordinates[3];

			vbuttons.push_back(LButton(nRect));
		}
	}
}


//==============================================================================
App* App::GetInstance() { return &App::Instance; }

int App::GetWindowWidth() { return WindowWidth; }
int App::GetWindowHeight() { return WindowHeight; }

//==============================================================================
