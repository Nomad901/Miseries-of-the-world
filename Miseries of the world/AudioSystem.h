#pragma once
#include <filesystem>
#include <unordered_map> 

#include <SDL.h>
#include <SDL_mixer.h>

#include "Loging.h"

#define LOG(msg) Loging::log(msg, __FILE__, __LINE__)
#define PATH std::filesystem::path

// extensible. in the future i can implement factory pattern, if i need
// but rn this is an usual audio-system, i dont need to make this overwhelming

enum class Sounds {WALKING, SHOT, TALK, HIT};
enum class Music  {MAIN_MENU,GAME,BOSSFIGHT};

class AudioSystem
{
public:
	AudioSystem();
	~AudioSystem();

	//for one
	void setSound(const Sounds& pType, const PATH& pPathSound);
	//for multiple at once
	void setSound(const std::vector<Sounds>& pTypes, const std::vector<PATH>& pPathSounds);
	//for one
	void setMusic(const Music& pType, const PATH& pPathMusic);
	//for multiple at once
	void setMusic(const std::vector<Music>& pTypes, const std::vector<PATH>& pPathMusic);

	//it can be no less than 0 and no more than 128
	void setVolumeMusic(const Music& pType, int pVolume);
	void setVolumeSound(const Sounds& pType, int pVolume);
	void setVolumeForAll(int pVolume);

	void playSound(const Sounds& pType) const;
	void playMusic(const Music& pType) const;

	void stopMusic(const Music& pType) const;
	//1 - pause, 0 - resume
	void stopForAll(int pNumber) const;

private:
	std::unordered_map<Music, Mix_Music*> mMusic;
	std::unordered_map<Sounds, Mix_Chunk*> mChunk;
};


