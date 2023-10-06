#pragma once
#include "Channel.h"

namespace TwoTune {

	class AudioManipulator
	{
	public:
		void SetPitch(Channel* channel, float pitch);
		float GetPitch(Channel* channel) const;

		void SetVolume(Channel* channel, float volume);
		float GetVolume(Channel* channel) const;

		void SetPan(Channel* channel, float pan);
	};
}

