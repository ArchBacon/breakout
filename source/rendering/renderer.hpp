#pragma once

#include <string>
#include <SDL3/SDL_render.h>

namespace breakout
{
    class Window;
    struct Image;
    
    class Renderer
    {
        SDL_Renderer* renderer {nullptr};
        
    public:
        Renderer();
        ~Renderer();

        Renderer(const Renderer& other) = delete;
        Renderer &operator=(const Renderer&) = delete;
        Renderer(Renderer&& other) = delete;
        Renderer& operator=(Renderer&& other) = delete;

        [[nodiscard]] Image* CreateImage(const std::string& image) const;
        
        void BeginFrame() const;
        void EndFrame() const;
        void Draw(Image* image, int x, int y);
    };
}
