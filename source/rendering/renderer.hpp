#pragma once

#include <memory>
#include <string>
#include <vector>
#include <SDL3/SDL_render.h>

#include "core/types.hpp"

namespace engine
{
    class Window;
    struct Image;
    
    class Renderer
    {
        friend class Font;
        
        SDL_Renderer* renderer {nullptr};
        uint3 clearColor {0, 0, 0};
        
    public:
        Renderer();
        ~Renderer();

        Renderer(const Renderer& other) = delete;
        Renderer &operator=(const Renderer&) = delete;
        Renderer(Renderer&& other) = delete;
        Renderer& operator=(Renderer&& other) = delete;

        [[nodiscard]] std::shared_ptr<Image> CreateImage(const std::string& image) const;
        void SetClearColor(uint3 rgb);
        
        void BeginFrame() const;
        void EndFrame() const;
        
        void Draw(const std::vector<std::shared_ptr<Image>>& images, int2 location) const;
        void Draw(const std::shared_ptr<Image>& image, int2 location) const;

        void DrawLine(int2 start, int2 end, uint3 color) const;
        void DrawBox(int2 start, int2 end, uint3 color) const;
    };
}
