#pragma once

#include <SDL3/SDL.h>

namespace breakout
{
    struct Image
    {
        int channels {0};
        int width {0};
        int height {0};
        unsigned char* pixels {nullptr};
        SDL_Surface* surface {nullptr};
        SDL_Texture* texture {nullptr};
    };
}
