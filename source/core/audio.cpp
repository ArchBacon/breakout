#include "audio.hpp"

#include <iostream>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio/miniaudio.h>

engine::Audio::Audio()
{
    if (ma_engine_init(nullptr, &audioEngine) != MA_SUCCESS)
    {
        std::cerr << "failed to initialize audio engine";
    }
}

engine::Audio::~Audio()
{
    ma_engine_uninit(&audioEngine);
}

void engine::Audio::PlayAudio(const std::string& file)
{
    ma_engine_play_sound(&audioEngine, file.c_str(), nullptr);
}

void engine::Audio::SetVolume(const float volume)
{
    ma_engine_set_volume(&audioEngine, volume);
}


