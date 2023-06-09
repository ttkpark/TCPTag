#include "Header.h"
#include "SDL_Print12864.h"
#include "TCPConnect.h"

uint8_t F6x8[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ,   // sp
	0x00, 0x00, 0x00, 0x2f, 0x00, 0x00 ,   // !
	0x00, 0x00, 0x07, 0x00, 0x07, 0x00 ,   // "
	0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14 ,   // #
	0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12 ,   // $
	0x00, 0x62, 0x64, 0x08, 0x13, 0x23 ,   // %
	0x00, 0x36, 0x49, 0x55, 0x22, 0x50 ,   // &
	0x00, 0x00, 0x05, 0x03, 0x00, 0x00 ,   // '
	0x00, 0x00, 0x1c, 0x22, 0x41, 0x00 ,   // (
	0x00, 0x00, 0x41, 0x22, 0x1c, 0x00 ,   // )
	0x00, 0x14, 0x08, 0x3E, 0x08, 0x14 ,   // *
	0x00, 0x08, 0x08, 0x3E, 0x08, 0x08 ,   // +
	0x00, 0x00, 0x00, 0xA0, 0x60, 0x00 ,   // ,
	0x00, 0x08, 0x08, 0x08, 0x08, 0x08 ,   // -
	0x00, 0x00, 0x60, 0x60, 0x00, 0x00 ,   // .
	0x00, 0x20, 0x10, 0x08, 0x04, 0x02 ,   // /
	0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E ,   // 0
	0x00, 0x00, 0x42, 0x7F, 0x40, 0x00 ,   // 1
	0x00, 0x42, 0x61, 0x51, 0x49, 0x46 ,   // 2
	0x00, 0x21, 0x41, 0x45, 0x4B, 0x31 ,   // 3
	0x00, 0x18, 0x14, 0x12, 0x7F, 0x10 ,   // 4
	0x00, 0x27, 0x45, 0x45, 0x45, 0x39 ,   // 5
	0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30 ,   // 6
	0x00, 0x01, 0x71, 0x09, 0x05, 0x03 ,   // 7
	0x00, 0x36, 0x49, 0x49, 0x49, 0x36 ,   // 8
	0x00, 0x06, 0x49, 0x49, 0x29, 0x1E ,   // 9
	0x00, 0x00, 0x36, 0x36, 0x00, 0x00 ,   // :
	0x00, 0x00, 0x56, 0x36, 0x00, 0x00 ,   // ;
	0x00, 0x08, 0x14, 0x22, 0x41, 0x00 ,   // <
	0x00, 0x14, 0x14, 0x14, 0x14, 0x14 ,   // =
	0x00, 0x00, 0x41, 0x22, 0x14, 0x08 ,   // >
	0x00, 0x02, 0x01, 0x51, 0x09, 0x06 ,   // ?
	0x00, 0x32, 0x49, 0x59, 0x51, 0x3E ,   // @
	0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C ,   // A
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x36 ,   // B
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x22 ,   // C
	0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C ,   // D
	0x00, 0x7F, 0x49, 0x49, 0x49, 0x41 ,   // E
	0x00, 0x7F, 0x09, 0x09, 0x09, 0x01 ,   // F
	0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A ,   // G
	0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F ,   // H
	0x00, 0x00, 0x41, 0x7F, 0x41, 0x00 ,   // I
	0x00, 0x20, 0x40, 0x41, 0x3F, 0x01 ,   // J
	0x00, 0x7F, 0x08, 0x14, 0x22, 0x41 ,   // K
	0x00, 0x7F, 0x40, 0x40, 0x40, 0x40 ,   // L
	0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F ,   // M
	0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F ,   // N
	0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E ,   // O
	0x00, 0x7F, 0x09, 0x09, 0x09, 0x06 ,   // P
	0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E ,   // Q
	0x00, 0x7F, 0x09, 0x19, 0x29, 0x46 ,   // R
	0x00, 0x46, 0x49, 0x49, 0x49, 0x31 ,   // S
	0x00, 0x01, 0x01, 0x7F, 0x01, 0x01 ,   // T
	0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F ,   // U
	0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F ,   // V
	0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F ,   // W
	0x00, 0x63, 0x14, 0x08, 0x14, 0x63 ,   // X
	0x00, 0x07, 0x08, 0x70, 0x08, 0x07 ,   // Y
	0x00, 0x61, 0x51, 0x49, 0x45, 0x43 ,   // Z
	0x00, 0x00, 0x7F, 0x41, 0x41, 0x00 ,   // [ 91
	0x00, 0x02, 0x04, 0x08, 0x10, 0x20 ,   // \92
	0x00, 0x00, 0x41, 0x41, 0x7F, 0x00 ,   // ]
	0x00, 0x04, 0x02, 0x01, 0x02, 0x04 ,   // ^
	0x00, 0x40, 0x40, 0x40, 0x40, 0x40 ,   // _
	0x00, 0x00, 0x01, 0x02, 0x04, 0x00 ,   // '
	0x00, 0x20, 0x54, 0x54, 0x54, 0x78 ,   // a
	0x00, 0x7F, 0x48, 0x44, 0x44, 0x38 ,   // b
	0x00, 0x38, 0x44, 0x44, 0x44, 0x20 ,   // c
	0x00, 0x38, 0x44, 0x44, 0x48, 0x7F ,   // d
	0x00, 0x38, 0x54, 0x54, 0x54, 0x18 ,   // e
	0x00, 0x08, 0x7E, 0x09, 0x01, 0x02 ,   // f
	0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C ,   // g
	0x00, 0x7F, 0x08, 0x04, 0x04, 0x78 ,   // h
	0x00, 0x00, 0x44, 0x7D, 0x40, 0x00 ,   // i
	0x00, 0x40, 0x80, 0x84, 0x7D, 0x00 ,   // j
	0x00, 0x7F, 0x10, 0x28, 0x44, 0x00 ,   // k
	0x00, 0x00, 0x41, 0x7F, 0x40, 0x00 ,   // l
	0x00, 0x7C, 0x04, 0x18, 0x04, 0x78 ,   // m
	0x00, 0x7C, 0x08, 0x04, 0x04, 0x78 ,   // n
	0x00, 0x38, 0x44, 0x44, 0x44, 0x38 ,   // o
	0x00, 0xFC, 0x24, 0x24, 0x24, 0x18 ,   // p
	0x00, 0x18, 0x24, 0x24, 0x18, 0xFC ,   // q
	0x00, 0x7C, 0x08, 0x04, 0x04, 0x08 ,   // r
	0x00, 0x48, 0x54, 0x54, 0x54, 0x20 ,   // s
	0x00, 0x04, 0x3F, 0x44, 0x40, 0x20 ,   // t
	0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C ,   // u
	0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C ,   // v
	0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C ,   // w
	0x00, 0x44, 0x28, 0x10, 0x28, 0x44 ,   // x
	0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C ,   // y
	0x00, 0x44, 0x64, 0x54, 0x4C, 0x44 ,   // z
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14     // horiz lines
};
Print12864::Print12864()
{
	w = 128;
	h = 128;
	zoom = 0;
}

