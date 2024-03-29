#include "LButton.h"

LButton::LButton()
{
	//Set top left corner point 
	mPosition.x = 0;
	mPosition.y = 0;
	
	glowRect.setColor(240, 240, 40);
	//set clickboxes for edges for box resizing
	setEdges();

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

LButton::LButton(int x, int y)
{
	//Set top left corner point 
	mPosition.x = x;
	mPosition.y = y;

	mRect.x = mPosition.x;
	mRect.y = mPosition.y;
	mRect.w = BUTTON_WIDTH;
	mRect.h = BUTTON_HEIGHT;
	glowRect.setColor(240, 240, 40);
	setEdges();

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

LButton::LButton(SDL_Rect* rect)
{
	mRect.x = mPosition.x = rect->x;
	mRect.y = mPosition.y = rect->y;

	BUTTON_WIDTH = mRect.w = rect->w;
	BUTTON_HEIGHT = mRect.h = rect->h;
	glowRect.setColor(240, 240, 40);
	setEdges();

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
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_KEYDOWN)
	{
	//Check collision of mouse and button
		//Get mouse position
		int x, y;
		int oldX, oldY;
		SDL_GetMouseState(&x, &y);
		SDL_GetRelativeMouseState(&oldX, &oldY);

		if (resizeDrag)
		{
			HandleResize(e, ResizeState);
		}

		else
		{
			ResizeState = checkResize(x, y);
			if (ResizeState != 0 && e->type == SDL_MOUSEBUTTONDOWN)
			{
				resizeDrag = true;
				relX = x - mPosition.x;
				relY = y - mPosition.y;
				stableEdgeY = mPosition.y + BUTTON_HEIGHT;
				stableEdgeX = mPosition.x + BUTTON_WIDTH;
				return;
			}
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
			if (!inside && !mouseDrag)
			{
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
				mouseHover = false;
			}
			//Mouse is inside button
			else
			{
				mouseHover = true;
				//BUTTON EVENT CODE
				switch (e->type)
				{
				case SDL_MOUSEMOTION:
					mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
					
					if (mouseDrag == true)
					{
						mCurrentSprite = BUTTON_SPRITE_DRAG;
						setPosition(x - relX, y - relY);
						setEdges();
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
}

SDL_Point* LButton::getPos()
{
	return &mPosition;
}

void LButton::setEdges()
{
	//overall box rectangle
	mRect.x = mPosition.x;
	mRect.y = mPosition.y;
	mRect.w = BUTTON_WIDTH;
	mRect.h = BUTTON_HEIGHT;

	glowRect.setDimensions(BUTTON_WIDTH + 10, BUTTON_HEIGHT + 10);
	glowRect.setPosition(mPosition.x - 5, mPosition.y - 5);

	//top & bottom
	for (int i = 0; i < 2; i++)
	{
		edgeBoxes[i].x = mPosition.x + BUTTON_WIDTH/2 - 10;
		edgeBoxes[i].y = mPosition.y - 10 + (i * BUTTON_HEIGHT);
		edgeBoxes[i].w = 20;
		edgeBoxes[i].h = 20;
	}
	//sides
	for (int i = 2; i < 4; i++)
	{
		edgeBoxes[i].x = mPosition.x - 10 + ((i-2) * BUTTON_WIDTH);
		edgeBoxes[i].y = mPosition.y + BUTTON_HEIGHT/2 - 10;
		edgeBoxes[i].w = 20;
		edgeBoxes[i].h = 20;
	}

	//corners
	for (int i = 0; i < 4; i++)
	{
		cornerBoxes[i].w = cornerBoxes[i].h = 20;
	}
	for (int i = 0; i <2; i++)
	{
		cornerBoxes[i].x = mPosition.x - 10;
		cornerBoxes[i].y = mPosition.y - 10 + BUTTON_HEIGHT * i;
	}
	for (int i = 2; i < 4; i++)
	{
		cornerBoxes[i].x = mPosition.x - 10 + BUTTON_WIDTH;
		cornerBoxes[i].y = mPosition.y - 10 + BUTTON_HEIGHT * (i - 2);
	}
}

int LButton::checkResize(int x, int y)
{
	SDL_Point mousePoint;
	mousePoint.x = x;
	mousePoint.y = y;
	for (int i = 0; i < 4; i++)
	{
		if (SDL_PointInRect(&mousePoint, &edgeBoxes[i]))
		{
			switch (i)
			{
			case 0:
				return TOP_RESIZE;
				break;
			case 1:
				return BOT_RESIZE;
				break;
			case 2:
				return LEFT_RESIZE;
				break;
			case 3:
				return RIGHT_RESIZE;
				break;
			}
		}
		if (SDL_PointInRect(&mousePoint, &cornerBoxes[i]))
		{
			switch (i)
			{
			case 0:
				return TLC_RESIZE;
				break;
			case 1:
				return BLC_RESIZE;
				break;
			case 2:
				return TRC_RESIZE;
				break;
			case 3:
				return BRC_RESIZE;
				break;
			}
		}

	}
	return NO_RESIZE;
}

void LButton::HandleResize(SDL_Event* e, int ResizeState)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
    switch (e->type)		
	{
	case SDL_MOUSEMOTION :
		if (resizeDrag == true)
		{
			switch (ResizeState)
			{
			case TOP_RESIZE:
				mRect.h = stableEdgeY -y;
				BUTTON_HEIGHT = mRect.h;
				mPosition.y = mRect.y = y;
				break;
			case BOT_RESIZE:
				mRect.h = y - mPosition.y;
				BUTTON_HEIGHT = mRect.h;
				break;
			case LEFT_RESIZE:
				mRect.w = stableEdgeX - x;
				BUTTON_WIDTH = mRect.w;
				mPosition.x = mRect.x = x;
				break;
			case RIGHT_RESIZE:
				mRect.w = x - mPosition.x;
				BUTTON_WIDTH = mRect.w;
				break;
			case TLC_RESIZE:
				mRect.h = stableEdgeY - y;
				BUTTON_HEIGHT = mRect.h;
				mPosition.y = mRect.y = y;
				mRect.w = stableEdgeX - x;
				BUTTON_WIDTH = mRect.w;
				mPosition.x = mRect.x = x;
				break;
			case BLC_RESIZE:
				mRect.h = y - mPosition.y;
				BUTTON_HEIGHT = mRect.h;
				mRect.w = stableEdgeX - x;
				BUTTON_WIDTH = mRect.w;
				mPosition.x = mRect.x = x;
				break;
			case TRC_RESIZE:
				mRect.h = stableEdgeY -y;
				BUTTON_HEIGHT = mRect.h;
				mPosition.y = mRect.y = y;
				mRect.w = x - mPosition.x;
				BUTTON_WIDTH = mRect.w;
				break;
			case BRC_RESIZE:
				mRect.h = y - mPosition.y;
				BUTTON_HEIGHT = mRect.h;
				mRect.w = x - mPosition.x;
				BUTTON_WIDTH = mRect.w;
				break;

			}
			setEdges();
		
		}
		break;

	case SDL_MOUSEBUTTONUP:
		mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
		resizeDrag = false;
		break;

	}

}