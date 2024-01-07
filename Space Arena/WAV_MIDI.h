#ifndef WAV_MIDI_H
#define WAV_MIDI_H


#include <windows.h>
#include <dmusici.h> 


class WaveMidi
{
public:

	WaveMidi(HWND);
	~WaveMidi();
	bool LoadSound(const  char* strFileName);
	bool Play(DWORD dwNumOfRepeats);
	//bool Stop();

private:

	IDirectMusicLoader8				*m_pLoader;			 
	IDirectMusicPerformance8		*m_Performance;		 
	IDirectMusicSegment8			*m_pSegment;		
 
};
#endif


