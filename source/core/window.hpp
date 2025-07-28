#pragma once

#include <string>
#include <SDL3/SDL.h>

namespace breakout
{
    class Window
    {
        SDL_Window* window {nullptr};
        
    public:
        Window(uint32_t width, uint32_t height, const std::string& name, const std::string& icon = {});
        ~Window();

        Window(const Window& other) = delete;
        Window &operator=(const Window&) = delete;
        Window(Window&& other) = delete;
        Window& operator=(Window&& other) = delete;
    };
}
