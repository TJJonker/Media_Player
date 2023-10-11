#include "pch.h"
#include "Channel.h"

namespace TwoTune {
	Channel::~Channel() { }

	Channel::Channel() {
		Reset();
	}

	void Channel::Reset() {
		FMODChannel = nullptr;
		Pan = 0;
		Pitch = 1;
		Volume = 1;
		HasChanged = false;
		AudioName = "";
		PlayNewAudio = false;

		PauseChanged = false;
		IsPaused = false;

		ShouldStop = false;
	}
}
