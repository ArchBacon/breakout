#pragma once

#include <memory>

#include "breakout/level.hpp"
#include "breakout/menu.hpp"

namespace breakout
{
    class MainMenu final : public Level
    {
        std::shared_ptr<engine::Image> background {nullptr};
        Menu menu {};

    public:
        void BeginPlay() override;
        void Draw() override;

        void KeyDown(const uint32_t key) override;
    };
}
