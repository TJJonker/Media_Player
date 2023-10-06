#include "pch.h"

#pragma once


namespace TwoTune {

	class AudioLibrary
	{
	private:
		FMOD::System* m_System;
		std::map<const char*, FMOD::Sound*> m_AudioLibrary;

	public:
		AudioLibrary(FMOD::System* system);
		~AudioLibrary();

		FMOD::Sound* LoadAudio(const char* audioPath, const char* audioName = "", FMOD_MODE mode = FMOD_DEFAULT, FMOD_CREATESOUNDEXINFO* extraInfo = 0);
		void UnloadAudio(const char* audioName);
		FMOD::Sound* GetAudio(const char* audioName);
	};
}

