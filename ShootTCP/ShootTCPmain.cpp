#include "Header.h"
#include "SDL_Print12864.h"
#include "TCPConnect.h"
#include "ShootTCPmain.h"
#define Wallsize 24
#undef main
SDL_Event event;
TCPConnect TCP;
Print12864 Print;
Rect Walls[] = { 
	Rect(0,0,32,1) * Wallsize,Rect(0,15,32,1) * Wallsize,Rect(0,1,1,14) * Wallsize,Rect(31,1,1,14) * Wallsize,
	Rect(2,2,1,7) * Wallsize,Rect(3,8,2,1) * Wallsize,Rect(4,2,5,1) * Wallsize,Rect(8,3,1,3) * Wallsize,
	Rect(6,4,1,10) * Wallsize,Rect(4,6,2,1) * Wallsize,Rect(7,8,2,1) * Wallsize,Rect(4,10,2,1) * Wallsize,
	Rect(2,10,1,4) * Wallsize,Rect(3,12,2,2) * Wallsize,Rect(10,2,1,4) * Wallsize,Rect(10,12,2,2) * Wallsize,
	Rect(8,10,1,4) * Wallsize,Rect(9,10,2,1) * Wallsize,Rect(12,3,1,2) * Wallsize,Rect(13,3,2,1) * Wallsize,
	Rect(16,2,1,4) * Wallsize,Rect(15,5,1,1) * Wallsize,Rect(17,4,1,1) * Wallsize,Rect(13,12,2,2) * Wallsize,
	Rect(18,2,2,1) * Wallsize,Rect(19,3,1,1) * Wallsize,Rect(19,4,3,1) * Wallsize,Rect(19,12,2,2) * Wallsize,
	Rect(12,10,9,1) * Wallsize,Rect(16,11,2,3) * Wallsize,Rect(21,6,1,1) * Wallsize,Rect(22,6,1,2) * Wallsize,
	Rect(22,8,2,1) * Wallsize,Rect(21,2,2,1) * Wallsize,Rect(23,2,1,3) * Wallsize,Rect(24,4,4,1) * Wallsize,
	Rect(25,2,5,1) * Wallsize,Rect(29,3,1,4) * Wallsize,Rect(27,6,2,1) * Wallsize,Rect(24,6,2,1) * Wallsize,
	Rect(22,10,2,3) * Wallsize,Rect(25,9,2,2) * Wallsize,Rect(28,8,2,3) * Wallsize,Rect(28,11,1,1) * Wallsize,
	Rect(25,12,1,2) * Wallsize,Rect(26,13,4,1) * Wallsize
};

