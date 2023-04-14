#include "Header.h"

SDL_Window* window;
SDL_Renderer* renderer;

unsigned short yyyn[50];
SDL_Surface * tet;
SDL_Texture * scot;

struct tm *t;

SDL_Texture *loadTexture(const char *file) {
	SDL_Surface *surface;
	SDL_Texture *texture;
	surface = IMG_Load(file);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
SDL_Texture *loadTex(SDL_Renderer* renderer, const char *file) {
	SDL_Surface *surface;
	SDL_Texture *texture;
	surface = IMG_Load(file);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
SDL_Texture *loadTextureColor(const char *file, unsigned int rgba) {
	SDL_Surface *surface;
	SDL_Texture *texture;
	surface = IMG_Load(file);
	SDL_SetColorKey(surface, SDL_TRUE, rgba);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
SDL_Texture *loadTexColor(SDL_Renderer* renderer, const char *file, unsigned int rgba) {
	SDL_Surface *surface;
	SDL_Texture *texture;
	surface = IMG_Load(file);
	SDL_SetColorKey(surface, SDL_TRUE, rgba);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void stretchTextureEx(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Texture *texture,
	float angle, SDL_RendererFlip flip) {
	SDL_Rect src, dst;
	SDL_Point center;

	src.x = src.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;

	center.x = w / 2;
	center.y = h / 2;

	SDL_RenderCopyEx(renderer, texture, &src, &dst, angle, &center, flip);
}
void stTE(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Texture *texture,
	float angle, int w1, int h1, SDL_RendererFlip flip) {
	SDL_Rect src, dst;
	SDL_Point center;

	src.x = src.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;

	center.x = w1;
	center.y = h1;

	SDL_RenderCopyEx(renderer, texture, &src, &dst, angle, &center, flip);
}
void stretchTextureExSprite(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Texture *texture,
	float angle, int w1, int h1, int step, SDL_RendererFlip flip) {
	SDL_Rect src, dst;
	SDL_Point center;

	src.x = src.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	src.x = (step % w1) * src.w / w1;
	src.y = (step / w1) * src.h / h1;
	src.w = src.w / w1;
	src.h = src.h / h1;

	center.x = w / 2;
	center.y = h / 2;

	SDL_RenderCopyEx(renderer, texture, &src, &dst, angle, &center, flip);
}
void drawTexture(SDL_Renderer *renderer, int x, int y, SDL_Texture *texture) {
	SDL_Rect src, dst;
	src.x = src.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;
	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void stretchTexture(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Texture *texture) {
	SDL_Rect src, dst;
	src.x = src.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, texture, &src, &dst);
}
int mouxbut(int x, int y, int w, int h, int moousex, int moousey) {          //x,y->w,h
	if (moousex <= x + w && moousex >= x && moousey <= y + h && moousey >= y) {
		return 1;
	}
	else {
		return 0;
	}
}

int mouxbut2(int x, int y, int x1, int y1, int moousex, int moousey) {       //x,y->x1,y1
	if (moousex <= x1 && moousex >= x && moousey <= y1 && moousey >= y) {
		return 1;
	}
	else {
		return 0;
	}
}
int inout(int x, int y, int w, int h, int x1, int y1, int w1, int h1) {
	if ((((x1 <= x && x <= x1 + w1) || (x1 <= x + w && x + w <= x1 + w1)) || ((x <= x1 && x1 <= x + w) || (x <= x1 + w1 && x1 + w1 <= x + w))) &&
		(((y1 <= y && y <= y1 + h1) || (y1 <= y + h && y + h <= y1 + h1)) || ((y <= y1 && y1 <= y + h) || (y <= y1 + h1 && y1 + h1 <= y + h)))) {
		return 1;
	}
	else {
		return 0;
	}
}

int inout2(int x, int y, int xw, int yh, int x1, int y1, int xw1, int yh1) {
	if ((((x1 <= x && x <= xw1) || (x1 <= xw && xw <= xw1)) || ((x <= x1 && x1 <= xw) || (x <= xw1 && xw1 <= xw))) &&
		(((y1 <= y && y <= yh1) || (y1 <= yh && yh <= yh1)) || ((y <= y1 && y1 <= yh) || (y <= yh1 && yh1 <= yh)))) {
		return 1;
	}
	else {
		return 0;
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////SDL1
void DrawPixel(SDL_Surface *screen, int x, int y, unsigned int rgba) {
	*((unsigned int*)screen->pixels + (screen->w * y) + x) = rgba;
}
void DrawSprite(SDL_Surface *screen, int x, int y, SDL_Surface *surface, int w, int h, int step) {
	SDL_Rect rectDst, rectSrc;
	rectDst.x = x;
	rectDst.y = y;
	rectSrc.x = (step % w) * surface->w / w;
	rectSrc.y = (step / w) * surface->h / h;
	rectSrc.w = surface->w / w;
	rectSrc.h = surface->h / h;
	SDL_BlitSurface(surface, &rectSrc, screen, &rectDst);
}
void DrawSurface(SDL_Surface *dst, int x, int y, SDL_Surface *src) {
	SDL_Rect rectDst;
	rectDst.x = x;
	rectDst.y = y;
	SDL_BlitSurface(src, NULL, dst, &rectDst);
}
