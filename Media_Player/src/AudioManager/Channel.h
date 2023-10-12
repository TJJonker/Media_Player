#pragma once
#include "ObjectPooling/PoolObject.h"
#include <fmod.h>

namespace TwoTune {
	
	/// <summary>
	/// Struct containing channel properties and change states.
	/// </summary>
	struct Channel : public PoolObject
	{
	public:
		// Reference to a FMOD Channel.
		FMOD::Channel* FMODChannel;

		// Pan value of this channel.
		float Pan;

		// Pitch value of this channel.
		float Pitch;

		// Volume value of this channel.
		int Volume;

		// Audio name of the currently playing audio file.
		const char* AudioName;

		// Whether the Pan, Pitch or Volume has changed inside this Channel.
		bool HasChanged;

		// Whether a new audio file should be played.
		bool PlayNewAudio;

		// Whether the audio should be paused.
		bool IsPaused;

		// Whether the pause state has changed.
		bool PauseChanged;

		// Whether the audio should be stopped.
		bool ShouldStop;

		Channel();
		~Channel();

		bool IsPlaying();

		void Reset() override;
	};

}

