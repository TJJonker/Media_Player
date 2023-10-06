#include "pch.h"
#include <AudioManager/AudioManager.h>
#include <AudioManager/AudioLibrary.h>
#include <AudioManager/AudioPlayer.h>
#include <ObjectPooling/Pool.h>
#include <AudioManager/Channel.h>


int main() {
    TwoTune::Log::Init();
    TwoTune::AudioManager audioManager;
    TwoTune::AudioLibrary audioLibrary(audioManager.GetSystem());
    TwoTune::AudioPlayer audioPlayer(audioManager.GetSystem());

    TwoTune::Pool<TwoTune::Channel> pool(audioManager.GetMaxChannels());
    TwoTune::Channel* channel = pool.Get();
    
    audioLibrary.LoadAudio("Resources/Sounds/swoosh.mp3", "Swoosh");
    FMOD::Sound* sound = audioLibrary.GetAudio("Swoosh");

    audioPlayer.Play(sound, channel);

    while (true) {
        audioManager.Update();

        
    }
}