#include "pch.h"
#include "AudioLibrary.h"

namespace TwoTune {
	AudioLibrary::AudioLibrary(FMOD::System* system) 
		: m_System(system) { }

	AudioLibrary::~AudioLibrary() { }

	FMOD::Sound* AudioLibrary::LoadAudio(const char* audioPath, const char* audioName, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* extraInfo)
	{
		// Adjust the audioName if left empty
		audioName = audioName == "" ? audioPath : audioName;

		// Check if the audiolibrary already contains an entry with the same name.
		if (m_AudioLibrary.count(audioName)) {
			TWOTUNE_LOG_WARNING("AudioLibrary already contains an audio file called '{0}'. Loading audio will be canceled.", audioName);
			return nullptr;
		}

		// Load audio file into memory.
		FMOD::Sound* sound; 
		FMOD_RESULT result = m_System->createSound(audioPath, mode, extraInfo, &sound); 
		CHECK_RESULT_LOG(result, "Load audio");

		// Save audio file in the audiolibrary
		m_AudioLibrary.insert({ audioName, sound });
		return sound;
	}

	void AudioLibrary::UnloadAudio(const char* audioName)
	{
		FMOD::Sound* sound = GetAudio(audioName);
		
		CHECK_NULL_LOG(sound, "Getting audio");

		sound->release();
		m_AudioLibrary.erase(audioName);
	}

	FMOD::Sound* AudioLibrary::GetAudio(const char* audioName)
	{
		if (!m_AudioLibrary.count(audioName)) {
			TWOTUNE_LOG_WARNING("AudioLibrary does not contain an audio file called '{0}'.", audioName);
			return nullptr;
		}

		return m_AudioLibrary[audioName];
	}



}