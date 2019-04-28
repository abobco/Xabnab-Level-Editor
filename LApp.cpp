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
					//Set buttons
					for (int i = 0; i < TOTAL_BUTTONS; i++)
					{
						//add buttons to vector
						vbuttons.push_back(LButton());
					}
					//Set sprites
					for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
					{
						//get button dimensions
						int h = vbuttons[0].BUTTON_HEIGHT, w = vbuttons[0].BUTTON_WIDTH;

						//set sprite clip rects
						bSpriteClips[i].x = 0;
						bSpriteClips[i].y = i * h;
						bSpriteClips[i].w = w;
						bSpriteClips[i].h = h;
					}
					//Set buttons in corners
					/*
					int h = vbuttons[0].BUTTON_HEIGHT, w = vbuttons[0].BUTTON_WIDTH;
					vbuttons[0].setPosition(0, 0);
					vbuttons[1].setPosition(WindowWidth - w, 0);
					vbuttons[2].setPosition(0, WindowHeight - h);
					vbuttons[3].setPosition(WindowWidth - w, WindowHeight - h);
					*/
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
				Font = TTF_OpenFont("stages/OpenSans-Regular.ttf", 12);
				SDL_Color Stagecolor;
				Stagecolor.a = 0;
				Stagecolor.r = 0;
				Stagecolor.b = 0;
				Stagecolor.g = 0;
				stageList.textTexture.loadFromRenderedText("garbage", Stagecolor, Font);
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
	/*
	for (int i = 0; i < stageList.vButtons.size(); ++i)
	{
		SDL_SetRenderDrawColor(Renderer, 0x8F, 0x99, 0xAA, 0xFF);
		SDL_RenderDrawRect(Renderer, &stageList.vButtons[i].mRect);
		SDL_RenderFillRect(Renderer, &stageList.vButtons[i].mRect);

		SDL_RenderCopyEx(Renderer, stageList.textTexture.getTexture(), 0, &stageList.vButtons[i].mRect, 0, 0, SDL_FLIP_NONE);
	}
	*/
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
					}
				}
				for (int i = 0; i < vbuttons.size(); ++i)
				{
					vbuttons[i].handleEvent(&Event);
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
	outfile.open("output.txt");
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
App* App::GetInstance() { return &App::Instance; }

int App::GetWindowWidth() { return WindowWidth; }
int App::GetWindowHeight() { return WindowHeight; }

//==============================================================================
