#include <iostream>
#include <Windows.h>
#include <thread>
#include <array> 

#include <iostream>

#include "AudioPlayer/Include/Sound.h"

#pragma comment(lib, "AudioPlayer/lib/Audio player.lib")
#pragma comment(lib, "AudioPlayer/lib/Audio player.pdb")


 
 

// Function to be executed in the background thread
DWORD WINAPI BackgroundThread(LPVOID lpParam) {
	// Your background work goes here

	std::string path = "a.wav";
	Sound sound(path);
	sound.play();


	while (sound.getStatut() == Sound::Statut::playing) {
	 
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Adjust as needed
	}

	// You can perform cleanup here if needed

	return 0;
}


int Playwav() {

	 
	 

 
	HANDLE hThread = CreateThread(NULL, 0, BackgroundThread, NULL, 0, NULL);

	if (hThread == NULL) {
		//std::cerr << "Failed to create thread." << std::endl;
		return 1;
	}

	
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	 
	//snd.stop();
	return 0;

} 
 
int test() {
	 
	/*
	 std::string path = "a.wav";
	 Sound sound(path);
	 sound.play();
	 std::this_thread::sleep_for(std::chrono::milliseconds(15));
	 */

	//Sound sfx("../Sound/sfx1.wav")

		// play it
	//	sfx.play();

	// play the file and close when the file stop
	//while (sfx.getStatut() == Sound::Statut::playing) { 
	//}

	//tests("a.wav");
	return 0;
}


