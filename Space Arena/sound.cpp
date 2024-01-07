
#define WIN32_LEAN_AND_MEAN // include tous les macros

#define INITGUID            // include tous les GUIDs

#include <windows.h>        
 
#include <mmsystem.h>
#include <dsound.h>

 
#pragma comment ( lib, "dsound.lib" )
#pragma comment(lib, "WINMM.LIB")

 
#include <Windows.h>
#include <mmsystem.h>
#include <vector>

// Function to load a WAV file into memory using WINMM.LIB
void LoadWavIntoMemory(const char* filename, BYTE*& audioData, DWORD& dataSize) {
    MMIOINFO mmioInfo = { 0 };
    HMMIO hFile = mmioOpenA(const_cast<LPSTR>(filename), &mmioInfo, MMIO_READ);

    if (hFile == NULL) {
        // Handle file opening error
        return;
    }

    // Get the size of the WAV file
    dataSize = mmioInfo.adwInfo[0];

    // Allocate memory for audio data
    audioData = new BYTE[dataSize];

    // Read the WAV file into memory
    if (mmioRead(hFile, reinterpret_cast<HPSTR>(audioData), dataSize) != dataSize) {
        // Handle read error
        delete[] audioData;
        audioData = nullptr;
        dataSize = 0;
    }

    // Close the file handle
    mmioClose(hFile, 0);
}

// Function to play audio asynchronously
void PlayAudioAsync(BYTE* audioData, DWORD dataSize, HWAVEOUT& hWaveOut, WAVEHDR& waveHeader) {
    WAVEFORMATEX waveFormat = { 0 };
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nChannels = 2;               // Stereo
    waveFormat.nSamplesPerSec = 44100;      // Sample rate
    waveFormat.wBitsPerSample = 16;         // Bits per sample
    waveFormat.nBlockAlign = waveFormat.nChannels * waveFormat.wBitsPerSample / 8;
    waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

    MMRESULT result = waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, CALLBACK_NULL);

    if (result != MMSYSERR_NOERROR) {
        // Handle waveOutOpen error
        return;
    }

    waveHeader.lpData = reinterpret_cast<LPSTR>(audioData);
    waveHeader.dwBufferLength = dataSize;

    result = waveOutPrepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR));

    if (result != MMSYSERR_NOERROR) {
        // Handle waveOutPrepareHeader error
        waveOutClose(hWaveOut);
        return;
    }

    result = waveOutWrite(hWaveOut, &waveHeader, sizeof(WAVEHDR));

    if (result != MMSYSERR_NOERROR) {
        // Handle waveOutWrite error
        waveOutUnprepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR));
        waveOutClose(hWaveOut);
        return;
    }
}

int test() {
    BYTE* wavData1;
    DWORD wavSize1;
    BYTE* wavData2;
    DWORD wavSize2;

    LoadWavIntoMemory("example1.wav", wavData1, wavSize1);
    LoadWavIntoMemory("example2.wav", wavData2, wavSize2);

    if (wavData1 != nullptr && wavData2 != nullptr) {
        // Play the first WAV file asynchronously
        HWAVEOUT hWaveOut1;
        WAVEHDR waveHeader1 = { 0 };
        PlayAudioAsync(wavData1, wavSize1, hWaveOut1, waveHeader1);

        // Play the second WAV file asynchronously
        HWAVEOUT hWaveOut2;
        WAVEHDR waveHeader2 = { 0 };
        PlayAudioAsync(wavData2, wavSize2, hWaveOut2, waveHeader2);

        // Use wavData1 and wavData2 for further processing if needed
        // ...

        // Wait for both playback instances to finish (or implement more sophisticated synchronization)
        while (waveHeader1.dwFlags & WHDR_DONE == 0 || waveHeader2.dwFlags & WHDR_DONE == 0) {
            Sleep(100);
        }

        // Cleanup for the first playback instance
        waveOutUnprepareHeader(hWaveOut1, &waveHeader1, sizeof(WAVEHDR));
        waveOutClose(hWaveOut1);

        // Cleanup for the second playback instance
        waveOutUnprepareHeader(hWaveOut2, &waveHeader2, sizeof(WAVEHDR));
        waveOutClose(hWaveOut2);

        // Don't forget to delete the allocated memory when done
        delete[] wavData1;
        delete[] wavData2;
    }

    return 0;
}
