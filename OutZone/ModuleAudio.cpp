#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

ModuleAudio::ModuleAudio() : Module()
{
	music = nullptr;

	for (uint i = 0; i < MAX_FX; ++i)
		fx[i] = nullptr;

}

// Destructor
ModuleAudio::~ModuleAudio()
{}

bool ModuleAudio::Init()
{
	bool ret = true;

	Mix_Init(MIX_INIT_OGG);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, 2, 1024);

	return ret;
}

bool ModuleAudio::CleanUp()
{
	LOG("Freeing sounds and Mixer library");

	Mix_FreeMusic(music);

	
	for (uint i = 0; i < MAX_FX; ++i)
		if (fx[i] != nullptr)
			Mix_FreeChunk(fx[i]);
	

	Mix_CloseAudio();
	Mix_Quit();
	return true;
}


Mix_Music* ModuleAudio::Load(const char* path)
{
	Mix_Music* music = Mix_LoadMUS(path);

	if (music == NULL)
	{
		LOG("Error playing the music");
	}
	else
	{
		while (!Mix_FadeOutMusic(700) && Mix_PlayingMusic()) {
			SDL_Delay(0);
		}
		Mix_PlayMusic(music, -1);
		return music;
	}
}

