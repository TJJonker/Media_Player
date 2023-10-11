#include "pch.h"

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <ImGuiRenderer.h>
#include <AudioManager/AudioManager.h>
#include <AudioManager/AudioLibrary.h>
#include <AudioManager/AudioPlayer.h>
#include <AudioManager/AudioManipulator.h>


int main()
{
	TwoTune::AudioManager audioManager(100);
	TwoTune::AudioLibrary audioLibrary(audioManager.GetSystem());
	TwoTune::AudioPlayer audioPlayer(audioManager.GetSystem());
	TwoTune::AudioManipulator audioManipulator;

	FMOD::Sound* sound = audioLibrary.LoadAudio("Resources/Sounds/swoosh.mp3", "Swoosh");
	audioLibrary.LoadAudio("Resources/Sounds/swoosh.mp3", "");
	audioLibrary.LoadAudio("Resources/Sounds/swoosh.mp3", "Car");
	audioLibrary.LoadAudio("Resources/Sounds/swoosh.mp3", "Gun");

	FMOD_RESULT result;
	FMOD::System* systom;
	result = FMOD::System_Create(&systom);

	result = systom->init(512, FMOD_INIT_NORMAL, 0);

	TwoTune::Channel channel;
	FMOD::Channel* chinchan = nullptr;
	systom->playSound(sound, 0, false, &chinchan);

	//audioPlayer.Play(sound, &channel);


	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(960, 540, "ImGui + GLFW", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	glViewport(0, 0, 800, 800);


	ImGuiRenderer igRenderer(window);
	igRenderer.SetListAudioLibrary(audioLibrary.GetAllAudioNames());
	igRenderer.SetChannel(&channel);


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		igRenderer.Render();

		if (channel.HasChanged && channel.FMODChannel) {
			audioManipulator.SetVolume(&channel);
			audioManipulator.SetPan(&channel);
			audioManipulator.SetPitch(&channel);
			channel.HasChanged = false;

			TWOTUNE_LOG_TRACE("Channel properties have changed and changes have been applied.");
		}

		if (channel.PlayNewAudio) {
			FMOD::Sound* soundToPlay = audioLibrary.GetAudio(channel.AudioName);
			if (channel.FMODChannel)
				audioPlayer.Stop(&channel);
			audioPlayer.Play(soundToPlay, &channel);
			channel.PlayNewAudio = false;
		}

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}