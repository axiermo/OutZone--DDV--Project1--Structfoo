#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

ModuleAudio::ModuleAudio() : Module()
{
	music = nullptr;

	for (uint i = 0; i < MAX_FX; ++i)
		fx[i] = nullptr;

}

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
	LOG("Closing sounds and Mixer library");

	Mix_CloseAudio();
	Mix_Quit();
	return true;
}


Mix_Music* ModuleAudio::LoadMusic(const char* path)
{
	music = Mix_LoadMUS(path);

	return music;
}

Mix_Chunk* ModuleAudio::LoadFX(const char* path)
{
	fx[last_fx] = Mix_LoadWAV(path);

	return fx[last_fx];
}

void ModuleAudio::UnloadAudio()
{
	Mix_FreeMusic(music);

	for (uint i = 0; i < MAX_FX; ++i)
	if (fx[i] != nullptr)
		Mix_FreeChunk(fx[i]);

	last_fx = 0;
}

void ModuleAudio::PlayFX(Mix_Chunk* fx)
{
	if (fx == NULL)
	{
		LOG("Error playing the music");
	}
	else
	{
		Mix_PlayChannel(-1, fx, 0);
	}
}

void ModuleAudio::PlayMusic(Mix_Music* music)
{
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
	}
}
