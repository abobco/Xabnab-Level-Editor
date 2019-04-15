#include "LButton.h"

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
	//Check collision of mouse and button
		//Get mouse position
		int x, y;
		int oldX, oldY;
		SDL_GetMouseState(&x, &y);
		SDL_GetRelativeMouseState(&oldX, &oldY);

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

		//Mouse is outside button
		if (!inside & !mouseDrag)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//BUTTON EVENT CODE
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				if (mouseDrag == true)
				{
					mCurrentSprite = BUTTON_SPRITE_DRAG;
					setPosition(x - relX, y- relY);
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				mouseDrag = true;
				relX = x - mPosition.x;
				relY = y - mPosition.y;
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				mouseDrag = false;
				break;
			}
		}
	}
}

SDL_Point* LButton::getPos()
{
	return &mPosition;
}