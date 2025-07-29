#pragma once

namespace engine
{
    class GameState
    {
    public:
        GameState() = default;
        ~GameState() = default;
        
        GameState(const GameState& other) = delete;
        GameState &operator=(const GameState&) = delete;
        GameState(GameState&& other) = delete;
        GameState& operator=(GameState&& other) = delete;
    };
}
