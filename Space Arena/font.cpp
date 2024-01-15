#define WIN32_LEAN_AND_MEAN
#define INITGUID

 

#include "2x11.h"

///////////FONT


//extern LPDIRECT3DDEVICE9 g_pd3dDevice;



//font

LPD3DXFONT Font = NULL;
RECT FontPosition = { 0, 0, 0, 0 };

 
void chardraw(int x, int y, char ch, int r, int g, int b);
void  Drawtext(LPCWSTR STR, float x, float y, int r, int g, int b);
void iniText(int size, LPCWSTR font);
int SetFont(LPCWSTR name, int height, UINT width);
LPD3DXSPRITE		g_Sprite = NULL;
void tdraw(int x, int y, LPCWSTR  text, int r, int g, int b);

int testfont();


 /*
 if(fx==1) { 
	for( int x = 0; x < strlen(c); x++ )
		TextOut( xdc, ix+(x*S), 	 y+S,  &c[x],1		 );
	}

	else {

		for( int x = 0; x < strlen(c); x++ ) {

			    double g=scroll_y+S*x;
				g/=15;
		        double f=60*sin(g/3);
				TextOut( xdc,ix+(x*S), 	(int)f+ y-S,  &c[x],1		 );
				scroll_y=(scroll_y+1);

		}


	}

	  skull[i].x=((int)  (X/2 + (X/2)*sin((ftmp-r)/skull[i].i)));
	  skull[i].y=((int)  (Y/2 + (Y/2)*cos((ftmp-r)/skull[i].ii)));
	   skull[i].x=((int)(X/2 + (X/3)*sin((ftmp-r)/skull[i].ii)));
	  skull[i].y=((int)(Y/2 + (Y/3)*cos((ftmp-r)/skull[i].i)));
	  skull[i].x=5+((int)(X/2 + (X/3)*sin((ftmp-r)/skull[i].ii)));
	  skull[i].y=5+((int)(Y/2 + (Y/3)*cos((ftmp-r)/skull[i].i)));
	  if(rand()%111==1) skull[i].col=D3DCOLOR_XRGB(rand()%255,rand()%255,160+rand()%250) ;
	*/
	

 


void tdraw(int x, int y, LPCWSTR  text, int r, int g, int b)
{

	FontPosition.top = y;
	FontPosition.left = x;


	//Font->DrawText(NULL, text , -1, &FontPosition, DT_CENTER, 0xffffffff);
	//Font->DrawText(NULL, text , -1, &FontPosition, DT_LEFT, D3DCOLOR_XRGB(r,g,b));
	Font->DrawText(NULL, text, -1, &FontPosition, DT_NOCLIP, D3DCOLOR_XRGB(r, g, b));

}

void chardraw(int x, int y, char ch, int r, int g, int b)
{
	WCHAR buf[2];
	buf[0] = ch;
	buf[1] = '\0';

	FontPosition.top = y;
	FontPosition.left = x;

	// Font->DrawText(NULL, buf , -1, &FontPosition, DT_CENTER, D3DCOLOR_XRGB(r,g,b));
	Font->DrawText(NULL, buf, -1, &FontPosition, DT_NOCLIP, D3DCOLOR_XRGB(r, g, b));
}


void  Drawtext(LPCWSTR STR, float x, float y, int r, int g, int b)
{
	RECT rct;
	SetRect(&rct, (int)x, (int)y, (int)x + 200, (int)y + 200);
	Font->DrawText(g_Sprite, STR, -1, &rct, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(r, g, b));
}



void iniText(int size, LPCWSTR font)
{
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	if (FAILED(D3DXCreateFont(g_pd3dDevice, size, 0, 0, 1, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, font, &Font))) return;

	FontPosition.top = 0;
	FontPosition.left = 0;
	FontPosition.right = X;
	FontPosition.bottom = Y;
}


int SetFont(LPCWSTR name, int height, UINT width)
{
	D3DXFONT_DESC lf;
	ZeroMemory(&lf, sizeof(D3DXFONT_DESC));
	lf.Height = height;
	lf.Width = width;
	lf.Weight = 500;
	lf.Italic = false;
	lf.CharSet = DEFAULT_CHARSET;
	lstrcpy(lf.FaceName, name);

	D3DXCreateFontIndirect(g_pd3dDevice, &lf, &Font);
	return true;
}