#include "pch.h"
#include "AudioLibrary.h"

namespace TwoTune {

	/// <summary>
	/// Initializes the AudioLibrary.
	/// </summary>
	/// <param name="system">FMOD::System, created in the AudioManager.</param>
	AudioLibrary::AudioLibrary(FMOD::System* system) 
		: m_System(system) { }

	/// <summary>
	/// Destroys the AudioLibrary.
	/// </summary>
	AudioLibrary::~AudioLibrary() { }

	/// <summary>
	/// Loads an audio file into memory and places it in the audio library.
	/// </summary>
	/// <param name="audioPath">Path to the audio file.</param>
	/// <param name="audioName">Name for the audio file.</param>
	/// <param name="mode">Audio mode.</param>
	/// <param name="extraInfo">Extra audio information.</param>
	/// <returns>Pointer to the audio file.</returns>
	FMOD::Sound* AudioLibrary::LoadAudio(const char* audioPath, const char* audioName, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* extraInfo)
	{
		// Adjust the audioName if left empty.
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

		// Save audio file in the audiolibrary.
		m_AudioLibrary.insert({ audioName, sound });
		return sound;
	}

	/// <summary>
	/// Loads an audio file into memory as a stream and places it in the audio library.
	/// </summary>
	/// <param name="audioPath">Path to the audio file.</param>
	/// <param name="audioName">Name of the audio file.</param>
	/// <param name="mode">Audio mode.</param>
	/// <param name="extraInfo">Extra audio information.</param>
	/// <returns>Pointer to the audio file.</returns>
	FMOD::Sound* AudioLibrary::LoadStream(const char* audioPath, const char* audioName, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO* extraInfo)
	{
		// Adjust the audioName if left empty.
		audioName = audioName == "" ? audioPath : audioName;

		// Check if the audiolibrary already contains an entry with the same name.
		if (m_AudioLibrary.count(audioName)) {
			TWOTUNE_LOG_WARNING("AudioLibrary already contains an audio file called '{0}'. Loading audio will be canceled.", audioName);
			return nullptr;
		}

		// Load audio file into memory.
		FMOD::Sound* sound;
		FMOD_RESULT result = m_System->createStream(audioPath, mode, extraInfo, &sound);
		CHECK_RESULT_LOG(result, "Load audio");

		// Save audio file in the audiolibrary.
		m_AudioLibrary.insert({ audioName, sound });
		return sound;

		return nullptr;
	}

	/// <summary>
	/// Removes an audio file out of memory and out of the audiolibrary.
	/// </summary>
	/// <param name="audioName">Name of the audio file.</param>
	void AudioLibrary::UnloadAudio(const char* audioName)
	{
		FMOD::Sound* sound = GetAudio(audioName);
		
		CHECK_NULL_LOG(sound, "Getting audio");

		sound->release();
		m_AudioLibrary.erase(audioName);
	}

	/// <summary>
	/// Retrieves sound from the audiolibrary.
	/// </summary>
	/// <param name="audioName">Name of the audio file.</param>
	/// <returns>Pointer to the audio file.</returns>
	FMOD::Sound* AudioLibrary::GetAudio(const char* audioName)
	{
		if (!m_AudioLibrary.count(audioName)) {
			TWOTUNE_LOG_WARNING("AudioLibrary does not contain an audio file called '{0}'.", audioName);
			return nullptr;
		}

		return m_AudioLibrary[audioName];
	}

	/// <summary>
	/// Retrieves a list of all the audio file names in the audiolibrary.
	/// </summary>
	/// <returns>A std::vec containing all the audio file names in the audiolibrary.</returns>
	std::shared_ptr<std::vector<const char*>> AudioLibrary::GetAllAudioNames()
	{
		std::vector<const char*> listOfNames;
		for (std::map<const char*, FMOD::Sound*>::iterator it = m_AudioLibrary.begin(); it != m_AudioLibrary.end(); ++it) {
			listOfNames.push_back(it->first);
		}
		return std::make_shared<std::vector<const char*>>(listOfNames);
	}
}