#pragma once

#include <string>
#include <SDL3/SDL.h>

namespace engine
{
    class Window
    {
        friend class Renderer;
        
        SDL_Window* window {nullptr};
        
    public:
        Window(uint32_t width, uint32_t height, const std::string& name);
        ~Window();

        Window(const Window& other) = delete;
        Window &operator=(const Window&) = delete;
        Window(Window&& other) = delete;
        Window& operator=(Window&& other) = delete;

        void SetTitle(const std::string& name) const;
        void SetIcon(const std::string& icon) const;
        void SetSize(uint32_t width, uint32_t height) const;

        [[nodiscard]] uint32_t Width() const;
        [[nodiscard]] uint32_t Height() const;
    };
}
