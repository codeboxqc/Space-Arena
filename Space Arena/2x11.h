#pragma once

#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

// Declare global variables
extern ID3D11Device* g_pd3dDevice;
extern ID3D11DeviceContext* g_pd3dDeviceContext;
extern IDXGISwapChain* g_pSwapChain;

// Function declarations
void InitD3D(HWND hWnd);
void SetViewport();
void Render();

