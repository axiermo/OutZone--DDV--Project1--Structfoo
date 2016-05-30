#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define MAX_FX 15

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	bool CleanUp();

	Mix_Music* LoadMusic(const char* path);
	Mix_Chunk* LoadFX(const char* path);
	void PlayMusic1(Mix_Music* music);
	void PlayMusic0(Mix_Music* music);
	void ModuleAudio::PlayFX(Mix_Chunk* fx);
	void UnloadAudio();

public:
	Mix_Music* music;
	Mix_Chunk* fx[MAX_FX];
	int last_fx = 0;
};

#endif // __ModuleAudio_H__