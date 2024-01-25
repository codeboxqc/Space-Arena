#include <windows.h>
#include <dmusici.h>
#include <dshow.h>


#include <xaudio2.h>


//#define DIRECTINPUT_VERSION 0x800
#include <dsound.h>
#include <ddraw.h>        
#pragma comment(lib, "ddraw.LIB")
#pragma comment ( lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")


class CMP3
{
public:

	CMP3();
	~CMP3();
	bool PlayMp3(const char* szSoundFileName);
	bool Pause();
	bool Run();
	bool Stop();
	bool State();


private:

	IGraphBuilder* m_pGraph;
	IMediaControl* m_pMediaControl;
	IMediaPosition* m_pMediaPosition;

	IDirectMusicLoader8* m_pLoader;
	IDirectMusicPerformance8* m_Performance;
	IDirectMusicSegment8* m_pSegment;

};






CMP3::CMP3()
{

	CoInitialize(NULL);

	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
		IID_IGraphBuilder, (void**)&m_pGraph);

	m_pGraph->QueryInterface(IID_IMediaControl, (void**)&m_pMediaControl);

	m_pGraph->QueryInterface(IID_IMediaPosition, (void**)&m_pMediaPosition);

}

CMP3::~CMP3()
{
	m_pMediaControl->Stop();
	m_pMediaControl->Release();
	m_pMediaPosition->Release();
	m_pGraph->Release();
	CoUninitialize();

}




/////////////////////////////////////////////////////////////////
bool CMP3::PlayMp3(const char* szSoundFileName)
{

	WCHAR wstrSoundPath[MAX_PATH];


	MultiByteToWideChar(CP_ACP, 0, szSoundFileName, -1, wstrSoundPath, MAX_PATH);

	m_pGraph->RenderFile(wstrSoundPath, NULL);

	m_pMediaPosition->put_CurrentPosition(0);

	m_pMediaControl->Run();

	return true;

}
/////////////////////////////////////////////////////////

bool CMP3::Run()
{

	m_pMediaControl->Run();

	return true;

}

bool CMP3::Pause()
{

	m_pMediaControl->Pause();

	return true;

}

//////////////////


bool CMP3::State()
{
	FILTER_STATE fs;

	HRESULT hr = m_pMediaControl->GetState(INFINITE, (OAFilterState*)&fs);


	return hr;

}


bool CMP3::Stop()
{

	m_pMediaControl->Stop();


	return true;

}

 


int playmidi(const char* filename) {
     
	CMP3 *one;
     
	
	//one = new CMP3();
 	//one->PlayMp3("a.mp3");
	//one->Run();


	 

    return 0;
}


//===============================================
/*
class CMIDI
{
public:
    CMIDI();
    ~CMIDI();
    bool PlayMIDI(const char* szMIDIFileName);
    bool Stop();

private:
    IDirectMusicLoader8* m_pLoader;
    IDirectMusicPerformance8* m_Performance;
    IDirectMusicSegment8* m_pSegment;
};

CMIDI::CMIDI()
{
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    CoCreateInstance(CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC,
        Severity	Code	Description	Project	File	Line	Suppression State	Details
Error	LNK2001	unresolved external symbol IID_IDirectMusicLoader8	Space Arena	F:\c-2024\Space Arena\Space Arena\midi.obj	1		
Error	LNK2001	unresolved external symbol CLSID_DirectMusicSegment	Space Arena	F:\c-2024\Space Arena\Space Arena\midi.obj	1		
Error	LNK2001	unresolved external symbol IID_IDirectMusicSegment8	Space Arena	F:\c-2024\Space Arena\Space Arena\midi.obj	1		
Error	LNK2001	unresolved external symbol CLSID_DirectMusicLoader	Space Arena	F:\c-2024\Space Arena\Space Arena\midi.obj	1		
Error	LNK2001	unresolved external symbol IID_IDirectMusicPerformance8	Space Arena	F:\c-2024\Space Arena\Space Arena\midi.obj	1		
Error	LNK2001	unresolved external symbol CLSID_DirectMusicPerformance	Space Arena	F:\c-2024\Space Arena\Space Arena\midi.obj	1		
, (void**)&m_pLoader);

    CoCreateInstance(CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC,
        IID_IDirectMusicPerformance8, (void**)&m_Performance);

    m_Performance->InitAudio(NULL, NULL, NULL, DMUS_APATH_SHARED_STEREOPLUSREVERB, 64, DMUS_AUDIOF_ALL, NULL);
    m_Performance->AddPort(NULL);
}

CMIDI::~CMIDI()
{
    Stop();

    if (m_pLoader)
    {
        m_pLoader->Release();
    }

    if (m_Performance)
    {
        m_Performance->CloseDown();
        m_Performance->Release();
    }

    CoUninitialize();
}

bool CMIDI::PlayMIDI(const char* szMIDIFileName)
{
    WCHAR wstrMIDIPath[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, szMIDIFileName, -1, wstrMIDIPath, MAX_PATH);

    m_pLoader->LoadObjectFromFile(CLSID_DirectMusicSegment, IID_IDirectMusicSegment8, wstrMIDIPath, (LPVOID*)&m_pSegment);
    m_Performance->PlaySegment(m_pSegment, 0, 0, NULL);

    return true;
}

bool CMIDI::Stop()
{
    if (m_pSegment)
    {
        m_pSegment->Release();
        m_pSegment = nullptr;
    }

    return true;
}

int playmidi(const char* filename) {
    CMIDI* midiPlayer = new CMIDI();
    midiPlayer->PlayMIDI(filename);

    // You can add a delay here or use some mechanism to keep the program running
    // while the MIDI plays, or you can implement a message loop if needed.

    // For example:
    // Sleep(5000); // Sleep for 5 seconds
    // midiPlayer->Stop();

    delete midiPlayer;

    return 0;
}

*/