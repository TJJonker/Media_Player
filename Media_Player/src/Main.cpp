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
	TwoTune::Log::Init();

	TwoTune::AudioManager audioManager(100);
	TwoTune::AudioLibrary audioLibrary(audioManager.GetSystem());
	TwoTune::AudioPlayer audioPlayer(audioManager.GetSystem());
	TwoTune::AudioManipulator audioManipulator;

	audioLibrary.LoadAudio("Resources/Sounds/Swoosh.mp3", "Swoosh");
	audioLibrary.LoadAudio("Resources/Sounds/Bullet.mp3", "Bullet");
	audioLibrary.LoadAudio("Resources/Sounds/Bullet_impact.mp3", "Bullet impact");
	audioLibrary.LoadAudio("Resources/Sounds/Car_driving_ambience.mp3", "Car ambience");
	audioLibrary.LoadAudio("Resources/Sounds/Sci-fi_weapon_charging.mp3", "Sci-fi weapon charging");
	audioLibrary.LoadAudio("Resources/Sounds/Alien_ship_landing.mp3", "Alien ship landing");

	TwoTune::Channel channel;


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

		//-------------------------------------------------- Check what er gebeurd met de FMOD Channel. Wellicht denkt ie dat the channel debiel doet... leuk!

		if (channel.HasChanged) {
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

			audioManipulator.SetVolume(&channel);
			audioManipulator.SetPan(&channel);
			audioManipulator.SetPitch(&channel);
		}

		if (channel.PauseChanged) {
			channel.PauseChanged = false;
			audioPlayer.SetPaused(&channel);
		}

		if (channel.ShouldStop) {
			channel.ShouldStop = false;
			audioPlayer.Stop(&channel);
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