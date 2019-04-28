#include "menuButton.h"


menuButton::menuButton()
{
	setPosition(0, 0);
	mRect.h = BUTTON_HEIGHT;
	mRect.w = BUTTON_WIDTH;
}
menuButton::menuButton(int x, int y)
{
	setPosition(x, y);
	mRect.h = BUTTON_HEIGHT;
	mRect.w = BUTTON_WIDTH;
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

		if (!inside)
		{

		}
		else
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
