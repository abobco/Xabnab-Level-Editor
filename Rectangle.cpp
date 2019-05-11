#include "Rectangle.h"

Rectangle::Rectangle() {
	rect.x = position.x = 0;
	rect.y = position.y = 0;
	rect.w = dimensions.x = 1;
	rect.h = dimensions.y = 1;

	color.a = 0;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	angle = 0;

}
Rectangle::Rectangle(int x, int y) {
	*this =Rectangle();
	setPosition(x, y);
}
Rectangle::Rectangle(int x, int y, int w, int h) {
	*this = Rectangle(x, y);
	setDimensions(w, h);
}
Rectangle::Rectangle(int x, int y, int w, int h, float ang) {
	*this = Rectangle(x, y, w, h);
	angle = ang;
}
Rectangle::Rectangle(int x, int y, int w, int h, int r, int g, int b) {
	*this = Rectangle(x, y, w, h);
	setColor(r, g, b);
}

void Rectangle::setColor(int r, int g, int b) {
	color.a = 0;
	color.r = r;
	color.g = g;
	color.b = b;
}

void Rectangle::setColor(int r, int g, int b, int a)
{
	color.a = a;
	color.r = r;
	color.g = g;
	color.b = b;
}
void Rectangle::setAngle(float ang) {
	angle = ang;
}
void Rectangle::setPosition(int x, int y) {
	rect.x = position.x = x;
	rect.y = position.y = y;
	
}
void Rectangle::setDimensions(int w, int h) {
	rect.w = dimensions.x = w;
	rect.h = dimensions.y = h;
}

void Rectangle::render(SDL_Renderer* Renderer)
{
	SDL_SetRenderDrawColor(Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(Renderer, &rect);
}