#include <fmod.hpp>
#include <fmod_errors.h>
#include <stdio.h>
#include <stdlib.h>


int main() {
    FMOD_RESULT fm_result;
    FMOD::System* fm_system;
    fm_result = FMOD::System_Create(&fm_system);        // Create the main system object.

    if (fm_result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", fm_result, FMOD_ErrorString(fm_result));
        exit(-1);
    }

    fm_result = fm_system->init(100, FMOD_INIT_NORMAL, 0);  // Initialize FMOD.

    if (fm_result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", fm_result, FMOD_ErrorString(fm_result));
        exit(-1);
    }

    FMOD::Sound* sound;
    fm_result = fm_system->createSound("Resources/Sounds/swoosh.mp3", FMOD_DEFAULT, 0, &sound);

    FMOD::Channel* channel = nullptr;
    fm_result = fm_system->playSound(sound, 0, false, &channel);

    while (true) {
        fm_system->update();
    }

    sound->release();
    fm_system->release();
}