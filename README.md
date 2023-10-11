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
