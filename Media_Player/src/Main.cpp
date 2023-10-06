#include "pch.h"
#include <AudioManager/AudioManager.h>
#include <AudioManager/AudioLibrary.h>
#include <AudioManager/AudioPlayer.h>
#include <ObjectPooling/Pool.h>
#include <AudioManager/Channel.h>
#include <GLFW/glfw3.h>
#include <imgui.h>



int main() {

    if (!glfwInit()) {
        // Initialization failed
        return -1;
    }

    // Set GLFW to not create an OpenGL context on window creation (for ImGui)
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui GLFW Example", NULL, NULL);
    if (!window) {
        // Window creation failed
        glfwTerminate();
        return -1;
    }

    // Cleanup and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();





    TwoTune::Log::Init();
    TwoTune::AudioManager audioManager;
    TwoTune::AudioLibrary audioLibrary(audioManager.GetSystem());
    TwoTune::AudioPlayer audioPlayer(audioManager.GetSystem());

    TwoTune::Pool<TwoTune::Channel> pool(audioManager.GetMaxChannels());
    TwoTune::Channel* channel = pool.Get();
    
    audioLibrary.LoadAudio("Resources/Sounds/swoosh.mp3", "Swoosh");
    FMOD::Sound* sound = audioLibrary.GetAudio("Swoosh");

    audioPlayer.Play(sound, channel);





    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Add your rendering code here (OpenGL or other graphics API)

        // Swap buffers
        glfwSwapBuffers(window);
        audioManager.Update();
    }
}