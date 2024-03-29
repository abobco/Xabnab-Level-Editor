#include "KeyboardHandler.h"

KeyboardHandler::KeyboardHandler(SDL_Renderer* Renderer, int size)
{
	inputText = "stage" + std::to_string(size + 1);
	//Enable text input 
	textColor.a = 0;
	textColor.r = 160;
	textColor.b = 180;
	textColor.g = 180;
	textDisplay = menuButton(WINDOW_WIDTH / 2 + 155, 80, inputText);
	textDisplay.loadText(Renderer, textColor);
	SDL_StartTextInput();

	kRenderer = Renderer;
}

bool KeyboardHandler::handleInput(SDL_Event* e)
{
	bool renderText = false;
	//Handle events on queue
		if (e->type == SDL_KEYDOWN)
		{
					//Handle backspace
			if (e->key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
			{
				//lop off character
				inputText.pop_back();
				renderText = true;
			}
			//Special text input event
			else if (e->key.keysym.sym == SDLK_RETURN && inputText.length() > 0)
				done = true;
					
		}
		else if (e->type == SDL_TEXTINPUT)
		{
			if (firstinput)
			{
				inputText = e->text.text;
				firstinput = false;
				renderText = true;
			}
			else
			{
				//Append character
				inputText += e->text.text;
				renderText = true;
			}

		}
	
	if (renderText)
	{
		textDisplay.changeText(inputText);
		textDisplay.loadText(kRenderer,textColor);
	}
	return renderText;
}