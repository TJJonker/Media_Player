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
}