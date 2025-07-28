#include "window.hpp"

breakout::Window::Window(
    const uint32_t width,
    const uint32_t height,
    const std::string& name,
    const std::string& icon
) {
    // Initialize SDL3
    SDL_Init(SDL_INIT_VIDEO);

    // Create Window
    constexpr SDL_WindowFlags windowFlags = SDL_WINDOW_OPENGL;
    window = SDL_CreateWindow(
        name.c_str(),
        static_cast<int>(width),
        static_cast<int>(height),
        windowFlags
    );

    // Add icon to window if specified
    if (!icon.empty())
    {
        SDL_Surface* iconSurface = SDL_LoadBMP(icon.c_str());
        SDL_SetWindowIcon(window, iconSurface);
        SDL_DestroySurface(iconSurface);
    }
}

breakout::Window::~Window()
{
    SDL_DestroyWindow(window);
}