Print12864::~Print12864()
{
	if(surface!=nullptr)SDL_FreeSurface(surface);
}
void Print12864::Draw_dot(int x, int y, char OnOff) {
	uint8_t *byte = (uint8_t *)PrintPixel+ (y/8) * 128 + x;
	if (OnOff)*byte |= 1 << (y & 7);
	else *byte &= ~(1 << (y & 7));
}
void Print12864::Window_Create(char* title,int _x, int _y, int _w=128, int _h=64, double _zoom=1) {
	if (128 * _zoom > (double)_w)_zoom = _w/128;
	if (64 * _zoom > (double)_h)_zoom = _h/64;
	w = _w; h = _h; zoom = _zoom;

	window = SDL_CreateWindow(title, _x, _y, _w, _h, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);

	surface = SDL_CreateRGBSurfaceFrom(SurfacePrintPixel,128, 64, 32, 512, 0, 0, 0, 0);
	SDL_SetRenderDrawColor(renderer, 64, 64, 64,0);
	SDL_RenderClear(renderer);
}

void Print12864::ClearBuffer(char OnOff) {
	for (int i = 0; i < 1024; i++)
		PrintPixel[i] = (OnOff ? 0xFF : 0x00);
}
void Print12864::PrintBuffer() {
	if(RendererTexture != nullptr)SDL_DestroyTexture(RendererTexture);
	for (unsigned int x = 0; x < 128; x++)for (unsigned int y = 0; y < 64; y++)
		SurfacePrintPixel[x+y*128] = ((*((uint8_t *)PrintPixel + (y / 8) * 128 + x))&(1<< (y & 7)) ? 0xFFFFFFFF : 0x00000000);
	RendererTexture = SDL_CreateTextureFromSurface(renderer, surface);

	stretchTexture(renderer, (w-128 * zoom)/2, (h-64 * zoom)/2, 128 * zoom, 64 * zoom,RendererTexture);

}

