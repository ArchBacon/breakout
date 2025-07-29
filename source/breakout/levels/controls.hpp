#pragma once
#include <memory>

#include "breakout/level.hpp"
#include "breakout/menu.hpp"

namespace breakout
{
    class Controls final : public Level
    {
    public:
        std::shared_ptr<engine::Image> background {nullptr};
        std::shared_ptr<engine::Image> controls {nullptr};
        std::shared_ptr<engine::Image> acceptSettings {nullptr};
        Menu menu {};

        void BeginPlay() override;
        void Draw() override;

        void KeyDown(const uint32_t key) override;
    };
}
