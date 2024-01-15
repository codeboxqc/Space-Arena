#define WIN32_LEAN_AND_MEAN
#define INITGUID



#include "2x11.h"
#include <wrl/client.h>
#include <sapi.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#pragma comment(lib, "sapi.lib")

HRESULT talko(LPCWSTR ta);





const float PI = 3.14159265358979323846f;
const float DEG_TO_RAD = PI / 180.0f;

void ang360faster(int xo, int yo, int rad, int ang, int& rx, int& ry) {
    float angRad = ang * DEG_TO_RAD;
    rx = xo + static_cast<int>(cosf(angRad) * rad);
    ry = yo + static_cast<int>(sinf(angRad) * rad);
}

void ang360(int xo, int yo, int rad, int ang, int& rx, int& ry) {

 


	rx = xo + cos(ang * 3.14 / 180) * rad;
	ry = yo + sin(ang * 3.14 / 180) * rad;





}

 
int opentxtfiletalk(LPCWSTR ta) {
    std::wifstream file(ta);  // Use 'ta' as the file path

    if (!file.is_open()) {
        
        return 1;
    }

    std::wstringstream buffer;
    buffer << file.rdbuf();

    std::wstring word;
    while (buffer >> word) {
        talko(word.c_str());
         
    }
    return 0;
}
 
 
 

 
HRESULT talk(LPCWSTR ta) {
    std::thread backgroundThread(talko, ta);
    backgroundThread.detach();

}
         

 

HRESULT talko(LPCWSTR ta) {
    ISpVoice* pVoice = NULL;

    if (FAILED(::CoInitialize(NULL))) {
        return E_FAIL;
    }

    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    if (FAILED(hr)) {
        ::CoUninitialize();
        return hr;
    }

    // Set speech synthesis options for a robotic voice
   // pVoice->SetRate(2);      // Adjust rate as needed (higher value for robotic)
    pVoice->SetVolume(100);  // Adjust volume as needed
    

    pVoice->SetRate(-4);
    pVoice->SetOutput(0, TRUE);
    

    // Speak the given text
     hr = pVoice->Speak(ta, 0, NULL);
   // hr = pVoice->Speak(ta, SPF_ASYNC, NULL);

    // Release resources
    pVoice->Release();
    pVoice = NULL;

    ::CoUninitialize();

    return hr;
}