struct SendRecvPacket {
	TCPTag Client;//TCPTag Client;
	struct {
		float x, y;
		char end = 0;
	}Server;
}Recv;
uint8_t black[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t Player[] = {
	0x3C,0x66,0xC3,0x81,0x81,0xC3,0x66,0X3C,
	0x3C,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x3C
};
uint8_t SelectArrow[] = {
	0xFF,0xFF,0x7E,0x7E,0x3C,0x3C,0x18,0x18,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
uint8_t NumberUpDown[] = {
	0x80,0xB0,0xBC,0xBF,0xBF,0xBC,0xB0,0x80,
	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
	0x01,0x0D,0x3D,0xFD,0xFD,0x3D,0x0D,0x01,

	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,

	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
uint8_t logo[356] = {
	0x00,0x00,0x00,0x00,0x78,0x48,0x48,0x4F,0x40,0x40,0x4F,0x48,0x48,0x78,0x00,0x7F,0x40,0x40,0x4F,0x48,0x48,0x48,0x48,0x78,0x00,0x7F,0x40,0x40,0x4C,0x4C,0x4C,0x40,0x40,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x20,0x90,0x48,0x00,0x3E,0x63,0x41,0x41,0x41,0x63,0x3E,0x01,0x02,0x04,0x05,0x05,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x08,0x08,0xf8,0x00,0x00,0x00,0x00,0xF8,0x08,0x08,0xC8,0x48,0x48,0x48,0x48,0x78,0x00,0xF8,0x08,0x08,0xF8,0x80,0x80,0x87,0x87,0x87,0x07,0x07,0x07,0x07,0x07,0x07,0x0F,0x0F,0x1E,0x1E,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x06,0x06,0x06,0x02,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0xE0,0x00,0x78,0x80,0x00,0x3E,0x7F,0x7F,0x7F,0x7F,0x7F,0x3E,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x0C,0x08,0x08,0x08,0x0C,0x07,0x08,0x12,0x14,0x25,0x29,0x02,0x00,0x70,0x50,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x30,0x08,0x05,0x02,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x19,0x33,0x33,0x33,0x33,0x1F,0x1F,0x00,0x00,0x00,0x00,0x00,0xE0,0xF9,0x3B,0x1B,0x1B,0x3B,0x72,0xFF,0xFF,0x06,0x0C,0x6C,0x5A,0xC2,0x04,0x04,0xC2,0x5A,0x64,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xC0,0x60,0x20,0x20,0x20,0x60,0xC0,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x50,0x70,0x80,0x00,0x00,0xF8,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF8,0x18,0x18,0x18,0x18,0xF8,0xF0,0x30,0x18,0x08,0x00,0x00,0xE0,0xF0,0x18,0x0C,0x0C,0x0C,0x18,0xF8,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
int main(int argc, char **argv) {
	FreeConsole();
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)return 0;
	const Uint8 *keystate;
	int quit = 0, count = 0;
	int mode = 0, premode = 0 , startarrow = 0;
	int mapview = 0;
	int client_arrow = 0, plusval = 0; uint8_t editval;
	DWORD timea = 0, ta = 0, tb = 0, tm = 0, times[10] = { 0, }, cycletime = 0, cyclecount = 0, FpsView = 0; float floatcycletime = 0, fps = 0, delay = 20;
	long buttonstate[7] = { 0,0,0,0,0,0,0 };
	char buttonpressed[6] = { 0,0,0,0,0,0 };
	char Str[60] = { 0, };
	in_addr my_IP = TCP.GetmyIP();
	in_addr you_IP = TCP.GetmyIP();
	SDL_Init(SDL_INIT_EVERYTHING);
	Print.Window_Create("TCP Tag Project",100, 100, 878, 621, 5);
	Print.Func_BufferFlip(logo, sizeof logo);
	while (!quit) {
		ta = GetTickCount();
		if(mode != premode)
			Print.ClearBuffer(0);
		premode = mode;
		keystate = SDL_GetKeyboardState(NULL);
		if (mode == 0) {
			if (startarrow > 2)startarrow = 2;
			if (startarrow < 0)startarrow = 0;
			Print.Draw_Image(20, 0, 89, 32, logo);
			Print.Draw_Image(28, 35, 8, 8, SelectArrow + 8 * (startarrow != 0));
			Print.Draw_Image(28, 44, 8, 8, SelectArrow + 8 * (startarrow != 1));
			Print.Draw_Image(28, 53, 8, 8, SelectArrow + 8 * (startarrow != 2));
			Print.Draw_6x8String(40, 35, "Server Mode");
			Print.Draw_6x8String(40, 44, "Client Mode");
			Print.Draw_6x8String(40, 53, "Exit game");
			if (buttonpressed[4]) { buttonpressed[4] = 0; mode += startarrow + 1; }
			if (buttonpressed[0]) { buttonpressed[0] = 0; startarrow--; }
			if (buttonpressed[1]) { buttonpressed[1] = 0; startarrow++; }
		}
		else if (mode == 1) {//server
			Print.ClearBuffer(0);
			Print.Draw_Image(20, 0, 89, 32, logo);
			Print.Draw_6x8String(20, 44, "Accepting....      ");
			my_IP = TCP.GetmyIP();
			int i = 0;
			while (!TCP.SocketServer(my_IP = TCP.GetmyIP(), 7355)) { if (i++ > 50)break; }
			if (i > 50) {TCP.SocketClose(); Print.Draw_6x8String(0, 44, "Accepting failed.    "); Wait(500); mode = 0;}else mode = 4;
		}
		else if (mode == 4) {//server
			Print.ClearBuffer(0);
			Print.Draw_Image(20, 0, 89, 32, logo);
			sprintf_s(Str, "%d.%d.%d.%d:7355",
				my_IP.S_un.S_un_b.s_b1, my_IP.S_un.S_un_b.s_b2,
				my_IP.S_un.S_un_b.s_b3, my_IP.S_un.S_un_b.s_b4);
			Print.Draw_6x8String(20, 34, Str);
			Print.Draw_6x8String(20, 44, "Accepting....      ");
			if (buttonpressed[5]) { buttonpressed[5] = 0; Print.Draw_6x8String(0, 44, "Accepting Canceled.  "); Wait(500); TCP.SocketClose(); mode = 0;}
			if (TCP.AcceptThreadVal) {
				if (TCP.AcceptThreadVal == 2) {
					Print.Draw_6x8String(0, 44, "Accepting failed.    ");Wait(500);TCP.SocketClose(); mode = 0;
				}
				else if (TCP.AcceptThreadVal == 1) {
					you_IP = TCP.clientAddr.sin_addr;
					Print.Draw_6x8String(0, 44, "Accepted Sucessfilly.");
					sprintf_s(Str, "you IP:%d.%d.%d.%d",
						you_IP.S_un.S_un_b.s_b1, you_IP.S_un.S_un_b.s_b2,
						you_IP.S_un.S_un_b.s_b3, you_IP.S_un.S_un_b.s_b4);
					Print.Draw_6x8String(0, 54, Str);
					Wait(1000);
					Print.Draw_6x8String(0, 44, "Connecting....!      ");
					Wait(500);
					int i = 0;
					char ch = 0;
					while (i < 100) {i++;
						if (TCP.ServerRecv(&ch, 1) != SOCKET_ERROR && ch == 'a')break;
					}if(i>=100) { TCP.SocketClose(); Print.Draw_6x8String(0, 44, "Can not Interface.   "); Wait(500); mode = 0; }
					mode = 7;
					Wait(500);
					My.x = 1.5*Wallsize; My.y = 1.5*Wallsize; My.dx = 0; My.dy = 0;
					Recv.Server.x = 30.5*Wallsize; Recv.Server.y = 14.5*Wallsize; Recv.Server.end = 0;
				}
			}
		}
		else if (mode == 2) {//client
			Print.ClearBuffer(0);
			sprintf_s(Str, "%03d%03d%03d%03d",
				you_IP.S_un.S_un_b.s_b1, you_IP.S_un.S_un_b.s_b2,
				you_IP.S_un.S_un_b.s_b3, you_IP.S_un.S_un_b.s_b4);
			Print.Draw_Image(20, 0, 89, 32, logo);


			Print.Draw_Image(1, 40, 8, 24, NumberUpDown + (client_arrow == 0 ? 0 : 48));
			Print.Draw_Image(10, 40, 8, 24, NumberUpDown + (client_arrow == 1 ? 0 : 48));
			Print.Draw_Image(19, 40, 8, 24, NumberUpDown + (client_arrow == 2 ? 0 : 48));

			Print.Draw_Image(31, 40, 8, 24, NumberUpDown + (client_arrow == 3 ? 0 : 48));
			Print.Draw_Image(40, 40, 8, 24, NumberUpDown + (client_arrow == 4 ? 0 : 48));
			Print.Draw_Image(49, 40, 8, 24, NumberUpDown + (client_arrow == 5 ? 0 : 48));

			Print.Draw_Image(60, 40, 8, 24, NumberUpDown + (client_arrow == 6 ? 0 : 48));
			Print.Draw_Image(69, 40, 8, 24, NumberUpDown + (client_arrow == 7 ? 0 : 48));
			Print.Draw_Image(78, 40, 8, 24, NumberUpDown + (client_arrow == 8 ? 0 : 48));

			Print.Draw_Image(90, 40, 8, 24, NumberUpDown + (client_arrow == 9 ? 0 : 48));
			Print.Draw_Image(99, 40, 8, 24, NumberUpDown + (client_arrow == 10 ? 0 : 48));
			Print.Draw_Image(108, 40, 8, 24, NumberUpDown + (client_arrow == 11 ? 0 : 48));

			Print.Draw_Image(119, 40, 8, 24, NumberUpDown + (client_arrow == 12 ? 24 : 48));

			Print.Draw_6x8Char(2, 48, Str[0]);
			Print.Draw_6x8Char(11, 48, Str[1]);
			Print.Draw_6x8Char(20, 48, Str[2]);

			Print.Draw_dot(28, 56, 1);

			Print.Draw_6x8Char(32, 48, Str[3]);
			Print.Draw_6x8Char(41, 48, Str[4]);
			Print.Draw_6x8Char(50, 48, Str[5]);

			Print.Draw_dot(58, 56, 1);

			Print.Draw_6x8Char(61, 48, Str[6]);
			Print.Draw_6x8Char(70, 48, Str[7]);
			Print.Draw_6x8Char(79, 48, Str[8]);

			Print.Draw_dot(87, 56, 1);

			Print.Draw_6x8Char(91, 48, Str[9]);
			Print.Draw_6x8Char(100, 48, Str[10]);
			Print.Draw_6x8Char(109, 48, Str[11]);

			Print.Draw_6x8Char(120, 48, 'Y');
			

			if (buttonpressed[0] && client_arrow < 12) {
				buttonpressed[0] = 0;
				editval = ((uint8_t*)&you_IP.S_un)[client_arrow / 3];
				if (client_arrow % 3 == 0) plusval = 100; else if (client_arrow % 3 == 1) plusval = 10; else plusval = 1;
				((uint8_t*)&you_IP.S_un)[client_arrow / 3] += plusval;
			}
			if (buttonpressed[1]) {
				buttonpressed[1] = 0;
				editval = ((uint8_t*)&you_IP.S_un)[client_arrow / 3];
				if (client_arrow % 3 == 0) plusval = 100; else if (client_arrow % 3 == 1) plusval = 10; else plusval = 1;
				((uint8_t*)&you_IP.S_un)[client_arrow / 3] -= plusval;
			}
			if (buttonpressed[2]) { buttonpressed[2] = 0; client_arrow--; if (client_arrow < 0)client_arrow = 0; }
			if (buttonpressed[3]) { buttonpressed[3] = 0; client_arrow++; if (client_arrow > 12)client_arrow = 12; }
			if (buttonpressed[4]) {
				buttonpressed[4] = 0; if (client_arrow == 12) mode = 5;
			}
			if (buttonpressed[5]) { buttonpressed[5] = 0; mode = 0;}
		}
		else if (mode == 5) {//"                    "
			Print.ClearBuffer(0);
			Print.Draw_Image(20, 0, 89, 32, logo);
			int i = 0;
			while (!TCP.SocketConnect(you_IP, 7355)) { if (i++ > 50)break; }
			if(i>50){ TCP.SocketClose(); Print.Draw_6x8String(0, 44, "Connecting failed    "); Wait(500); mode = 2;}else mode = 6;

		}
		else if (mode == 3) { quit = 1; }
		else if (mode == 6) {
			Print.Draw_Image(20, 0, 89, 32, logo);
			sprintf_s(Str, "%03d.%03d.%03d.%03d:7355",
				you_IP.S_un.S_un_b.s_b1, you_IP.S_un.S_un_b.s_b2,
				you_IP.S_un.S_un_b.s_b3, you_IP.S_un.S_un_b.s_b4);
			Print.Draw_6x8String(0, 34, "Connecting to ...   ");
			Print.Draw_6x8String(0, 44, Str);
			if (TCP.ConnectThreadVal) {
				if (TCP.ConnectThreadVal == 2) { Print.Draw_6x8String(0, 34, "Connecting failed.  "); Wait(500); TCP.SocketClose(); mode = 2; }
				if (TCP.ConnectThreadVal == 1) {
					Print.Draw_6x8String(0, 34, "Connecting Succeed! ");
					Wait(1000);
					Print.Draw_6x8String(0, 44, "Connecting....!      ");
					Wait(500);
					int i = 0;
					while (i<100) {i++;
						if (TCP.ClientSend("a",1) != SOCKET_ERROR)break;
					}if (i >= 100) { TCP.SocketClose(); Print.Draw_6x8String(0, 44, "Can not Interface.   "); Wait(500); mode = 0; }
					mode = 8;
					My.x = 30.5*Wallsize; My.y = 14.5*Wallsize;
					Recv.Client.x = 1.5*Wallsize; Recv.Client.y = 1.5*Wallsize; Recv.Server.end = 0;
					My.dx = 0; My.dy = 0; Recv.Client.dx = 0; Recv.Client.dy = 0;
				}
			}
			if (buttonpressed[5]) { buttonpressed[5] = 0; TCP.SocketClose(); Print.Draw_6x8String(0, 44, "Connecting Canceled. "); Wait(500); mode = 0;}
		}
		else if (mode == 7) {//server mode
			Print.ClearBuffer(0);
			for (int i = 0; i < sizeof Walls / sizeof Rect; i++)Walls[i].Printblock(My.x, My.y);
			Print.Draw_Image(64, 32, My.w, My.h, Player);
			Print.Draw_Image(Recv.Client.x - My.x + 64, Recv.Client.y - My.y + 32, Recv.Client.w, Recv.Client.h, Player + 8);

			My.Process();

			if (TCP.ServerRecv(&Recv, sizeof SendRecvPacket) == INVALID_SOCKET) { TCP.SocketClose(); mode = 0; }
			Recv.Client.Process();
			Recv.Server.x = My.x;
			Recv.Server.y = My.y;
			if (My.IsTaged(Recv.Client))Recv.Server.end = 1;
			if (TCP.ServerSend(&Recv, sizeof SendRecvPacket) == INVALID_SOCKET) { TCP.SocketClose(); mode = 0; }
						
			if (buttonstate[0]) { My.dy -= 0.05; }
			if (buttonstate[1]) { My.dy += 0.05; }
			if (buttonstate[2]) { My.dx -= 0.05; }
			if (buttonstate[3]) { My.dx += 0.05; }
			if (buttonpressed[5]) { buttonpressed[5] = 0; TCP.SocketClose(); mode = 0; }
			times[7] = GetTickCount();
		}
		else if (mode == 8) {//client mode
			Print.ClearBuffer(0);
			for (int i = 0; i < sizeof Walls / sizeof Rect; i++)Walls[i].Printblock(My.x, My.y);
			Print.Draw_Image(64, 32, My.w, My.h, Player + 8);
			Print.Draw_Image(Recv.Server.x - My.x + 64, Recv.Server.y - My.y + 32, My.w, My.h, Player);
			
			Recv.Client = My;

			Sleep(3);
			if (TCP.ClientSend(&Recv, sizeof SendRecvPacket) == INVALID_SOCKET) { TCP.SocketClose(); mode = 0; }
			if (TCP.ClientRecv(&Recv, sizeof SendRecvPacket) == INVALID_SOCKET) { TCP.SocketClose(); mode = 0; }
			My = Recv.Client;
			if (Recv.Server.end) { TCP.SocketClose(); mode = 0; }

			if (buttonstate[0]) { My.dy -= 0.05; }
			if (buttonstate[1]) { My.dy += 0.05; }
			if (buttonstate[2]) { My.dx -= 0.05; }
			if (buttonstate[3]) { My.dx += 0.05; }
			if (buttonpressed[5]) { buttonpressed[5] = 0; TCP.SocketClose(); mode = 0; }
			times[7] = GetTickCount();
		}
		if (FpsView) {
			sprintf_s(Str, "%3.0f", fps);
			Print.Draw_6x8String(0, 0, Str);
		}
		tb = GetTickCount(); tm = tb - ta;
		delay = 16 - tm;
		if (delay < 60 && delay > 0)Sleep(delay);
		floatcycletime = GetTickCount() - timea;
		fps = 1000 / floatcycletime;
		timea = GetTickCount();
		cyclecount = 0;

		Print.PrintBuffer();
		SDL_RenderPresent(renderer);
		if (keystate[SDL_SCANCODE_UP])buttonstate[0]++; else buttonstate[0] = 0; if (buttonstate[0] == 2)buttonpressed[0] = 1;
		if (keystate[SDL_SCANCODE_DOWN])buttonstate[1]++; else buttonstate[1] = 0; if (buttonstate[1] == 2)buttonpressed[1] = 1;
		if (keystate[SDL_SCANCODE_LEFT])buttonstate[2]++; else buttonstate[2] = 0; if (buttonstate[2] == 2)buttonpressed[2] = 1;
		if (keystate[SDL_SCANCODE_RIGHT])buttonstate[3]++; else buttonstate[3] = 0; if (buttonstate[3] == 2)buttonpressed[3] = 1;
		if (keystate[SDL_SCANCODE_Z])buttonstate[4]++; else buttonstate[4] = 0; if (buttonstate[4] == 2)buttonpressed[4] = 1;
		if (keystate[SDL_SCANCODE_X])buttonstate[5]++; else buttonstate[5] = 0; if (buttonstate[5] == 2)buttonpressed[5] = 1;
		if (keystate[SDL_SCANCODE_A])buttonstate[6]++; else buttonstate[6] = 0; if (buttonstate[6] == 2)FpsView = !FpsView;
		
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT) {}
				break;
			case SDL_QUIT:quit = 1; break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_SPACE: break;
				case SDLK_F12:quit = 1; break;
				}break;
			}
		}
	}
	WSACleanup();
	SDL_Quit();
	return 0;
}

