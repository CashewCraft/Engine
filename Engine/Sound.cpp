#include "Sound.h"

int Sound::Volume = 64;

Sound::Sound(std::string name)
{
	Track = ResourceManager::GetSound(name);
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
		Debug::Flag("Playing sound on channel " + std::to_string(Channel));
		Playing = true;
	}
}
void Sound::Stop()
{
	if (Playing)
	{
		Debug::Flag("Expiring channel " + std::to_string(Channel));
		Mix_ExpireChannel(Channel, 1);
		Playing = false;
	}
}