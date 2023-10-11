#pragma once
#include "Channel.h"

namespace TwoTune {

	class AudioManipulator
	{
	public:
		AudioManipulator();
		~AudioManipulator();

		void SetPitch(Channel* channel);
		void SetVolume(Channel* channel);
		void SetPan(Channel* channel);
	};
}

