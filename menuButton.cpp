#include "menuButton.h"


menuButton::menuButton()
{
	setPosition(0, 0);
	mRect.h = BUTTON_HEIGHT;
	mRect.w = BUTTON_WIDTH;
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
	Font = TTF_OpenFont("stages/pixelart.ttf", 72);
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

	SDL_Surface* surface = TTF_RenderText_Solid(Font, buttonText.c_str(), Stagecolor);
	if (surface == NULL)
	{
		printf("Failed to create surface! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	ttfTexture = SDL_CreateTextureFromSurface(Renderer, surface);

	SDL_FreeSurface(surface);

	return success;
}

bool menuButton::render(SDL_Renderer* Renderer)
{
	bool success = true;
	SDL_SetRenderDrawColor(Renderer, 0x8F, 0x99, 0xAA, 0xFF);
	SDL_RenderDrawRect(Renderer, &mRect);
	SDL_RenderFillRect(Renderer, &mRect);

	if (!SDL_RenderCopyEx(Renderer, ttfTexture, 0, &mRect, 0, 0, SDL_FLIP_NONE))
	{
		printf("failed to render button! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	return success;
}





//==============================================================================================//

//newStageButtonFunctions
/*
newStageButton::newStageButton()
{
	setPosition(300, 0);
	mRect.h = BUTTON_HEIGHT;
	mRect.w = BUTTON_WIDTH;
}

std::string newStageButton::getFileName()
{

	extern char *text;
	extern char *composition;
	extern Sint32 cursor;
	extern Sint32 selection_len;
	SDL_bool done = SDL_FALSE;

	SDL_StartTextInput();
	while (!done) {
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				/* Quit */
		//		done = SDL_TRUE;
	//			break;
		//	case SDL_TEXTINPUT:
				/* Add new text onto the end of our text */
	//			strcat(text, event.text.text);
		//		break;
	//		case SDL_TEXTEDITING:
				/*
				Update the composition text.
				Update the cursor position.
				Update the selection length (if any).
				*/
		//		composition = event.edit.text;
		//		cursor = event.edit.start;
		//		selection_len = event.edit.length;
		//		break;
//			}
//		}
//	}
//	return composition;
//}
