#define WIN32_LEAN_AND_MEAN
//#define STRICT

#define INITGUID

//#pragma comment(linker,"/NODEFAULTLIB:strmbasd.lib ") //dx 10


#include "2x11.h"


//HWND main;

LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device

LPDIRECT3DSURFACE9  back;
LPDIRECT3DSURFACE9	Surface;

LPDIRECT3DTEXTURE9  Sprite = NULL;
LPD3DXSPRITE	DXSPRITE = NULL;
RECT				bmpr;
POINT				Point;
int Pitch32;
DWORD* pData;


#define CELL 50
#define SZ 128
int bmp = 1;


//void testmp3();
//int test();

static HMODULE d3d9_handle = 0;

void say(const wchar_t* message) {



}


wchar_t* MWC(char* name) {
	int len = MultiByteToWideChar(CP_ACP, 0, name, -1, NULL, 0);
	wchar_t* wideName = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, name, -1, wideName, len);

	return wideName;
}


void lock()
{
	D3DLOCKED_RECT	LockedRect;

	back->LockRect(&LockedRect, NULL, NULL);
	pData = (DWORD*)LockedRect.pBits;
	Pitch32 = LockedRect.Pitch / 4;
}

void unlock() { back->UnlockRect(); }




//efface le background
void clear(int r, int g, int b)
{
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(r, g, b), 1.0f, 0);
}


 


void mainloop()
{


	circle(111, 111, 59, 200, 0, 0);

	//for(register int i=0;i<200;i++)	pix(rand()%X,rand()%Y,  200,100,200);





}

void main2d()
{
	int c = D3DCOLOR_XRGB(100, 100, 100);
	 


	 imax(DXSPRITE, Sprite, 100, 100, SZ, SZ, 0xFFFFFFFF);
 
	


}

void Render()
{

	if (bmp == 0) clear(0, 0, 0); 




	g_pd3dDevice->BeginScene();



	 if (bmp == 1) {

	 	g_pd3dDevice->UpdateSurface(Surface, &bmpr, back, &Point);
		//g_pd3dDevice->UpdateSurface(Surface2, &bmpr, back, &Point);
	 }



	main2d();

 
	g_pd3dDevice->EndScene();



	//////////////////////////////////////////
	lock();

	mainloop();

	unlock();
	///////////////////////////////////////////////////
 
	 
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
	 
	//control();

}



//-----------------------------------------------------------------------------
//InitD3D()
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd, int dx, int dy, int w)
{
	D3DPRESENT_PARAMETERS d3dpp;


	D3DDISPLAYMODE d3ddm;
	static HMODULE library = 0;
	static HMODULE d3d = 0;


	library = (HMODULE)LoadLibrary(L"ddraw.dll");
	if (!library) return 0;

	d3d = (HMODULE)LoadLibrary(L"d3d9.dll");
	if (!d3d) return 0;

	 

	IDirect3D9* (__stdcall * d3d9_create)(UINT SDKVersion) = 0;
	HMODULE d3d9_handle = 0;
	IDirect3D9* d3d9_ptr = 0;
	IDirect3DDevice9* device_ptr = 0;
	//     D3DPRESENT_PARAMETERS present_parameters;
	//     HRESULT hres;

	d3d9_handle = LoadLibrary(L"d3d9.dll");
	if (d3d9_handle == NULL) say(L"Failed to load d3d9.\n");
	if (!d3d9_handle) say(L"d3d9_handle\n");


	CoInitialize(NULL);

	CoCreateInstance(IID_IDirect3D9, NULL, CLSCTX_INPROC_SERVER, IID_IDirect3D9, (void**)&g_pD3D);

 

	// Create D3D object.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))    return E_FAIL;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);

 
	d3dpp.Windowed = w;
	d3dpp.BackBufferWidth = dx;//
	d3dpp.BackBufferHeight = dy;//
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; //32 bp
	//d3dpp.BackBufferFormat = d3ddm.Format;

	d3dpp.BackBufferCount = 1;//
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;//
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;



	d3dpp.hDeviceWindow = hWnd;//



	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;//D3DFMT_D16;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;//




	// Create D3DDevice
	g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice);
	 




	g_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &back);



	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));
	g_pd3dDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

 
	D3DVIEWPORT9 vp = { 0, 0, dx, dy, 0.0f, 1.0f };

	g_pd3dDevice->SetViewport(&vp);

	ShowCursor(FALSE);
	srand(GetTickCount64());
	clear(0, 0, 0);


	char fileName[] = "A1.PNG";
	LoadSprite(fileName, DXSPRITE, Sprite);

	char fileName2[] = "A1.bmp";
	LoadBMP(MWC(fileName2));


	//test();
	//Sleep(100);

	//testmp3();

	return S_OK;
}


