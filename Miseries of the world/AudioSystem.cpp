#include "AudioSystem.h"

AudioSystem::AudioSystem()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_CHANNELS, 2, 2048);
}

AudioSystem::~AudioSystem()
{
	for (auto& i : mMusic)
	{
		if (i.second)
			Mix_FreeMusic(i.second);
	}
	mMusic.clear();
	for (auto& i : mChunk)
	{
		if (i.second)
			Mix_FreeChunk(i.second);
	}
	mChunk.clear();
	Mix_CloseAudio();
}

void AudioSystem::setSound(const Sounds& pType, const PATH& pPathSound)
{
	auto it = mChunk.find(pType);
	if (it == mChunk.end())
		mChunk[pType] = nullptr;
	mChunk[pType] = Mix_LoadWAV(pPathSound.string().c_str());
}

void AudioSystem::setSound(const std::vector<Sounds>& pTypes, const std::vector<PATH>& pPathSounds)
{
	if (pTypes.size() > pPathSounds.size() || pTypes.size() < pPathSounds.size())
	{
		LOG("SMTH BIGGER THAN EXPECTED!");
		return;
	}
	for (size_t i = 0; i < pTypes.size()-1 ; i++)
	{
		auto it = mChunk.find(pTypes[i]);
		if (it == mChunk.end())
			mChunk[pTypes[i]] = nullptr;
		mChunk[pTypes[i]] = Mix_LoadWAV(pPathSounds[i].string().c_str());
	}
}

void AudioSystem::setMusic(const Music& pType, const PATH& pPathMusic)
{
	auto it = mMusic.find(pType);
	if (it == mMusic.end())
		mMusic[pType] = nullptr;
	mMusic[pType] = Mix_LoadMUS(pPathMusic.string().c_str());
}

void AudioSystem::setMusic(const std::vector<Music>& pTypes, const std::vector<PATH>& pPathMusic)
{
	if (pTypes.size() > pPathMusic.size() || pTypes.size() < pPathMusic.size())
	{
		LOG("SMTH BIGGER THAN EXPECTED!");
		return;
	}
	for (size_t i = 0; i < pTypes.size() - 1; i++)
	{
		auto it = mMusic.find(pTypes[i]);
		if (it == mMusic.end())
			mMusic[pTypes[i]] = nullptr;
		mMusic[pTypes[i]] = Mix_LoadMUS(pPathMusic[i].string().c_str());
	}
}

void AudioSystem::setVolumeMusic(const Music& pType, int pVolume)
{
	auto it = mMusic.find(pType);
	if (it == mMusic.end())
	{
		LOG("There is not such a type!");
		return;
	}
	else
		Mix_VolumeMusic(std::clamp(pVolume, 0, 128));
}

void AudioSystem::setVolumeSound(const Sounds& pType, int pVolume)
{
	auto it = mChunk.find(pType);
	if (it == mChunk.end())
	{
		LOG("There is not such a type!");
		return;
	}
	else
		Mix_VolumeChunk(mChunk[pType], std::clamp(pVolume, 0, 128));
}

void AudioSystem::setVolumeForAll(int pVolume)
{
	Mix_Volume(-1, std::clamp(pVolume, 0, 128));
}

void AudioSystem::playSound(const Sounds& pType) const
{
	auto it = mChunk.find(pType);
	if (it == mChunk.end())
	{
		LOG("There is not such a type!");
		return;
	}
	else
		Mix_PlayChannel(-1, it->second, 0);
}

void AudioSystem::playMusic(const Music& pType) const
{
	auto it = mMusic.find(pType);
	if (it == mMusic.end())
	{
		LOG("There is not such a type!");
		return;
	}
	else
		Mix_PlayMusic(it->second, -1);
}

void AudioSystem::stopMusic(const Music& pType) const
{
	auto it = mMusic.find(pType);
	if (it == mMusic.end())
	{
		LOG("There is not such a type!");
		return;
	}
	else
		Mix_PauseMusic();
}

void AudioSystem::stopForAll(int pNumber) const
{
	Mix_PauseAudio(std::clamp(pNumber,0,1));
}
