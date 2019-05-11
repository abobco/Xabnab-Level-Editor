#include "stageList.h"

stageList::stageList()
{
	//load text file of stage filenames
	loadFile();

}

stageList::stageList(SDL_Renderer* oRenderer)
{
	loadFile();
	Renderer = oRenderer;

	innerWindow = Rectangle(WINDOW_WIDTH / 2 + 5, 5, WINDOW_WIDTH / 2 - 10, WINDOW_HEIGHT - 10, 0, 40, 200);
	borderWindow = Rectangle(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, 219, 76, 76);
	appWindow = Rectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	for (int i = 0; i < vStages.size(); i++)
	{
		stageButtons.push_back(new menuButton(innerWindow.getPosition().x+20, innerWindow.getPosition().y + 5 + i * 52, vStages[i]));
		stageButtons[i]->displayRect.setDimensions(200, 50);
		stageButtons[i]->loadText(Renderer);
	}
}

void stageList::loadFile()
{
	listIF.open("stages/stageList.txt");
	string currStage;
	while (getline(listIF, currStage))
	{
		vStages.push_back(currStage);
	}
	listIF.close();
}
void stageList::newStage(string filename)
{
	vStages.push_back(filename);
	listOF.open("stages/stageList.txt", std::ofstream::app );
	listOF << filename << endl;
	listOF.close();

	listOF.open(filename);

	listOF << "Size: 1\n100, 100, 100, 100\n";
	listOF.close();
}
void stageList::removeItem(int index)
{
	vStages.erase(vStages.begin() + index);
}

void stageList::render()
{
	SDL_Color tempCol = borderWindow.getColor();
	
	SDL_SetRenderDrawColor(Renderer, 80, 80, 80, 80);
	SDL_RenderFillRect(Renderer, &borderWindow.getRect());

	tempCol = innerWindow.getColor();
	SDL_SetRenderDrawColor(Renderer, 190, 100, 100, 99);
	SDL_RenderFillRect(Renderer, &innerWindow.getRect());

	
	for (int i = 0; i < vStages.size(); i++)
	{
		SDL_RenderSetViewport(Renderer, &innerWindow.getRect());
		stageButtons[i]->render(Renderer);
	}
	
	SDL_RenderSetViewport(Renderer, &appWindow.getRect());
}