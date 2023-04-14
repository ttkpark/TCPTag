#pragma once

void Wait(DWORD dwMillisecond);
class Rect {
public:
	int x, y, w, h;
	Rect(int _x, int _y, int _w, int _h);
	void Printblock(int cx, int cy);
	Rect operator* (int i);
};
class Vector
{
public:
	float x, y, dx, dy;
};
class TCPTag {
public:
	TCPTag();
	TCPTag operator= (TCPTag oth);
	float x, y; const int w = 8, h = 8;
	float dx, dy, maxdx = 1, maxdy = 1;
	int IsTaged(TCPTag oth);
	int IsCrashed(Rect *blocks, int len);
	void Process();
	TCPTag operator= (Vector i);
}My, you;
