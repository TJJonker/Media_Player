#include "pch.h"
#include "AudioManager.h"

namespace TwoTune {

	AudioManager::AudioManager(unsigned int maxChannels, FMOD_INITFLAGS flags, void* extraDriverData)
		: m_System(nullptr), m_Initialized(false), m_MaxChannels(maxChannels)
	{
		Initialize(maxChannels, flags, extraDriverData);
	}

	AudioManager::~AudioManager() 
	{ 
		Destroy();
	}

	void AudioManager::Initialize(unsigned int maxChannels, FMOD_INITFLAGS flags, void* extraDriverData)
	{
		FMOD_RESULT result;
		result = FMOD::System_Create(&m_System);
		CHECK_RESULT_ASSERT(result, "Create system");

		result = m_System->init(maxChannels, flags, extraDriverData);
		CHECK_RESULT_ASSERT(result, "Intialize system");
	}

	void AudioManager::Destroy()
	{
		m_System->release();
	}

	void AudioManager::Update()
	{
		m_System->update();
	}

	FMOD::System* AudioManager::GetSystem() const
	{
		return m_System;
	}

	unsigned int AudioManager::GetMaxChannels() const
	{
		return m_MaxChannels;
	}



}

