#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#pragma comment(lib, "Ws2_32.lib")

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/sdl_mixer.h>
#pragma comment (lib,"SDL2_mixer.lib")
#pragma comment (lib,"SDL2.lib")
#pragma comment (lib,"SDL2main.lib")
#pragma comment (lib,"SDL2_image.lib")


extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern unsigned short yyyn[50];
extern SDL_Surface * tet;
extern SDL_Texture * scot;

extern struct tm *t;


SDL_Texture *loadTexture(const char *file);
SDL_Texture *loadTex(SDL_Renderer* renderer, const char *file);
SDL_Texture *loadTextureColor(const char *file, unsigned int rgba);
SDL_Texture *loadTexColor(SDL_Renderer* renderer, const char *file, unsigned int rgba);
void stretchTextureEx(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Texture *texture,
	float angle, SDL_RendererFlip flip);
void stTE(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Texture *texture,
	float angle, int w1, int h1, SDL_RendererFlip flip);
void stretchTextureExSprite(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Texture *texture,
	float angle, int w1, int h1, int step, SDL_RendererFlip flip);
void drawTexture(SDL_Renderer *renderer, int x, int y, SDL_Texture *texture);
void stretchTexture(SDL_Renderer *renderer, int x, int y, int w, int h, SDL_Texture *texture);
int mouxbut(int x, int y, int w, int h, int moousex, int moousey); //x,y->w,h;
int mouxbut2(int x, int y, int x1, int y1, int moousex, int moousey); //x,y->x1,y1
int inout(int x, int y, int w, int h, int x1, int y1, int w1, int h1);
int inout2(int x, int y, int xw, int yh, int x1, int y1, int xw1, int yh1);
//////////////////////////////////////////////////////////////////////////////////////////////////////////SDL1
void DrawPixel(SDL_Surface *screen, int x, int y, unsigned int rgba);
void DrawSprite(SDL_Surface *screen, int x, int y, SDL_Surface *surface, int w, int h, int step);
void DrawSurface(SDL_Surface *dst, int x, int y, SDL_Surface *src);
