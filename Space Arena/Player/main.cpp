#include "Player.h"

void main()
{
	std::string e;
	std::string s;
	//std::cin >> s;


	s= "a.wav";
	printf("0");

	Sound sound;
	Player player;

	printf("1");

	if (!player.Create()) {
		printf("player.Create");  return;
	}
	if (!sound.LoadFromFile(s)) {
		printf("sound.LoadFromFile");  return;
	}
	if (!player.SetSound(sound)) {
		printf("player.SetSound");  return;
	}

	printf("2");
	player.Play();

	printf("3");

	do
	{
		std::cin >> e;
	} 
	while (e != "exit");
}