#include "Sound.h"

bool Sound::ForeMuted = false;
bool Sound::BackMuted = false;
int Sound::ForeVolume = 64;
int Sound::BackVolume = 64;

Sound::Sound(std::string name, bool Fore)
{
	Fore = Fore;
	Track = ResourceManager::GetSound(name);
}
Sound::~Sound()
{
	if (Playing)
	{
		Stop();
	}
}

void Sound::PlayOnce()
{
	if (!((Fore) ? ForeMuted : BackMuted))
	{
		Mix_Volume(Mix_PlayChannel(-1, Track, 0), (Fore) ? ForeVolume : BackVolume);
	}
}

void Sound::Play()
{
	if (!Playing && !((Fore) ? ForeMuted : BackMuted))
	{
		Mix_VolumeChunk(Track, (Fore)?ForeVolume:BackVolume);
		Channel = Mix_PlayChannel(-1, Track, -1);
		Mix_Volume(Channel, (Fore) ? ForeVolume : BackVolume);
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