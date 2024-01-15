
#define WIN32_LEAN_AND_MEAN
#define INITGUID



#include "2x11.h"

 



/*
PALETTEENTRY g_PaletteEntries[256];

// Function to initialize the palette
void InitPalette()
{
    for (int i = 0; i < 256; ++i)
    {
        g_PaletteEntries[i].peRed = i;
        g_PaletteEntries[i].peGreen = 0;
        g_PaletteEntries[i].peBlue = 0;
        g_PaletteEntries[i].peFlags = PC_NOCOLLAPSE;
    }

    SetPalette();
}

// Function to set the palette
void SetPalette()
{
    g_pd3dDevice->SetPaletteEntries(0, g_PaletteEntries);
    g_pd3dDevice->SetCurrentTexturePalette(0);
}

// Function to fade in colors using palette
void FadeInColorsPalette(int speed)
{
    for (int i = 0; i <= 255; i += speed)
    {
        for (int j = 0; j <= i; ++j)
        {
            g_PaletteEntries[j].peRed = i;
        }
        SetPalette();
        Render();
    }
}

// Function to fade out colors using palette
void FadeOutColorsPalette(int speed)
{
    for (int i = 255; i >= 0; i -= speed)
    {
        for (int j = i; j < 256; ++j)
        {
            g_PaletteEntries[j].peRed = i;
        }
        SetPalette();
        Render();
    }
}

// Function to flash colors using palette
void FlashColorsPalette(int duration, int speed)
{
    for (int i = 0; i < duration; i++)
    {
        for (int j = 0; j <= 255; ++j)
        {
            g_PaletteEntries[j].peRed = 255;
        }
        SetPalette();
        Render();
        Sleep(speed);
        for (int j = 0; j <= 255; ++j)
        {
            g_PaletteEntries[j].peRed = 0;
        }
        SetPalette();
        Render();
        Sleep(speed);
    }
}

// Function to change all colors to red using palette
void ChangeToRedPalette()
{
    for (int i = 0; i <= 255; ++i)
    {
        g_PaletteEntries[i].peRed = 255;
    }
    SetPalette();
    Render();
}
*/