#include "pch.h"
#include "Channel.h"

namespace TwoTune {

	/// <summary>
	/// Channel constructor.
	/// </summary>
	Channel::Channel() {
		Reset();
	}

	/// <summary>
	/// Channel destructor.
	/// </summary>
	Channel::~Channel() { }

	/// <summary>
	/// Returns whether the channel is active or not.
	/// </summary>
	/// <returns>Whether the channel is active or not.</returns>
	bool Channel::IsPlaying()
	{
		bool isPlaying;
		FMODChannel->isPlaying(&isPlaying);
		return isPlaying;
	}

	/// <summary>
	/// Resets the Channel properties to their default values.
	/// </summary>
	void Channel::Reset() {
		FMODChannel = nullptr;
		Pan = 0;
		Pitch = 1;
		Volume = 50;
		HasChanged = false;
		AudioName = "";
		PlayNewAudio = false;

		PauseChanged = false;
		IsPaused = false;

		ShouldStop = false;
	}
}
