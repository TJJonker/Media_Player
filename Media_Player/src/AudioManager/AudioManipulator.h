#pragma once
#include "Channel.h"

namespace TwoTune {

	/// <summary>
	/// Class responsible for manipulating channel/audio properties.
	/// </summary>
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

