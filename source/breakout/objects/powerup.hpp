#pragma once

#include <memory>
#include <random>

#include "breakout/collision.hpp"
#include "breakout/fonts/power_font.hpp"
#include "core/engine.hpp"
#include "core/types.hpp"
#include "rendering/image.hpp"
#include "utils/timer.hpp"

namespace breakout
{
    struct Paddle;
}

namespace breakout
{
    struct Player;
    struct Ball;
    
    template<typename T>
    concept FontType = std::derived_from<T, PowerFont>;

    enum class PowerUpType
    {
        None,
        ExtraLife,
        Slow,
        // Break,
        Enlarge,
        MAX__,
    };
    
    struct PowerUp
    {
        std::vector<std::shared_ptr<engine::Image>> sprites {};
        std::shared_ptr<engine::Image> shadow {
            Engine.Renderer().CreateImage("assets/images/power_shadow.png"),
        };
        float2 location = {0.0f, 0.0f};
        float2 direction = {0.0f, 1.0f}; // Default direction is straight down
        float speed {100.f};
        float duration {0.0f};
        float animationSpeed {8.0f}; // Frames per second
        engine::Timer animationTimer {};
        engine::Timer powerTimer {};
        int animationIndex {0};
        uint8_t score {250};
        PowerUpType type {PowerUpType::None};
        
    protected:
        std::function<void()> internalBeginCallback {};
        std::function<void()> internalEndCallback {};
    public:
        std::function<void()> onBeginCallback {};
        std::function<void()> onEndCallback {};

    public:
        bool active {false};
        bool consumed {false};
        Bounds bounds {};

        explicit PowerUp();
        virtual ~PowerUp();
        
        void OnBegin();
        void OnEnd();
        void Update(float deltaTime);
        void Animate();

        template <FontType T>
        void PopulateSprites();

        /**
         * @param chance chance to roll a powerup that is not `None` between 0.0f and 1.0f
         */
        static PowerUpType Roll(const float chance)
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    
            if (dist(gen) <= chance)
            {
                // Random powerup type (excluding None and MAX__)
                static std::uniform_int_distribution<int> powerupDist(1, static_cast<int>(PowerUpType::MAX__) - 1);
                return static_cast<PowerUpType>(powerupDist(gen));
            }
    
            return PowerUpType::None;
        }
    };

    template <FontType T>
    void PowerUp::PopulateSprites()
    {
        sprites.clear();
        sprites.reserve(8);
        for (int i = 0; i < 8; i++) {
            sprites.push_back(Engine.GetFont<T>()->CreateText(std::to_string(i)));
        }
    }
    
    // Gain an extra life
    struct PowerExtraLife : PowerUp
    {
        PowerExtraLife(Player& player);
    };
    
    // Slow speed of balls
    struct PowerSlow : PowerUp
    {
        PowerSlow(std::vector<Ball>& balls);
    };
    
    // Split balls into 3
    // struct PowerBreak : PowerUp
    // {
    //     PowerBreak();
    // };
    
    // Paddle becomes longer
    struct PowerEnlarge : PowerUp
    {
        int ogWidth {0};
        PowerEnlarge(Paddle& paddle);
    };
}
