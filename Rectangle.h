#pragma once
#include <SDL.h>

#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__
class Rectangle {
private:
	SDL_Rect rect;
	SDL_Point position;
	SDL_Point dimensions;
	SDL_Color color;
	//SDL_Renderer* Renderer = NULL;
	float angle;
	

public:
	Rectangle();
	//Rectangle(SDL_Renderer* oRenderer);
	Rectangle(int x, int y);
	Rectangle(int x, int y, int w, int h);
	Rectangle(int x, int y, int w, int h, float ang);
	Rectangle(int x, int y, int w, int h, int r, int g, int b);
	
	void setColor(int r, int g, int b);
	void setColor(int r, int g, int b, int a);
	void setAngle(float ang);
	void setPosition(int x, int y);
	void setDimensions(int w, int h);
	
	SDL_Rect getRect() { return rect; }
	SDL_Point getPosition() { return position; }
	SDL_Color getColor() { return color; }
	float getAngle() { return angle; }
	
	SDL_Point getDimensions() { return dimensions; };

	void render(SDL_Renderer* Renderer);
};
#endif