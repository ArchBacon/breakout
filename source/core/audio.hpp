#pragma once

#include <string>
#include <miniaudio/miniaudio.h>

namespace breakout
{
    class Audio
    {
        ma_engine audioEngine {};
        
    public:
        Audio();
        ~Audio();

        Audio(const Audio& other) = delete;
        Audio &operator=(const Audio&) = delete;
        Audio(Audio&& other) = delete;
        Audio& operator=(Audio&& other) = delete;

        void PlayAudio(const std::string& file);
        /**
         * @param volume Percentage of volume between 0.0 and 1.0
         */
        void SetVolume(float volume);
    };
}