void retpix(int x, int y, int& r, int& g, int& b)
{
	// Check bounds outside the function
	if (x < 0 || x >= X || y < 0 || y >= Y) return;

	// Lock the back buffer for direct access to pixel data
	D3DLOCKED_RECT lockedRect;
	back->LockRect(&lockedRect, NULL, NULL);
	DWORD* pData = (DWORD*)lockedRect.pBits;
	int pitch32 = lockedRect.Pitch / 4;


	// Use bitwise left shift instead of multiplication
	DWORD pixelValue = (DWORD)pData[(Pitch32 << 5) + y + x];

	back->UnlockRect();

	// Extract individual color components using bit masking
	b = pixelValue & 0xFF;               // Blue component
	g = (pixelValue >> 8) & 0xFF;        // Green component
	r = (pixelValue >> 16) & 0xFF;       // Red component
}

void circle(int xo, int yo, int rad, int r, int g, int b)
{
	int x = rad;
	int y = 0;
	int err = 0;
 

	 


	while (x >= y)
	{
		// Draw the octants of the circle using symmetry
		pix(xo + x, yo + y, r, g, b);
		pix(xo + y, yo + x, r, g, b);
		pix(xo - y, yo + x, r, g, b);
		pix(xo - x, yo + y, r, g, b);
		pix(xo - x, yo - y, r, g, b);
		pix(xo - y, yo - x, r, g, b);
		pix(xo + y, yo - x, r, g, b);
		pix(xo + x, yo - y, r, g, b);

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}

		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
 
}



void drawline(int x1, int y1, int x2, int y2, int r, int g, int b)
{
	int deltax = abs(x2 - x1);
	int deltay = abs(y2 - y1);
	int xerr = 0, yerr = 0;
	int incx, incy;

 

	if (x1 < x2)
		incx = 1;
	else
		incx = -1;

	if (y1 < y2)
		incy = 1;
	else
		incy = -1;

	int distance;

	if (deltax > deltay)
		distance = deltax;
	else
		distance = deltay;

	for (int t = 0; t <= distance; ++t)
	{
		pix(x1, y1, r, g, b);

		xerr += deltax;
		yerr += deltay;

		if (xerr > distance)
		{
			xerr -= distance;
			x1 += incx;
		}

		if (yerr > distance)
		{
			yerr -= distance;
			y1 += incy;
		}
	}

	 
}


void Rectangle(int x1, int y1, int x2, int y2, int r, int g, int b)
{

	drawline(x1, y1, x2, y1, r, g, b);
	drawline(x1, y2, x2, y2, r, g, b);

	drawline(x1, y1, x1, y2, r, g, b);
	drawline(x2, y1, x2, y2, r, g, b);


}

DWORD retpix2(int x, int y)
{
	// Check bounds outside the function
	 if (x < 0 || x >= X || y < 0 || y >= Y) return 0;

	// Use bitwise left shift instead of multiplication
	 return (DWORD)pData[(Pitch32 << 5) + y + x];

	/* Example usage:
   DWORD c = retpix(x, y);
   int b = c & 0xFF;            // Blue component
   int g = (c >> 8) & 0xFF;     // Green component
   int r = (c >> 16) & 0xFF;    // R*/
}



void pix(int x, int y, int r, int g, int b)
{
	// Check if the pixel coordinates are within the valid range
	if (x >= X || x < 0 || y >= Y || y < 0)
		return;

	// Ensure that the coordinates are within the dimensions of the frame buffer
	x = (x == X) ? (X - 1) : x;
	y = (y == Y) ? (Y - 1) : y;

	// Ensure that RGB values are within the valid range
	r = (r < 0) ? 0 : (r > 255) ? 255 : r;
	g = (g < 0) ? 0 : (g > 255) ? 255 : g;
	b = (b < 0) ? 0 : (b > 255) ? 255 : b;

	// Calculate the index of the pixel in the linear array
	int pixelIndex = Pitch32 * y + x;

 

	// Set the color of the pixel in the frame buffer
	pData[pixelIndex] = D3DCOLOR_XRGB(r, g, b);
 
}

