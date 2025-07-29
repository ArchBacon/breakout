#include "renderer.hpp"

#include <iostream>
#include <SDL3/SDL.h>

#include "image.hpp"
#include "core/engine.hpp"
#include "core/window.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

engine::Renderer::Renderer()
{
    renderer = SDL_CreateRenderer(::Engine.Window().window, nullptr);
}

engine::Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
}

std::shared_ptr<engine::Image> engine::Renderer::CreateImage(const std::string& image) const
{
    int channels, width, height;
    const auto pixels = stbi_load(image.c_str(), &width, &height, &channels, 4);
    if (pixels == nullptr)
    {
        LogRenderer->Error("Failed to create image {}", image);
        return nullptr;
    }

    const auto surface = SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, pixels, 4 * width);
    const auto texture = SDL_CreateTextureFromSurface(renderer, surface);

    return std::make_shared<Image>(Image{
        .channels = channels,
        .width = width,
        .height = height,
        .pixels = pixels,
        .surface = surface,
        .texture = texture, 
    });
}

void engine::Renderer::SetClearColor(const uint3 rgb)
{
    clearColor = rgb;
}

void engine::Renderer::BeginFrame() const
{
    // Set the clear color to black
    SDL_SetRenderDrawColor(
        renderer,
        static_cast<uint8_t>(clearColor.r),
        static_cast<uint8_t>(clearColor.g),
        static_cast<uint8_t>(clearColor.b),
        SDL_ALPHA_OPAQUE
    );
    SDL_RenderClear(renderer);
}

void engine::Renderer::EndFrame() const
{
    SDL_RenderPresent(renderer);
}

void engine::Renderer::Draw(const std::vector<std::shared_ptr<Image>>& images, const int2 location) const
{
    for (auto& image : images)
    {
        Draw(image, location);
    }
}

void engine::Renderer::Draw(const std::shared_ptr<Image>& image, const int2 location) const
{
    const SDL_FRect dstRect
    {
        .x = static_cast<float>(location.x),
        .y = static_cast<float>(location.y),
        .w = static_cast<float>(image->width),
        .h = static_cast<float>(image->height)
    };
    
    SDL_RenderTexture(renderer, image->texture, nullptr, &dstRect);
}

