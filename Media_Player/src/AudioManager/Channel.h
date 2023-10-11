#pragma once
#include "ObjectPooling/PoolObject.h"
#include <fmod.h>

namespace TwoTune {
	
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

		Channel();
		~Channel();

		void Reset() override;
	};

}

