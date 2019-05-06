#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* Renderer)
{
	int count = int(stages.vStages.size());
	for (int i = 0; i < count; i++)
	{
		menuButton* button = new menuButton(WINDOW_WIDTH/2 - 150, 100+ 110 * (i + 1), stages.vStages.at(i).c_str());

		button->loadText(Renderer);

		buttons.push_back(*button);
	}

	NSbutton.loadText(Renderer);

	mRenderer = Renderer;
}

void MainMenu::handleEvent(SDL_Event* e)
{
	for (int i = 0; i < int(buttons.size()); i++)
	{
		buttons[i].handleEvent(e);
		if (buttons[i].pressed)
		{
			filename = stages.vStages[i];
			loadStage = true;
			exit = true;
			buttons[i].pressed = false;
			break;
		}
	}

	NSbutton.handleEvent(e);
	if (NSbutton.pressed && KBhandler == nullptr)
	{
		NSbutton.pressed = false;
		KBhandler = new KeyboardHandler(mRenderer, int(stages.vStages.size()));
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
}

bool MainMenu::render(SDL_Renderer* Renderer)
{
	bool success = true;
	for (int i = 0; i < int(buttons.size()); ++i)
	{
		if (!buttons[i].render(Renderer))
		{
			success = false;
		}
	}
	if (!NSbutton.render(Renderer))
		success = false;

	if ( KBhandler!=nullptr )
	{
		KBhandler->textDisplay.render(Renderer);
	}
	return success;
}