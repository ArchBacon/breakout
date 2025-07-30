#pragma once

#include <memory>
#include <vector>
#include <SDL3/SDL_events.h>
#include <concepts>

#include "game.hpp"
#include "gamestate.hpp"
#include "window.hpp"
#include "rendering/font.hpp"

template<typename T>
concept GameStateType = std::derived_from<T, engine::GameState>;

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
        std::unordered_map<std::string, std::unique_ptr<Font>> fonts {};
        
        std::unique_ptr<Window> window {nullptr};
        std::unique_ptr<Audio> audio {nullptr};
        std::unique_ptr<Renderer> renderer {nullptr};
        std::unique_ptr<FileIO> fileIO {nullptr};
        std::unique_ptr<GameState> gameState {nullptr};
        std::unique_ptr<Game> game {nullptr};
        
        bool running {true};

        std::vector<uint32_t> pressedKeys {};
        std::vector<uint32_t> pressedButtons {};

        float deltaTime {0.0f};

    public:
        void Initialize();
        void Run();
        void Cleanup();

        template <class T>
        void StartGame();

        [[nodiscard]] Window& Window() const { return *window; }
        [[nodiscard]] Audio& Audio() const { return *audio; }
        [[nodiscard]] Renderer& Renderer() const { return *renderer; }
        [[nodiscard]] FileIO& FileIO() const { return *fileIO; }
        
        template <GameStateType T>
        [[nodiscard]] T& GameState() const { return *static_cast<T*>(gameState.get()); }
        
        template <GameStateType T>
        void SetGameState();

        template <class T>
        [[nodiscard]] Font* GetFont();
        
        [[nodiscard]] float DeltaTime() const { return deltaTime; }
        void Shutdown();

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

    template <GameStateType T>
    void Engine::SetGameState()
    {
        gameState = std::make_unique<T>();
    }

    template <class T>
    Font* Engine::GetFont()
    {
        const std::string id = typeid(T).name();

        // Return or create and return
        if (fonts.contains(id))
        {
            return fonts[id].get();
        }

        fonts[id] = std::make_unique<T>();
        return fonts[id].get();
    }
}

extern engine::Engine Engine;
