#include "pch.h"
#include "AudioManipulator.h"

namespace TwoTune {

	/// <summary>
	/// AudioManipulator Constructor.
	/// </summary>
	AudioManipulator::AudioManipulator() { }

	/// <summary>
	/// AudioManipulator Destructor.
	/// </summary>
	AudioManipulator::~AudioManipulator() { }

	/// <summary>
	/// Sets the pitch of the given channel.
	/// </summary>
	/// <param name="channel">Reference to the channel that should be manipulated.</param>
	void AudioManipulator::SetPitch(Channel* channel)
	{
		CHECK_NULL_LOG(channel, "Setting pitch");
		CHECK_NULL_LOG(channel->FMODChannel, "Checking FMODChannel");
		CHECK_ISPLAYING(channel->FMODChannel);

		FMOD_RESULT result = channel->FMODChannel->setPitch(channel->Pitch); 
		CHECK_RESULT_LOG(result, "Setting pitch");
	}

	/// <summary>
	/// Sets the Volume of the given channel.
	/// </summary>
	/// <param name="channel">Reference to the channel that should be manipulated.</param>
	void AudioManipulator::SetVolume(Channel* channel)
	{
		CHECK_NULL_LOG(channel, "Setting volume");
		CHECK_NULL_LOG(channel->FMODChannel, "Checking FMODChannel"); 
		CHECK_ISPLAYING(channel->FMODChannel);
		FMOD_RESULT result = channel->FMODChannel->setVolume(channel->Volume / 100.0f);
		CHECK_RESULT_LOG(result, "Setting volume");
	}

	/// <summary>
	/// Sets the Pan of the given channel.
	/// </summary>
	/// <param name="channel">Reference to the channel that should be manipulated.</param>
	void AudioManipulator::SetPan(Channel* channel)
	{
		CHECK_NULL_LOG(channel, "Setting pan");
		CHECK_NULL_LOG(channel->FMODChannel, "Checking FMODChannel"); 
		CHECK_ISPLAYING(channel->FMODChannel);

		FMOD_RESULT result = channel->FMODChannel->setPan(channel->Pan);
		CHECK_RESULT_LOG(result, "Setting pan");
	}
}
