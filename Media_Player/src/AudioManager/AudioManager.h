#pragma once
#include "pch.h"

namespace TwoTune {

	/// <summary>
	/// Class responsible for initializing and configuring the FMOD System.
	/// </summary>
	class AudioManager
	{
	private:
		// Reference to the FMOD system.
		FMOD::System* m_System;

		// Maximum amount of channels.
		unsigned int m_MaxChannels;

		void Initialize(unsigned int maxChannels, FMOD_INITFLAGS flags, void* extraDriverData);
		void Destroy();
	public:
		AudioManager(unsigned int maxChannels = 100, FMOD_INITFLAGS flags = FMOD_INIT_NORMAL, void* extraDriverData = 0);
		~AudioManager();

		void Update();

		FMOD::System* GetSystem() const;
		unsigned int GetMaxChannels() const;	
	};
}