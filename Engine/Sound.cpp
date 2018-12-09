#include "Sound.h"

int Sound::Volume = 64;

Sound::Sound(std::string name)
{
	Track = LoaderTool::SoundDict[name];
}

Sound::~Sound()
{
	Mix_FreeChunk(Track);
}

void Sound::PlayOnce()
{
	Mix_PlayChannel(-1, Track, 0);
}

void Sound::Play()
{
	if (!Playing)
	{
		Mix_VolumeChunk(Track, Sound::Volume);
		Channel = Mix_PlayChannel(-1, Track, -1);
		Debug::Log("Playing sound on channel " + std::to_string(Channel));
		Playing = true;
	}
}
void Sound::Stop()
{
	if (Playing)
	{
		Debug::Log("Expiring channel " + std::to_string(Channel));
		Mix_ExpireChannel(Channel, 1);
		Playing = false;
	}
}