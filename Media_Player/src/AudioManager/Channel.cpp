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
		Pitch = 0;
		Volume = 1;
		HasChanged = false;
		AudioName = "";
		PlayNewAudio = false;
	}
}
