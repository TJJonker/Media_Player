#pragma once
#include "Channel.h"

namespace TwoTune {

	class AudioPlayer
	{
	private:
		FMOD::System* m_System;

	public:
		AudioPlayer(FMOD::System* system);
		~AudioPlayer();

		void Play(FMOD::Sound* sound, Channel* channel, FMOD::ChannelGroup* group = 0);
		void Stop(Channel* channel);
		void SetPaused(Channel* channel);
	};
}

