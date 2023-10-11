#include "pch.h"
#include "AudioManipulator.h"

namespace TwoTune {
	AudioManipulator::AudioManipulator()
	{
	}
	AudioManipulator::~AudioManipulator()
	{
	}
	void AudioManipulator::SetPitch(Channel* channel)
	{
		CHECK_NULL_LOG(channel, "Setting pitch");
		CHECK_NULL_LOG(channel->FMODChannel, "Checking FMODChannel");
		CHECK_ISPLAYING(channel->FMODChannel);

		FMOD_RESULT result = channel->FMODChannel->setPitch(channel->Pitch); 
		CHECK_RESULT_LOG(result, "Setting pitch");
	}

	void AudioManipulator::SetVolume(Channel* channel)
	{
		CHECK_NULL_LOG(channel, "Setting volume");
		CHECK_NULL_LOG(channel->FMODChannel, "Checking FMODChannel"); 
		CHECK_ISPLAYING(channel->FMODChannel);
		FMOD_RESULT result = channel->FMODChannel->setVolume(channel->Volume / 100.0f);
		CHECK_RESULT_LOG(result, "Setting volume");
	}

	void AudioManipulator::SetPan(Channel* channel)
	{
		CHECK_NULL_LOG(channel, "Setting pan");
		CHECK_NULL_LOG(channel->FMODChannel, "Checking FMODChannel"); 
		CHECK_ISPLAYING(channel->FMODChannel);

		FMOD_RESULT result = channel->FMODChannel->setPan(channel->Pan);
		CHECK_RESULT_LOG(result, "Setting pan");
	}
}