/*
void test_Play(std::string path) {
	Sound sound(path);
	sound.play();

	std::this_thread::sleep_for(std::chrono::seconds(15));
}
void test_PauseResume(std::string path) {
	Sound sound(path);
	sound.play();

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	sound.pause();
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	sound.resume();
	std::this_thread::sleep_for(std::chrono::milliseconds(15));

	std::this_thread::sleep_for(std::chrono::seconds(5));
}
void test_MultiPlay(std::string path) {
	Sound sound(path);
	sound.play();
	std::this_thread::sleep_for(std::chrono::milliseconds(6000));
	sound.play();

	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}
void test_Stop(std::string path) {
	Sound sound(path);
	sound.play();

	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	sound.stop();

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
void test_Volume(std::string path) {
	Sound sound(path);
	sound.setVolume(10.f);
	sound.play();
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	sound.setVolume(50.f);
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	sound.setVolume(25.f);

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}
void test_Speed(std::string path) {
	Sound sound(path);
	sound.play();
	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	sound.setSpeed(125.f);

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}
void test_Duration(std::string path) {
	Sound sound(path);
	std::cout << "Total play time : " << sound.getAudioDuration() << std::endl;
}
void test_CurrentPlaytime(std::string path) {
	Sound sound(path);
	sound.play();
	std::cout << "wait ~ 3.5 sec " << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(3500));
	std::cout << "Current play time : " << sound.getAudioTime() << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	sound.stop();
}
void test_SetAudioTime(std::string path) {
	Sound sound(path);
	sound.play();

	std::cout << "set time to middle" << std::endl;
	sound.setAudioTime(std::chrono::seconds(static_cast<int>(sound.getAudioDuration() / 2.0)));
	std::cout << "Time : " << sound.getAudioTime() << " / " << sound.getAudioDuration() << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

}
void test_Looping(std::string path) {
	Sound sound(path);
	sound.play();
	sound.setLooping(true);

	std::this_thread::sleep_for(std::chrono::seconds(int(sound.getAudioDuration()) + 10));
}
void test_3D(std::string path) {
	Sound sound(path);
	sound.enable3D(true);
	sound.setPosition(-100.f, 15.f, 0.f);
	sound.play();

	while (sound.getPosition().x < 100) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		sound.movePosition(1.f, 0.f, 0.f);
	}
}
void test_SubMixer(std::string path) {
	Audio_System::addSubMixer("Custom1");
	Sound sound(path);
	sound.setMixer("CUSTOM1");
	sound.play();

	while (Audio_System::getSubMixerVolume("custom1") > 1.f) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		Audio_System::setSubMixerVolume("custom1", Audio_System::getSubMixerVolume("custom1") - 1.f);
	}
}
void test_SubMixer3D(std::string path) {
	Audio_System::setSubMixerVolume("Custom1", 100.f);
	Sound sound(path);
	sound.setPosition(-25.f, 15.f, 0.f);
	sound.setMixer("CUSTOM1");
	sound.play();

	while (Audio_System::getSubMixerVolume("custom1") > 1.f) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		Audio_System::setSubMixerVolume("custom1", Audio_System::getSubMixerVolume("custom1") - 1.f);
	}
}
void test_Reverb(std::string path) {
	Sound sound(path);
	sound.setReverb(Sound::Reverb::Concerthall);
	sound.play();

	std::this_thread::sleep_for(std::chrono::seconds(15));
}



const XAUDIO2FX_REVERB_I3DL2_PARAMETERS& getReverbFromID(int id) {
	int trueID = id % 30;

	switch (trueID)
	{
	case 0: return Sound::Reverb::Default; break;
	case 1: return Sound::Reverb::Generic; break;
	case 2: return Sound::Reverb::Paddedcell; break;
	case 3: return Sound::Reverb::Room; break;
	case 4: return Sound::Reverb::Bathroom; break;
	case 5: return Sound::Reverb::Livingroom; break;
	case 6: return Sound::Reverb::Stoneroom; break;
	case 7: return Sound::Reverb::Auditorium; break;
	case 8: return Sound::Reverb::Concerthall; break;
	case 9: return Sound::Reverb::Cave; break;
	case 10: return Sound::Reverb::Arena; break;
	case 11: return Sound::Reverb::Hangar; break;
	case 12: return Sound::Reverb::Carpetedhallway; break;
	case 13: return Sound::Reverb::Hallway; break;
	case 14: return Sound::Reverb::Stonecorridor; break;
	case 15: return Sound::Reverb::Alley; break;
	case 16: return Sound::Reverb::Forest; break;
	case 17: return Sound::Reverb::City; break;
	case 18: return Sound::Reverb::Mountains; break;
	case 19: return Sound::Reverb::Quarry; break;
	case 20: return Sound::Reverb::Plain; break;
	case 21: return Sound::Reverb::Parkinglot; break;
	case 22: return Sound::Reverb::Sewerpipe; break;
	case 23: return Sound::Reverb::Underwater; break;
	case 24: return Sound::Reverb::Smallroom; break;
	case 25: return Sound::Reverb::Mediumroom; break;
	case 26: return Sound::Reverb::Largeroom; break;
	case 27: return Sound::Reverb::Mediumhall; break;
	case 28: return Sound::Reverb::Largehall; break;
	case 29: return Sound::Reverb::Plate; break;
	}

	return Sound::Reverb::Default;
}

std::string nameOfReverbFromID(int id) {
	int trueID = id % 30;

	switch (trueID)
	{
	case 0: return "Default / none"; break;
	case 1: return "Generic"; break;
	case 2: return "Padded cell"; break;
	case 3: return "Room"; break;
	case 4: return "Bathroom"; break;
	case 5: return "Living room"; break;
	case 6: return "Stone room"; break;
	case 7: return "Auditorium"; break;
	case 8: return "Concert hall"; break;
	case 9: return "Cave"; break;
	case 10: return "Arena"; break;
	case 11: return "Hangar"; break;
	case 12: return "Carpeted hallway"; break;
	case 13: return "Hallway"; break;
	case 14: return "Stone corridor"; break;
	case 15: return "Alley"; break;
	case 16: return "Forest"; break;
	case 17: return "City"; break;
	case 18: return "Mountains"; break;
	case 19: return "Quarry"; break;
	case 20: return "Plain"; break;
	case 21: return "Parking lot"; break;
	case 22: return "Sewer pipe"; break;
	case 23: return "Underwater"; break;
	case 24: return "Small room"; break;
	case 25: return "Medium room"; break;
	case 26: return "Larger room"; break;
	case 27: return "Medium hall"; break;
	case 28: return "Large hall"; break;
	case 29: return "Plate"; break;
	}

	return "Default / none";
}

bool Controles(Sound& Emitter, bool& quit, int& m_reverb) {
	bool change = false;

	if (GetKeyState(VK_ESCAPE) & 0x8000) {
		quit = true;
		return false;
	}

	// Position controles
	{
		float addX = 0.f;
		float addY = 0.f;
		float addZ = 0.f;

		//auto actual = Audio_System::getListenerForwad();

		if (GetKeyState('A') & 0x8000) {
			addX -= 1;
		}

		if (GetKeyState('W') & 0x8000) {
			addY -= 1;
		}

		if (GetKeyState('D') & 0x8000) {
			addX += 1;
		}

		if (GetKeyState('S') & 0x8000) {
			addY += 1;
		}

		if (addX != 0 || addY != 0 || addZ != 0) {
			Audio_System::moveListenerPosition(addX, addY, addZ);
			change = true;
		}
	}

	// Orientation Controles
	{
		if (GetKeyState(VK_LEFT) & 0x8000) {
			Audio_System::setListenerForward(1, 0, 0);
			change = true;
		}

		if (GetKeyState(VK_UP) & 0x8000) {
			Audio_System::setListenerForward(0, 1, 0);
			change = true;
		}

		if (GetKeyState(VK_RIGHT) & 0x8000) {
			Audio_System::setListenerForward(-1, 0, 0);
			change = true;
		}

		if (GetKeyState(VK_DOWN) & 0x8000) {
			Audio_System::setListenerForward(0, -1, 0);
			change = true;
		}
	}

	// Reverb Controles
	{
		if (GetKeyState(VK_ADD) & 0x8000) {
			if (m_reverb < MAXINT) {
				Emitter.setReverb(getReverbFromID(++m_reverb));
			}
			change = true;
		}

		if (GetKeyState(VK_SUBTRACT) & 0x8000) {
			if (m_reverb > 0) {
				Emitter.setReverb(getReverbFromID(--m_reverb));
			}
			change = true;
		}
	}

	return change;
}

void PrintInfos(Sound& Emitter, const int m_reverb) {
	 

	for (int y = 0; y < 25; y++) {

		if (y == 20) {
			std::cout << "Y\t\t";
		}
		else if (y == 21) {
			std::cout << "^\t\t";
		}
		else if (y == 22 || y == 23) {
			std::cout << "|\t\t";
		}
		else if (y == 24) {
			std::cout << " ---> X\t\t";
		}
		else {
			std::cout << "\t\t";
		}


		for (int x = 0; x < 25; x++) {

			if (Audio_System::getListenerPosition().x == x && Audio_System::getListenerPosition().y == y) {
				auto forward = Audio_System::getListenerForward();

				if (forward.x == 1 && forward.y == 0) {
					std::cout << "< ";
				}
				else if (forward.x == 0 && forward.y == 1) {
					std::cout << "^ ";
				}
				else if (forward.x == -1 && forward.y == 0) {
					std::cout << "> ";
				}
				else if (forward.x == 0 && forward.y == -1) {
					std::cout << "v ";
				}
				else {
					std::cout << "? ";
				}

			}
			else if (Emitter.getPosition().x == x && Emitter.getPosition().y == y) {
				std::cout << "o ";
			}
			else {
				std::cout << ". ";
			}
		}


		if (y == 0) {
			std::cout << "\t\t\t Position ";
		}
		else if (y == 1) {
			std::cout << "\t\t\t x : " << Audio_System::getListenerPosition().x;
		}
		else if (y == 2) {
			std::cout << "\t\t\t y : " << Audio_System::getListenerPosition().y;
		}

		else if (y == 4) {
			std::cout << "\t\t\t Forward ";
		}
		else if (y == 5) {
			std::cout << "\t\t\t x : " << Audio_System::getListenerForward().x;
		}
		else if (y == 6) {
			std::cout << "\t\t\t y : " << Audio_System::getListenerForward().y;
		}
		else if (y == 7) {
			std::cout << "\t\t\t z : " << Audio_System::getListenerForward().z;
		}

		else if (y == 9) {
			std::cout << "\t\t\t Misc ";
		}
		else if (y == 10) {
			std::cout << "\t\t\t Left : " << Emitter.getDSPInfos().pMatrixCoefficients[0];
		}
		else if (y == 11) {
			std::cout << "\t\t\t Right : " << Emitter.getDSPInfos().pMatrixCoefficients[1];
		}
		else if (y == 12) {
			std::cout << "\t\t\t reverb type : " << nameOfReverbFromID(m_reverb);
		}
		else if (y == 13) {
			std::cout << "\t\t\t reverb Level : " << Emitter.getDSPInfos().ReverbLevel;
		}

		else if (y == 15) {
			std::cout << "\t\t\t Controles ";
		}
		else if (y == 16) {
			std::cout << "\t\t\t Move : w a s d keys";
		}
		else if (y == 17) {
			std::cout << "\t\t\t Orientation : Arrow keys";
		}
		else if (y == 18) {
			std::cout << "\t\t\t Reverb : Add / Subtract";
		}

		std::cout << "\n";
	}
}
 


void tests(std::string SoundPath)
{
	Audio_System::setListenerOrientation({ 0, 1, 0 }, { 0, 0, -1 });
	Audio_System::setMasterVolume(100.f);


	std::cout << "Test : play\n";
	test_Play(SoundPath);


	std::cout << "Test : Pause and resume\n";
	test_PauseResume(SoundPath);


	std::cout << "Test : Multi play\n";
	test_MultiPlay(SoundPath);


	std::cout << "Test : Stop\n";
	test_Stop(SoundPath);


	std::cout << "Test : Volume\n";
	test_Volume(SoundPath);


	std::cout << "Test : Speed\n";
	test_Speed(SoundPath);


	std::cout << "Test : Duration\n";
	test_Duration(SoundPath);


	std::cout << "Test : Current play time\n";
	test_CurrentPlaytime(SoundPath);


	std::cout << "Test : Set audio time\n";
	test_SetAudioTime(SoundPath);


	std::cout << "Test : Looping\n";
	test_Looping(SoundPath);


	std::cout << "Test : 3D\n";
	test_3D(SoundPath);


	std::cout << "Test : Submixer\n";
	test_SubMixer(SoundPath);


	std::cout << "Test : Submixer3D\n";
	test_SubMixer3D(SoundPath);

	std::cout << "Test : Reverb\n";
	test_Reverb(SoundPath);
}

*/