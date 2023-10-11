#include "pch.h"

#pragma once


namespace TwoTune {

	/// <summary>
	/// Class containing audio loading, removing and storaging logic.
	/// </summary>
	class AudioLibrary
	{
	private:
		FMOD::System* m_System;
		std::map<const char*, FMOD::Sound*> m_AudioLibrary;

	public:
		AudioLibrary(FMOD::System* system);
		~AudioLibrary();

		FMOD::Sound* LoadAudio(const char* audioPath, const char* audioName = "", FMOD_MODE mode = FMOD_DEFAULT, FMOD_CREATESOUNDEXINFO* extraInfo = 0);
		FMOD::Sound* LoadStream(const char* audioPath, const char* audioName = "", FMOD_MODE mode = FMOD_DEFAULT, FMOD_CREATESOUNDEXINFO* extraInfo = 0);
		void UnloadAudio(const char* audioName);
		FMOD::Sound* GetAudio(const char* audioName);

		std::shared_ptr<std::vector<const char*>> GetAllAudioNames();
	};
}

