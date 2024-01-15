#pragma once

#include <Windows.h>

 
#include <d3d9.h>
#include <d3dx9.h>
#include <commctrl.h>
#include <commdlg.h>
#include <mmsystem.h>
#include <ddraw.h>
#include <objbase.h>
#include <shellapi.h>
#include <shlobj.h>

#include <stdio.h>

#include <fstream> // Include for file stream operations
#include <iostream> // Include for console output (cout)
#include <string>


#pragma comment ( lib, "ddraw.lib" )
//#pragma comment ( lib, "d3dx9.lib" )
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "dxguid.lib")

 
#pragma comment ( lib, "dsound.lib" )
 
#pragma comment ( lib, "strmiids.lib ")
#pragma comment ( lib, "Winmm.lib")


//using namespace DirectX;

const int X = 1920;
const int Y = 1080;

 

 

HRESULT InitD3D(HWND hWnd, int dx, int dy, int w);
void Rectangle(int x1, int y1, int x2, int y2, int r, int g, int b);

HRESULT LoadSprite(char* name, LPD3DXSPRITE& Spr, LPDIRECT3DTEXTURE9& Texture);

void clear(int r, int g, int b);

void imax(LPD3DXSPRITE Spr, LPDIRECT3DTEXTURE9 Texture, int x, int y, int xx, int yy, DWORD c);
void imax_scale(LPD3DXSPRITE Spr, LPDIRECT3DTEXTURE9 Texture, int x, int y, int xx, int yy, float scale);
void imax_rotate(LPD3DXSPRITE Spr, LPDIRECT3DTEXTURE9 Texture, int x, int y, int xx, int yy, float rot);
void Max(LPD3DXSPRITE Spr, LPDIRECT3DTEXTURE9 Texture, int x, int y, int xx, int yy, float scale, float rot, DWORD c);
void Max2(LPD3DXSPRITE Spr, LPDIRECT3DTEXTURE9 Texture, int x, int y, int xx, int yy, float scale, float rot, DWORD c);
void Putimage(LPD3DXSPRITE Spr, LPDIRECT3DTEXTURE9 Texture,
	int x, int y, int xx, int yy,
	float scale, float rot,
	DWORD c);




void pix(int x, int y, int r, int g, int b);
void retpix(int x, int y, int& r, int& g, int& b);
DWORD retpix2(int x, int y);

void box(int x1, int y1, int x2, int y2, int r, int g, int b);
void circle(int xo, int yo, int rad, int r, int g, int b);
void drawline(int x1, int y1, int x2, int y2, int r, int g, int b);
void Cleanup();
void lock();
void unlock();
void Render();
int LoadBMP(LPCTSTR lpszName);

void say(const wchar_t* message);



HRESULT talk(LPCWSTR ta);
int opentxtfiletalk(LPCWSTR ta);
 
//extern int tes();


///////////////////////////////////////////////////////
extern void chardraw(int x, int y, char ch, int r, int g, int b);
extern void chardraw(int x, int y, char ch, int r, int g, int b);
extern void  Drawtext(LPCWSTR STR, float x, float y, int r, int g, int b);
extern void iniText(int size, LPCWSTR font);
extern int SetFont(LPCWSTR name, int height, UINT width);
extern  LPD3DXSPRITE		g_Sprite ;
extern void tdraw(int x, int y, LPCWSTR  text, int r, int g, int b);

extern LPDIRECT3DDEVICE9 g_pd3dDevice;


//////////////////////////
 

///////////////////////////////
/*
extern  void InitPalette();
extern void SetPalette();
extern void FadeInColorsPalette(int speed);
extern void FadeInColorsPalette(int speed);
extern void FlashColorsPalette(int duration, int speed);
extern void ChangeToRedPalette();
*/



 