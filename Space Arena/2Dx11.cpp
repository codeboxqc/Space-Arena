 #include "2x11.h"


#pragma comment(lib, "d3d11.lib")

// Function to initialize DirectX 11
// Define your global variables
ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;

void InitD3D(HWND hWnd) {
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = 1920;
    swapChainDesc.BufferDesc.Height = 1080;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = FALSE;  // Set to FALSE for full-screen

    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &g_pSwapChain,
        &g_pd3dDevice,
        nullptr,
        &g_pd3dDeviceContext
    );

    ID3D11Texture2D* pBackBuffer = nullptr;
    g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));

    if (pBackBuffer) {
        g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);
        pBackBuffer->Release();
    }
    else {
        // Handle the error or log a message that the back buffer retrieval failed
    }
}


// Set up the viewport
void SetViewport() {
    D3D11_VIEWPORT viewport = { 0.0f, 0.0f, 1920.0f, 1080.0f, 0.0f, 1.0f };
    g_pd3dDeviceContext->RSSetViewports(1, &viewport);
}

// Rendering loop
void Render() {
    // Clear the back buffer with a black color
    float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };  // Black background
    g_pd3dDeviceContext->ClearRenderTargetView(g_pRenderTargetView, clearColor);

    // Render your game here...

    // Present the frame
    g_pSwapChain->Present(1, 0);
}
