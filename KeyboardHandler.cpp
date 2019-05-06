#include "KeyboardHandler.h"

KeyboardHandler::KeyboardHandler(SDL_Renderer* Renderer, int size)
{
	//Enable text input 
	textDisplay = menuButton(WINDOW_WIDTH / 2 + 155, 80, "stage" + std::to_string(size +1));
	textDisplay.loadText(Renderer);
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
		textDisplay.loadText(kRenderer);
	}
	return renderText;
}