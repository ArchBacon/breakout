#pragma once

#include <memory>

#include "breakout/level.hpp"


namespace breakout
{
    class MainMenu final : public Level
    {
        std::shared_ptr<engine::Image> background {nullptr};
        
    public:
        void BeginPlay() override;
        void Draw() override;
    };
}