uint8_t flagBuffer[8]		 = { 0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF };
uint8_t flagBuffer_mirror[8] = { 0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF };
void Print12864::Draw_Area(int _x, int _y, int _w, int _h, char OnOff) {
	if (_x >= 128 || _x <= -_w)return;
	if (_y >= 64 || _y <= -_h)return;
	if (_x < 0) { _w += _x; _x = 0; }
	if (_y < 0) { _h += _y; _y = 0; }
	if (_x + _w > 128)_w = 128 - _x;
	if (_y + _h > 64)_h = 64 - _y;

	uint8_t byteflag = OnOff ? 0xFF : 0x00;
	int remained_h = _h;
	int image_ypage = 0;
	//step 1:head
	int a = 7 - _y % 8 + 1;
	if (a != 8) {
		for (int i = 0; i < _w; i++) {
			PrintPixel[(_y / 8) * 128 + i + _x] = PrintPixel[(_y / 8) * 128 + i + _x] & (flagBuffer[_y % 8 - 1]) | (uint8_t)(byteflag << ((_y % 8)));
		}
		remained_h -= a;
	}

	//step 2:body
	int remained_bodys = remained_h / 8;
	if (remained_bodys != 0) {
		if (a != 8) {
			for (int j = 0; j < remained_bodys; j++) {
				for (int i = 0; i < _w; i++) {
					PrintPixel[(_y / 8 + j + 1) * 128 + _x + i] = byteflag;
				}
				image_ypage++;
				remained_h -= 8;
			}
		}
		else {
			for (int j = 0; j < remained_bodys; j++) {
				for (int i = 0; i < _w; i++) {
					PrintPixel[(_y / 8 + j) * 128 + _x + i] = byteflag;
				}
				image_ypage++;
				remained_h -= 8;
			}
		}
	}

	//step 3:tail
	int tail_a = remained_h;
	if (remained_h != 0) {
		for (int i = 0; i < _w; i++) {
			PrintPixel[((_y + _h - remained_h) / 8) * 128 + i + _x] = PrintPixel[((_y + _h - remained_h) / 8) * 128 + i + _x] & (flagBuffer_mirror[7 - tail_a]) | (uint8_t)(byteflag >> 8 - tail_a);
		}
	}

}
void Print12864::Draw_Image(int _x, int _y, int _imagew, int _imageh, uint8_t *image) {
	if (_x >= 128 || _x <= -_imagew)return;
	if (_y >= 64 || _y <= -_imageh)return;
	if (_x < 0) { _imagew += _x; image -= _x; _x = 0; }
	if (_y < 0) { _imageh += _y; _y = 0; }
	if (_x + _imagew > 128)_imagew = 128 - _x;
	if (_y + _imageh > 64)_imageh = 64 - _y;
	int remained_h = _imageh;
	int image_ypage = 0;
	//step 1:head
	int a = 7 - _y % 8 + 1;
	if (a != 8) {
		for (int i = 0; i < _imagew; i++) {
			PrintPixel[(_y / 8) * 128 + i + _x] = PrintPixel[(_y / 8) * 128 + i + _x] & (flagBuffer[_y % 8 - 1]) | (uint8_t)(image[i] << ((_y % 8)));
		}
		remained_h -= a;
	}

	//step 2:body
	int remained_bodys = remained_h / 8;
	if (remained_bodys != 0) {
		if (a != 8) {
			for (int j = 0; j < remained_bodys; j++) {
				for (int i = 0; i < _imagew; i++) {
					PrintPixel[(_y / 8 + j + 1) * 128 + _x + i] = image[image_ypage * _imagew + i] & (flagBuffer[_y % 8 - 1]) | image[image_ypage * _imagew + i + _imagew] & (flagBuffer_mirror[a - 1]);
				}
				image_ypage++;
				remained_h -= 8;
			}
		}
		else {
			for (int j = 0; j < remained_bodys; j++) {
				for (int i = 0; i < _imagew; i++) {
					PrintPixel[(_y / 8 + j) * 128 + _x + i] = image[image_ypage * _imagew + i];
				}
				image_ypage++;
				remained_h -= 8;
			}
		}
	}

	//step 3:tail
	int tail_a = remained_h;
	if (remained_h != 0) {
		for (int i = 0; i < _imagew; i++) {
			PrintPixel[((_y + _imageh - remained_h) / 8) * 128 + i + _x] = PrintPixel[((_y + _imageh - remained_h) / 8) * 128 + i + _x] & (flagBuffer_mirror[7 - tail_a]) | (uint8_t)(image[(_imageh / 8 - 1)*_imagew + i] >> 8 - tail_a);
		}
	}

}
void Print12864::Draw_6x8Char(int _x, int _y, char ch) {
	Draw_Image(_x, _y, 6, 8, F6x8 + 6*(ch-32));
}
void Print12864::Draw_6x8String(int _x, int _y, char *str) {
	while (*str) {
		Draw_6x8Char(_x, _y, *str);
		_x += 6, str++;
	}

}

void Print12864::Func_BufferFlip(uint8_t *image, int image_size) {
	uint8_t byte;
	for (int i = 0; i < image_size; i++) {
		byte = image[i];
		image[i] =
			(byte&(1 << 7)) >> 7 | (byte&(1 << 6)) >> 5 | (byte&(1 << 5)) >> 3 | (byte&(1 << 4)) >> 1 |
			(byte&(1 << 3)) << 1 | (byte&(1 << 2)) << 3 | (byte&(1 << 1)) << 5 | (byte&1) << 7 ;
	}
}