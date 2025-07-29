#pragma once

#include <memory>
#include <vector>
#include <SDL3/SDL_events.h>

#include "game.hpp"
#include "window.hpp"

namespace breakout
{
    class Breakout;
}

namespace engine
{
    class Window;
    class Audio;
    class Renderer;
    class FileIO;
    class Game;

    class Engine
    {
        std::unique_ptr<Window> window {nullptr};
        std::unique_ptr<Audio> audio {nullptr};
        std::unique_ptr<Renderer> renderer {nullptr};
        std::unique_ptr<FileIO> fileIO {nullptr};
        
        std::unique_ptr<Game> game {nullptr};
        
        bool running {true};

        std::vector<uint32_t> pressedKeys {};
        std::vector<uint32_t> pressedButtons {};

        float deltaTime {0.0f};

    public:
        void Initialize();
        void Run();
        void Shutdown();

        template <class T>
        void StartGame();

        [[nodiscard]] Window& Window() const { return *window; }
        [[nodiscard]] Audio& Audio() const { return *audio; }
        [[nodiscard]] Renderer& Renderer() const { return *renderer; }
        [[nodiscard]] FileIO& FileIO() const { return *fileIO; }
        
        [[nodiscard]] float DeltaTime() const { return deltaTime; }

    private:
        void PassInputEventsToGame(const SDL_Event& event);
    };

    template <class T>
    void Engine::StartGame()
    {
        if (game)
        {
            game->Shutdown();
        }
        
        game = std::make_unique<T>();
        game->BeginPlay();
    }
}

extern engine::Engine Engine;
