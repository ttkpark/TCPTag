
#pragma once
//128x64 Display
class Print12864
{
	int w, h;double zoom;
public:
	SDL_Texture *RendererTexture;
	char PrintPixel[1024];
	uint32_t SurfacePrintPixel[8192];
	void Draw_dot(int x, int y, char OnOff);
	void PrintBuffer();
	void ClearBuffer(char OnOff);
	void Window_Create(char* title,int _x, int _y, int _w, int _h, double _zoom);
	void Draw_Image(int _x, int _y, int _imagew, int _imageh, uint8_t *image);
	void Draw_6x8Char(int _x, int _y, char ch);
	void Draw_6x8String(int _x, int _y, char *str);
	void Func_BufferFlip(uint8_t *image,int image_size);
	void Draw_Area(int _x, int _y, int _w, int _h, char OnOff);

	SDL_Surface *surface;

	Print12864();
	~Print12864();
};
