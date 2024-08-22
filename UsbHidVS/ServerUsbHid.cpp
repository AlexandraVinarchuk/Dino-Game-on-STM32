#define WIN32
#ifdef WIN32
#include <windows.h>
#else
#include <stdlib.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include "hidapi.h"
#include <stdint.h>
#define MAX_STR 255
#include <locale.h>
#include <string.h>
#include <wchar.h>
#pragma comment(lib, "ws2_32.lib")
#include "ServerUsbHid.h"
#include <iostream>
using namespace std;

struct Modbus
{
	UINT16 TransID;  
	UINT16 ProtocolID;
	UINT8 Length; 
	UINT8 UnitID; 

	UINT8 FuncCode; 
	char Data[128]; 
};
struct GameSettings
{
	int GameMode;
	int SpeedOFTime;
};

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	int res;
	unsigned char buf[256];
	#define MAX_STR 255
	wchar_t wstr[MAX_STR];
	hid_device* handle;
	int i;

	handle = hid_open(0x1234, 0x0001, NULL);
	if (!handle) {
		printf("unable to open device\n");
		return 1;
	}
	GameSettings game;
	game.GameMode = 0;
	game.SpeedOFTime = 1000;




	// Инициализируем DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	// Создаем сокет
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);


	// Привязываем сокет
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr)); // Каждый байт заполняется 0
	sockAddr.sin_family = PF_INET; // Использовать IPv4-адрес
	sockAddr.sin_addr.s_addr = inet_addr("0.0.0.0"); // Определенный IP-адрес
	sockAddr.sin_port = htons(502); // Порт
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));


	// Входим в состояние мониторинга
	listen(servSock, 20);


	// Получение клиентского запроса
	SOCKADDR clntAddr;
	int nSize;
	char szBuffer[MAXBYTE] = { 0 };
	SOCKET clntSock;
	Modbus mod;

	nSize = sizeof(SOCKADDR);
	clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	recv(clntSock, szBuffer, MAXBYTE, NULL);
	memcpy(&mod, &szBuffer[0], sizeof(mod));


		switch (mod.FuncCode)
		{
		case 1:
		{
			int k, j;
			memcpy(&game, &mod.Data[0], sizeof(game));
			buf[0] = 0x02;	
			strcpy(mod.Data, "Data is ok");
			printf(" %s ", mod.Data);
		}break;
		default: {
			mod.TransID = 0x00;
			mod.ProtocolID = 0x00;
			mod.UnitID = 0x00;
			mod.FuncCode = 0x00;
			game.GameMode = 0;
			game.SpeedOFTime = 1000;
			strcpy(mod.Data, "Invalid Function Code!");
		}break;
		}

		char mod_for_send[256]; // массив для отправки
		memcpy(&mod_for_send[0], &mod, sizeof(mod)); // Упаковка для отправки
		send(clntSock, mod_for_send, sizeof(mod), NULL); // отправил
	





	int x_pos = 10, y_pos = 30; // dino
	int x_pos_o = 120, y_pos_o = 40; // object
	int buttonPressedTimer = 0;
	bool anyObj = 0;
	int score = 0, tick = 0;
	int sun_ary[21][21] = {
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
{ 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
{ 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0},
{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
{ 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	};

	int k, j;
	if (game.GameMode)
	{
		x_pos = 100;
		x_pos_o = 10;

		for (k = 0;k < 21; k++) // spawn
		{
			for (j = 0;j < 21/2; j++) // spawn
			{
				swap(sun_ary[k][j], sun_ary[k][21 - j- 1]);
			}
		}
	}

	ClearScreenFunc(buf, res, handle);
	SpawnRoad(buf, res, handle);


	while (1) // game while
	{
		tick++;
		if (tick == 10)
		{
			tick = 0;
			score++;
		}
		
		char nchar[5];
		sprintf_s(nchar, "%d", score);
		buf[0] = 0x02;
		memcpy(&buf[1], nchar, 5);

		res = hid_send_feature_report(handle, buf, 3);
		if (res == -1)
		{
			printf("hid_write error.\n");
		}

		Sleep(game.SpeedOFTime);
		ObjLogic(anyObj, buf, x_pos_o, y_pos_o, game.GameMode,  res, handle);
		DinoPrint(buf, x_pos, y_pos, res, handle, sun_ary);

		buf[0] = 0x01;
		hid_get_feature_report(handle, buf, sizeof(buf));
		printf("%d", buf[1]);

		if (y_pos!= 30 && !buttonPressedTimer) // прыжок нажат
		{
			y_pos += 2;
			continue;
		}

		if (buf[1] && !buttonPressedTimer) // прыжок
		{
			buttonPressedTimer = 10;
		}

		if (buttonPressedTimer) // падение
		{
			buttonPressedTimer--;
			y_pos -= 2;
		}
		if (!game.GameMode)
		{
			if (((x_pos + 21 - x_pos_o) > 3) && (y_pos + 21 > 40))
			{
				break;
			}
		}
		else
		{
			if (((x_pos_o - x_pos) > 3) && (y_pos + 21 > 40))
			{
				break;
			}
		}

	}
	char nchar[5];
	ClearScreenFunc(buf, res, handle);
	sprintf_s(nchar, "%d", score);
	buf[0] = 0x02;
	memcpy(&buf[1], nchar, 5);

	res = hid_send_feature_report(handle, buf, 3);
	if (res == -1)
	{
		printf("hid_write error.\n");
	}

	// Закрываем сокет
	closesocket(clntSock);
	closesocket(servSock);


	// Прекращаем использование DLL
	WSACleanup();

	return 0;
}

void DinoPrint(unsigned char  buf[256], int x_pos, int y_pos, int& res, hid_device* handle, int  sun_ary[21][21])
{
	int k, j;
	for (k = 0;k < 24;k++) // spawn
	{
		for (j = 0;j < 24; j++)
		{
			buf[0] = 0x04;
			buf[1] = j + x_pos - 2; //10 usually
			buf[2] = k + y_pos - 2; //30
			buf[3] = 0x00;
			res = hid_send_feature_report(handle, buf, 4);
			if (res == -1) {
				printf("hid_write error.\n");
			}

		}
	}


	int revx, revy;
	for (k = 0;k < 21;k++) // spawn
	{
		for (j = 0;j < 21; j++)
		{
			if (sun_ary[k][j] == 1)
			{
				buf[0] = 0x04;
				buf[1] = j + x_pos; //10 usually
				buf[2] = k + y_pos; //30
				buf[3] = 0x01;
				res = hid_send_feature_report(handle, buf, 4);
				if (res == -1) {
					printf("hid_write error.\n");
				}
			}

		}
	}
}

void ObjLogic(bool &anyObj, unsigned char  buf[256], int &x_pos_o, int &y_pos_o, int &GameMode, int& res, hid_device* handle)
{
	int k, j;
	for (k = 0;k < 12;k++) //clear
	{
		for (j = 0;j < 2; j++)
		{
			buf[0] = 0x04;
			buf[1] = j + x_pos_o; //120
			buf[2] = k + y_pos_o; //40
			buf[3] = 0x00;
			res = hid_send_feature_report(handle, buf, 4);
			if (res == -1) {
				printf("hid_write error.\n");
			}
		}
	}

	if (!anyObj)
	{
		anyObj = 1;	
	}
	else if ((x_pos_o > 0) && (x_pos_o < 128))
	{
		if(!GameMode)
			x_pos_o -= 3;
		else
			x_pos_o += 3;
	}
	else
	{
		if (!GameMode)
		{
			x_pos_o = 120;
			y_pos_o = 40;
		}
		else
		{
			x_pos_o = 10;
			y_pos_o = 40;
		}
	}

	for (k = 0;k < 12;k++)
	{
		for (j = 0;j < 2; j++)
		{
			buf[0] = 0x04;
			buf[1] = j + x_pos_o; //120
			buf[2] = k + y_pos_o; //40
			buf[3] = 0x01;
			res = hid_send_feature_report(handle, buf, 4);
			if (res == -1) {
				printf("hid_write error.\n");
			}
		}
	}
}

void SpawnRoad(unsigned char  buf[256], int& res, hid_device* handle)
{
	int k, j;
	for (k = 0;k < 64;k++)
	{
		for (j = 0;j < 128; j++)
		{
			if (k == 52)
			{
				buf[0] = 0x04;
				buf[1] = j;
				buf[2] = k;
				buf[3] = 0x01;
				res = hid_send_feature_report(handle, buf, 4);
				if (res == -1) {
					printf("hid_write error.\n");
				}
			}

		}
	}
}

void ClearScreenFunc(unsigned char  buf[256], int& res, hid_device* handle)
{
	int k, j;
	for (k = 0;k < 128;k++)
	{
		for (j = 0;j < 64; j++)
		{

			buf[0] = 0x04;
			buf[1] = k;
			buf[2] = j;
			buf[3] = 0x00;
			res = hid_send_feature_report(handle, buf, 4);
			if (res == -1) {
				printf("hid_write error.\n");
			}

		}
	}
}
