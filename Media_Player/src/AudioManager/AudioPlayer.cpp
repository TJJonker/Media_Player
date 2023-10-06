#include "pch.h"
#include "AudioPlayer.h"
#include "Channel.h"

namespace TwoTune {
	AudioPlayer::AudioPlayer(FMOD::System* system)
		: m_System(system) { }

	AudioPlayer::~AudioPlayer() { }

	void AudioPlayer::Play(FMOD::Sound* sound, Channel* channel, FMOD::ChannelGroup* group, bool paused)
	{
		CHECK_NULL_LOG(sound, "play");
		m_System->playSound(sound, group, paused, &channel->FMODChannel);
	}

	void AudioPlayer::Stop(Channel* channel)
	{
		CHECK_NULL_LOG(channel, "Stop");
		CHECK_ISPLAYING(channel->FMODChannel);

		FMOD_RESULT result = channel->FMODChannel->stop();
		CHECK_RESULT_LOG(result, "Stopping channel");
	}

	void AudioPlayer::Pause(Channel* channel)
	{
		CHECK_NULL_LOG(channel, "Pause");
		CHECK_ISPLAYING(channel->FMODChannel);

		FMOD_RESULT result = channel->FMODChannel->setPaused(true);
		CHECK_RESULT_LOG(result, "Pausing channel");
	}

	void AudioPlayer::UnPause(Channel* channel)
	{
		CHECK_NULL_LOG(channel, "Unpause");
		CHECK_ISPLAYING(channel->FMODChannel);

		FMOD_RESULT result = channel->FMODChannel->setPaused(false);
		CHECK_RESULT_LOG(result, "Unpausing channel");
	}
}
