#include "pch.h"
#include "AudioManipulator.h"

namespace TwoTune {

	void AudioManipulator::SetPitch(FMOD::Channel* channel, float pitch)
	{
		CHECK_NULL_LOG(channel, "Setting pitch");
		CHECK_ISPLAYING(channel);

		FMOD_RESULT result = channel->setPitch(pitch); 
		CHECK_RESULT_LOG(result, "Setting pitch");
	}

	float AudioManipulator::GetPitch(FMOD::Channel* channel) const
	{
		CHECK_NULL_LOG_RETURN(channel, "Getting pitch", -10);
		CHECK_ISPLAYING(channel);

		float pitch;
		FMOD_RESULT result = channel->getPitch(&pitch);
		CHECK_RESULT_LOG(result, "Getting pitch");

		return pitch;
	}

	void AudioManipulator::SetVolume(FMOD::Channel* channel, float volume)
	{
		CHECK_NULL_LOG(channel, "Setting volume");
		CHECK_ISPLAYING(channel);

		FMOD_RESULT result = channel->setVolume(volume);
		CHECK_RESULT_LOG(result, "Setting volume");
	}

	float AudioManipulator::GetVolume(FMOD::Channel* channel) const
	{
		CHECK_NULL_LOG_RETURN(channel, "Getting volume", -10);
		CHECK_ISPLAYING(channel);

		float volume;
		FMOD_RESULT result = channel->getPitch(&volume);
		CHECK_RESULT_LOG(result, "Getting volume");

		return volume;
	}

	void AudioManipulator::SetPan(FMOD::Channel* channel, float pan)
	{
		CHECK_NULL_LOG(channel, "Setting pan");
		CHECK_ISPLAYING(channel);

		FMOD_RESULT result = channel->setVolume(pan);
		CHECK_RESULT_LOG(result, "Setting pan");
	}
}
