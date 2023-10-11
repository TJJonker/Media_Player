#include "pch.h"
#include "AudioPlayer.h"
#include "Channel.h"

namespace TwoTune {

	/// <summary>
	/// AudioPlayer constructor.
	/// </summary>
	/// <param name="system">The FMOD system created in the AudioManager.</param>
	AudioPlayer::AudioPlayer(FMOD::System* system)
		: m_System(system) { }

	/// <summary>
	/// AudioPlayer destructor.
	/// </summary>
	AudioPlayer::~AudioPlayer() { }

	/// <summary>
	/// Plays the given audio file.
	/// </summary>
	/// <param name="sound">The audio file that should be played.</param>
	/// <param name="channel">TwoTune channel to which the FMOD channel will be saved.</param>
	/// <param name="group">Channelgroup the channel should be part of.</param>
	void AudioPlayer::Play(FMOD::Sound* sound, Channel* channel, FMOD::ChannelGroup* group)
	{
		CHECK_NULL_LOG(sound, "play");
		FMOD_RESULT result = m_System->playSound(sound, group, channel->IsPaused, &channel->FMODChannel);

		CHECK_RESULT_LOG(result, "Playing sound");
	}

	/// <summary>
	/// Stops the channel playing audio.
	/// </summary>
	/// <param name="channel">TwoTune channel containing the FMOD channel.</param>
	void AudioPlayer::Stop(Channel* channel)
	{
		CHECK_NULL_LOG(channel, "Stop");
		CHECK_ISPLAYING(channel->FMODChannel);

		FMOD_RESULT result = channel->FMODChannel->stop();
		CHECK_RESULT_LOG(result, "Stopping channel");
	}

	/// <summary>
	/// Sets the pause state of the channel playing audio.
	/// </summary>
	/// <param name="channel">TwoTune channel containing the FMOD channel.</param>
	void AudioPlayer::SetPaused(Channel* channel)
	{
		CHECK_NULL_LOG(channel, "Pause");
		CHECK_ISPLAYING(channel->FMODChannel);

		FMOD_RESULT result = channel->FMODChannel->setPaused(channel->IsPaused);
		CHECK_RESULT_LOG(result, "Pausing channel");
	}
}
