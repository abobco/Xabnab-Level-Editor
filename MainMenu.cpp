#include "MainMenu.h"
#include <time.h>

MainMenu::MainMenu(SDL_Renderer* Renderer)
{
	stages = stageList(Renderer);
	int count = int(stages.vStages.size());

	NSbutton = menuButton(100 , 150, "New Stage");
	NSbutton.loadText(Renderer);

	stageListButton = menuButton(100, 260, "Load Stage");
	stageListButton.loadText(Renderer);

	instructions = new menuButton(WINDOW_WIDTH / 2 + 155, 30, "just type a name and press enter ya dingus");
	
	instructions->displayRect.setDimensions(200, 50);
	instructions->loadText(Renderer);
	//instructions->textRect.h = instructions->mRect.h *= 0.4;
	instructions->textRect.w = instructions->mRect.w *= 0.5;
	instructions->displayRect.setDimensions(instructions->textRect.w, 50);
	
	mRenderer = Renderer;

}

void MainMenu::handleEvent(SDL_Event* e)
{
	
	NSbutton.handleEvent(e);
	if (NSbutton.pressed && KBhandler == nullptr)
	{
		NSbutton.pressed = false;
		KBhandler = new KeyboardHandler(mRenderer, int(stages.vStages.size()));
		showStageList = false;
	}
	if (KBhandler != nullptr && KBhandler->done != true)
	{
		KBhandler->handleInput(e);
	}
	if (KBhandler != nullptr && KBhandler->done == true)
	{
		filename = KBhandler->inputText;
		filename = "stages/" + filename + ".txt";
		stages.newStage(filename);
		exit = true;
	}
	stageListButton.handleEvent(e);
	if (stageListButton.pressed)
	{
		KBhandler = nullptr;
		stageListButton.pressed = false;
		showStageList = true;
	}
	if (showStageList)
	{
		for (int i = 0; i < int(stages.stageButtons.size()); i++)
		{
			stages.stageButtons[i]->handleEvent(e);
			if (stages.stageButtons[i]->pressed)
			{
				filename = stages.vStages[i];
				loadStage = true;
				exit = true;
				stages.stageButtons[i]->pressed = false;
				break;
			}
		}
	}
}

bool MainMenu::render(SDL_Renderer* Renderer)
{
	bool success = true;

	if (!NSbutton.render(Renderer))
		success = false;
	if (!stageListButton.render(Renderer))
		success = false;

	if ( KBhandler!=nullptr )
	{
		SDL_Color textbutton;
		textbutton.a = 0;
		textbutton.r = 160;
		textbutton.b = 0;
		textbutton.g = 0;
		KBhandler->textDisplay.render(Renderer, textbutton);

		instructions->render(Renderer);
	}
	else if (showStageList) 
	{
		stages.render();
	}
	return success;
}