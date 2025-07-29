#pragma once

#include <memory>

#include "breakout/level.hpp"
#include "breakout/menu.hpp"

namespace breakout
{
    class Gameplay final : public Level
    {
        std::shared_ptr<engine::Image> background {nullptr};

    public:
        void BeginPlay() override;
        void Draw() override;
    };
}
