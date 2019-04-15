#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#ifndef __LTEXTURE_H__
#define __LTEXTURE_H__

class LTexture
{
public:
	//Initializes variables
	LTexture();

	//Renderer pass Constructor
	LTexture(SDL_Renderer *gRenderer);

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer *mRenderer);

#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	SDL_Texture *getTexture() { return mTexture; };

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	void* mPixels;
	int mPitch;
	//Image dimensions
	int mWidth;
	int mHeight;

	SDL_Renderer* gRendptr;
};

#endif