void box(int x1, int y1, int x2, int y2, int r, int g, int b)
{
	// Ensure the coordinates are within bounds
	if (x1 < 0) x1 = 0;
	if (y1 < 0) y1 = 0;
	if (x2 >= X) x2 = X - 1;
	if (y2 >= Y) y2 = Y - 1;
 

	// Iterate through the specified rectangle and set pixel colors
	for (int y = y1; y <= y2; ++y)
	{
		for (int x = x1; x <= x2; ++x)
		{
			// Calculate the index for the current pixel
			int index = Pitch32 * y + x;

			// Set the pixel color in ARGB format
			pData[index] = D3DCOLOR_XRGB(r, g, b);
		}
	}
 
}




void Putimage(LPD3DXSPRITE Spr, LPDIRECT3DTEXTURE9 Texture, 
	               int x, int y, int xx, int yy, 
	                 float scale, float rot, 
	                   DWORD c)
{
	RECT r;

	D3DXMATRIX Matrix;
	D3DXVECTOR2 Translation((float)x, (float)y);

	r.left = 0;
	r.top = 0;
	r.right = xx;
	r.bottom = yy;

	Spr->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR2 spriteCentre = D3DXVECTOR2((float)xx / 2, (float)yy / 2);
	D3DXVECTOR2 scaling(scale, scale);

	Spr->Begin(D3DXSPRITE_ALPHABLEND);//transparent
	D3DXMatrixTransformation2D(&Matrix, NULL, 0.0, &scaling, &spriteCentre, rot, &Translation);
	Spr->SetTransform(&Matrix);
	Spr->Draw(Texture, &r, NULL, NULL, c);
	Spr->End();
}


void imax(LPD3DXSPRITE Spr, LPDIRECT3DTEXTURE9 Texture, int x, int y, int xx, int yy, DWORD c)
{
	RECT r;

	D3DXMATRIX Matrix;
	D3DXVECTOR2 Translation((float)x, (float)y);


	r.left = 0;
	r.top = 0;
	r.right = xx;
	r.bottom = yy;
 
	Spr->Begin(D3DXSPRITE_ALPHABLEND);//transparent

	D3DXMatrixTransformation2D(&Matrix, NULL, NULL, NULL, NULL, 0, &Translation);
	Spr->SetTransform(&Matrix);
	Spr->Draw(Texture, &r, NULL, NULL, c);
	Spr->End();

}



void imax_rotate(LPD3DXSPRITE Spr, LPDIRECT3DTEXTURE9 Texture, int x, int y, int xx, int yy, float rot)
{
	RECT r;

	D3DXMATRIX Matrix;
	D3DXVECTOR2 Translation((float)x, (float)y);


	r.left = 0;
	r.top = 0;
	r.right = xx;
	r.bottom = yy;



	D3DXVECTOR2 spriteCentre = D3DXVECTOR2((float)xx / 2, (float)yy / 2);
	//D3DXVECTOR2 spriteCentre=D3DXVECTOR2((float)xx,(float)yy);

	D3DXVECTOR2 scaling(1, 1);

	Spr->Begin(D3DXSPRITE_ALPHABLEND);//transparent
	D3DXMatrixTransformation2D(&Matrix, NULL, 0.0, &scaling, &spriteCentre, rot, &Translation);
	Spr->SetTransform(&Matrix);
	//Spr->Draw(Texture, &r,  NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
	Spr->Draw(Texture, &r, NULL, NULL, 0xFFFFFFFF);
	//Spr->Draw(Texture, &r, NULL,  NULL, 0);
	Spr->End();

}


