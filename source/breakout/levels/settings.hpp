#pragma once

#include <memory>

#include "breakout/levels/level.hpp"
#include "breakout/menu.hpp"

namespace breakout
{
    class Settings final : public Level
    {
    public:
        std::shared_ptr<engine::Image> background {nullptr};
        std::shared_ptr<engine::Image> volumeText {nullptr};
        std::shared_ptr<engine::Image> volume {nullptr};
        std::shared_ptr<engine::Image> carretRight {nullptr};
        std::shared_ptr<engine::Image> carretLeft {nullptr};
        std::shared_ptr<engine::Image> acceptSettings {nullptr};
        std::shared_ptr<engine::Image> settings {nullptr};
        int fullVolumeSize {0};
        float volumeStep = 0.05f;

        void BeginPlay() override;
        void Draw() override;

        void KeyDown(const uint32_t key) override;
    };
}
