#include "menuButton.h"


//============================================================================================//
//	Constructors
//============================================================================================//
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

	displayRect = Rectangle(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, 10, 10, 10);

	DefaultColor = { 120,120,120,0 };
	HoldColor = { 100,190,100,0 };
	HoverColor = { 240,240,40,0 };

	hoverBox = Rectangle(x - 2, y - 2, BUTTON_WIDTH +4, BUTTON_HEIGHT +4);
}
menuButton::menuButton(Rectangle oRect, std::string text, SDL_Renderer* Renderer)
{
	mRect = oRect.getRect();
	setPosition(mRect.x, mRect.y);
	setDimensions(mRect.w, mRect.h);

	displayRect = oRect;

	DefaultColor = { 120,120,120,0 };
	HoldColor = { 100,190,100,0 };
	HoverColor = { 240,240,40,0 };

	hoverBox = Rectangle(mPosition.x - 2, mPosition.y - 2, BUTTON_WIDTH + 4, BUTTON_HEIGHT + 4);
	loadText(Renderer);

	textRect.w = mRect.w = oRect.getDimensions().x;
	textRect.h = mRect.h = oRect.getDimensions().y;
}

//============================================================================================//
//	setters
//============================================================================================//
void menuButton::setPosition(int x, int y)
{
	mPosition.x = mRect.x = x;
	mPosition.y = mRect.y = y;
}
void menuButton::setDimensions(int w, int h)
{
	mRect.w = BUTTON_WIDTH = w;
	mRect.h = BUTTON_HEIGHT = h;

	displayRect.setDimensions(w, h);
}

void menuButton::setDimensions(int w, int h, SDL_Renderer* Renderer)
{
	mRect.w = BUTTON_WIDTH = w;
	mRect.h = BUTTON_HEIGHT = h;

	displayRect.setDimensions(w, h);
	loadText(Renderer);
}

//============================================================================================//
//	event loop
//============================================================================================//
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
			hovering = true;
			//BUTTON EVENT CODE
			switch (e->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				displayRect.setColor(100, 190, 100);
				held = true;
				break;
			case SDL_MOUSEBUTTONUP:
				held = false;
				pressed = true;
				break;
			}
		}
		else hovering = false;
	}
}
bool menuButton::checkMouse(int x, int y)
{
	//Check if mouse is in button
	bool inside = true;

	//Mouse is left of the button
	if (x < mPosition.x)
	{
		held = inside = false;
	}
	//Mouse is right of the button
	else if (x > mPosition.x + displayRect.getDimensions().x)
	{
		held = inside = false;
	}
	//Mouse above the button
	else if (y < mPosition.y)
	{
		held = inside = false;
	}
	//Mouse below the button
	else if (y > mPosition.y + displayRect.getDimensions().y)
	{
		held = inside = false;
	}
	return inside;
}

//============================================================================================//
//	rendering
//============================================================================================//
bool menuButton::render(SDL_Renderer* Renderer)
{
	bool success = true;

	SDL_Point dimensions = displayRect.getDimensions();
	SDL_Rect oRect = { 0,0,dimensions.x,dimensions.y };
	SDL_Rect oTextRect = { 0,0,textRect.w,textRect.h };
	SDL_Rect oHoverRect = { 0,0,dimensions.x + 4, dimensions.y + 4 };
	SDL_Rect screen = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
	SDL_RenderSetViewport(Renderer, &hoverBox.getRect());
	if (hovering)
	{
		SDL_SetRenderDrawColor(Renderer, HoverColor.r, HoverColor.g, HoverColor.b, HoverColor.a);
		SDL_RenderFillRect(Renderer, &oHoverRect);
	}
	SDL_RenderSetViewport(Renderer, &displayRect.getRect());
	if (held)
	{
		SDL_Color tempcol = displayRect.getColor();
		SDL_SetRenderDrawColor(Renderer, tempcol.r, tempcol.b, tempcol.g, 0xFF);
	}
	else
		SDL_SetRenderDrawColor(Renderer, 0x8F, 0x99, 0xAA, 0xFF);

	SDL_RenderFillRect(Renderer, &oRect);
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(Renderer, &oRect);

	SDL_RenderCopyEx(Renderer, ttfTexture, 0, &oTextRect, 0, 0, SDL_FLIP_NONE);

	SDL_RenderSetViewport(Renderer, &screen);
	return success;
}
bool menuButton::render(SDL_Renderer* Renderer, SDL_Color buttonColor)
{
	bool success = true;
	SDL_SetRenderDrawColor(Renderer, buttonColor.r, buttonColor.b, buttonColor.g, buttonColor.a);
	SDL_RenderFillRect(Renderer, &mRect);
	SDL_SetRenderDrawColor(Renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(Renderer, &mRect);

	SDL_RenderCopyEx(Renderer, ttfTexture, 0, &textRect, 0, 0, SDL_FLIP_NONE);
	return success;
}

//============================================================================================//
//	font loading
//============================================================================================//
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
	textRect.x = displayRect.getPosition().x;
	textRect.y = displayRect.getPosition().y;
	textRect.w = textWidth;
	textRect.h = displayRect.getDimensions().y;

	mRect.w = textWidth;


	SDL_FreeSurface(surface);

	return success;
}

bool menuButton::loadText(SDL_Renderer* Renderer, SDL_Color stagecolor)\
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

	std::string txt;
	if (buttonText.size() > 6 && buttonText[0] == 's' && buttonText[1] == 't' && buttonText[2] == 'a' && buttonText[3] == 'g' && buttonText[4] == 'e' && buttonText[5] == 's' && buttonText[6] == '/')
	{
		for (int i = 7; i < int(buttonText.size()) - 4; i++)
		{
			txt += buttonText[i];
		}
	}
	else txt = buttonText;
	SDL_Surface* surface = TTF_RenderText_Solid(Font, txt.c_str(), stagecolor);
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


//============================================================================================//
//	newStageButton
//============================================================================================//
newStageButton::newStageButton()
{
	mRect.h = BUTTON_HEIGHT;
	mRect.w = BUTTON_WIDTH;
	setPosition(100, 150);
	buttonText = "NEW STAGE";
}