void imax_scale(LPD3DXSPRITE Spr, LPDIRECT3DTEXTURE9 Texture, int x, int y, int xx, int yy, float scale)
{
	RECT r;

	D3DXMATRIX Matrix;
	D3DXVECTOR2 Translation((float)x, (float)y);


	r.left = 0;
	r.top = 0;
	r.right = xx;
	r.bottom = yy;



	D3DXVECTOR2 spriteCentre = D3DXVECTOR2((float)xx / 2, (float)yy / 2);

	D3DXVECTOR2 scaling(scale, scale);


	Spr->Begin(D3DXSPRITE_ALPHABLEND);//transparent
	D3DXMatrixTransformation2D(&Matrix, NULL, 0.0, &scaling, &spriteCentre, NULL, &Translation);
	Spr->SetTransform(&Matrix);
	Spr->Draw(Texture, &r, NULL, NULL, 0xFFFFFFFF);
	Spr->End();

}

void Max(LPD3DXSPRITE Spr, LPDIRECT3DTEXTURE9 Texture, int x, int y, int xx, int yy, float scale, float rot, DWORD c)
{
	RECT r;

	D3DXMATRIX Matrix;
	D3DXVECTOR2 Translation((float)x, (float)y);


	r.left = 0;
	r.top = 0;
	r.right = xx;
	r.bottom = yy;



	D3DXVECTOR2 spriteCentre = D3DXVECTOR2((float)xx / 2, (float)yy / 2);
	//D3DXVECTOR2 spriteCentre=D3DXVECTOR2((float)xx,(float)yy);
	D3DXVECTOR2 scaling(scale, scale);


	Spr->Begin(D3DXSPRITE_ALPHABLEND);//transparent
	D3DXMatrixTransformation2D(&Matrix, NULL, 0.0, &scaling, &spriteCentre, rot, &Translation);
	Spr->SetTransform(&Matrix);
	Spr->Draw(Texture, &r, NULL, NULL, c);
	Spr->End();


}


void Max2(LPD3DXSPRITE Spr, LPDIRECT3DTEXTURE9 Texture, int x, int y, int xx, int yy, float scale, float rot, DWORD c)
{
	RECT r;

	D3DXMATRIX Matrix;
	D3DXVECTOR2 Translation((float)x, (float)y);


	r.left = 0;
	r.top = 0;
	r.right = xx;
	r.bottom = yy;



	D3DXVECTOR2 spriteCentre = D3DXVECTOR2((float)CELL / 2, (float)CELL / 2);

	D3DXVECTOR2 scaling(scale, scale);


	Spr->Begin(D3DXSPRITE_ALPHABLEND);//transparent
	D3DXMatrixTransformation2D(&Matrix, NULL, 0.0, &scaling, &spriteCentre, rot, &Translation);
	Spr->SetTransform(&Matrix);
	Spr->Draw(Texture, &r, NULL, NULL, c);
	Spr->End();


}






int LoadBMP(LPCTSTR lpszName) {
	HBITMAP hbm;
	BITMAP bm;
 	D3DFORMAT    Format = D3DFMT_A8R8G8B8;


	if (!g_pd3dDevice) return -1;


	if (Surface)
	{
		Surface->Release();
		Surface = NULL;
	}

	 

	hbm = (HBITMAP)LoadImage(NULL, lpszName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hbm, sizeof(BITMAP), &bm);


	if (hbm == NULL) return 0;

 
	g_pd3dDevice->CreateOffscreenPlainSurface(X, Y, Format, D3DPOOL_SYSTEMMEM, &Surface, NULL);
	 
	D3DXLoadSurfaceFromFile(Surface, NULL, NULL, lpszName, NULL, D3DX_DEFAULT, NULL, NULL);
	 
	bmpr.left = 0;
	bmpr.top = 0;
 
	bmpr.right = X;
	bmpr.bottom = Y;

 

	Point.x = 0;
	Point.y = 0;


	DeleteObject(hbm);

	return 1;

}
//-----------------------------------------------------------------------------
//load image
//-----------------------------------------------------------------------------


HRESULT LoadSprite(char* name, LPD3DXSPRITE& Spr, LPDIRECT3DTEXTURE9& Texture)
{
	if (!g_pd3dDevice) return -1;

	if (Spr) Spr->Release();

	if (Texture)
	{
		Texture->Release();
		Texture = NULL;
	}


	 
	D3DXCreateSprite(g_pd3dDevice, &Spr);

	 
	wchar_t* wideName = MWC(name);
	return D3DXCreateTextureFromFile(g_pd3dDevice, wideName, &Texture);



	return 0;
}

