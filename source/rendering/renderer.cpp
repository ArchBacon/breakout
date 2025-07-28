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

engine::Image* engine::Renderer::CreateImage(const std::string& image) const
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

    return new Image
    {
        .channels = channels,
        .width = width,
        .height = height,
        .pixels = pixels,
        .surface = surface,
        .texture = texture, 
    };
}

void engine::Renderer::BeginFrame() const
{
    // Set the clear color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void engine::Renderer::EndFrame() const
{
    SDL_RenderPresent(renderer);
}

void engine::Renderer::Draw(Image* image, const int x, const int y)
{
    const SDL_FRect dstRect
    {
        .x = (float)x,
        .y = (float)y,
        .w = (float)image->width,
        .h = (float)image->height 
    };
    
    SDL_RenderTexture(renderer, image->texture, nullptr, &dstRect);
}
