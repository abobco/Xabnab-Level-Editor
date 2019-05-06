#include "menuButton.h"


menuButton::menuButton()
{
	setPosition(300, 300);
	mRect.h = BUTTON_HEIGHT;
	mRect.w = BUTTON_WIDTH;
	buttonText = "NEW STAGE";
}
menuButton::menuButton(int x, int y, std::string text)
{
	setPosition(x, y);
	mRect.h = BUTTON_HEIGHT;
	mRect.w = BUTTON_WIDTH;
	buttonText = text;
}
void menuButton::handleEvent(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_KEYDOWN)
	{
		//Check collision of mouse and button
			//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = checkMouse(x, y);

		if (inside)
		{
			//BUTTON EVENT CODE
			switch (e->type)
			{
			case SDL_MOUSEBUTTONUP:
				pressed = true;
				break;
			}
		}
	}
}

void menuButton::setPosition(int x, int y)
{
	mPosition.x = mRect.x = x;
	mPosition.y = mRect.y = y;
}

bool menuButton::checkMouse(int x, int y)
{
	//Check if mouse is in button
	bool inside = true;

	//Mouse is left of the button
	if (x < mPosition.x)
	{
		inside = false;
	}
	//Mouse is right of the button
	else if (x > mPosition.x + BUTTON_WIDTH)
	{
		inside = false;
	}
	//Mouse above the button
	else if (y < mPosition.y)
	{
		inside = false;
	}
	//Mouse below the button
	else if (y > mPosition.y + BUTTON_HEIGHT)
	{
		inside = false;
	}
	return inside;
}

void menuButton::loadTexture(SDL_Renderer* Renderer)
{
	Font = TTF_OpenFont("stages/OpenSans-Regular.ttf", 12);
	SDL_Color fontcolor;
	fontcolor.a = 0;
	fontcolor.r = 0;
	fontcolor.b = 0;
	fontcolor.g = 0;
	textTexture.loadFromRenderedText(Renderer, buttonText, fontcolor, Font);

}

bool menuButton::loadText(SDL_Renderer* Renderer)
{
	bool success = true;
	//Init Font
	if (TTF_Init() < 0) {
		// Error handling code
		printf("SDL_TTF could not initialize! SDL_TTF Error: %s\n", TTF_GetError());
		success = false;
	}
	Font = TTF_OpenFont("stages/fonts/VT323.ttf", 60);
	if (Font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	SDL_Color Stagecolor;
	Stagecolor.a = 0;
	Stagecolor.r = 160;
	Stagecolor.b = 0;
	Stagecolor.g = 0;

	std::string txt;
	if (buttonText[0] == 's' && buttonText[6] == '/')
	{
		for (int i = 7; i < int(buttonText.size()) - 4; i++)
		{
			txt += buttonText[i];
		}
	}
	else txt = buttonText;
	SDL_Surface* surface = TTF_RenderText_Solid(Font, txt.c_str(), Stagecolor);
	if (surface == NULL)
	{
		printf("Failed to create surface! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	ttfTexture = SDL_CreateTextureFromSurface(Renderer, surface);

	
	SDL_QueryTexture(ttfTexture, NULL, NULL, &textWidth, &textHeight);
	textRect.x = mRect.x;
	textRect.y = mRect.y;
	textRect.w = textWidth;
	textRect.h = mRect.h;

		mRect.w = textWidth;


	SDL_FreeSurface(surface);

	return success;
}

bool menuButton::render(SDL_Renderer* Renderer)
{
	bool success = true;

	SDL_SetRenderDrawColor(Renderer, 0x8F, 0x99, 0xAA, 0xFF);
	SDL_RenderFillRect(Renderer, &mRect);
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(Renderer, &mRect);

	SDL_RenderCopyEx(Renderer, ttfTexture, 0, &textRect, 0, 0, SDL_FLIP_NONE);
	return success;
}





//==============================================================================================//

//newStageButtonFunctions

newStageButton::newStageButton()
{
	mRect.h = BUTTON_HEIGHT;
	mRect.w = BUTTON_WIDTH;
	setPosition(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 80);
	buttonText = "NEW STAGE";
}


