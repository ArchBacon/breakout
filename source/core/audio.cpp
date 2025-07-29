#include "audio.hpp"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio/miniaudio.h>

#include "core.hpp"

engine::Audio::Audio()
{
    if (ma_engine_init(nullptr, &audioEngine) != MA_SUCCESS)
    {
        LogEngine->Error("Failed to initialize audio engine");
    }
}

engine::Audio::~Audio()
{
    ma_engine_uninit(&audioEngine);
}

void engine::Audio::Play(const std::string& file)
{
    ma_engine_play_sound(&audioEngine, file.c_str(), nullptr);
}

void engine::Audio::SetVolume(const float volume)
{
    ma_engine_set_volume(&audioEngine, volume);
}


