#pragma once
#include "ObjectPooling/PoolObject.h"
#include <fmod.h>

namespace TwoTune {
	
	class Channel : public PoolObject
	{
	public:
		FMOD::Channel* FMODChannel;
		float Pan;
		float Pitch;
		float Volume;
		bool hasChanged;

		Channel() {
			Reset();
		}

		void Reset() override {
			FMODChannel = nullptr;
			Pan = 0;
			Pitch = 0;
			Volume = 1;
			hasChanged = 0;
		}
	};

}