void Wait(DWORD dwMillisecond)
{
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		Print.PrintBuffer();
		SDL_Delay(1);
		SDL_RenderPresent(renderer);
		SDL_PollEvent(&event);
	}
}
Rect::Rect(int _x, int _y, int _w, int _h) { x = _x; y = _y; w = _w; h = _h; }
void Rect::Printblock(int cx, int cy) {
	Print.Draw_Area(x - cx + 64, y - cy + 32, w, h, 1);
}
Rect Rect::operator* (int i) {
	this->x *= i;
	this->y *= i;
	this->w *= i;
	this->h *= i;
	return *this;
}
TCPTag::TCPTag() {}
TCPTag TCPTag::operator= (TCPTag oth) {
	memcpy(this, &oth, sizeof TCPTag);
	return *this;
}
int TCPTag::IsTaged(TCPTag oth) {
	return inout((int)x, (int)y, w, h, oth.x, oth.y, oth.w, oth.h);
}
int TCPTag::IsCrashed(Rect *blocks, int len) {
	for (int i = 0; i < len; i++)
		if (inout((int)x, (int)y, w, h, blocks[i].x, blocks[i].y, blocks[i].w, blocks[i].h))return i;
	return -1;
}
void TCPTag::Process() {
	if (dx > maxdx)dx = maxdx;
	if (dx < -maxdx)dx = -maxdx;
	if (dy > maxdy)dy = maxdy;
	if (dy < -maxdy)dy = -maxdy;
	x += dx; y += dy;
	int block = IsCrashed(Walls, sizeof Walls / sizeof Rect);
	if (block != -1) {
		uint8_t top = inout(x, y, w, h - 3, Walls[block].x, Walls[block].y, Walls[block].w, Walls[block].h);
		uint8_t bottom = inout(x, y + 3, w, h - 3, Walls[block].x, Walls[block].y, Walls[block].w, Walls[block].h);
		uint8_t left = inout(x, y, w - 3, h, Walls[block].x, Walls[block].y, Walls[block].w, Walls[block].h);
		uint8_t right = inout(x + 3, y, w - 3, h, Walls[block].x, Walls[block].y, Walls[block].w, Walls[block].h);
		if (!top & bottom & left & right) {
			if (dy>0)dy = -dy * 0.8;
			y -= 0.2;
		}
		if (top & !bottom & left & right) {
			if (dy<0)dy = -dy * 0.8;
			y += 0.2;
		}
		if (top & bottom & !left & right) {
			if (dx>0)dx = -dx * 0.8;
			x -= 0.2;
		}
		if (top & bottom & left & !right) {
			if (dx<0)dx = -dx * 0.8;
			x += 0.2;
		}
		x += dx; y += dy;

	}

}
TCPTag TCPTag::operator= (Vector i) {
	this->x = i.x;
	this->y = i.y;
	this->dx = i.dx;
	this->dy = i.dy;
	return *this;
}
