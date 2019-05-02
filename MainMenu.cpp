#include "MainMenu.h"

MainMenu::MainMenu(SDL_Renderer* Renderer)
{
	int count = int(stages.vStages.size());
	for (int i = 0; i < count; i++)
	{
		menuButton* button = new menuButton(600, 200 * (i + 1), stages.vStages.at(i).c_str());

		button->loadText(Renderer);

		buttons.push_back(*button);
	}


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
			break;
		}
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
	return success;
}