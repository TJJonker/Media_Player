#include "pch.h"
#include "AudioManager.h"

namespace TwoTune {

	/// <summary>
	/// AudioManager constructor.
	/// </summary>
	/// <param name="maxChannels">Max amount of channels available in the system.</param>
	/// <param name="flags">Initialisation flags for initalising the system.</param>
	/// <param name="extraDriverData">Extra driver data.</param>
	AudioManager::AudioManager(unsigned int maxChannels, FMOD_INITFLAGS flags, void* extraDriverData)
		: m_System(nullptr), m_MaxChannels(maxChannels)
	{
		Initialize(maxChannels, flags, extraDriverData);
	}

	/// <summary>
	/// AudioManager destructor.
	/// </summary>
	AudioManager::~AudioManager() 
	{ 
		Destroy();
	}

	/// <summary>
	/// Initializes the FMOD system.
	/// </summary>
	/// <param name="maxChannels">Max amount of channels available in the system.</param>
	/// <param name="flags">Initialisation flags for initalising the system.</param>
	/// <param name="extraDriverData">Extra driver data.</param>
	void AudioManager::Initialize(unsigned int maxChannels, FMOD_INITFLAGS flags, void* extraDriverData)
	{
		FMOD_RESULT result;
		result = FMOD::System_Create(&m_System);
		CHECK_RESULT_ASSERT(result, "Create system");

		result = m_System->init(maxChannels, flags, extraDriverData);
		CHECK_RESULT_ASSERT(result, "Intialize system");
	}

	/// <summary>
	/// Releases the FMOD system.
	/// </summary>
	void AudioManager::Destroy()
	{
		m_System->release();
	}

	/// <summary>
	/// Updates the system.
	/// </summary>
	void AudioManager::Update()
	{
		m_System->update();
	}

	/// <summary>
	/// Returns the intialized system.
	/// </summary>
	/// <returns>The initalized system.</returns>
	FMOD::System* AudioManager::GetSystem() const
	{
		return m_System;
	}

	/// <summary>
	/// Returns the maximum amount of channels in the system.
	/// </summary>
	/// <returns>The maximum amount of channels in the system.</returns>
	unsigned int AudioManager::GetMaxChannels() const
	{
		return m_MaxChannels;
	}



}

