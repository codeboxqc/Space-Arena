#include "2x11.h"

 /*
#include <DirectXTex.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "uuid.lib")

// Function to initialize DirectX 11
// Define your global variables

ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
ID3D11Texture2D* g_pOffScreenTexture = nullptr;
ID3D11RenderTargetView* g_pOffScreenRenderTargetView = nullptr;

ID3D11Texture2D* pBackBuffer = nullptr;
ID3D11ShaderResourceView* pTexture = nullptr;


void InitD3D(HWND hWnd) {
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = X;
    swapChainDesc.BufferDesc.Height = Y;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = FALSE;  // Set to FALSE for full-screen

    // Create device, swap chain, and off-screen texture
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

    // Create render target view for the back buffer
    if (pBackBuffer) {
        g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);
        pBackBuffer->Release();
    }
    else {
        // Handle the error or log a message that the back buffer retrieval failed
    }

    // Create off-screen texture and render target view
    D3D11_TEXTURE2D_DESC textureDesc = {};
    textureDesc.Width = X;
    textureDesc.Height = Y;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET;

    g_pd3dDevice->CreateTexture2D(&textureDesc, nullptr, &g_pOffScreenTexture);
    g_pd3dDevice->CreateRenderTargetView(g_pOffScreenTexture, nullptr, &g_pOffScreenRenderTargetView);

    ///////////////test

    LoadImage(g_pd3dDevice, L"a1.png", pTexture);
    imax(g_pd3dDeviceContext, pTexture, 10, 10, 128, 128, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
    pTexture->Release(); // Release the shader resource view
}


// Set up the viewport
void SetViewport() {
    D3D11_VIEWPORT viewport = { 0.0f, 0.0f, 1920.0f, 1080.0f, 0.0f, 1.0f };
    g_pd3dDeviceContext->RSSetViewports(1, &viewport);
}

// Rendering loop
// Rendering loop
void Render() {
    // Render to off-screen buffer
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_pOffScreenRenderTargetView, nullptr);

    // Render your game here...

    // Reset render targets to back buffer
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_pRenderTargetView, nullptr);

    imax(g_pd3dDeviceContext, pTexture, 10, 10, 128, 128, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

    // Copy from off-screen buffer to back buffer without clearing
    g_pd3dDeviceContext->CopyResource(pBackBuffer, g_pOffScreenTexture);

    // Release the shader resource view after using it
    // (do not release it immediately after imax)
    // pTexture->Release();

    // Present the frame
    g_pSwapChain->Present(1, 0);
}


/////////////////////////////////

HRESULT LoadImage(ID3D11Device* pd3dDevice, const wchar_t* filename, ID3D11ShaderResourceView*& pTexture)
{
    if (!pd3dDevice)
        return E_INVALIDARG;

    if (pTexture)
    {
        pTexture->Release();
        pTexture = nullptr;
    }

    // Load the image using DirectXTex
    DirectX::TexMetadata metadata;
    DirectX::ScratchImage scratchImage;
    HRESULT hr = DirectX::LoadFromWICFile(filename, DirectX::WIC_FLAGS_NONE, &metadata, scratchImage);

    if (SUCCEEDED(hr))
    {
        // Create a texture from the loaded image
        hr = DirectX::CreateShaderResourceView(pd3dDevice, scratchImage.GetImages(), scratchImage.GetImageCount(), metadata, &pTexture);
    }

    return hr;
}

////////////////////////////////

void imax(ID3D11DeviceContext* pd3dDeviceContext, ID3D11ShaderResourceView* pTexture, int x, int y, int xx, int yy, DirectX::XMFLOAT4 color)
{
    // Define the region to copy from (off-screen texture)
    D3D11_BOX sourceRegion;
    sourceRegion.left = 0;
    sourceRegion.top = 0;
    sourceRegion.front = 0;
    sourceRegion.right = xx;
    sourceRegion.bottom = yy;
    sourceRegion.back = 1;

    // Define the destination region on the back buffer
    D3D11_BOX destRegion;
    destRegion.left = x;
    destRegion.top = y;
    destRegion.front = 0;
    destRegion.right = x + xx;
    destRegion.bottom = y + yy;
    destRegion.back = 1;

    // Copy the texture data from the off-screen texture to the back buffer
    pd3dDeviceContext->CopySubresourceRegion(pBackBuffer, 0, x, y, 0, g_pOffScreenTexture, 0, &sourceRegion);

    // Optionally, release the shader resource view after the copy (not immediately)
    // pTexture->Release(); // Comment or remove this line
}

*/