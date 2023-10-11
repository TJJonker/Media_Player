#include "pch.h"
#include "AudioPlayer.h"
#include "Channel.h"

namespace TwoTune {
	AudioPlayer::AudioPlayer(FMOD::System* system)
		: m_System(system) { }

	AudioPlayer::~AudioPlayer() { }

	void AudioPlayer::Play(FMOD::Sound* sound, Channel* channel, FMOD::ChannelGroup* group)
	{
		CHECK_NULL_LOG(sound, "play");
		FMOD_RESULT result = m_System->playSound(sound, group, channel->IsPaused, &channel->FMODChannel);

		CHECK_RESULT_LOG(result, "Playing sound");
	}

	void AudioPlayer::Stop(Channel* channel)
	{
		CHECK_NULL_LOG(channel, "Stop");
		CHECK_ISPLAYING(channel->FMODChannel);

		FMOD_RESULT result = channel->FMODChannel->stop();
		CHECK_RESULT_LOG(result, "Stopping channel");
	}

	void AudioPlayer::SetPaused(Channel* channel)
	{
		CHECK_NULL_LOG(channel, "Pause");
		CHECK_ISPLAYING(channel->FMODChannel);

		FMOD_RESULT result = channel->FMODChannel->setPaused(channel->IsPaused);
		CHECK_RESULT_LOG(result, "Pausing channel");
	}
}
