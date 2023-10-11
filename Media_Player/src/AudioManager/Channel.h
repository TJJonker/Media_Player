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
		FMOD::Channel* FMODChannel;
		float Pan;
		float Pitch;
		int Volume;

		const char* AudioName;
		bool HasChanged;
		bool PlayNewAudio;

		bool IsPaused;
		bool PauseChanged;

		bool ShouldStop;

		Channel();
		~Channel();

		bool IsPlaying();

		void Reset() override;
	};

}

