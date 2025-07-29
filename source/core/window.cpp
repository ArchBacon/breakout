#include "window.hpp"

engine::Window::Window(
    const uint32_t width,
    const uint32_t height,
    const std::string& name
) {
    // Initialize SDL3
    SDL_Init(SDL_INIT_VIDEO);

    // Create Window
    constexpr SDL_WindowFlags windowFlags = 0;
    window = SDL_CreateWindow(
        name.c_str(),
        static_cast<int>(width),
        static_cast<int>(height),
        windowFlags
    );
}

engine::Window::~Window()
{
    SDL_DestroyWindow(window);
}

void engine::Window::SetTitle(const std::string& name) const
{
    SDL_SetWindowTitle(window, name.c_str());
}

void engine::Window::SetIcon(const std::string& icon) const
{
    if (!icon.empty())
    {
        SDL_Surface* iconSurface = SDL_LoadBMP(icon.c_str());
        SDL_SetWindowIcon(window, iconSurface);
        SDL_DestroySurface(iconSurface);
    }
}

void engine::Window::SetSize(const uint32_t width, const uint32_t height) const
{
    SDL_SetWindowSize(window, static_cast<int>(width), static_cast<int>(height));
}

uint32_t engine::Window::Width() const
{
    int32_t width {};
    SDL_GetWindowSize(window, &width, nullptr);

    return width;
}

uint32_t engine::Window::Height() const
{
    int32_t height {};
    SDL_GetWindowSize(window, nullptr, &height);

    return height;
}

