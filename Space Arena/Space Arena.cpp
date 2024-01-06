// Space Arena.cpp : Defines the entry point for the application.
//
#include <Windows.h>
#include "framework.h"
#include "Space Arena.h"

#include "2x11.h"


 
const int X = 1920;
const int Y = 1080;

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hWnd;  // Declare hWnd as a global variable

// Global variable declaration
bool ShouldExit = false;

// Timer variables
LARGE_INTEGER g_frequency;
LARGE_INTEGER g_startTime;
double g_secondsPerCount;


HHOOK g_hKeyboardHook;

// Function to handle user input
void ProcessInput(HWND hWnd) {
    MSG msg;
    while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

 
/// ////////////////////////////////////////////////
 
void StartTimer()
{
    QueryPerformanceFrequency(&g_frequency);
    QueryPerformanceCounter(&g_startTime);

    g_secondsPerCount = 1.0 / static_cast<double>(g_frequency.QuadPart);
}

double GetTime()
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);

    return (currentTime.QuadPart - g_startTime.QuadPart) * g_secondsPerCount;
}
////////////////////////////////////////////////////////

//disable key
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboard = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

        // Check for Alt + Tab
        if (pKeyboard->vkCode == VK_TAB && GetAsyncKeyState(VK_MENU) & 0x8000) {
            return 1; // Block Alt + Tab
        }

        if (pKeyboard->vkCode == VK_F4 && GetAsyncKeyState(VK_MENU) & 0x8000) {
            return 1; // Block Alt + F4
        }

    }

    return CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam);
}



// Message handler function
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            ShouldExit = true; // Set the exit flag
        }
        break;
    case WM_DESTROY:
        ShouldExit = true; // Set the exit flag
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPACEARENA));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;  // Remove the menu reference
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

   // hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        //CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_POPUP, 0, 0, X, Y, nullptr, nullptr, hInstance, nullptr);


    if (!hWnd)
    {
        return FALSE;
    }

    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);


    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


// Rest of your code...

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SPACEARENA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    StartTimer();
    InitD3D(hWnd);


    g_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);



    // Your main loop
    while (true) {
        ProcessInput(hWnd);  // Pass hWnd to handle user input

        
        double deltaTime = GetTime();
        Render( );

     /////////////////////////   
        double targetFrameRate = 60.0;
        double targetFrameTime = 1.0 / targetFrameRate;

        
        double remainingTime = targetFrameTime - deltaTime;
        if (remainingTime > 0) {
            // Sleep for the remaining time to achieve the target frame rate
            Sleep(static_cast<DWORD>(remainingTime * 1000));
        }
     /////////////////////////////////////////////
 
        // Your rendering and game logic code...

        // Check for exit condition (for example, a flag set by the WM_KEYDOWN handler)
        if (ShouldExit) {
            break;
        }
    }

    // Cleanup code...
    UnhookWindowsHookEx(g_hKeyboardHook);
    return 0;
}

















// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
