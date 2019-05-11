#include "ToolPanel.h"


ToolPanel::ToolPanel()
{
	border = Rectangle(WINDOW_WIDTH, 0, 200, WINDOW_HEIGHT, 219, 76, 76);
	toolBox = Rectangle(WINDOW_WIDTH + 5, 5, 190, WINDOW_HEIGHT - 10, 0, 40, 200);
}

ToolPanel::ToolPanel(SDL_Renderer* oRenderer, vector<LButton>& vbuttons)
{
	Renderer = oRenderer;

	border = Rectangle(WINDOW_WIDTH, 0, 400, WINDOW_HEIGHT, 219, 76, 76);
	toolBox = Rectangle(WINDOW_WIDTH + 5, 5, 390, WINDOW_HEIGHT - 10, 0, 40, 200);

	toolBox.setColor(120, 100, 100, 99);

	SDL_Point tempOrigin = toolBox.getPosition();
	for (int i = 0; i < int(vbuttons.size()); i++)
	{
		rectButtons.push_back(menuButton(tempOrigin.x + 10, tempOrigin.y + 10 + i * 52, "rect " + std::to_string(i)));
		rectButtons[i].setDimensions(160, 50);
		rectButtons[i].loadText(Renderer);

		Lbuttons.push_back(&vbuttons[i]);
	}
}

void ToolPanel::render()
{
	SDL_RenderSetViewport(Renderer, &fullwindow);
	border.render(Renderer);
	toolBox.render(Renderer);

	for (int i = 0; i < int(rectButtons.size()); i++)
	{
		rectButtons[i].render(Renderer);
	}
}

void ToolPanel::handleEvent(SDL_Event* e)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	
	if (checkMouse(x, y))
	{
		for (int i = 0; i < int(rectButtons.size()); i++)
		{
			rectButtons[i].handleEvent(e);
			if (rectButtons[i].hovering )
			{
				Lbuttons[i]->toolHover = true;
			}
			else
			{
				Lbuttons[i]->toolHover = false;
			}
		}
		
	}
	else
	{
		for (int i = 0; i < int(rectButtons.size()); i++)
		{
			Lbuttons[i]->toolHover = false;
		}
	}
}

bool ToolPanel::checkMouse(int x, int y)
{
	//Check if mouse is in button
	bool inside = true;

	SDL_Point tempOrigin = toolBox.getPosition();
	//Mouse is left of the button
	if (x < tempOrigin.x)
	{
		inside = false;
	}
	//Mouse is right of the button
	else if (x > tempOrigin.x + toolBox.getDimensions().x)
	{
		inside = false;
	}
	//Mouse above the button
	else if (y < tempOrigin.y)
	{
		inside = false;
	}
	//Mouse below the button
	else if (y > tempOrigin.y + toolBox.getDimensions().y)
	{
		inside = false;
	}
	return inside;
}

void ToolPanel::addButton(LButton *butt)
{
	Lbuttons.push_back(butt);

	SDL_Point tempOrigin = toolBox.getPosition();
	int tempsize = int(rectButtons.size());
	rectButtons.push_back(menuButton(tempOrigin.x + 10, tempOrigin.y + 10 + (tempsize) * 52, "rect " + std::to_string(tempsize)));
	rectButtons[tempsize].setDimensions(160, 50);
	rectButtons[tempsize].loadText(Renderer);
}

void ToolPanel::removeButton()
{
	if (Lbuttons.size() > 0)
	{
		Lbuttons.pop_back();
		rectButtons.pop_back();
	}
}