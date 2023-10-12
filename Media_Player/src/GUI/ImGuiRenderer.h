#pragma once
#include<GLFW/glfw3.h>
#include <AudioManager/Channel.h>

/// <summary>
/// Class containing ImGui logic and visualisation.
/// </summary>
class ImGuiRenderer
{
public:
	ImGuiRenderer(GLFWwindow* window);
	~ImGuiRenderer();

	void Render();

	void SetChannel(TwoTune::Channel* channel) { m_Channel = channel; }
	void SetListAudioLibrary(std::shared_ptr<std::vector<const char*>> listOfAudioNames) { m_ListOfAudioNames = listOfAudioNames; }
private:
	void Initialize(GLFWwindow* window);
	void Destroy();

	void Begin();
	void End();

	// List of audio names, retrieved from the AudioLibrary.
	std::shared_ptr<std::vector<const char*>> m_ListOfAudioNames;

	// Reference to the TwoTune channel to properly play around with the audio files / sound.
	TwoTune::Channel* m_Channel;
};

