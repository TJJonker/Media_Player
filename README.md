# TwoTune Media Player

TwoTune Media Player is a Hello World project for both the FMOD and DearImGui library. 
The aim of the project was to create an audio API, built with the FMOD library, which would be able to load and unload assets. (both sampled and streaming audio) and contains methods to play, pause, stop, set pitch, 
set volume, and set pan for Audio Sources on their channel.

In addition to the audio API, there should also be a CLI or GUI media player in which the user can easily play around with preloaded audio files, their pitch, pan, and volume.
This seemed like the perfect opportunity to mess around with the DearImGui library and see what it has to offer.


### How to build
To save memory, the folder doesn't contain a solution file and/or bin and bin-int folder. Premake5 is integrated into the project and is responsible for building the necessary files. 
Clicking the 'GenerateFiles' WBF (Windows Batch File) will open the command prompt and run Premake5. This will generate the files, after which the user can click any button to close the command prompt.
A solution file should appear in the folder, which can be opened. This project already contains all the necessary links and project settings. Clicking the 'Run' or 'Debug' button should run the program without issues.


### Project structure
All the code written for this project can be found in the [src folder](Media_Player/src). With the exception of [vendor](Media_Player/src/vendor). The source folder is split into different modules:
- **AudioManager**: Contains the core Two Tune API.
- **Debug**: Logging, Assertion, and FMOD Error utils/helpers.
- **GUI**: A class containing DearImGui rendering-related logic.
- **ObjectPooling**: A quickly written object pooling template, which ended up not being used.
- **vendor**: Containing the DearImGui source files.

All the audio files can be found in the [resources folder](Media_Player/Resources) and the used external libraries in the [vendor folder](Media_Player/vendor).


### How does it work?
Initialization of all the modules is done in [Main](Media_Player/src/Main.cpp). 
- The AudioManager will create an FMOD system with the given amount of channels.
- The AudioLibrary is responsible for loading and removing audio files in and out of memory respectively.
- The AudioPlayer is responsible for playing, pausing, and stopping audio files and channels.
- The AudioManipulator is responsible for adjusting a channel's pitch, pan, and volume.
- A Channel is the base of audio playback. This struct will keep track of settings and apply these settings to all the audio files played with that particular channel.

After the initialization, all the audio files are loaded into memory with the help of the audio library. 

Just before the GLFW window loop, the ImGui rendering class is initialized and provided with the necessary data. Inside the ImGuiRenderer class, we're drawing a hardcoded GUI, making changes to the Channel, and reading from a list of audio names that is provided by the audio library.

Inside the GLFW window loop, we're checking if there are changes inside the channel struct and forwarding the changes to the designated TwoTune module.


### Evaluation
I think the TwoTune API worked out decent. The GUI is what messed up a big part of the codebase. I wanted (and should have) abstracted the GUI into separate files, added an Event system, and ultimately added a small layer structure to keep things really clean. Not doing this, caused the Channel struct to be filled with nonsense and redundant data because the GUI can't properly communicate with the rest of the codebase. I also wanted to change the GLFW and GLAD initialization a bit. This could've been extracted and abstracted, but I don't think reworking this would've been worth it, as this still is a Hello World project.

All in all, I'm happy with the result and I'll take everything I've learned with me to future projects.
