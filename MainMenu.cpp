#include "MainMenu.h"

MainMenu::MainMenu()
{


}

void MainMenu::handleEvent(SDL_Event* e)
{
	for (int i = 0; i < stages.vButtons.size(); i++)
	{
		stages.vButtons[i].handleEvent(e);
		if (stages.vButtons[i].pressed)
		{
			filename = stages.vStages[i];
			loadStage = true;
			exit = true;
			break;
		}
	}

}