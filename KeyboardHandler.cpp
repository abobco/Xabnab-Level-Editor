#include "KeyboardHandler.h"

KeyboardHandler::KeyboardHandler(SDL_Renderer* Renderer)
{
	//Enable text input 
	textDisplay = menuButton(WINDOW_WIDTH / 2 + 155, 80, "input text");
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
					
		}
		else if (e->type == SDL_TEXTINPUT)
		{

			//Append character
			inputText += e->text.text;
			renderText = true;

		}
	
	if (renderText)
	{
		textDisplay.changeText(inputText);
		textDisplay.loadText(kRenderer);
	}
	return renderText;
}