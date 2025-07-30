#include "engine.hpp"

#include <chrono>
#include <SDL3/SDL_events.h>

#include "audio.hpp"
#include "fileio.hpp"
#include "game.hpp"
#include "window.hpp"
#include "rendering/image.hpp"
#include "rendering/renderer.hpp"

engine::Engine Engine;

void engine::Engine::Initialize()
{
    window = std::make_unique<engine::Window>(400, 300, "engine");
    audio = std::make_unique<engine::Audio>();
    renderer = std::make_unique<engine::Renderer>();
    fileIO = std::make_unique<engine::FileIO>();
    
    StartGame<Game>();
}

void engine::Engine::Run()
{
    auto previousTime = std::chrono::high_resolution_clock::now();
    SDL_Event event {};

    while (running)
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        const float elapsed = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - previousTime).count());
        deltaTime = elapsed / 1000000.0f; // time in seconds
        previousTime = currentTime;

        game->Tick(deltaTime);
        
        while (SDL_PollEvent(&event))
        {
            // Exit engine on [X] button
            if (event.type == SDL_EVENT_QUIT)
            {
                Shutdown();
            }

            PassInputEventsToGame(event);
        }

        // Trigger key every frame while held down
        for (const auto key : pressedKeys)
        {
            game->KeyPressed(key);
        }
        
        // Trigger button every frame while held down
        for (const auto button : pressedButtons)
        {
            game->ButtonPressed(button);
        } 
        
        renderer->BeginFrame();
        game->Draw();
        renderer->EndFrame();
    }
}

void engine::Engine::Cleanup()
{
    if (running)
    {
        LogEngine->Warn("Engine not exited gracefully.");
    }
    
    game->Shutdown();
    SDL_Quit();
}

void engine::Engine::Shutdown()
{
    running = false;
}

void engine::Engine::PassInputEventsToGame(const SDL_Event& event)
{
    if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat)
    {
        const uint32_t key = event.key.key;
        pressedKeys.push_back(key);
        game->KeyDown(key);
    }
            
    if (event.type == SDL_EVENT_KEY_UP && !event.key.repeat)
    {
        const uint32_t key = event.key.key;
        std::erase(pressedKeys, key);
        game->KeyUp(key);
    }
            
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        const uint32_t button = event.button.button;
        pressedButtons.push_back(button);
        game->ButtonDown(button);
    }
            
    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        const uint32_t button = event.button.button;
        std::erase(pressedButtons, button);
        game->ButtonUp(button);
    }

    if (event.type == SDL_EVENT_MOUSE_WHEEL)
    {
        game->MouseWheel(event.wheel.y);
    }

    if (event.type == SDL_EVENT_MOUSE_MOTION)
    {
        game->MouseMove(
            static_cast<uint32_t>(event.motion.x),
            static_cast<uint32_t>(event.motion.y)
        );
    }
}
